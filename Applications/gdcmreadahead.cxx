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
/*
 * OS Specific: Linux (>2.4.11)
 * gdcmreadahead is a daemon that runs in the background and prepare file
 * stored on disk to be cached by the system (readahead system call)
 */
#include "gdcmSystem.h"
#include "gdcmDirectory.h"
#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>

/*
UNIX Daemon Server Programming Sample Program
Levent Karakas <levent at mektup dot at> May 2001

To compile:	cc -o exampled examped.c
To run:		./exampled
To test daemon:	ps -ef|grep exampled (or ps -aux on BSD systems)
To test log:	tail -f /tmp/exampled.log
To test signal:	kill -HUP `cat /tmp/exampled.lock`
To terminate:	kill `cat /tmp/exampled.lock`
*/

#include <stdio.h>
#include <stdlib.h> /* exit */
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


#define RUNNING_DIR	"/tmp"
#define LOCK_FILE	"gdcmreadahead.lock"
#define LOG_FILE	"gdcmreadahead.log"
#define LIST_FILE	"gdcmreadahead.list"

void log_message(const char *filename,const char *message)
{
  FILE *logfile;
  logfile=fopen(filename,"a");
  if(!logfile) return;
  fprintf(logfile,"%s\n",message);
  fclose(logfile);
}

void signal_handler(int sig)
{
  std::ostringstream os;
  switch(sig) {
  case SIGHUP:
    log_message(LOG_FILE,"hangup signal catched");
    break;
  case SIGTERM:
    log_message(LOG_FILE,"terminate signal catched");
    exit(0);
    break;
  default:
    os << "Unknown signal caught: " << sig;
    log_message(LOG_FILE, os.str().c_str() );
    break;
  }
}

void daemonize()
{
  int i,lfp;
  char str[10];
  if(getppid()==1) return; /* already a daemon */
  i=fork();
  if (i<0) exit(1); /* fork error */
  if (i>0) exit(0); /* parent exits */
  /* child (daemon) continues */
  setsid(); /* obtain a new process group */
  for (i=getdtablesize();i>=0;--i) close(i); /* close all descriptors */
  i=open("/dev/null",O_RDWR); dup(i); dup(i); /* handle standart I/O */
  umask(027); /* set newly created file permissions */
  chdir(RUNNING_DIR); /* change running directory */
  lfp=open(LOCK_FILE,O_RDWR|O_CREAT,0640);
  if (lfp<0) exit(1); /* can not open */
  if (lockf(lfp,F_TLOCK,0)<0) exit(0); /* can not lock */
  /* first instance continues */
  sprintf(str,"%d\n",getpid());
  write(lfp,str,strlen(str)); /* record pid to lockfile */
  signal(SIGCHLD,SIG_IGN); /* ignore child */
  signal(SIGTSTP,SIG_IGN); /* ignore tty signals */
  signal(SIGTTOU,SIG_IGN);
  signal(SIGTTIN,SIG_IGN);
  signal(SIGHUP,signal_handler); /* catch hangup signal */
  signal(SIGTERM,signal_handler); /* catch kill signal */
}

/*
 * http://www.linuxinsight.com/adaptive_readahead_benchmark.html
 *
 * http://www.togaware.com/linux/survivor/CD_DVD_Drives.html
 * http://www.4p8.com/eric.brasseur/linux_optimization.html
 * http://portal.itauth.com/2007/11/20/howto-linux-double-your-disk-read-performance-single-command
 * http://preload.cvs.sourceforge.net/preload/preload/src/
 *
 * The following command clears anything in the disk cache:
 * sync && echo 3 > /proc/sys/vm/drop_caches
 */


int ReadAhead(std::string const & path)
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

  // be nice to other processes now 
  int res = sched_yield();
  if( res != 0 ) return 1;

  return 0;
}

void ProcessFile(const char *path)
{
  std::string filename = path;

  int res = 0;
  if( gdcm::System::FileIsDirectory( filename.c_str() ) )
    {
    gdcm::Directory d;
    // recursively look for any file
    d.Load(filename, true);
    gdcm::Directory::FilenamesType const &filenames = d.GetFilenames();
    for( gdcm::Directory::FilenamesType::const_iterator it = filenames.begin(); it != filenames.end(); ++it )
      {
      res += ReadAhead(*it);
      }
    }
  else
    {
    res += ReadAhead(filename);
    }

}

void ProcessFiles(const char *path)
{
  std::ifstream is(path);
  const size_t pathmax = PATH_MAX;
  std::string file;
  while( std::getline(is, file) )
    {
    std::ostringstream os;
    // get rid of easy cases:
    if( file.size() > PATH_MAX )
      {
      os << "ERROR: garbage string, its length is too long for a UNIX path:";
      os << file;
      log_message(LOG_FILE, os.str().c_str() );
      }
    else if( file[0] != '/' )
      {
      os << "ERROR: full path only:";
      os << file;
      log_message(LOG_FILE, os.str().c_str() );
      }
    else
      {
      // Ok let's try to readahead this file:
      int ret = ReadAhead(file);
      os << "DEBUG: processing file:";
      os << file;
      os << "\nreturn value was: " << ret;
      log_message(LOG_FILE, os.str().c_str() );
      }
    file.clear();
    }
}

// #define LIST_FILE	"gdcmreadahead.list"
void WatchFile(time_t &reference)
{
  const char *listfile = LIST_FILE;
  struct stat buf;
  int ret = stat(listfile, &buf);
  if( ret != 0 )
    {
    log_message(LOG_FILE,"ERROR: the list file do not exist !");
    return;
    }
  time_t lastmodification = buf.st_mtime;
  if( lastmodification > reference )
    {
    std::ostringstream os;
    os << "REREAD: file list was modified let's readahead: ";
    os << lastmodification << " > " << reference;
    log_message(LOG_FILE, os.str().c_str());
    ProcessFiles(listfile);
    // done let's store the new reference time:
    reference = lastmodification;
    }
  else
    {
    // uncomment me to check if daemon is still running (visual check)
    //log_message(LOG_FILE, "NOTHING DONE");
    }
}

int main(int argc, char *argv[])
{
  (void)argc; (void)argv;
  daemonize();
  time_t start = 0; // make sure to always read the list file
  while(1) 
    {
    //log_message(LOG_FILE,"running");
    WatchFile( start );
    sleep(10); /* run every 10 seconds */
    }

  return 0;
}

