/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkGDCMThreadedImageReader2.h"

#include "vtkObjectFactory.h"
#include "vtkImageData.h"
#include "vtkStringArray.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDemandDrivenPipeline.h"
#include "vtkStreamingDemandDrivenPipeline.h"

//FIXME
#include "vtkImageIterator.h"
#include "vtkImageProgressIterator.h"
#include "vtkDoubleArray.h"
// END FIXME

#include "gdcmImageReader.h"

#include <assert.h>

vtkCxxRevisionMacro(vtkGDCMThreadedImageReader2, "$Revision: 1.1 $")
vtkStandardNewMacro(vtkGDCMThreadedImageReader2)

// Output Ports are as follow:
// #0: The image/volume (root PixelData element)
// #1: (if present): the Icon Image (0088,0200)
// #2-xx: (if present): the Overlay (60xx,3000)

#define IconImagePortNumber 1
#define OverlayPortNumber   2

vtkGDCMThreadedImageReader2::vtkGDCMThreadedImageReader2()
{
  this->SetNumberOfInputPorts(0);
  this->FileLowerLeft = 1;
  this->FileNames = NULL;
  this->FileName = NULL;
  LoadIconImage = 0;
  memset(DataExtent,0,6*sizeof(*DataExtent));
  DataSpacing[0] = DataSpacing[1] = DataSpacing[2] = 1;
  LoadOverlays = 0;
  NumberOfOverlays = 0;
  DataScalarType = VTK_VOID;
}

vtkGDCMThreadedImageReader2::~vtkGDCMThreadedImageReader2()
{
  if( this->FileNames )
    {
    this->FileNames->Delete();
    }
  this->SetFileName(NULL);
}

#if 0
struct threadparams
{
  const char **filenames;             // array of filenames thread will process (order is important!)
  unsigned int nfiles;                // number of files the thread will process
  char *scalarpointer;                // start of the image buffer affected to the thread
  unsigned char *overlayscalarpointer;
  unsigned long len;                  // This is not required but useful to check if files are consistant
  unsigned long overlaylen;
  unsigned long totalfiles;           // total number of files being processed (needed to compute progress)
  pthread_mutex_t lock;               // critial section for updating progress
  vtkGDCMThreadedImageReader2 *reader; // needed for calling updateprogress
};

void *ReadFilesThread(void *voidparams)
{
  threadparams *params = static_cast<threadparams *> (voidparams);
  assert( params );

  const unsigned int nfiles = params->nfiles;
  assert( nfiles ); //
  // pre compute progress delta for one file:
  assert( params->totalfiles );
  const double progressdelta = 1. / params->totalfiles;
  for(unsigned int file = 0; file < nfiles; ++file)
    {
    const char *filename = params->filenames[file];
    //std::cerr << filename << std::endl;

    }

  return voidparams;
}

void ShowFilenames(const threadparams &params)
{
  std::cout << "start" << std::endl;
  for(unsigned int i = 0; i < params.nfiles; ++i)
    {
    const char *filename = params.filenames[i];
    std::cout << filename << std::endl;
    }
  std::cout << "end" << std::endl;
}

