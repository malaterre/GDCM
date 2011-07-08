/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// See docs:
// http://www.swig.org/Doc1.3/Java.html
// http://www.swig.org/Doc1.3/SWIGPlus.html#SWIGPlus

%module(docstring="A DICOM library",directors=1) gdcm
#pragma SWIG nowarn=302,303,312,325,362,383,389,401,503,504,509,510,514,516,822

// There is something funky with swig 1.3.33, one cannot simply test defined(SWIGCSHARP)
// I need to redefine it myself... seems to be solved in later revision
#if defined(SWIGJAVA)
%{
#define SWIGJAVA
%}
#endif

%{
#include "gdcmTypes.h"
#include "gdcmASN1.h"
#include "gdcmSmartPointer.h"
#include "gdcmSwapCode.h"
#include "gdcmEvent.h"
#include "gdcmProgressEvent.h"
#include "gdcmAnonymizeEvent.h"
#include "gdcmDirectory.h"
#ifdef GDCM_BUILD_TESTING
#include "gdcmTesting.h"
#endif
#include "gdcmObject.h"
#include "gdcmPixelFormat.h"
#include "gdcmMediaStorage.h"
#include "gdcmTag.h"
#include "gdcmPrivateTag.h"
#include "gdcmVL.h"
#include "gdcmVR.h"
#include "gdcmVM.h"
#include "gdcmObject.h"
#include "gdcmValue.h"
#include "gdcmByteValue.h"
#include "gdcmDataElement.h"
#include "gdcmItem.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmDataSet.h"
//#include "gdcmString.h"
//#include "gdcmCodeString.h"
#include "gdcmPreamble.h"
#include "gdcmFile.h"
#include "gdcmBitmap.h"
#include "gdcmPixmap.h"
#include "gdcmImage.h"
#include "gdcmIconImage.h"
#include "gdcmFragment.h"
#include "gdcmCSAHeader.h"
#include "gdcmPDBHeader.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmTransferSyntax.h"
#include "gdcmBasicOffsetTable.h"
//#include "gdcmLO.h"
#include "gdcmCSAElement.h"
#include "gdcmPDBElement.h"
#include "gdcmFileSet.h"

#include "gdcmReader.h"
#include "gdcmPixmapReader.h"
#include "gdcmImageReader.h"
#include "gdcmWriter.h"
#include "gdcmPixmapWriter.h"
#include "gdcmImageWriter.h"
#include "gdcmStringFilter.h"
#include "gdcmGlobal.h"
#include "gdcmDicts.h"
#include "gdcmDict.h"
#include "gdcmCSAHeaderDict.h"
#include "gdcmDictEntry.h"
#include "gdcmCSAHeaderDictEntry.h"
#include "gdcmUIDGenerator.h"
//#include "gdcmConstCharWrapper.h"
#include "gdcmScanner.h"
#include "gdcmAttribute.h"
#include "gdcmSubject.h"
#include "gdcmCommand.h"
#include "gdcmAnonymizer.h"
#include "gdcmSystem.h"
#include "gdcmTrace.h"
#include "gdcmUIDs.h"
#include "gdcmSorter.h"
#include "gdcmIPPSorter.h"
#include "gdcmSpectroscopy.h"
#include "gdcmPrinter.h"
#include "gdcmDumper.h"
#include "gdcmOrientation.h"
#include "gdcmFiducials.h"
#include "gdcmWaveform.h"
#include "gdcmPersonName.h"
#include "gdcmIconImage.h"
#include "gdcmCurve.h"
#include "gdcmDICOMDIR.h"
#include "gdcmValidate.h"
#include "gdcmApplicationEntity.h"
#include "gdcmDictPrinter.h"
#include "gdcmFilenameGenerator.h"
#include "gdcmVersion.h"
#include "gdcmFilename.h"
#include "gdcmEnumeratedValues.h"
#include "gdcmPatient.h"
#include "gdcmStudy.h"
#include "gdcmUsage.h"
#include "gdcmMacroEntry.h"
#include "gdcmModuleEntry.h"
#include "gdcmNestedModuleEntries.h"
#include "gdcmMacro.h"
#include "gdcmMacros.h"
#include "gdcmModule.h"
#include "gdcmModules.h"
#include "gdcmDefs.h"
#include "gdcmIOD.h"
#include "gdcmIODs.h"
#include "gdcmTableEntry.h"
#include "gdcmDefinedTerms.h"
#include "gdcmSeries.h"
#include "gdcmIODEntry.h"
#include "gdcmRescaler.h"
#include "gdcmSegmentedPaletteColorLookupTable.h"
#include "gdcmUnpacker12Bits.h"
//#include "gdcmPythonFilter.h"
#include "gdcmDirectionCosines.h"
#include "gdcmTagPath.h"
#include "gdcmBitmapToBitmapFilter.h"
#include "gdcmPixmapToPixmapFilter.h"
#include "gdcmImageToImageFilter.h"
#include "gdcmSOPClassUIDToIOD.h"
#include "gdcmCoder.h"
#include "gdcmDecoder.h"
#include "gdcmCodec.h"
#include "gdcmImageCodec.h"
#include "gdcmJPEGCodec.h"
#include "gdcmJPEGLSCodec.h"
#include "gdcmJPEG2000Codec.h"
#include "gdcmImageChangeTransferSyntax.h"
#include "gdcmImageApplyLookupTable.h"
#include "gdcmSplitMosaicFilter.h"
#include "gdcmImageChangePhotometricInterpretation.h"
#include "gdcmImageChangePlanarConfiguration.h"
#include "gdcmImageFragmentSplitter.h"
#include "gdcmDataSetHelper.h"
#include "gdcmFileExplicitFilter.h"
#include "gdcmImageHelper.h"
#include "gdcmMD5.h"
#include "gdcmDummyValueGenerator.h"
#include "gdcmSHA1.h"
#include "gdcmBase64.h"
#include "gdcmCryptographicMessageSyntax.h"
#include "gdcmSpacing.h"
#include "gdcmIconImageGenerator.h"
#include "gdcmIconImageFilter.h"

#include "gdcmSimpleSubjectWatcher.h"
#include "gdcmDICOMDIRGenerator.h"
#include "gdcmFileDerivation.h"

using namespace gdcm;
%}

