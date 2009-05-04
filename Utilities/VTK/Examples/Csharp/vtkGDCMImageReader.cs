/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

using Kitware.VTK;
using System;

namespace vtkgdcm
{
  // using vtkgdcmswig;
  public class vtkGDCMImageReader : vtkMedicalImageReader2
    {
    vtkgdcmswig.vtkGDCMImageReader inter;
    public vtkGDCMImageReader() {
      inter = vtkgdcmswig.vtkGDCMImageReader.New();
      }
    public void MySetFileName(string filename) {
      SetFileName( filename );
      inter.SetFileName( filename );
      }
    public void MyUpdate() {
      Update();
      inter.SetOutput( GetOutput() );
      inter.Update();
      }
    //public vtkDataObject GetOutput() {
    //vtkImageData data = null;
    //uint mteStatus = 0;
    //uint maxValue = uint.MaxValue;
    //uint rawRefCount = 0;
    //IntPtr rawCppThis = vtkImageAlgorithm.vtkImageAlgorithm_GetOutput_06(base.GetCppThis(), ref mteStatus, ref maxValue, ref rawRefCount);

    //  //return inter.GetOutput();
    //  }
    }

  public class vtkGDCMImageWriter /*: vtkImageWriter*/
    {
    vtkgdcmswig.vtkGDCMImageWriter inter;
    public vtkGDCMImageWriter() {
      inter = vtkgdcmswig.vtkGDCMImageWriter.New();
      }
    public void SetFileName(string filename) {
      inter.SetFileName( filename );
      }
    public void SetInput(vtkImageData obj) {
      inter.SetInput( obj );
      }
    //public void SetInput(vtkDataObject obj) {
    //  inter.SetInput( obj );
    //  }
    public void Write() {
      inter.Write();
      }
    }
}

