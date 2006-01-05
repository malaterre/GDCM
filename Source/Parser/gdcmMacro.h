#ifndef __gdcmMacro_h
#define __gdcmMacro_h

#include "gdcmConfigure.h"

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
#ifdef NDEBUG
#define gdcmDebugMacro(msg) {}
#else
#define gdcmDebugMacro(msg)                                 \
{                                                           \
   if( Debug::GetDebugFlag() )                              \
   {                                                        \
   std::ostringstream osmacro;                              \
   osmacro << "Debug: In " __FILE__ ", line " << __LINE__   \
           << ", function " << GDCM_FUNCTION << '\n';       \
   if( errno )                                              \
     osmacro  << "Last system error was: " <<               \
       strerror(errno) << '\n';                             \
   osmacro << msg << "\n\n";                                \
   if( Debug::GetDebugToFile() )                            \
      Debug::GetDebugFile() << osmacro.str() << std::endl;  \
   else                                                     \
      std::cerr << osmacro.str() << std::endl;              \
   }                                                        \
}
#endif //NDEBUG

/**
 * \brief   Warning : To be used to warn the user when some oddity occurs
 * @param msg message part
 */
#ifdef NDEBUG
#define gdcmWarningMacro(msg) {}
#else
#define gdcmWarningMacro(msg)                               \
{                                                           \
   if( Debug::GetWarningFlag() )                            \
   {                                                        \
   std::ostringstream osmacro;                              \
   osmacro << "Warning: In " __FILE__ ", line " << __LINE__ \
           << ", function " << GDCM_FUNCTION << "\n"        \
           << msg << "\n\n";                                \
   if( Debug::GetDebugToFile() )                            \
      Debug::GetDebugFile() << osmacro.str() << std::endl;  \
   else                                                     \
      std::cerr << osmacro.str() << std::endl;              \
   }                                                        \
}
#endif //NDEBUG

/**
 * \brief   Error : To be used when unecoverabale error occurs
 *          at a 'deep' level. (don't use it if file is not ACR/DICOM!)
 * @param msg second message part 
 */
#ifdef NDEBUG
#define gdcmErrorMacro(msg) {}
#else
#define gdcmErrorMacro(msg)                                 \
{                                                           \
   std::ostringstream osmacro;                              \
   osmacro << "Error: In " __FILE__ ", line " << __LINE__   \
           << ", function " << GDCM_FUNCTION << '\n'        \
           << msg << "\n\n";                                \
   if( Debug::GetDebugToFile() )                            \
      Debug::GetDebugFile() << osmacro.str() << std::endl;  \
   else                                                     \
      std::cerr << osmacro.str() << std::endl;              \
}
#endif //NDEBUG

/**
 * \brief   Assert : To be used when an *absolutely* impossible error occurs
 *          No function should be allowed to stop the process instead of
 *          warning the caller!
 * @param arg argument to test
 *        An easy solution to pass also a message is to do:
 *        gdcmAssertMacro( "my message" && 2 < 3 )
 */
#ifdef NDEBUG
#define gdcmAssertMacro(arg) {}
#else
#define gdcmAssertMacro(arg)                                \
{                                                           \
   if( !(arg) )                                             \
   {                                                        \
   std::ostringstream osmacro;                              \
   osmacro << "Assert: In " __FILE__ ", line " << __LINE__  \
           << ", function " << GDCM_FUNCTION                \
           << "\n\n";                                       \
   if( Debug::GetDebugToFile() )                            \
      Debug::GetDebugFile() << osmacro.str() << std::endl;  \
   else                                                     \
      std::cerr << osmacro.str() << std::endl;              \
   assert ( arg );                                          \
   }                                                        \
}
#endif //NDEBUG

//-----------------------------------------------------------------------------
//
// Define GDCM_LEGACY macro to mark legacy methods where they are
// declared in their class.
// 
// WARNING : Don't try to use it with 'inline' methods ! 
//
//Example usage:
//
//   // @deprecated Replaced by MyOtherMethod() as of gdcm 2.0.
//   GDCM_LEGACY(void MyMethod());
#if defined(GDCM_LEGACY_REMOVE)
  // Remove legacy methods completely.
# define GDCM_LEGACY(method)
#elif defined(GDCM_LEGACY_SILENT) || defined(SWIG)
  // Provide legacy methods with no warnings.
# define GDCM_LEGACY(method) method
#else
  // Setup compile-time warnings for uses of deprecated methods if
  // possible on this compiler.
# if defined(__GNUC__) && !defined(__INTEL_COMPILER) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
#if defined(__APPLE__) && (__GNUC__ == 3) && (__GNUC_MINOR__ == 3)
// Seems like there is a bug in APPLE gcc for deprecated attribute and ctor
// This is fixed in g++ 4.0 (Tiger)
#  define GDCM_LEGACY(method) method
#else
#  define GDCM_LEGACY(method) method __attribute__((deprecated))
#endif
# elif defined(_MSC_VER) && _MSC_VER >= 1300
#  define GDCM_LEGACY(method) __declspec(deprecated) method
# else
#  define GDCM_LEGACY(method) method
# endif
#endif

// Macros to create runtime deprecation warning messages in function
// bodies.  Example usage:
//
//   void MyClass::MyOldMethod()
//   {
//     GDCM_LEGACY_BODY(MyClass::MyOldMethod, 2.0);
//   }
//
//   void MyClass::MyMethod()
//   {
//     GDCM_LEGACY_REPLACED_BODY(MyClass::MyMethod, 5.0,
//                               MyClass::MyOtherMethod);
//   }
#if defined(GDCM_LEGACY_REMOVE) || defined(GDCM_LEGACY_SILENT)
# define GDCM_LEGACY_BODY(method, version)
# define GDCM_LEGACY_REPLACED_BODY(method, version, replace)
#else
# define GDCM_LEGACY_BODY(method, version) \
  gdcmWarningMacro(#method " was deprecated for gdcm" #version " and will be removed in a future version.")
# define GDCM_LEGACY_REPLACED_BODY(method, version, replace) \
  gdcmWarningMacro(#method " was deprecated for gdcm" #version " and will be removed in a future version.  Use " #replace " instead.")
#endif

#endif //__gdcmMacro_h