// swig need to know what are uint16_t, uint8_t...
%include "stdint.i"

// gdcm does not use std::string in its interface, but we do need it for the
// %extend (see below)
%include "std_string.i"
%include "std_set.i"
%include "std_vector.i"
%include "std_pair.i"
%include "std_map.i"
%include "exception.i"

// operator= is not needed in python AFAIK
%ignore operator=;                      // Ignore = everywhere.
%ignore operator++;                     // Ignore

%define EXTEND_CLASS_PRINT_GENERAL(classfuncname,classname)
%extend classname
{
  const char *classfuncname() {
    static std::string buffer;
    std::ostringstream os;
    os << *self;
    buffer = os.str();
    return buffer.c_str();
  }
};
%enddef

#if defined(SWIGJAVA)
%define EXTEND_CLASS_PRINT(classname)
// Remove Print( ostream & os )
//%ignore classname::Print
EXTEND_CLASS_PRINT_GENERAL(toString,classname)
%enddef
#endif

//%feature("autodoc", "1")
%include "gdcmConfigure.h"

// http://www.swig.org/Doc1.3/Java.html#imclass_pragmas
// Need to be located *after* gdcmConfigure.h
#ifdef GDCM_AUTOLOAD_GDCMJNI
%pragma(java) jniclasscode=%{
 static {
   try {
       System.loadLibrary("gdcmjni");
   } catch (UnsatisfiedLinkError e) {
     System.err.println("Native code library failed to load. \n" + e);
     System.exit(1);
   }
 }
%}
#endif


//%include "gdcmTypes.h"
//%include "gdcmWin32.h"
// I cannot include gdcmWin32.h without gdcmTypes.h, first. But gdcmTypes.h needs to know _MSC_VER at swig time...
#define GDCM_EXPORT
%include "gdcmLegacyMacro.h"

%include "gdcmSwapCode.h"

//%feature("director") Event;
//%feature("director") AnyEvent;
%include "gdcmEvent.h"

