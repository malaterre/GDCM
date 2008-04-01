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
 * \ see also See typical init.d (debian) gdcmreadahead that starts the service
 *
 * LOG file is: /var/log/daemon.log
 * LOCK file is: /tmp/gdcmreadahead.lock
 * LIST file is: /tmp/gdcmreadahead.list
 *
 * The list file is typically the output of a `find /path -type f`
 * no comment are allowed in this file, full path only to file
 * no check is done to make sure the file is a dicom file
 *
 * the working (running) directory of this daemon is /tmp
 *
 * NOTE: On WIN32 disk caching is done automatically and can
 * be made more agressive using FILE_FLAG_SEQUENTIAL
 */
#define _GNU_SOURCE /* This is required to get the declaration of readahead */

#include <fcntl.h> /* readahead */
#include <assert.h>
#include <stdio.h>
#include <limits.h> /* PATH_MAX */
#include <stdlib.h> /* exit */
#include <signal.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <sched.h> /* sched_yield */
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#undef _GNU_SOURCE


/*
 * http://www.cca.me.uk/cms.php?act=showarticle&article_id=6
 * http://www.enderunix.org/documents/eng/daemon.php
 *
UNIX Daemon Server Programming Sample Program
Levent Karakas <levent at mektup dot at> May 2001

To compile:	cc -o exampled examped.c
To run:		./exampled
To test daemon:	ps -ef|grep exampled (or ps -aux on BSD systems)
To test log:	tail -f /tmp/exampled.log
To test signal:	kill -HUP `cat /tmp/exampled.lock`
To terminate:	kill `cat /tmp/exampled.lock`
*/


#define RUNNING_DIR	"/tmp"
#define LOCK_FILE	"/var/run/gdcmreadahead.pid"
#define LIST_FILE	"/tmp/gdcmreadahead.list"

void shutdown(int ex)
{
  int ret;
  syslog(LOG_DEBUG,"process quitting.");
  /* now is a good time to remove the lock file, just before we exit: */
  ret = unlink(LOCK_FILE);
  if( ret != 0 )
    {
    syslog(LOG_ERR,"could not remove lock file: %s",  LOCK_FILE );
    ex = 1; /* mark it as error */
    }
  /* close the system logging connection */
  closelog();
  /* bye. */
  exit(ex);
}

void signal_handler(int sig)
{
  switch(sig) {
  case SIGHUP:
    syslog(LOG_INFO,"hangup signal caught");
    break;
  case SIGTERM:
    syslog(LOG_INFO,"terminate signal caught");
    shutdown(0);
    break;
  default:
    syslog(LOG_DEBUG,"%s : %d", "Unknown signal caught", sig);
    break;
  }
}

