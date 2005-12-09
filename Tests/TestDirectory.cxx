// generated file
#include "gdcmDataImages.h"

#include "gdcmDirectory.h"

// Check if name can be found in gdcmData
bool IsFileInData(std::string const name, const char * const list[])
{
  int j = 0;
  const char *filename;
  while( (filename = list[j]) )
    {
    if( name == filename ) 
      {
      //std::cout << "Found: " << name << std::endl;
      break;
      }
    ++j;
    }
  return filename != NULL;
}

int TestDirectory(int argc, char *argv[])
{
  gdcm::Directory::FilenameType dir = GDCM_DATA_ROOT;
  if( argc == 2 )
    {
    // Ok user gaves us a directory to test
    dir = argv[1];
    }
  if( ! gdcm::Directory::IsDirectory( dir ) )
    return 1;

  gdcm::Directory d;
  unsigned int i, nfiles = d.Load( dir, false);
  d.Print();

  if( ! gdcm::Directory::IsDirectory( d.GetToplevel() ) )
    return 1;
  // Check that all directories are indeed directory
  const gdcm::Directory::FilenamesType &directories = d.GetDirectories();
  unsigned int ndirs = directories.size();
  for(i=0; i<ndirs; ++i)
    {
    const std::string directory = directories[i];
    if( ! gdcm::Directory::IsDirectory( directory ) )
      {
      std::cerr << "Directory: " << directory << " is not a directory" << std::endl;
      return 1;
      }
    }

  const gdcm::Directory::FilenamesType &filenames = d.GetFilenames();
  //std::cout << "NFiles= " << nfiles << std::endl;
  if (nfiles != filenames.size() )
    return 1;

  for(i=0; i<nfiles; ++i)
    {
    const gdcm::Directory::FilenameType filename = filenames[i];
    std::string extension;
    gdcm::Directory::FilenameType::size_type dot_pos = filename.rfind(".");
    if(dot_pos != gdcm::Directory::FilenameType::npos)
      {
      extension = filename.substr(dot_pos);
      }
    if( extension == ".dcm"
      || extension == ".acr" )
      {
      //std::cout << i  << ": " << filename << std::endl;
      if( !IsFileInData(filename, gdcmDataImages)
      && !IsFileInData(filename, gdcmBlackListDataImages) )
        {
        std::cerr << "Could not find file: " << filename << std::endl;
        break;
        }
      }
    else
      {
      std::cerr << "Discarding: " << filename << 
        " because ext is: " << extension << std::endl;
      }
    }

  return i != nfiles;
}