%include "gdcmPixelFormat.h"
EXTEND_CLASS_PRINT(gdcm::PixelFormat)
%include "gdcmMediaStorage.h"
EXTEND_CLASS_PRINT(gdcm::MediaStorage)
//%rename(__getitem__) gdcm::Tag::operator[];
//%rename(this ) gdcm::Tag::operator[];
%include "gdcmTag.h"
EXTEND_CLASS_PRINT(gdcm::Tag)
%include "gdcmPrivateTag.h"
EXTEND_CLASS_PRINT(gdcm::PrivateTag)

%include "gdcmProgressEvent.h"
%extend gdcm::ProgressEvent {
  static ProgressEvent *Cast(Event *event) {
    return dynamic_cast<ProgressEvent*>(event);
  }
};
//%feature("director") AnonymizeEvent;
%include "gdcmAnonymizeEvent.h"
%extend gdcm::AnonymizeEvent {
  static AnonymizeEvent *Cast(Event *event) {
    return dynamic_cast<AnonymizeEvent*>(event);
  }
};

%include "gdcmVL.h"
EXTEND_CLASS_PRINT(gdcm::VL)
%include "gdcmVR.h"
EXTEND_CLASS_PRINT(gdcm::VR)
%include "gdcmVM.h"
EXTEND_CLASS_PRINT(gdcm::VM)
//%template (FilenameType) std::string;
%template (FilenamesType) std::vector<std::string>;
%include "gdcmDirectory.h"
EXTEND_CLASS_PRINT(gdcm::Directory)
//%clear FilenameType;
%clear FilenamesType;
%include "gdcmObject.h"
%include "gdcmValue.h"
EXTEND_CLASS_PRINT(gdcm::Value)
// Array marshaling for arrays of primitives
// http://www.swig.org/Doc2.0/Java.html#Java_unbounded_c_arrays

// %clear commands should be unnecessary, but do it just-in-case
%clear char* buffer;
%clear unsigned char* buffer;

%include "arrays_java.i"

%ignore gdcm::ByteValue::WriteBuffer(std::ostream &os) const;
%ignore gdcm::ByteValue::GetPointer() const;
%ignore gdcm::ByteValue::GetBuffer(char *buffer, unsigned long length) const;
%apply signed char[] { signed char* buffer }
%include "gdcmByteValue.h"
%extend gdcm::ByteValue
{
  bool GetBuffer(signed char *buffer, unsigned long length) const {
    return self->GetBuffer((char*)buffer, length);
  }
};
EXTEND_CLASS_PRINT(gdcm::ByteValue)
%clear signed char* buffer;


%apply char[] { const char* array }

%include "gdcmASN1.h"
%include "gdcmSmartPointer.h"
%template(SmartPtrSQ) gdcm::SmartPointer<gdcm::SequenceOfItems>;
%template(SmartPtrFrag) gdcm::SmartPointer<gdcm::SequenceOfFragments>;
%include "gdcmDataElement.h"
EXTEND_CLASS_PRINT(gdcm::DataElement)

%clear const char* array;
%extend gdcm::DataElement
{
 void SetArray(signed char array[], unsigned int nitems) {
   $self->SetByteValue((char*)array, nitems * sizeof(signed char) );
 }
 void SetArray(signed short array[], unsigned int nitems) {
   $self->SetByteValue((char*)array, nitems * sizeof(signed short) );
 }
 void SetArray(signed int array[], unsigned int nitems) {
   $self->SetByteValue((char*)array, nitems * sizeof(signed int) );
 }
 void SetArray(float array[], unsigned int nitems) {
   $self->SetByteValue((char*)array, nitems * sizeof(float) );
 }
 void SetArray(double array[], unsigned int nitems) {
   $self->SetByteValue((char*)array, nitems * sizeof(double) );
 }
};