//----------------------------------------------------------------------------
void vtkGDCMThreadedImageReader2::ReadFiles(unsigned int nfiles, const char *filenames[])
{
  // image data:
  vtkImageData *output = this->GetOutput(0);
  assert( output->GetNumberOfPoints() % nfiles == 0 );
  const unsigned long len = output->GetNumberOfPoints() * output->GetScalarSize() / nfiles;
  const unsigned long overlaylen = output->GetNumberOfPoints() / nfiles;
  char * scalarpointer = static_cast<char*>(output->GetScalarPointer());
  // overlay data:
  unsigned char * overlayscalarpointer = 0;
  if( this->LoadOverlays )
    {
    vtkImageData *overlayoutput = this->GetOutput(OverlayPortNumber);
    overlayoutput->SetScalarTypeToUnsignedChar();
    overlayoutput->AllocateScalars();
    overlayscalarpointer = static_cast<unsigned char*>(overlayoutput->GetScalarPointer());
    }

  const unsigned int nprocs = sysconf( _SC_NPROCESSORS_ONLN );
  const unsigned int nthreads = std::min( nprocs, nfiles );
  threadparams *params = new threadparams[nthreads];

  pthread_mutex_t lock;
  pthread_mutex_init(&lock, NULL);

  pthread_t *pthread = new pthread_t[nthreads];
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
  this->Debug = 0;

  // There is nfiles, and nThreads
  assert( nfiles >= nthreads );
  const unsigned int partition = nfiles / nthreads;
  assert( partition );
  for (unsigned int thread=0; thread < nthreads; ++thread)
    {
    params[thread].filenames = filenames + thread * partition;
    params[thread].nfiles = partition;
    if( thread == nthreads - 1 )
      {
      // There is slightly more files to process in this thread:
      params[thread].nfiles += nfiles % nthreads;
      }
    assert( thread * partition < nfiles );
    //ShowFilenames(params[thread]);
    params[thread].scalarpointer = scalarpointer + thread * partition * len;
    params[thread].overlayscalarpointer = overlayscalarpointer + thread * partition * len;
    params[thread].len = len;
    params[thread].overlaylen = overlaylen;
    params[thread].totalfiles = nfiles;
    params[thread].lock = lock;
    assert( this->Debug == 0 );
    params[thread].reader = this;
    assert( params[thread].reader->Debug == 0 );
    // start thread:
    //int res = pthread_create( &pthread[thread], NULL, ReadFilesThread, &params[thread]);
    int res = pthread_create( &pthread[thread], &attr, ReadFilesThread, &params[thread]);
    if( res )
      {
      std::cerr << "Unable to start a new thread, pthread returned: " << res << std::endl;
      abort();
      }
    }
// DEBUG
  unsigned int total = 0;
  for (unsigned int thread=0; thread < nthreads; ++thread)
    {
    total += params[thread].nfiles;
    }
  assert( total == nfiles );
// END DEBUG

  for (unsigned int thread=0;thread<nthreads;thread++)
    {
    pthread_join( pthread[thread], NULL);
    }
  delete[] pthread;

  pthread_mutex_destroy(&lock);
  delete[] params;
 
/*
  // For some reason writing down the file is painfully slow...
  vtkStructuredPointsWriter *writer = vtkStructuredPointsWriter::New();
  writer->SetInput( output );
  writer->SetFileName( "/tmp/threadgdcm.vtk" );
  writer->SetFileTypeToBinary();
  //writer->Write();
  writer->Delete();
*/

  //output->Print( std::cout );
}

//----------------------------------------------------------------------------
int vtkGDCMThreadedImageReader2::RequestData(vtkInformation *vtkNotUsed(request),
                                vtkInformationVector **vtkNotUsed(inputVector),
                                vtkInformationVector *outputVector)
{
  (void)outputVector;
  //std::cerr << "vtkGDCMThreadedImageReader2::RequestData Start" << std::endl;
  //this->UpdateProgress(0.2);

  // Make sure the output dimension is OK, and allocate its scalars

  for(int i = 0; i < this->GetNumberOfOutputPorts(); ++i)
    {
    // Copy/paste from vtkImageAlgorithm::AllocateScalars. Cf. "this needs to be fixed -Ken"
    vtkStreamingDemandDrivenPipeline *sddp = 
      vtkStreamingDemandDrivenPipeline::SafeDownCast(this->GetExecutive());
    if (sddp)
      {
      int extent[6];
      sddp->GetOutputInformation(i)->Get(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(),extent);
      this->GetOutput(i)->SetExtent(extent);
      }
    this->GetOutput(i)->AllocateScalars();
    }

  RequestDataCompat();

  //std::cerr << "vtkGDCMThreadedImageReader2::RequestData End" << std::endl;
  return 1;
}

void vtkGDCMThreadedImageReader2::RequestDataCompat()
{
  int *dext = this->GetDataExtent();
  if( this->FileNames )
    {
    // Make sure that each file is single slice
    assert( dext[5] - dext[4] == this->FileNames->GetNumberOfValues() - 1 ); (void)dext;
    const unsigned int nfiles = this->FileNames->GetNumberOfValues();
    const char **filenames = new const char* [ nfiles ];
    for(unsigned int i = 0; i < nfiles; ++i)
      {
      filenames[i] = this->FileNames->GetValue( i );
      //std::cerr << filenames[i] << std::endl;
      }
    ReadFiles(nfiles, filenames);
    delete[] filenames;
    }
  else if( this->FileName )
    {
    // File can be a volume
    const char *filename = this->FileName;
    ReadFiles(1, &filename);
    }
  else
    {
    // Impossible case since ExecuteInformation would have failed earlier...
    assert( 0 && "Impossible happen" );
    }

}
#endif


