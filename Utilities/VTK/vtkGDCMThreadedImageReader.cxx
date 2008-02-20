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
#include "vtkGDCMThreadedImageReader.h"

#include "vtkObjectFactory.h"
#include "vtkImageData.h"
#include "vtkMedicalImageProperties.h"
#include "vtkStringArray.h"
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDemandDrivenPipeline.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#endif /* (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 ) */

#include "gdcmImageReader.h"
#include "gdcmDataElement.h"
#include "gdcmByteValue.h"
#include "gdcmSwapper.h"

#include <sstream>

#include <pthread.h>
#include <unistd.h> // sysconf

vtkCxxRevisionMacro(vtkGDCMThreadedImageReader, "$Revision: 1.1 $");
vtkStandardNewMacro(vtkGDCMThreadedImageReader);

vtkGDCMThreadedImageReader::vtkGDCMThreadedImageReader()
{
  this->Shift = 0.;
  this->Scale = 1.;
}

vtkGDCMThreadedImageReader::~vtkGDCMThreadedImageReader()
{
}

#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
#else /* (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 ) */
void vtkGDCMThreadedImageReader::ExecuteInformation()
{
  std::cerr << "ExecuteInformation" << std::endl;
  if (this->FileNames->GetNumberOfValues() > 0)
    {
    this->DataExtent[4] = 0;
    this->DataExtent[5] = this->FileNames->GetNumberOfValues() - 1; 
    }

  // This reader only implement case where image is flipped upside down
  if( !this->FileLowerLeft )
    {
    vtkErrorMacro( "You need to set the FileLowerLeft flag to On" );
    }
  this->vtkImageReader2::ExecuteInformation();
}

void vtkGDCMThreadedImageReader::ExecuteData(vtkDataObject *output)
{
  std::cerr << "ExecuteData" << std::endl;
  vtkImageData *data = this->AllocateOutputData(output);
  //data->GetPointData()->GetScalars()->SetName("GDCM");
  RequestDataCompat();
}
#endif /* (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 ) */

//----------------------------------------------------------------------------
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
int vtkGDCMThreadedImageReader::RequestInformation(vtkInformation *request,
                                      vtkInformationVector **inputVector,
                                      vtkInformationVector *outputVector)
{
  // Some information need to have been set outside (user specified)
  //assert( this->GetOutput(0)->GetNumberOfPoints() != 0 );
  // For now only handles series:
  if( !this->FileNames && !this->FileName )
    {
    return 0;
    }

  if( this->DataExtent[4] != 0 
   || this->DataExtent[5] != this->FileNames->GetNumberOfValues() - 1 )
    {
    vtkErrorMacro( "Problem with extent" );
    return 0;
    }

  int numvol = 1;
  this->SetNumberOfOutputPorts(numvol);
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
    outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), DataExtent, 6);
    //outInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(), DataExtent, 6);

    outInfo->Set(vtkDataObject::SPACING(), this->DataSpacing, 3);
    outInfo->Set(vtkDataObject::ORIGIN(), this->DataOrigin, 3);

    vtkDataObject::SetPointDataActiveScalarInfo(outInfo, this->DataScalarType, this->NumberOfScalarComponents);
    }

  // Ok let's fill in the 'extra' info:
  //FillMedicalImageInformation(reader);

  // This reader only implement case where image is flipped upside down
  if( !this->FileLowerLeft )
    {
    vtkErrorMacro( "You need to set the FileLowerLeft flag to On" );
    return 0;
    }

  return 1;
}
#endif /*(VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )*/

struct threadparams
{
  const char **filenames;             // array of filenames thread will process (order is important!)
  unsigned int nfiles;                // number of files the thread will process
  char *scalarpointer;                // start of the image buffer affected to the thread
  unsigned long len;                  // This is not required but useful to check if files are consistant
  unsigned long totalfiles;           // total number of files being processed (needed to compute progress)
  pthread_mutex_t lock;               // critial section for updating progress
  vtkGDCMThreadedImageReader *reader; // needed for calling updateprogress
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

    gdcm::ImageReader reader;
    reader.SetFileName( filename );
    if( !reader.Read() )
      {
      return 0;
      }

    // Update progress
    // We are done reading one file, let's shout it loud:
    pthread_mutex_lock(&params->lock);
    // critical section
    const double progress = params->reader->GetProgress(); // other thread might have updated it also...
    params->reader->UpdateProgress( progress + progressdelta );
    pthread_mutex_unlock(&params->lock);