%include "gdcmItem.h"
EXTEND_CLASS_PRINT(gdcm::Item)
/*
*/
%template() std::set< gdcm::Item >;
%include "gdcmSequenceOfItems.h"
EXTEND_CLASS_PRINT(gdcm::SequenceOfItems)
%rename (JavaDataSet) SWIGDataSet;
%rename (JavaTagToValue) SWIGTagToValue;
%include "gdcmDataSet.h"
EXTEND_CLASS_PRINT(gdcm::DataSet)
//namespace std {
//  //struct lttag
//  //  {
//  //  bool operator()(const gdcm::DataElement &s1,
//  //    const gdcm::DataElement &s2) const
//  //    {
//  //    return s1.GetTag() < s2.GetTag();
//  //    }
//  //  };
//
//  //%template(DataElementSet) gdcm::DataSet::DataElementSet;
//  %template(DataElementSet) set<DataElement, lttag>;
//}

%include "gdcmPhotometricInterpretation.h"
EXTEND_CLASS_PRINT(gdcm::PhotometricInterpretation)
%include "gdcmObject.h"
%apply signed char[] { signed char* array }
%ignore gdcm::LookupTable::GetLUT(LookupTableType type, unsigned char *array, unsigned int &length) const;
%include "gdcmLookupTable.h"
%extend gdcm::LookupTable
{
  unsigned int GetLUT(LookupTableType type, signed char *array) const {
    unsigned int length = 0;
    self->GetLUT( type, (unsigned char*)array, length);
    return length;
  }
};
EXTEND_CLASS_PRINT(gdcm::LookupTable)
%include "gdcmOverlay.h"
EXTEND_CLASS_PRINT(gdcm::Overlay)
//%include "gdcmVR.h"
//%template (DataElementSet) std::set<gdcm::DataElement>;
%include "gdcmPreamble.h"
EXTEND_CLASS_PRINT(gdcm::Preamble)
%include "gdcmTransferSyntax.h"
EXTEND_CLASS_PRINT(gdcm::TransferSyntax)
%include "gdcmFileMetaInformation.h"
EXTEND_CLASS_PRINT(gdcm::FileMetaInformation)

//%template(File) gdcm::SmartPointer<gdcm::File>;
//%ignore gdcm::File;

%include "gdcmFile.h"
EXTEND_CLASS_PRINT(gdcm::File)
//%include "gdcm_arrays_csharp.i"

%apply signed char[] { signed char* buffer }
%apply unsigned int[] { unsigned int dims[3] }

//%apply byte OUTPUT[] { char* buffer } ;
//%ignore gdcm::Pixmap::GetBuffer(char*) const;
//%apply byte FIXED[] { char *buffer }
//%csmethodmodifiers gdcm::Pixmap::GetBuffer "public unsafe";
//%define %cs_marshal_array(TYPE, CSTYPE)
//       %typemap(ctype)  TYPE[] "void*"
//       %typemap(imtype, inattributes="[MarshalAs(UnmanagedType.LPArray)]") TYPE[] "CSTYPE[]"
//       %typemap(cstype) TYPE[] "CSTYPE[]"
//       %typemap(in)     TYPE[] %{ $1 = (TYPE*)$input; %}
//       %typemap(csin)   TYPE[] "$csinput"
//%enddef
//%cs_marshal_array(char, byte)
%ignore gdcm::Bitmap::GetBuffer(char* buffer) const;
%include "gdcmBitmap.h"
%extend gdcm::Bitmap
{
  bool GetBuffer(signed char *buffer) const {
    return self->GetBuffer((char*)buffer);
  }
  // There is no such thing as unsigned type in java
  // so we only wrap the signed API, and hope user understand what to do
  bool GetArray(signed char buffer[]) const {
    return $self->GetBuffer((char*)buffer);
  }
  bool GetArray(short buffer[]) const {
    return $self->GetBuffer((char*)buffer);
  }
  bool GetArray(int buffer[]) const { // is int always 32bits in Java ?
    return $self->GetBuffer((char*)buffer);
  }
  bool GetArray(float buffer[]) const {
    assert( $self->GetPixelFormat() == PixelFormat::FLOAT32 );
    return $self->GetBuffer((char*)buffer);
  }
  bool GetArray(double buffer[]) const {
    assert( $self->GetPixelFormat() == PixelFormat::FLOAT64 );
    return $self->GetBuffer((char*)buffer);
  }
};
%clear signed char* buffer;
%clear unsigned int* dims;
EXTEND_CLASS_PRINT(gdcm::Bitmap)

