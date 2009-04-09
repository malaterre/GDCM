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
#include "gdcmSystem.h"
#include "gdcmTrace.h"
#include "gdcmFilename.h"
#include "gdcmException.h"

#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <sys/stat.h>
#include <limits.h> // PATH_MAX

// gettimeofday
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#include <time.h>
#ifdef HAVE_WINSOCK_H
#include <winsock.h>
#endif
#include <stdio.h> // snprintf
#if defined(HAVE_SNPRINTF)
// ok nothing to do
#elif defined(HAVE__SNPRINTF)
#define snprintf _snprintf
#endif
#ifdef __APPLE__
#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFBundle.h>
#include <CoreFoundation/CFURL.h>
#endif // __APPLE__

#if defined(_WIN32) && (defined(_MSC_VER) || defined(__WATCOMC__) ||defined(__BORLANDC__) || defined(__MINGW32__))
#include <io.h>
#include <direct.h>
#define _unlink unlink
#else
//#include <features.h>	// we want GNU extensions
#include <dlfcn.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h> // strncasecmp
#endif 

// TODO: WIN32 replacement for C99 stuff:
// #if defined(_WIN32) || defined(_WIN64)
// #define snprintf _snprintf
// #define vsnprintf _vsnprintf
// #define strcasecmp _stricmp
// #define strncasecmp _strnicmp
// #endif

