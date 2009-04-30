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

namespace vtkgdcm
{
  // using vtkgdcmswig;
  public class vtkGDCMImageReader : vtkMedicalImageReader2
    {
    vtkgdcmswig.vtkGDCMImageReader inter;
    public vtkGDCMImageReader() {
      inter = vtkgdcmswig.vtkGDCMImageReader.New();
      }
    public override void SetFileName(string filename) {
      inter.SetFileName( filename );
      }
    }

  public class vtkGDCMImageWriter : vtkImageWriter
    {
    vtkgdcmswig.vtkGDCMImageWriter inter;
    public vtkGDCMImageWriter() {
      inter = vtkgdcmswig.vtkGDCMImageWriter.New();
      }
    public override void SetFileName(string filename) {
      inter.SetFileName( filename );
      }
    public void SetInput(vtkDataObject obj) {
      inter.SetInput( obj );
      }
    public override void Write() {
      inter.Write();
      }
    }
}