%include "gdcmPixmap.h"
EXTEND_CLASS_PRINT(gdcm::Pixmap)

%include "gdcmImage.h"
EXTEND_CLASS_PRINT(gdcm::Image)
%include "gdcmIconImage.h"
EXTEND_CLASS_PRINT(gdcm::IconImage)
%include "gdcmFragment.h"
EXTEND_CLASS_PRINT(gdcm::Fragment)
%include "gdcmPDBElement.h"
EXTEND_CLASS_PRINT(gdcm::PDBElement)
%include "gdcmPDBHeader.h"
EXTEND_CLASS_PRINT(gdcm::PDBHeader)
%include "gdcmCSAElement.h"
EXTEND_CLASS_PRINT(gdcm::CSAElement)
%include "gdcmCSAHeader.h"
EXTEND_CLASS_PRINT(gdcm::CSAHeader)
%include "gdcmSequenceOfFragments.h"
EXTEND_CLASS_PRINT(gdcm::SequenceOfFragments)
%include "gdcmBasicOffsetTable.h"
EXTEND_CLASS_PRINT(gdcm::BasicOffsetTable)
//%include "gdcmLO.h"
%include "gdcmFileSet.h"
EXTEND_CLASS_PRINT(gdcm::FileSet)

%include "gdcmGlobal.h"
EXTEND_CLASS_PRINT(gdcm::Global)

%include "gdcmDictEntry.h"
EXTEND_CLASS_PRINT(gdcm::DictEntry)
%include "gdcmCSAHeaderDictEntry.h"
EXTEND_CLASS_PRINT(gdcm::CSAHeaderDictEntry)

%include "gdcmDict.h"
EXTEND_CLASS_PRINT(gdcm::Dict)
%include "gdcmCSAHeaderDict.h"
EXTEND_CLASS_PRINT(gdcm::CSAHeaderDictEntry)
%include "gdcmDicts.h"
EXTEND_CLASS_PRINT(gdcm::Dicts)

#if 0
jstring JNU_NewStringNative(JNIEnv *env, const char *str)
 {
     jstring result;
     jbyteArray bytes = 0;
     int len;
     if (env->EnsureLocalCapacity(2) < 0) {
         return NULL; /* out of memory error */
     }
     len = strlen(str);
     bytes = (*env)->NewByteArray(env, len);
     if (bytes != NULL) {
         (*env)->SetByteArrayRegion(env, bytes, 0, len,
                                    (jbyte *)str);
         result = (*env)->NewObject(env, Class_java_lang_String,
                                    MID_String_init, bytes);
         (*env)->DeleteLocalRef(env, bytes);
         return result;
     } /* else fall through */
     return NULL;
}
#endif


%{
void
 JNU_ThrowByName(JNIEnv *env, const char *name, const char *msg)
 {
     jclass cls = env->FindClass(name);
     /* if cls is NULL, an exception has already been thrown */
     if (cls != NULL) {
         env->ThrowNew(cls, msg);
     }
     /* free the local ref */
     env->DeleteLocalRef(cls);
 }

char *JNU_GetStringNativeChars(JNIEnv *env, jstring jstr)
 {
  if (jstr == NULL) {
    return NULL;
  }
     jbyteArray bytes = 0;
     jthrowable exc;
     char *result = 0;
     if (env->EnsureLocalCapacity(2) < 0) {
         return 0; /* out of memory error */
     }
     jclass Class_java_lang_String = env->FindClass("java/lang/String");
     jmethodID MID_String_getBytes = env->GetMethodID(
       Class_java_lang_String, "getBytes", "()[B");
     bytes = (jbyteArray) env->CallObjectMethod(jstr,
                                      MID_String_getBytes);
     exc = env->ExceptionOccurred();
     if (!exc) {
         jint len = env->GetArrayLength(bytes);
         result = (char *)malloc(len + 1);
         if (result == 0) {
             JNU_ThrowByName(env, "java/lang/OutOfMemoryError",
                             0);
             env->DeleteLocalRef(bytes);
             return 0;
         }
         env->GetByteArrayRegion(bytes, 0, len,
                                    (jbyte *)result);
         result[len] = 0; /* NULL-terminate */
     } else {
         env->DeleteLocalRef(exc);
     }
     env->DeleteLocalRef(bytes);
     return result;
 }
%}