namespace gdcm
{

#if defined(_WIN32) && (defined(_MSC_VER) || defined(__WATCOMC__) || defined(__BORLANDC__) || defined(__MINGW32__)) 
inline int Mkdir(const char* dir)
{
  return _mkdir(dir);
}
inline int Rmdir(const char* dir)
{
  return _rmdir(dir);
}
inline const char* Getcwd(char* buf, unsigned int len)
{
  const char* ret = _getcwd(buf, len);
  return ret;
}

#else
inline int Mkdir(const char* dir)
{
  return mkdir(dir, 00777);
}
inline int Rmdir(const char* dir)
{
  return rmdir(dir);
}
inline const char* Getcwd(char* buf, unsigned int len)
{
  const char* ret = getcwd(buf, len);
  return ret;
}
#endif

/*
// 1.14 How can I find a process' executable file?
// http://www.faqs.org/faqs/unix-faq/programmer/faq/
static std::string Argv0;

void System::SetArgv0(const char *argv0)
{
  Argv0 = argv0;
//std::cout << "Set:" << Argv0 << std::endl;
}

const char* System::GetArgv0()
{
//std::cout << "Get:" << Argv0 << std::endl;
  return Argv0.c_str();
}
*/

const char * System::GetCWD()
{
  static char buf[2048];
  const char* cwd = Getcwd(buf, 2048);
  return cwd;
/*
  std::string path;
  if ( cwd )
    {
    path = cwd;
    }
  return path;
*/
}

bool System::MakeDirectory(const char *path)
{
  if(System::FileExists(path))
    {
    return true;
    }
  Filename fn(path);
  std::string dir = fn.ToUnixSlashes();

  std::string::size_type pos = dir.find(':');
  if(pos == std::string::npos)
    {
    pos = 0;
    }
  std::string topdir;
  while((pos = dir.find('/', pos)) != std::string::npos)
    {
    topdir = dir.substr(0, pos);
    Mkdir(topdir.c_str());
    pos++;
    }
  if(dir[dir.size()-1] == '/')
    {
    topdir = dir.substr(0, dir.size());
    }
  else
    {
    topdir = dir;
    }
  if(Mkdir(topdir.c_str()) != 0)
    {
    // There is a bug in the Borland Run time library which makes MKDIR
    // return EACCES when it should return EEXISTS
    // if it is some other error besides directory exists
    // then return false
    if( (errno != EEXIST)
#ifdef __BORLANDC__
        && (errno != EACCES)
#endif
      )
      {
      return false;
      }
    }
  return true;
}

// return true if the file exists
bool System::FileExists(const char* filename)
{
#ifdef _MSC_VER
# define access _access
#endif
#ifndef R_OK
# define R_OK 04
#endif
  if ( access(filename, R_OK) != 0 )
    {
    return false;
    }
  else
    {
    //assert( !FileIsDirectory(filename) );
    return true;
    }
}

bool System::FileIsDirectory(const char* name)
{
  struct stat fs;
  if(stat(name, &fs) == 0)
    {
#if _WIN32
    return ((fs.st_mode & _S_IFDIR) != 0);
#else
    return S_ISDIR(fs.st_mode);
#endif
    }
  else
    {
    return false;
    }
}

const char *System::GetLastSystemError()
{
  int e = errno;
  return strerror(e);
}

bool System::GetPermissions(const char* file, unsigned short& mode)
{
  if ( !file )
    {
    return false;
    }

  struct stat st;
  if ( stat(file, &st) < 0 )
    {
    return false;
    }
  mode = st.st_mode;
  return true;
}

bool System::SetPermissions(const char* file, unsigned short mode)
{
  if ( !file )
    {
    return false;
    }
  if ( !System::FileExists(file) )
    {
    return false;
    }
  if ( chmod(file, mode) < 0 )
    {
    return false;
    }

  return true;
}

bool System::RemoveFile(const char* source)
{
#ifdef _WIN32
  unsigned short mode;
  if ( !System::GetPermissions(source, mode) )
    {
    return false;
    }
  /* Win32 unlink is stupid --- it fails if the file is read-only  */
  System::SetPermissions(source, S_IWRITE);
#endif
  bool res = unlink(source) != 0 ? false : true;
#ifdef _WIN32
  if ( !res )
    {
    System::SetPermissions(source, mode);
    }
#endif
  return res;
}

// return size of file; also returns zero if no file exists
size_t System::FileSize(const char* filename)
{
  struct stat fs;
  if (stat(filename, &fs) != 0) 
    {
    return 0;
    }
  else
    {
    return fs.st_size;
    }
}

#if 0
const char *System::GetCurrentDataDirectory()
{
#ifdef _WIN32
  static char path[MAX_PATH];
  gdcm::Filename fn( GetCurrentProcessFileName() );
  if ( !fn.IsEmpty() )
    {
    std::string str = fn.GetPath();
    str += "/../" GDCM_INSTALL_DATA_DIR;
    strcpy(path, str.c_str());
    return path;
    }
#else

  static char path[PATH_MAX];

#ifdef __APPLE__
  Boolean success = false;
  CFURLRef pathURL = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
  if (pathURL != NULL)
    {
    success = CFURLGetFileSystemRepresentation(pathURL, true /*resolveAgainstBase*/, (unsigned char*) path, PATH_MAX);
    CFRelease(pathURL);
    }
  if (success)
    {
    strncat(path, "/" GDCM_INSTALL_DATA_DIR, PATH_MAX);
    return path;
    }
#endif
    
  gdcm::Filename fn( GetCurrentProcessFileName() );
  if ( !fn.IsEmpty() )
    {
    std::string str = fn.GetPath();
    str += "/../" GDCM_INSTALL_DATA_DIR;
    strcpy(path, str.c_str());
    return path;
    }
#endif
  return 0;
}
#endif

/* 
 * TODO:
 * check cygwin
 * check beos : get_next_image_info
 * check solaris
 * check hpux
 * check os2: DosGetInfoBlocks / DosQueryModuleName
 * check macosx : 
 *  ProcessSerialNumber psn = {kNoProcess, kCurrentProcess};
 *  GetProcessInformation -> FSMakeFSSpec
 * ...
 */
const char *System::GetCurrentProcessFileName()
{
#ifdef _WIN32
  static char buf[MAX_PATH];
  if ( ::GetModuleFileName(0, buf, sizeof(buf)) )
    {
    return buf;
    }
#elif defined(__APPLE__)
  static char buf[PATH_MAX];
  Boolean success = false;
  CFURLRef pathURL = CFBundleCopyExecutableURL(CFBundleGetMainBundle());
  if ( pathURL)
    {
    success = CFURLGetFileSystemRepresentation(pathURL, true /*resolveAgainstBase*/, (unsigned char*) buf, PATH_MAX);
    CFRelease(pathURL);
    }
  if (success)
    {
    return buf;
    }
#else
  static char path[PATH_MAX];
  if ( readlink ("/proc/self/exe", path, sizeof(path)) > 0) // Technically 0 is not an error, but that would mean
                                                            // 0 byte were copied ... thus considered it as an error
    {
    return path;
    }
#endif
   return 0;
}

static void where_am_i() {}

const char *System::GetCurrentModuleFileName()
{
#ifdef __USE_GNU
  static char path[PATH_MAX];
  Dl_info info;
  if (dladdr( (void*)&where_am_i, &info ) == 0)
    {
    size_t len = strlen(info.dli_fname);
    if( len >= PATH_MAX ) return 0; // throw error ?
    // else
    strcpy(path,info.dli_fname);
    return path; 
    }
#elif defined(_WIN32)
  // GetModuleFileName works the same on Win32 for library AFAIK
  return System::GetCurrentProcessFileName();
#endif

  return 0;
}

const char *System::GetCurrentResourcesDirectory()
{
#ifdef __APPLE__
  static char path[PATH_MAX];
  Boolean success = false;
  CFURLRef pathURL = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
  if (pathURL != NULL)
    {
    success = CFURLGetFileSystemRepresentation(pathURL, true /*resolveAgainstBase*/, (unsigned char*) path, PATH_MAX);
    CFRelease(pathURL);
    }
  if (success)
    {
    strncat(path, "/" GDCM_INSTALL_DATA_DIR, PATH_MAX);
    return path;
    }
#endif
  // Is there such beast on *any* other system but APPLE ?
  return 0;
}

/**
 * \brief Encode the mac address on a fixed length string of 15 characters.
 * we save space this way.
 */
inline int getlastdigit(unsigned char *data, unsigned long size)
{
  int extended, carry = 0;
  for(unsigned int i=0;i<size;i++)
    {
    extended = (carry << 8) + data[i];
    data[i] = extended / 10;
    carry = extended % 10;
    }
  return carry;
}

size_t System::EncodeBytes(char *out, const unsigned char *data, int size)
{
  bool zero = false;
  int res;
  std::string sres;
  unsigned char buffer[32];
  unsigned char *addr = buffer;
  memcpy(addr, data, size);
  while(!zero)
    {
    res = getlastdigit(addr, size);
    sres.insert(sres.begin(), '0' + res);
    zero = true;
    for(int i = 0; i < size; ++i)
      {
      zero = zero && (addr[i] == 0);
      }
    }

  //return sres;
  strcpy(out, sres.c_str()); //, sres.size() );
  return sres.size();
}

bool System::GetHardwareAddress(unsigned char addr[6])
{
  int stat = 0; //uuid_get_node_id(addr);
  memset(addr,0,6);
  /*
  // For debugging you need to consider the worse case where hardware addres is max number:
  addr[0] = 255;
  addr[1] = 255;
  addr[2] = 255;
  addr[3] = 255;
  addr[4] = 255;
  addr[5] = 255;
  */
  if (stat == 1) // success
    {
    return true;
    }
  // else
  //gdcmWarningMacro("Problem in finding the MAC Address");
  return false;
}

#if defined(_WIN32) && !defined(HAVE_GETTIMEOFDAY)
#include <stdio.h>
static int gettimeofday(struct timeval *tv, struct timezone *tz)
{
  FILETIME ft;
  const uint64_t c1 = 27111902;
  const uint64_t c2 = 3577643008UL;
  const uint64_t OFFSET = (c1 << 32) + c2;
  uint64_t filetime;
  GetSystemTimeAsFileTime(&ft);

  filetime = ft.dwHighDateTime;
  filetime = filetime << 32;
  filetime += ft.dwLowDateTime;
  filetime -= OFFSET;

  memset(tv,0, sizeof(*tv));
  assert( sizeof(*tv) == sizeof(struct timeval));
  tv->tv_sec = (time_t)(filetime / 10000000); /* seconds since epoch */
  tv->tv_usec = (uint32_t)((filetime % 10000000) / 10);

  return 0;
}
#endif

bool System::ParseDateTime(time_t &timep, const char date[18])
{
  long milliseconds;
  return ParseDateTime(timep, milliseconds, date);
}

#if defined(_MSC_VER)
// http://bugs.python.org/file10704/strftime.diff
// http://social.msdn.microsoft.com/Forums/en-US/vcgeneral/thread/25a654f9-b6b6-490a-8f36-c87483bb36b7/
// http://cvsweb.netbsd.org/bsdweb.cgi/src/lib/libc/time/
/*-
 * Copyright (c) 1997, 1998, 2005, 2008 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code was contributed to The NetBSD Foundation by Klaus Klein.
 * Heavily optimised by David Laight
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

typedef unsigned int uint;
#define TM_YEAR_BASE   1900
#define IsLeapYear(x)   ((x % 4 == 0) && (x % 100 != 0 || x % 400 == 0))

typedef struct {
    const char *abday[7];
    const char *day[7];
    const char *abmon[12];
    const char *mon[12];
    const char *am_pm[2];
    const char *d_t_fmt;
    const char *d_fmt;
    const char *t_fmt;
    const char *t_fmt_ampm;
} _TimeLocale;


/*
 * This is the C locale default.  On Windows, if we wanted to make this
 * localized, we would use GetLocaleInfo to get the correct values.
 * It may be acceptable to do localization of month/day names, as the
 * numerical values would be considered the locale-independent versions.
 */
static const _TimeLocale _DefaultTimeLocale = 
{
    {
	"Sun","Mon","Tue","Wed","Thu","Fri","Sat",
    },
    {
	"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
	"Friday", "Saturday"
    },
    {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    },
    {
	"January", "February", "March", "April", "May", "June", "July",
	"August", "September", "October", "November", "December"
    },
    {
	"AM", "PM"
    },
    "%a %b %d %H:%M:%S %Y",
    "%m/%d/%y",
    "%H:%M:%S",
    "%I:%M:%S %p"
};

static const _TimeLocale *_CurrentTimeLocale = &_DefaultTimeLocale;

#define	_ctloc(x)		(_CurrentTimeLocale->x)

/*
 * We do not implement alternate representations. However, we always
 * check whether a given modifier is allowed for a certain conversion.
 */
#define ALT_E			0x01
#define ALT_O			0x02
#define	LEGAL_ALT(x)		{ if (alt_format & ~(x)) return NULL; }

static char gmt[] = { "GMT" };
static char utc[] = { "UTC" };

static const u_char *conv_num(const unsigned char *, int *, uint, uint);
static const u_char *find_string(const u_char *, int *, const char * const *,
	const char * const *, int);

#ifndef __UNCONST
#define __UNCONST(a)	((char *)(unsigned long)(const char *)(a))
#endif

char *
strptime(const char *buf, const char *fmt, struct tm *tm)
{
	unsigned char c;
	const unsigned char *bp;
	int alt_format, i, split_year = 0, neg, offs;
	const char *new_fmt;

	bp = (const u_char *)buf;

	while (bp != NULL && (c = *fmt++) != '\0') {
		/* Clear `alternate' modifier prior to new conversion. */
		alt_format = 0;
		i = 0;

		/* Eat up white-space. */
		if (isspace(c)) {
			while (isspace(*bp))
				bp++;
			continue;
		}

		if (c != '%')
			goto literal;


again:		switch (c = *fmt++) {
		case '%':	/* "%%" is converted to "%". */
literal:
			if (c != *bp++)
				return NULL;
			LEGAL_ALT(0);
			continue;

		/*
		 * "Alternative" modifiers. Just set the appropriate flag
		 * and start over again.
		 */
		case 'E':	/* "%E?" alternative conversion modifier. */
			LEGAL_ALT(0);
			alt_format |= ALT_E;
			goto again;

		case 'O':	/* "%O?" alternative conversion modifier. */
			LEGAL_ALT(0);
			alt_format |= ALT_O;
			goto again;

		/*
		 * "Complex" conversion rules, implemented through recursion.
		 */
		case 'c':	/* Date and time, using the locale's format. */
			new_fmt = _ctloc(d_t_fmt);
			goto recurse;

		case 'D':	/* The date as "%m/%d/%y". */
			new_fmt = "%m/%d/%y";
			LEGAL_ALT(0);
			goto recurse;

		case 'F':	/* The date as "%Y-%m-%d". */
			new_fmt = "%Y-%m-%d";
			LEGAL_ALT(0);
			goto recurse;

		case 'R':	/* The time as "%H:%M". */
			new_fmt = "%H:%M";
			LEGAL_ALT(0);
			goto recurse;

		case 'r':	/* The time in 12-hour clock representation. */
			new_fmt =_ctloc(t_fmt_ampm);
			LEGAL_ALT(0);
			goto recurse;

		case 'T':	/* The time as "%H:%M:%S". */
			new_fmt = "%H:%M:%S";
			LEGAL_ALT(0);
			goto recurse;

		case 'X':	/* The time, using the locale's format. */
			new_fmt =_ctloc(t_fmt);
			goto recurse;

		case 'x':	/* The date, using the locale's format. */
			new_fmt =_ctloc(d_fmt);
		    recurse:
			bp = (const u_char *)strptime((const char *)bp,
							    new_fmt, tm);
			LEGAL_ALT(ALT_E);
			continue;

		/*
		 * "Elementary" conversion rules.
		 */
		case 'A':	/* The day of week, using the locale's form. */
		case 'a':
			bp = find_string(bp, &tm->tm_wday, _ctloc(day),
					_ctloc(abday), 7);
			LEGAL_ALT(0);
			continue;

		case 'B':	/* The month, using the locale's form. */
		case 'b':
		case 'h':
			bp = find_string(bp, &tm->tm_mon, _ctloc(mon),
					_ctloc(abmon), 12);
			LEGAL_ALT(0);
			continue;

		case 'C':	/* The century number. */
			i = 20;
			bp = conv_num(bp, &i, 0, 99);

			i = i * 100 - TM_YEAR_BASE;
			if (split_year)
				i += tm->tm_year % 100;
			split_year = 1;
			tm->tm_year = i;
			LEGAL_ALT(ALT_E);
			continue;

		case 'd':	/* The day of month. */
		case 'e':
			bp = conv_num(bp, &tm->tm_mday, 1, 31);
			LEGAL_ALT(ALT_O);
			continue;

		case 'k':	/* The hour (24-hour clock representation). */
			LEGAL_ALT(0);
			/* FALLTHROUGH */
		case 'H':
			bp = conv_num(bp, &tm->tm_hour, 0, 23);
			LEGAL_ALT(ALT_O);
			continue;

		case 'l':	/* The hour (12-hour clock representation). */
			LEGAL_ALT(0);
			/* FALLTHROUGH */
		case 'I':
			bp = conv_num(bp, &tm->tm_hour, 1, 12);
			if (tm->tm_hour == 12)
				tm->tm_hour = 0;
			LEGAL_ALT(ALT_O);
			continue;

		case 'j':	/* The day of year. */
			i = 1;
			bp = conv_num(bp, &i, 1, 366);
			tm->tm_yday = i - 1;
			LEGAL_ALT(0);
			continue;

		case 'M':	/* The minute. */
			bp = conv_num(bp, &tm->tm_min, 0, 59);
			LEGAL_ALT(ALT_O);
			continue;

		case 'm':	/* The month. */
			i = 1;
			bp = conv_num(bp, &i, 1, 12);
			tm->tm_mon = i - 1;
			LEGAL_ALT(ALT_O);
			continue;

		case 'p':	/* The locale's equivalent of AM/PM. */
			bp = find_string(bp, &i, _ctloc(am_pm), NULL, 2);
			if (tm->tm_hour > 11)
				return NULL;
			tm->tm_hour += i * 12;
			LEGAL_ALT(0);
			continue;

		case 'S':	/* The seconds. */
			bp = conv_num(bp, &tm->tm_sec, 0, 61);
			LEGAL_ALT(ALT_O);
			continue;

		case 'U':	/* The week of year, beginning on sunday. */
		case 'W':	/* The week of year, beginning on monday. */
			/*
			 * XXX This is bogus, as we can not assume any valid
			 * information present in the tm structure at this
			 * point to calculate a real value, so just check the
			 * range for now.
			 */
			 bp = conv_num(bp, &i, 0, 53);
			 LEGAL_ALT(ALT_O);
			 continue;

		case 'w':	/* The day of week, beginning on sunday. */
			bp = conv_num(bp, &tm->tm_wday, 0, 6);
			LEGAL_ALT(ALT_O);
			continue;

		case 'u':	/* The day of week, monday = 1. */
			bp = conv_num(bp, &i, 1, 7);
			tm->tm_wday = i % 7;
			LEGAL_ALT(ALT_O);
			continue;

		case 'g':	/* The year corresponding to the ISO week
				 * number but without the century.
				 */
			bp = conv_num(bp, &i, 0, 99);
			continue;

		case 'G':	/* The year corresponding to the ISO week
				 * number with century.
				 */
			do
				bp++;
			while (isdigit(*bp));
			continue;

		case 'V':	/* The ISO 8601:1988 week number as decimal */
			bp = conv_num(bp, &i, 0, 53);
			continue;

		case 'Y':	/* The year. */
			i = TM_YEAR_BASE;	/* just for data sanity... */
			bp = conv_num(bp, &i, 0, 9999);
			tm->tm_year = i - TM_YEAR_BASE;
			LEGAL_ALT(ALT_E);
			continue;

		case 'y':	/* The year within 100 years of the epoch. */
			/* LEGAL_ALT(ALT_E | ALT_O); */
			bp = conv_num(bp, &i, 0, 99);

			if (split_year)
				/* preserve century */
				i += (tm->tm_year / 100) * 100;
			else {
				split_year = 1;
				if (i <= 68)
					i = i + 2000 - TM_YEAR_BASE;
				else
					i = i + 1900 - TM_YEAR_BASE;
			}
			tm->tm_year = i;
			continue;

		case 'Z':
			tzset();
			if (strncmp((const char *)bp, gmt, 3) == 0) {
				tm->tm_isdst = 0;
#ifdef TM_GMTOFF
				tm->TM_GMTOFF = 0;
#endif
#ifdef TM_ZONE
				tm->TM_ZONE = gmt;
#endif
				bp += 3;
			} else {
				const unsigned char *ep;

				ep = find_string(bp, &i,
					       	 (const char * const *)tzname,
					       	  NULL, 2);
				if (ep != NULL) {
					tm->tm_isdst = i;
#ifdef TM_GMTOFF
					tm->TM_GMTOFF = -(timezone);
#endif
#ifdef TM_ZONE
					tm->TM_ZONE = tzname[i];
#endif
				}
				bp = ep;
			}
			continue;

		case 'z':
			/*
			 * We recognize all ISO 8601 formats:
			 * Z	= Zulu time/UTC
			 * [+-]hhmm
			 * [+-]hh:mm
			 * [+-]hh
			 */
			while (isspace(*bp))
				bp++;

			switch (*bp++) {
			case 'Z':
				tm->tm_isdst = 0;
#ifdef TM_GMTOFF
				tm->TM_GMTOFF = 0;
#endif
#ifdef TM_ZONE
				tm->TM_ZONE = utc;
#endif
				continue;
			case '+':
				neg = 0;
				break;
			case '-':
				neg = 1;
				break;
			default:
				return NULL;
			}
			offs = 0;
			for (i = 0; i < 4; ) {
				if (isdigit(*bp)) {
					offs = offs * 10 + (*bp++ - '0');
					i++;
					continue;
				}
				if (i == 2 && *bp == ':') {
					bp++;
					continue;
				}
				break;
			}
			switch (i) {
			case 2:
				offs *= 100;
				break;
			case 4:
				i = offs % 100;
				if (i >= 60)
					return NULL;
				/* Convert minutes into decimal */
				offs = (offs / 100) * 100 + (i * 50) / 30;
				break;
			default:
				return NULL;
			}
			if (neg)
				offs = -offs;
			tm->tm_isdst = 0;	/* XXX */
#ifdef TM_GMTOFF
			tm->TM_GMTOFF = offs;
#endif
#ifdef TM_ZONE
			tm->TM_ZONE = NULL;	/* XXX */
#endif
			continue;

		/*
		 * Miscellaneous conversions.
		 */
		case 'n':	/* Any kind of white-space. */
		case 't':
			while (isspace(*bp))
				bp++;
			LEGAL_ALT(0);
			continue;


		default:	/* Unknown/unsupported conversion. */
			return NULL;
		}
	}

	return __UNCONST(bp);
}
#endif

bool System::ParseDateTime(time_t &timep, long &milliseconds, const char date[18])
{
  if(!date) return false;
  size_t len = strlen(date); (void)len;
  struct tm ptm;
  char *ptr = strptime(date, "%Y%m%d%H%M%S", &ptm);
  if( ptr && *ptr ) // more data to process
    {
    if( sscanf( ptr, "%03ld", &milliseconds ) != 1 )
      {
      // Could not parse milliseconds but date looks ok, should I return false anyway ?
      return false;
      }
    }
  timep = mktime(&ptm);

  return true;
}

bool System::FormatDateTime(char date[18], time_t timep, long milliseconds)
{
  if(!date) return false;
  const size_t maxsize = 40;
  char tmp[maxsize];
  // Obtain the time of day, and convert it to a tm struct.
  struct tm *ptm = localtime (&timep);
  // Format the date and time, down to a single second.
  size_t ret = strftime (tmp, sizeof (tmp), "%Y%m%d%H%M%S", ptm);
  if( ret == 0 || ret >= maxsize )
    {
    return false;
    }

  // Add milliseconds
  const size_t maxsizall = 18;
  //char tmpAll[maxsizall];
  int ret2 = snprintf(date,maxsizall,"%s%03ld",tmp,milliseconds);
  assert( ret2 >= 0 );
  if( (unsigned int)ret2 >= maxsizall )
    {
    return false;
    }

  // Ok !
  return true;
}

bool System::GetCurrentDateTime(char date[18])
{
  long milliseconds;
  time_t timep;

  struct timeval tv;
  gettimeofday (&tv, NULL);
  timep = tv.tv_sec;
  // Compute milliseconds from microseconds.
  milliseconds = tv.tv_usec / 1000;

  return FormatDateTime(date, timep, milliseconds);
}

int System::StrNCaseCmp(const char *s1, const char *s2, size_t n)
{
#if defined(HAVE_STRNCASECMP)
  return strncasecmp(s1,s2,n);
#elif defined(HAVE__STRNICMP)
  return _strnicmp(s1,s2,n);
#else // default implementation
#error
  assert( n ); // TODO
  while (--n && *s1 && (tolower(*s1) == tolower(*s2)))
    {
    s1++;
    s2++;
    }

 return tolower(*s1) - tolower(*s2);
#endif
}

int System::StrCaseCmp(const char *s1, const char *s2)
{
#if defined(HAVE_STRCASECMP)
  return strcasecmp(s1,s2);
#elif defined(HAVE__STRNICMP)
  return _stricmp(s1,s2);
#else // default implementation
#error
  while (*s1 && (tolower(*s1) == tolower(*s2)))
    {
    s1++;
    s2++;
    }

 return tolower(*s1) - tolower(*s2);
#endif
}

} // end namespace gdcm