//----------------------------------------------------------------------------
// Description:
// This templated function executes the filter for any type of data.
template <class T>
void vtkImageWeightedSumExecute(vtkGDCMThreadedImageReader2 *self,
                          vtkImageData **inDatas, int numFiles, vtkImageData *outData,
                          int outExt[6], int id, T*)
{
  printf("outExt:%d,%d,%d,%d,%d,%d\n",
    outExt[0], outExt[1], outExt[2], outExt[3], outExt[4], outExt[5]);
  for( int i = outExt[4]; i <= outExt[5]; ++i )
    {
    const char *filename = self->GetFileNames()->GetValue( i );
    //ReadOneFile( filename );
    //outData->GetPointData()->GetScalars()->SetName("GDCMImage");


    if( id == 0 )
      self->UpdateProgress(float(i)/float(outExt[5]-outExt[4]+1));


    //char * pointer = static_cast<char*>(outData->GetScalarPointerForExtent(outExt));
    char * pointer = static_cast<char*>(outData->GetScalarPointer(0,0,i));
printf("pointer:%i\n",*pointer);
    gdcm::ImageReader reader;
    reader.SetFileName( filename );
    if( !reader.Read() )
      {
      abort();
      }
    const gdcm::Image &image = reader.GetImage();
    unsigned long len = image.GetBufferLength();
    image.GetBuffer(pointer);
    }

}

int vtkGDCMThreadedImageReader2::RequestInformation (
  vtkInformation * request,
  vtkInformationVector** inputVector,
  vtkInformationVector *outputVector)
{
  (void)request;(void)inputVector;(void)outputVector;
  // Some information need to have been set outside (user specified)
  //assert( this->GetOutput(0)->GetNumberOfPoints() != 0 );
  // For now only handles series:
  if( !this->FileNames && !this->FileName )
    {
    return 0;
    }

  // This reader only implement case where image is flipped upside down
  if( !this->FileLowerLeft )
    {
    vtkErrorMacro( "You need to set the FileLowerLeft flag to On" );
    return 0;
    }

  if( this->FileNames )
    {
    int zmin = 0;
    int zmax = 0;
    zmax = this->FileNames->GetNumberOfValues() - 1;
    if( this->DataExtent[4] != zmin || this->DataExtent[5] != zmax )
      {
      vtkErrorMacro( "Problem with extent" );
      return 0;
      }
    }
  // Cannot deduce anything else otherwise...

  int numvol = 1;
  if( this->LoadIconImage )
    {
    numvol = 2;
    return 0;
    }
  if( this->LoadOverlays )
    {
    this->NumberOfOverlays = 1;
    numvol = 3;
    }
  assert( numvol == 1 || numvol == 3 );
  this->SetNumberOfOutputPorts(numvol);
  assert( this->DataScalarType != VTK_VOID );
  // For each output:
  for(int i = 0; i < numvol; ++i)
    {
    // Allocate !
    if( !this->GetOutput(i) )
      {
      vtkImageData *img = vtkImageData::New();
      this->GetExecutive()->SetOutputData(i, img );
      img->Delete();
      }
    vtkInformation *outInfo = outputVector->GetInformationObject(i);
    switch(i)
      {
    // root Pixel Data
    case 0:
      outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), this->DataExtent, 6);
      //outInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(), this->DataExtent, 6);
      outInfo->Set(vtkDataObject::SPACING(), this->DataSpacing, 3);
      outInfo->Set(vtkDataObject::ORIGIN(), this->DataOrigin, 3);
      vtkDataObject::SetPointDataActiveScalarInfo(outInfo, this->DataScalarType, this->NumberOfScalarComponents);
      break;
    // Icon Image
    case IconImagePortNumber:
      outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), this->IconImageDataExtent, 6);
      vtkDataObject::SetPointDataActiveScalarInfo(outInfo, VTK_UNSIGNED_CHAR, 1);
      break;
    // Overlays:
    //case OverlayPortNumber:
    default:
      outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), 
        this->DataExtent[0], this->DataExtent[1], 
        this->DataExtent[2], this->DataExtent[3],
        0,0 );
      vtkDataObject::SetPointDataActiveScalarInfo(outInfo, VTK_UNSIGNED_CHAR, 1);
      break;
      }

    }

  // Ok let's fill in the 'extra' info:
  //FillMedicalImageInformation(reader);

  return 1;
}