%typemap(in) const char *filename_native {
$1 = JNU_GetStringNativeChars(jenv, $input);
}
%typemap(freearg, noblock=1) const char *filename_native { if ($1) free($1); }

%template (TagSetType) std::set<gdcm::Tag>;
%ignore gdcm::Reader::SetStream;
%include "gdcmReader.h"
//EXTEND_CLASS_PRINT(gdcm::Reader)
%include "gdcmPixmapReader.h"
//EXTEND_CLASS_PRINT(gdcm::PixmapReader)
%include "gdcmImageReader.h"
//EXTEND_CLASS_PRINT(gdcm::ImageReader)
%include "gdcmWriter.h"
//EXTEND_CLASS_PRINT(gdcm::Writer)
%include "gdcmPixmapWriter.h"
//EXTEND_CLASS_PRINT(gdcm::PixmapWriter)
%include "gdcmImageWriter.h"
//EXTEND_CLASS_PRINT(gdcm::ImageWriter)
%template (PairString) std::pair<std::string,std::string>;
//%template (MyM) std::map<gdcm::Tag,gdcm::ConstCharWrapper>;
%include "gdcmStringFilter.h"
//EXTEND_CLASS_PRINT(gdcm::StringFilter)
%include "gdcmUIDGenerator.h"
%template (ValuesType)      std::set<std::string>;
%rename (JavaTagToValue) SWIGTagToValue;
#define GDCM_STATIC_ASSERT(x)
%include "gdcmAttribute.h"
%include "gdcmSubject.h"
%include "gdcmCommand.h"

%template(SmartPtrScan) gdcm::SmartPointer<gdcm::Scanner>;
%include "gdcmScanner.h"
EXTEND_CLASS_PRINT(gdcm::Scanner)

%template(SmartPtrAno) gdcm::SmartPointer<gdcm::Anonymizer>;
//%ignore gdcm::Anonymizer::Anonymizer;


//%template(Anonymizer) gdcm::SmartPointer<gdcm::Anonymizer>;
//
//%ignore gdcm::Anonymizer;
//%feature("unref") Anonymizer "coucou $this->Delete();"
// http://www.swig.org/Doc1.3/SWIGPlus.html#SWIGPlus%5Fnn34
%include "gdcmAnonymizer.h"


//EXTEND_CLASS_PRINT(gdcm::Anonymizer)

// System is a namespace in C#, need to rename to something different
%rename (PosixEmulation) System;
%include "gdcmSystem.h"
//EXTEND_CLASS_PRINT(gdcm::System)

%include "gdcmTrace.h"
//EXTEND_CLASS_PRINT(gdcm::Trace)
%include "gdcmUIDs.h"
EXTEND_CLASS_PRINT(gdcm::UIDs)
//%feature("director") gdcm::IPPSorter;
%include "gdcmSorter.h"
EXTEND_CLASS_PRINT(gdcm::Sorter)
%include "gdcmIPPSorter.h"
EXTEND_CLASS_PRINT(gdcm::IPPSorter)
%include "gdcmSpectroscopy.h"
//EXTEND_CLASS_PRINT(gdcm::Spectroscopy)
%include "gdcmPrinter.h"
//EXTEND_CLASS_PRINT(gdcm::Printer)
%include "gdcmDumper.h"
//EXTEND_CLASS_PRINT(gdcm::Dumper)
%include "gdcmOrientation.h"
EXTEND_CLASS_PRINT(gdcm::Orientation)
%include "gdcmDirectionCosines.h"
EXTEND_CLASS_PRINT(gdcm::DirectionCosines)

