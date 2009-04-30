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
}

