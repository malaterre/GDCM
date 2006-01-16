#ifndef __gdcmTrace_h
#define __gdcmTrace_h

#include "gdcmType.h"

#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

namespace gdcm 
{
//-----------------------------------------------------------------------------
class GDCM_EXPORT Trace
{
public :
  Trace() { DebugFlag = WarningFlag = ErrorFlag = false; };
  ~Trace() {};

  static void DebugOn()  { DebugFlag = true; };
  static void DebugOff() { DebugFlag = false; };
  
  static void WarningOn()  { WarningFlag = true; };
  static void WarningOff() { WarningFlag = false; };

  static void ErrorOn()  { ErrorFlag = true; };
  static void ErrorOff() { ErrorFlag = false; };

protected:
private:
  static bool DebugFlag;
  static bool WarningFlag;
  static bool ErrorFlag;
};

#if 0
// Here we define function this is the only way to be able to pass
// stuff with indirection like:
// gdcmDebug( "my message:" << i << '\t' ); 
// You cannot use function unless you use vnsprintf ...

// __FUNCTION is not always defined by preprocessor
// In c++ we should use __PRETTY_FUNCTION__ instead...
#ifdef GDCM_COMPILER_HAS_FUNCTION
// Handle particular case for GNU C++ which also defines __PRETTY_FUNCTION__
// which is a lot nice in C++
#ifdef __BORLANDC__
#  define __FUNCTION__ __FUNC__
#endif
#ifdef __GNUC__
#  define GDCM_FUNCTION __PRETTY_FUNCTION__
#else
#  define GDCM_FUNCTION __FUNCTION__ 
#endif //__GNUC__
#else
#  define GDCM_FUNCTION "<unknow>"
#endif //GDCM_COMPILER_HAS_FUNCTION

/**
 * \brief   Debug : To be used to help bug tracking developer
 * @param msg message part
 */
#define gdcmMessageBodyMacro(type, obj, msg, adds)             \
{                                                              \
   std::ostringstream osmacro;                                 \
   osmacro << "In " __FILE__ ", line " << __LINE__             \
           << ", function " << GDCM_FUNCTION << "\n"           \
           << adds << msg << "\n\n";                           \
   gdcm::Debug::SendToOutput(type,osmacro.str(),obj);          \
}

// ------------------------------------------------------------------------

/**
 * \brief Debug : To be used to help bug tracking developer
 * @param msg message part
 */
#ifdef NDEBUG
#define gdcmDebugBodyMacro(obj, msg) {}
#define gdcmDebugMacro(msg) {}
#define gdcmStaticDebugMacro(msg) {}
#else
#define gdcmDebugBodyMacro(obj, msg)                           \
{                                                              \
   if( Debug::GetDebugFlag() )                                 \
   {                                                           \
      std::string adds="";                                     \
      if( errno )                                              \
      {                                                        \
         adds = "Last system error was: ";                     \
         adds += strerror(errno);                              \
         adds += "\n";                                         \
      }                                                        \
      gdcmMessageBodyMacro(gdcm::CMD_DEBUG,obj,msg,adds);      \
   }                                                           \
}
#define gdcmDebugMacro(msg)                                    \
   gdcmDebugBodyMacro(NULL,msg)
#define gdcmStaticDebugMacro(msg)                              \
   gdcmDebugBodyMacro(NULL,msg)
#endif //NDEBUG

// ------------------------------------------------------------------------

/**
 * \brief Log : we display messages when anything is not Dicom Kosher
 * @param msg message part
 */
// No NDEBUG test to always have a return of warnings !!!
// -> Rien compris! JPRx
#define gdcmLogBodyMacro(obj, msg)                         \
{                                                              \
   if( Debug::GetLogFlag() )                               \
      gdcmMessageBodyMacro(gdcm::CMD_LOG,obj,msg,"");      \
}
#define gdcmLogMacro(msg)                                  \
   gdcmLogBodyMacro(this,msg)
#define gdcmStaticLogMacro(msg)                            \
   gdcmLogBodyMacro(NULL,msg)
   
// ------------------------------------------------------------------------

/**
 * \brief Warning : To be used to warn the user when some oddity occurs
 * @param msg message part
 */
// No NDEBUG test to always have a return of warnings !!!
// -> Rien compris! JPRx
#define gdcmWarningBodyMacro(obj, msg)                         \
{                                                              \
   if( Debug::GetWarningFlag() )                               \
      gdcmMessageBodyMacro(gdcm::CMD_WARNING,obj,msg,"");      \
}
#define gdcmWarningMacro(msg)                                  \
   gdcmWarningBodyMacro(this,msg)
#define gdcmStaticWarningMacro(msg)                            \
   gdcmWarningBodyMacro(NULL,msg)

// ------------------------------------------------------------------------

/**
 * \brief   Error : To be used when unecoverabale error occurs
 *          at a 'deep' level. (don't use it if file is not ACR/DICOM!)
 * @param msg second message part 
 */
// No NDEBUG test to always have a return of errors !!!
// -> Rien compris! JPRx
#define gdcmErrorBodyMacro(obj, msg)                           \
{                                                              \
   gdcmMessageBodyMacro(gdcm::CMD_ERROR,obj,msg,"");           \
}
#define gdcmErrorMacro(msg)                                    \
   gdcmErrorBodyMacro(this,msg)
#define gdcmStaticErrorMacro(msg)                              \
   gdcmErrorBodyMacro(NULL,msg)

// ------------------------------------------------------------------------

/**
 * \brief Assert : To be used when an *absolutely* impossible error occurs
 *        No function should be allowed to stop the process instead of
 *        warning the caller!
 * @param arg argument to test
 *        An easy solution to pass also a message is to do:
 *        gdcmAssertMacro( "my message" && 2 < 3 )
 */
// No NDEBUG test to always have a return of asserts !!!
// -> Rien compris! JPRx
#define gdcmAssertBodyMacro(obj, arg)                          \
{                                                              \
   if( !(arg) )                                                \
   {                                                           \
      gdcmMessageBodyMacro(gdcm::CMD_ASSERT,obj,"","");        \
      assert ( arg );                                          \
   }                                                           \
}
#define gdcmAssertMacro(msg)                                   \
   gdcmAssertBodyMacro(NULL,msg)
#define gdcmStaticAssertMacro(msg)                             \
   gdcmAssertBodyMacro(NULL,msg)

#endif
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif
