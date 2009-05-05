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
using vtkgdcmswig;
using Kitware.VTK;

/*
 */
public class HelloActiviz
{
void ConnectSWIGToActiviz(Kitware.VTK.vtkImageExport imgin, Kitware.VTK.vtkImageImport imgout)
{
  imgout.SetUpdateInformationCallback(imgin.GetUpdateInformationCallback());
  imgout.SetPipelineModifiedCallback(imgin.GetPipelineModifiedCallback());
  imgout.SetWholeExtentCallback(imgin.GetWholeExtentCallback());
  imgout.SetSpacingCallback(imgin.GetSpacingCallback());
  imgout.SetOriginCallback(imgin.GetOriginCallback());
  imgout.SetScalarTypeCallback(imgin.GetScalarTypeCallback());
  imgout.SetNumberOfComponentsCallback(imgin.GetNumberOfComponentsCallback());
  imgout.SetPropagateUpdateExtentCallback(imgin.GetPropagateUpdateExtentCallback());
  imgout.SetUpdateDataCallback(imgin.GetUpdateDataCallback());
  imgout.SetDataExtentCallback(imgin.GetDataExtentCallback());
  imgout.SetBufferPointerCallback(imgin.GetBufferPointerCallback());
  imgout.SetCallbackUserData(imgin.GetCallbackUserData());
}


  public static int Main(string[] args)
    {
    string filename = args[0];
    vtkGDCMImageReader reader = vtkGDCMImageReader.New();
    reader.SetFileName( filename );
    //reader.Update();


    return 0;
    }
}

