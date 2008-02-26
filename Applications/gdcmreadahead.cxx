#include "gdcmSystem.h"
#include "gdcmDirectory.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>

/*
 * http://www.linuxinsight.com/adaptive_readahead_benchmark.html
 *
 * http://www.togaware.com/linux/survivor/CD_DVD_Drives.html
 * http://www.4p8.com/eric.brasseur/linux_optimization.html
 * http://portal.itauth.com/2007/11/20/howto-linux-double-your-disk-read-performance-single-command
 * http://preload.cvs.sourceforge.net/preload/preload/src/
 *
 * sync && echo 3 > /proc/sys/vm/drop_caches
 */
// fstat


int DoOperation(std::string const & path)
{
  bool readonly = true;
  int flags = (readonly ? O_RDONLY : O_RDWR);
  int handle = ::open(path.c_str(), flags, S_IRWXU);
  if( handle == -1 )
    {
    std::cerr << "Could not open: " << path << std::endl;
    std::cerr << strerror(errno) << std::endl;
    return 1;
    }
  struct stat info;
  bool success = ::fstat(handle, &info) != -1;
  if( !success )
    {
    std::cerr << "Could not fstat: " << path << std::endl;
    return 1;
    }
  off_t size = info.st_size;
  if(S_ISDIR(info.st_mode) || S_ISCHR(info.st_mode) || 
    S_ISBLK(info.st_mode) || S_ISFIFO(info.st_mode) ||
    S_ISSOCK(info.st_mode))
    {
    // we are done !
    return 0;
    }
  // Only deal with file
  assert( S_ISREG(info.st_mode) );

  ssize_t ret = ::readahead(handle, 0, size);
  if( ret == -1 )
    {
    std::cerr << "readahead failed for " << path << std::endl;
    return 1;
    }

  //std::cout << "done with " << path << "\n";
  bool error = ::close(handle) != 0;
  if( error ) return 1;

  return 0;
}

int main(int argc, char *argv[])
{
  if( argc < 2 )
    {
    return 1;
    }
  std::string filename = argv[1];

  int res = 0;
  if( gdcm::System::FileIsDirectory( filename.c_str() ) )
    {
    gdcm::Directory d;
    d.Load(filename, true);
    gdcm::Directory::FilenamesType const &filenames = d.GetFilenames();
    for( gdcm::Directory::FilenamesType::const_iterator it = filenames.begin(); it != filenames.end(); ++it )
      {
      res += DoOperation(*it);
      }
    }
  else
    {
    res += DoOperation(filename);
    }



  return res;
}