    const gdcm::Image &image = reader.GetImage();
    unsigned long len = image.GetBufferLength();
    // When not applying a transform:
    // len -> sizeof stored image
    // params->len sizeof world value image (after transform)
    if( params->reader->GetShift() == 1 && params->reader->GetScale() == 0 )
      assert( len == params->len ); // that would be very bad 

    char * pointer = params->scalarpointer;
    //memcpy(pointer + file*len, tempimage, len);
    char *tempimage = pointer + file*params->len;
    image.GetBuffer(tempimage);
    if( params->reader->GetShift() != 1 || params->reader->GetScale() != 0 )
      {
      const double shift = params->reader->GetShift();
      const int shift_int = (int)shift;
      const double scale = params->reader->GetScale();
      const int scale_int = (int)scale;
      if( scale == 1 && shift == (double)shift_int )
        {
        unsigned short *out = (unsigned short*)(pointer + file * params->len);
        unsigned short *pout = out;
        for( ; pout != out + params->len / sizeof(unsigned short); ++pout )
          {
          *pout = *pout + (short)shift;
          }
        }
      else if ( shift == 0 && scale != (double)scale_int )
        {
        // FIXME TODO tempimage stored the DICOM image at the beginning of the buffer,
        // we could avoid duplicating the memory by iterating over the buffer starting
        // from the end and filling out the target buffer by the end...
        // scale is a float !!
        char * duplicate = new char[len];
        memcpy(duplicate,tempimage,len);
        const unsigned short *in = (unsigned short*)duplicate;
        const unsigned short *pin = in;
        float *out = (float*)(pointer + file * params->len);
        float *pout = out;
        for( ; pout != out + params->len / sizeof(float); ++pout )
          {
          *pout = *pin * (float)scale; // scale is a double, but DICOM specify 32bits for floating point value
          ++pin;
          }
        assert( pin == in + len / sizeof(unsigned short) );
        delete[] duplicate;
        }
      else
        {
        assert( 0 && "Not Implemented" );
        }
      }
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
void vtkGDCMThreadedImageReader::ReadFiles(unsigned int nfiles, const char *filenames[])
{
  vtkImageData *output = this->GetOutput(0);
  assert( output->GetNumberOfPoints() % nfiles == 0 );
  const unsigned long len = output->GetNumberOfPoints() * output->GetScalarSize() / nfiles;
  char * scalarpointer = static_cast<char*>(output->GetScalarPointer());

  const unsigned int nprocs = sysconf( _SC_NPROCESSORS_ONLN );
  const unsigned int nthreads = std::min( nprocs, nfiles );
  threadparams params[nthreads];

  pthread_mutex_t lock;
  pthread_mutex_init(&lock, NULL);

  pthread_t *pthread = new pthread_t[nthreads];

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
    params[thread].len = len;
    params[thread].totalfiles = nfiles;
    params[thread].lock = lock;
    params[thread].reader = this;
    // start thread:
    int res = pthread_create( &pthread[thread], NULL, ReadFilesThread, &params[thread]);
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
 
#if 0
  // For some reason writing down the file is painfully slow...
  vtkStructuredPointsWriter *writer = vtkStructuredPointsWriter::New();
  writer->SetInput( output );
  writer->SetFileName( "/tmp/threadgdcm.vtk" );
  writer->SetFileTypeToBinary();
  //writer->Write();
  writer->Delete();
#endif

  //output->Print( std::cout );
}

//----------------------------------------------------------------------------
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
int vtkGDCMThreadedImageReader::RequestData(vtkInformation *vtkNotUsed(request),
                                vtkInformationVector **vtkNotUsed(inputVector),
                                vtkInformationVector *outputVector)
{
  //std::cerr << "vtkGDCMThreadedImageReader::RequestData Start" << std::endl;
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

  //std::cerr << "vtkGDCMThreadedImageReader::RequestData End" << std::endl;
  return 1;
}
#endif /*(VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )*/

void vtkGDCMThreadedImageReader::RequestDataCompat()
{
  int *dext = this->GetDataExtent();
  if( this->FileNames )
    {
    // Make sure that each file is single slice
    assert( dext[5] - dext[4] == this->FileNames->GetNumberOfValues() - 1 );
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

//----------------------------------------------------------------------------
void vtkGDCMThreadedImageReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}

