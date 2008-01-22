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
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDemandDrivenPipeline.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkMedicalImageProperties.h"
#include "vtkStringArray.h"

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
}

vtkGDCMThreadedImageReader::~vtkGDCMThreadedImageReader()
{
}

void vtkGDCMThreadedImageReader::ExecuteInformation()
{
  std::cerr << "ExecuteInformation" << std::endl;
}

void vtkGDCMThreadedImageReader::ExecuteData(vtkDataObject *output)
{
  std::cerr << "ExecuteData" << std::endl;
}

int vtkGDCMThreadedImageReader::CanReadFile(const char* fname)
{
  gdcm::ImageReader reader;
  reader.SetFileName( fname );
  if( reader.Read() )
    {
    return 0;
    }
  // Problem reading:
  return 3;
}

//----------------------------------------------------------------------------
int vtkGDCMThreadedImageReader::ProcessRequest(vtkInformation* request,
                                 vtkInformationVector** inputVector,
                                 vtkInformationVector* outputVector)
{
  // generate the data
  if(request->Has(vtkDemandDrivenPipeline::REQUEST_DATA()))
    {
    return this->RequestData(request, inputVector, outputVector);
    }

  // execute information
  if(request->Has(vtkDemandDrivenPipeline::REQUEST_INFORMATION()))
    {
    return this->RequestInformation(request, inputVector, outputVector);
    }

  return this->Superclass::ProcessRequest(request, inputVector, outputVector);
}

//----------------------------------------------------------------------------
int vtkGDCMThreadedImageReader::RequestInformation(vtkInformation *request,
                                      vtkInformationVector **inputVector,
                                      vtkInformationVector *outputVector)
{
#if 0
  // Let's read the first file :
  const char *filename;
  if( this->FileName )
    {
    filename = this->FileName;
    }
  else
    {
    assert( this->FileNames && this->FileNames->GetNumberOfValues() >= 1 );
    filename = this->FileNames->GetValue( 0 ).c_str();
    }
  gdcm::ImageReader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    return 0;
    }
  const gdcm::Image &image = reader.GetImage();
  const unsigned int *dims = image.GetDimensions();

  // Set the Extents.
  assert( image.GetNumberOfDimensions() >= 2 );
  this->DataExtent[0] = 0;
  this->DataExtent[1] = dims[0] - 1;
  this->DataExtent[2] = 0;
  this->DataExtent[3] = dims[1] - 1;
  if( image.GetNumberOfDimensions() == 2 )
    {
    // This is just so much painfull to deal with DICOM / VTK
    // they simply assume that number of file is equal to the dimension
    // of the last axe (see vtkImageReader2::SetFileNames )
    if ( this->FileNames && this->FileNames->GetNumberOfValues() > 1 )
      {
      this->DataExtent[4] = 0;
      //this->DataExtent[5] = this->FileNames->GetNumberOfValues() - 1;
      }
    else
      {
      this->DataExtent[4] = 0;
      this->DataExtent[5] = 0;
      }
    }
  else
    {
    assert( image.GetNumberOfDimensions() == 3 );
    this->FileDimensionality = 3;
    this->DataExtent[4] = 0;
    this->DataExtent[5] = dims[2] - 1;
    }
  //this->DataSpacing[0] = 1.;
  //this->DataSpacing[1] = -1.;
  //this->DataSpacing[2] = 1.;

  gdcm::PixelType pixeltype = image.GetPixelType();
  switch( pixeltype )
    {
  case gdcm::PixelType::INT8:
    this->DataScalarType = VTK_SIGNED_CHAR;
    break;
  case gdcm::PixelType::UINT8:
    this->DataScalarType = VTK_UNSIGNED_CHAR;
    break;
  case gdcm::PixelType::INT12:
    abort();
    this->DataScalarType = VTK_SHORT;
    break;
  case gdcm::PixelType::UINT12:
    abort();
    this->DataScalarType = VTK_UNSIGNED_SHORT;
    break;
  case gdcm::PixelType::INT16:
    this->DataScalarType = VTK_SHORT;
    break;
  case gdcm::PixelType::UINT16:
    this->DataScalarType = VTK_UNSIGNED_SHORT;
    break;
  default:
    ;
    }

  this->NumberOfScalarComponents = pixeltype.GetSamplesPerPixel();
  if( image.GetPhotometricInterpretation() == 
    gdcm::PhotometricInterpretation::PALETTE_COLOR )
    {
    assert( this->NumberOfScalarComponents == 1 );
    this->NumberOfScalarComponents = 3;
    }

#endif
  // Some information need to have been set outside (user specified)
  //assert( this->GetOutput(0)->GetNumberOfPoints() != 0 );

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
    outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),
      DataExtent[0], DataExtent[1], DataExtent[2], DataExtent[3], DataExtent[4], DataExtent[5]);

    vtkDataObject::SetPointDataActiveScalarInfo(outInfo, this->DataScalarType, this->NumberOfScalarComponents);
    outInfo->Set(vtkDataObject::SPACING(), this->DataSpacing, 3);

    double origin[3] = {};
    outInfo->Set(vtkDataObject::ORIGIN(), origin, 3);
    }

  // Ok let's fill in the 'extra' info:
  //FillMedicalImageInformation(reader);

  // For now only handles series:
  if( !this->FileNames )
    {
    return 0;
    }

  return 1;
}

struct threadparams
{
  const char **filenames; // array of filenames thread will process
  unsigned int nfiles; // number of files the thread will process
  char *scalarpointer; // start of the image buffer affected to the thread
  unsigned long len; // This is not required but useful to check if files are consistant
  unsigned long totalfiles; // total number of files being processed (needed to compute progress)
  pthread_mutex_t lock; // critial section for updating progress
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
    assert( len == params->len ); // that would be very bad 

    char * pointer = params->scalarpointer;
    //memcpy(pointer + file*len, tempimage, len);
    char *tempimage = pointer + file*len;
    image.GetBuffer(tempimage);
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

  int *dext = this->GetDataExtent();
  assert( this->FileNames );
  assert( dext[5] - dext[4] == this->FileNames->GetNumberOfValues() - 1 );
  const unsigned int nfiles = this->FileNames->GetNumberOfValues();
  const char **filenames = new const char* [ nfiles ];
  for(unsigned int i = 0; i < nfiles; ++i)
    {
    filenames[i] = this->FileNames->GetValue( i ).c_str();
    //std::cerr << filenames[i] << std::endl;
    }
  ReadFiles(nfiles, filenames);
  delete[] filenames;

  //std::cerr << "vtkGDCMThreadedImageReader::RequestData End" << std::endl;
  return 1;
}

//----------------------------------------------------------------------------
void vtkGDCMThreadedImageReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}