%include "gdcmFiducials.h"
%include "gdcmWaveform.h"
%include "gdcmPersonName.h"
%include "gdcmIconImage.h"
%include "gdcmCurve.h"
%include "gdcmDICOMDIR.h"
%include "gdcmValidate.h"
%include "gdcmApplicationEntity.h"
%include "gdcmDictPrinter.h"
%include "gdcmFilenameGenerator.h"
%include "gdcmVersion.h"
EXTEND_CLASS_PRINT(gdcm::Version)
%include "gdcmFilename.h"
%include "gdcmEnumeratedValues.h"
%include "gdcmPatient.h"
%include "gdcmStudy.h"
%include "gdcmUsage.h"
%include "gdcmMacroEntry.h"
%include "gdcmModuleEntry.h"
EXTEND_CLASS_PRINT(gdcm::ModuleEntry)
%include "gdcmNestedModuleEntries.h"
%include "gdcmMacro.h"
%include "gdcmMacros.h"
%include "gdcmModule.h"
%include "gdcmModules.h"
%include "gdcmDefs.h"
%include "gdcmIOD.h"
%include "gdcmIODs.h"
%include "gdcmTableEntry.h"
%include "gdcmDefinedTerms.h"
%include "gdcmSeries.h"
%include "gdcmIODEntry.h"
%apply signed char[] { signed char* outbuffer }
%apply signed char[] { signed char* inbuffer }
%include "gdcmRescaler.h"
%extend gdcm::Rescaler
{
  bool Rescale(signed char *outbuffer, const signed char *inbuffer, size_t n) {
    return self->Rescale((char*)outbuffer, (const char*)inbuffer, n);
  }
  bool InverseRescale(char *outbuffer, const char *inbuffer, size_t n) {
    return self->InverseRescale((char*)outbuffer, (const char*)inbuffer, n);
  }
};
%clear signed char* outbuffer;
%clear signed char* inbuffer;

%include "gdcmSegmentedPaletteColorLookupTable.h"
%include "gdcmUnpacker12Bits.h"

%include "gdcmConfigure.h"
#ifdef GDCM_BUILD_TESTING
%include "gdcmTesting.h"
%ignore gdcm::Testing::ComputeMD5(const char *, const unsigned long , char []);
%ignore gdcm::Testing::ComputeFileMD5(const char*, char []);
%extend gdcm::Testing
{
  static const char *ComputeFileMD5(const char *filename) {
    static char buffer[33];
    gdcm::Testing::ComputeFileMD5(filename, buffer);
    return buffer;
  }
};
#endif
//%include "gdcmPythonFilter.h"
%include "gdcmTagPath.h"
%include "gdcmBitmapToBitmapFilter.h"
%include "gdcmPixmapToPixmapFilter.h"
//%ignore gdcm::ImageToImageFilter::GetOutput() const;
%include "gdcmImageToImageFilter.h"
%include "gdcmSOPClassUIDToIOD.h"
//%feature("director") Coder;
//%include "gdcmCoder.h"
//%feature("director") Decoder;
//%include "gdcmDecoder.h"
//%feature("director") Codec;
//%include "gdcmCodec.h"
%feature("director") ImageCodec;
%include "gdcmImageCodec.h"
%include "gdcmJPEGCodec.h"
%include "gdcmJPEGLSCodec.h"
%include "gdcmJPEG2000Codec.h"
%include "gdcmImageChangeTransferSyntax.h"
%include "gdcmImageApplyLookupTable.h"
%include "gdcmSplitMosaicFilter.h"
%include "gdcmImageChangePhotometricInterpretation.h"
%include "gdcmImageChangePlanarConfiguration.h"
%include "gdcmImageFragmentSplitter.h"
%include "gdcmDataSetHelper.h"
%include "gdcmFileExplicitFilter.h"
%template (DoubleArrayType) std::vector<double>;
%template (UShortArrayType) std::vector<unsigned short>;
%template (UIntArrayType) std::vector<unsigned int>;
%include "gdcmImageHelper.h"
%include "gdcmMD5.h"
%include "gdcmDummyValueGenerator.h"
%include "gdcmSHA1.h"
%include "gdcmBase64.h"
%include "gdcmCryptographicMessageSyntax.h"
%include "gdcmSpacing.h"
%include "gdcmIconImageGenerator.h"
%include "gdcmIconImageFilter.h"

%feature("director") SimpleSubjectWatcher;
%include "gdcmSimpleSubjectWatcher.h"
%include "gdcmDICOMDIRGenerator.h"
%include "gdcmFileDerivation.h"
