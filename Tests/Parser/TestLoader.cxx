#include "gdcmLoader.h"

int TestLoader(int argc, char *argv[])
{
  std::string filename = argv[1];
  gdcm::Loader Is;
  Is.SetFileName(filename);
  Is.Open();
  Is.Initialize();
  Is.Update();

  Is.Close();

  return 0;
}