// For streaming and threads.  Splits output update extent into num pieces.
// This method needs to be called num times.  Results must not overlap for
// consistent starting extent.  Subclass can override this method.
// This method returns the number of peices resulting from a successful split.
// This can be from 1 to "total".  
// If 1 is returned, the extent cannot be split.
int vtkGDCMThreadedImageReader2::SplitExtent(int splitExt[6], int startExt[6], 
                             int num, int total)
{
  memcpy(splitExt, startExt, 6 * sizeof(*splitExt));

  vtkDebugMacro("SplitExtent: ( " << startExt[0] << ", " << startExt[1] << ", "
                << startExt[2] << ", " << startExt[3] << ", "
                << startExt[4] << ", " << startExt[5] << "), " 
                << num << " of " << total);

  // We should only split along the Z direction (only in the case of multiple files...)
  int splitAxis = 2;
  int min = startExt[4];
  int max = startExt[5];
  if( min >= max )
    {
    assert ( min == 0 );
    assert ( max == 0 );
    return 1;
    }

  // else normal SplitExtent as copied from vtkThreadedImageAlgorithm

  // determine the actual number of pieces that will be generated
  int range = max - min + 1;
  int valuesPerThread = static_cast<int>(ceil(range/static_cast<double>(total)));
  int maxThreadIdUsed = static_cast<int>(ceil(range/static_cast<double>(valuesPerThread))) - 1;
  if (num < maxThreadIdUsed)
    {
    splitExt[splitAxis*2] = splitExt[splitAxis*2] + num*valuesPerThread;
    splitExt[splitAxis*2+1] = splitExt[splitAxis*2] + valuesPerThread - 1;
    }
  if (num == maxThreadIdUsed)
    {
    splitExt[splitAxis*2] = splitExt[splitAxis*2] + num*valuesPerThread;
    }
  
  vtkDebugMacro("  Split Piece: ( " <<splitExt[0]<< ", " <<splitExt[1]<< ", "
                << splitExt[2] << ", " << splitExt[3] << ", "
                << splitExt[4] << ", " << splitExt[5] << ")");

  return maxThreadIdUsed + 1;
}

void vtkGDCMThreadedImageReader2::ThreadedRequestData (
  vtkInformation * vtkNotUsed( request ), 
  vtkInformationVector** vtkNotUsed( inputVector ),
  vtkInformationVector * vtkNotUsed( outputVector ),
  vtkImageData ***inData, 
  vtkImageData **outData,
  int outExt[6], int id)
{
//  printf("ThreadedRequestData::outExt:%d,%d,%d,%d,%d,%d\n",
//    outExt[0], outExt[1], outExt[2], outExt[3], outExt[4], outExt[5]);

  assert( this->DataScalarType != VTK_VOID );

  //switch (inData[0][0]->GetScalarType())
  switch (this->GetDataScalarType())
    {
    vtkTemplateMacro(
      vtkImageWeightedSumExecute(this , 0 /*inData[0]*/, 3,
        outData[0], outExt, id, static_cast<VTK_TT *>(0))
      );
    default:
      vtkErrorMacro(<< "Execute: Unknown ScalarType");
      return;
    }
  //float progress = this->GetProgress();
  //int i = outExt[4];
  //int numFiles = 1920;
  //this->UpdateProgress(float(i)/float(numFiles));

}

void vtkGDCMThreadedImageReader2::SetFileNames(vtkStringArray *filenames)
{
  if (filenames == this->FileNames)
    {
    return;
    }
  if (this->FileNames)
    {
    this->FileNames->Delete();
    this->FileNames = 0;
    }
  if (filenames)
    {
    this->FileNames = filenames;
    this->FileNames->Register(this);
    if (this->FileNames->GetNumberOfValues() > 0)
      {
      this->DataExtent[4] = 0;
      this->DataExtent[5] = this->FileNames->GetNumberOfValues() - 1;
      }
    //if (this->FilePrefix)
    //  {
    //  delete [] this->FilePrefix;
    //  this->FilePrefix = NULL;
    //  }
    if (this->FileName)
      {
      delete [] this->FileName;
      this->FileName = NULL;
      }
    }

  this->Modified();
}

//----------------------------------------------------------------------------
//int vtkGDCMThreadedImageReader2::FillInputPortInformation(int i, vtkInformation* info)
//{
//  info->Set(vtkAlgorithm::INPUT_IS_REPEATABLE(), 1);
//  return this->Superclass::FillInputPortInformation(i,info);
//}


//----------------------------------------------------------------------------
void vtkGDCMThreadedImageReader2::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}