void daemonize()
{
  pid_t pg;
  int i,lfp;
  char str[10];
  if( getppid() == 1 ) return; /* already a daemon */
  i = fork();
  if ( i < 0 )
    {
    syslog(LOG_ERR,"Fork error: %s", strerror(errno) );
    exit(1); /* fork error */
    }
  if ( i > 0 )
    {
    exit(0); /* parent exits */
    }
  /* child (daemon) continues */
  pg = setsid(); /* obtain a new process group */
  if( pg == -1 )
    {
    syslog(LOG_ERR,"setsid failed");
    }
  for (i=getdtablesize();i>=0;--i)
    {
    int c = close(i); /* close all descriptors */
    if( c != 0 )
      {
      /* most of the descriptor are not open anyway, do not print
         too much garbage in the syslog then: */
      /*syslog(LOG_ERR,"close failed on descriptor: %d", i); */
      }
    }
  i=open("/dev/null",O_RDWR); 
  if( i == -1 ) /* stdin */
    {
    syslog(LOG_ERR,"open error for stdin: %s", strerror(errno) );
    }
  if( dup(i) == -1 ) /* stdout */
    {
    syslog(LOG_ERR,"open error for stdout: %s", strerror(errno) );
    }
  if( dup(i) == -1 )
    {
    syslog(LOG_ERR,"open error for stderr: %s", strerror(errno) );
    }
  umask(027); /* set newly created file permissions */
  if( chdir(RUNNING_DIR) != 0 ) /* change running directory */
    {
    syslog(LOG_ERR,"could not chdir into: %s", RUNNING_DIR );
    }
  lfp=open(LOCK_FILE,O_RDWR|O_CREAT,0640);
  if( lfp < 0 )
    {
    syslog(LOG_ERR,"could not open: %s", LOCK_FILE );
    exit(1);
    }
  if (lockf(lfp,F_TLOCK,0)<0) 
    {
    syslog(LOG_ERR,"could not lockf: %s, error was: %s ", LOCK_FILE, strerror(errno) );
    exit(0); /* can not lock */
    }
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

void startup()
{
  /* first thing we should check for the obvious: did we cleanly exit last time: */
  struct stat buf;
  int st = stat(LOCK_FILE, &buf);
  if( st == 0 )
    {
    fprintf( stderr, "Lock file: %s is still present\n", LOCK_FILE);
    exit(1);
    }

  /* start up the system logging connection */
  openlog("gdcmreadahead",LOG_PID,LOG_DAEMON);
  syslog(LOG_DEBUG,"process starting up.");
  daemonize();
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
 *
 * http://kerneltrap.org/node/6642
 * -> 
 * That would involve using posix_fadvise(POSIX_FADV_RANDOM) to disable kernel
 * readahead and then using posix_fadvise(POSIX_FADV_WILLNEED) to launch
 * application-level readahead.
 *
 *  #include <fcntl.h>
 * 
 * int posix_fadvise(int fd, off_t offset, off_t len, int advice);
 * 
 */


int ReadAhead(const char * path)
{
  struct stat info;
  int success;
  int readonly = 1;
  int flags = (readonly ? O_RDONLY : O_RDWR);
  int handle = open(path, flags, S_IRWXU);
  off_t size;
  ssize_t ret;
  int error;
  int res;
  if( handle == -1 )
    {
    syslog(LOG_WARNING, "Could not open: %s", path);
    return 1;
    }
  success = fstat(handle, &info);
  if( success != 0 )
    {
    syslog(LOG_WARNING, "Could not fstat: %s", path);
    return 1;
    }
  size = info.st_size;
  /* get rid of any weird non-file thingy */
  if(S_ISDIR(info.st_mode) || S_ISCHR(info.st_mode) || 
    S_ISBLK(info.st_mode) || S_ISFIFO(info.st_mode) ||
    S_ISSOCK(info.st_mode))
    {
    /* we are done ! */
    close(handle);
    return 0;
    }
  /* Only deal with file */
  assert( S_ISREG(info.st_mode) );

  ret = readahead(handle, 0, size);
  if( ret == -1 )
    {
    syslog(LOG_ERR, "readahead failed for %s", path );
    return 1;
    }

  error = close(handle);
  if( error != 0 ) 
    {
    syslog(LOG_ERR, "close failed for %s", path );
    return 1;
    }

  /* be nice to other processes now */
  res = sched_yield();
  if( res != 0 ) 
    {
    syslog(LOG_ERR, "sched_yield failed" );
    return 1;
    }

  return 0;
}

void ProcessFiles(const char *path)
{
  int ret;
  char file[PATH_MAX];
  FILE *fp = fopen(path, "r");
  assert( fp ); /* previous call made sure this file existed on the system... */
  while (fgets(file, PATH_MAX, fp))  
    {
    size_t size = strlen(file);
    assert( size < PATH_MAX );
    /* get rid of easy cases: */
    if( file[size-1] != '\n' )
      {
      /* actually this case can also happen when the file was truncated, basically
       * when we are reading the file while another process overwrite it
       */
      syslog(LOG_INFO, "string length too long for a UNIX path: %s", file );
      }
    else if( file[0] != '/' )
      {
      syslog(LOG_INFO, "full path only: %s", file );
      }
    else
      {
      /* Ok let's try to readahead this file: */
      file[size-1] = 0; /* remove the \n */
      /*syslog(LOG_DEBUG, "processing file: %s", file );*/
      ret = ReadAhead(file);
      (void)ret;
      }
    }
  ret = fclose(fp);
  if( ret != 0 )
    {
    syslog(LOG_ERR, "could not close: %s", path );
    }
  syslog(LOG_INFO, "The whole file was processed: %s", path );
}

/* #define LIST_FILE	"gdcmreadahead.list" */
void WatchFile(time_t *reference)
{
  const char *listfile = LIST_FILE;
  struct stat buf;
  int ret = stat(listfile, &buf);
  time_t lastmodification;
  if( ret != 0 )
    {
    syslog(LOG_DEBUG, "the list file does not exist !");
    return;
    }
  lastmodification = buf.st_mtime;
  if( lastmodification > *reference )
    {
    syslog(LOG_INFO, "file list was modified let's readahead: %ld > %ld", lastmodification, *reference);
    ProcessFiles(listfile);
    /* done let's store the new reference time: */
    *reference = lastmodification;
    }
}

int main(int argc, char *argv[])
{
  time_t start;
  (void)argc; (void)argv;
  startup();
  start = 0; /* make sure to always read the list file at least once */
  while(1) 
    {
    /*syslog(LOG_DEBUG,"   still running...");*/
    WatchFile( &start );
    sleep(1); /* run every 1 second */
    }

  return 0;
}

