// generated file
#include "gdcmDataImages.h"

#include "gdcmDirectory.h"
#include "gdcmFileSeeker.h"
#include "gdcmDict.h"

void TestPrintUID(const std::string &filename)
{
  std::cerr << "UID of file: " << filename << std::endl;
  gdcm::FileSeeker f;
  f.SetFileName(filename);
  f.Open();
  f.Initialize();
  const gdcm::Tag siUID(0x0020,0x000d);  // [Study Instance UID]
  static const gdcm::Dict d; /// \TODO FIXME this thing is friggin slow
  const gdcm::DictEntry &de = d.GetDictEntry(siUID);
  if ( ! f.FindTag( siUID )  )
    {
    std::cerr << "This file does not contains: " << de.GetName() << std::endl;
    }
  else
    {
    std::cout << "This file contains: " << de.GetName() << std::endl;
    const char *uid = f.GetTagAsRaw( siUID );
    std::cout << "Value is: "  << uid << std::endl;
    }
  f.Close();
}

int TestAllPrintUID(int argc, char *argv[])
{
  std::cerr << std::endl;
  if( argc == 2 )
    {
    const char *filename = argv[1];
    TestPrintUID(filename);
    return 0;
    }

  // else
  int i = 0;
  const char *filename;
  while( (filename = gdcmDataImages[i]) )
    {
    TestPrintUID( filename );
    ++i;
    }

  return 0;
}

int TestAllPrintUID_old(int argc, char *argv[])
{
  gdcm::Directory::FilenameType dir = GDCM_DATA_ROOT;
  if( argc == 2 )
    {
    dir = argv[1];
    }
  if( ! gdcm::Directory::IsDirectory( dir ) )
    return 1;

  gdcm::Directory d;
  d.Load( dir );
  const gdcm::Directory::FilenamesType &filenames = d.GetFilenames();
  gdcm::Directory::FilenamesType::const_iterator it = filenames.begin();
  for(; it != filenames.end(); ++it)
    {
    std::string extension;
    const gdcm::Directory::FilenameType filename = *it;
    gdcm::Directory::FilenameType::size_type dot_pos = filename.rfind(".");
    if(dot_pos != gdcm::Directory::FilenameType::npos)
      {
      extension = filename.substr(dot_pos);
      }
    if( extension == ".dcm" )
      {
      std::cerr << "Seekering: " << filename << std::endl;
      gdcm::FileSeeker f;
      f.SetFileName(filename);
      f.Open();
      f.Initialize();
      f.Close();
      }
    }

  return 0;
}
