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
#include "gdcmSOPClassUIDToIOD.h"

namespace gdcm
{
  static const char * const SOPClassToIOD[][2] = {
{"1.2.840.10008.5.1.4.1.1.1" , ""},
{"1.2.840.10008.5.1.4.1.1.1.1" , "DX IOD (see B.5.1.1)"},
{"1.2.840.10008.5.1.4.1.1.1.1.1" , "DX IOD (see B.5.1.1)"},
{"1.2.840.10008.5.1.4.1.1.1.2" , "Digital Mammography X Ray Image IOD Modules"}, // (see B.5.1.2)
{"1.2.840.10008.5.1.4.1.1.1.2.1" , "Digital Mammography X Ray Image IOD Modules"}, // (see B.5.1.2)
{"1.2.840.10008.5.1.4.1.1.1.3" , "Digital Intra Oral X Ray Image IOD Modules"}, // (see B.5.1.3)
{"1.2.840.10008.5.1.4.1.1.1.3.1" , "Digital Intra Oral X Ray Image IOD Modules"}, // (see B.5.1.3)
{"1.2.840.10008.5.1.4.1.1.2" , ""},
{"1.2.840.10008.5.1.4.1.1.2.1" , "Enhanced CT Image IOD Modules"}, // (see B.5.1.7)
{"1.2.840.10008.5.1.4.1.1.3.1" , ""},
{"1.2.840.10008.5.1.4.1.1.4" , ""},
{"1.2.840.10008.5.1.4.1.1.4.1" , "Enhanced MR Image IOD Modules"}, // (see B.5.1.6)
{"1.2.840.10008.5.1.4.1.1.4.2" , "MR Spectroscopy IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.6.1" , ""},
{"1.2.840.10008.5.1.4.1.1.7" , ""},
{"1.2.840.10008.5.1.4.1.1.7.1" , "Multi Frame Single Bit SC Image IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.7.2" , "Multi Frame Grayscale Byte SC Image IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.7.3" , "Multi Frame Grayscale Word SC Image IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.7.4" , "Multi Frame True Color SC Image IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.9.1.1" , "12 Lead ECG IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.9.1.2" , "General ECG IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.9.1.3" , "Ambulatory ECG IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.9.2.1" , "Hemodynamic IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.9.3.1" , "Cardiac Electrophysiology Waveform"},
{"1.2.840.10008.5.1.4.1.1.9.4.1" , "Basic Voice Audio IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.11.1" , "Grayscale Softcopy Presentation State IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.11.2" , "Color Softcopy Presentation State"},
{"1.2.840.10008.5.1.4.1.1.11.3" , "Pseudo-Color Softcopy Presentation State"},
{"1.2.840.10008.5.1.4.1.1.11.4" , "Blending Softcopy Presentation State"},
{"1.2.840.10008.5.1.4.1.1.12.1" , ""},
{"1.2.840.10008.5.1.4.1.1.12.1.1" , ""},
{"1.2.840.10008.5.1.4.1.1.12.2" , ""},
{"1.2.840.10008.5.1.4.1.1.12.2.1" , ""},
{"1.2.840.10008.5.1.4.1.1.13.1.1" , "X-Ray 3D Angiographic Image"},
{"1.2.840.10008.5.1.4.1.1.13.1.2" , "X-Ray 3D Craniofacial Image"},
{"1.2.840.10008.5.1.4.1.1.20" , ""},
{"1.2.840.10008.5.1.4.1.1.66" , "Raw Data IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.66.1" , "Spatial Registration IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.66.2" , "Spatial Fiducials IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.66.3" , "Deformable Spatial Registration"},
{"1.2.840.10008.5.1.4.1.1.66.4" , "Segmentation IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.67" , "Real World Value Mapping"},
{"1.2.840.10008.5.1.4.1.1.77.1.1" , "VL Endoscopic Image"},
{"1.2.840.10008.5.1.4.1.1.77.1.1.1" , "Video Endoscopic Image IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.77.1.2" , "VL Microscopic Image"},
{"1.2.840.10008.5.1.4.1.1.77.1.2.1" , "Video Microscopic Image"},
{"1.2.840.10008.5.1.4.1.1.77.1.3" , "VL Slide-Coordinates Microscopic Image"},
{"1.2.840.10008.5.1.4.1.1.77.1.4" , "VL Photographic Image IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.77.1.4.1" , "Video Photographic Image"},
{"1.2.840.10008.5.1.4.1.1.77.1.5.1" , "Ophthalmic Photography 8 Bit Image"},
{"1.2.840.10008.5.1.4.1.1.77.1.5.2" , "Ophthalmic Photography 16 Bit Image"},
{"1.2.840.10008.5.1.4.1.1.77.1.5.3" , "Stereometric Relationship"},
{"1.2.840.10008.5.1.4.1.1.77.1.5.4" , "Ophthalmic Tomography Image"},
{"1.2.840.10008.5.1.4.1.1.88.11" , "Basic Text SR IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.88.22" , "Enhanced SR IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.88.33" , "Comprehensive SR IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.88.40" , "Procedure Log"},
{"1.2.840.10008.5.1.4.1.1.88.50" , "Mammography CAD SR IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.88.59" , "Key Object Selection Document IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.88.65" , "Chest CAD SR IOD"},
{"1.2.840.10008.5.1.4.1.1.88.67" , "X-Ray Radiation Dose SR"},
{"1.2.840.10008.5.1.4.1.1.104.1" , "Encapsulated PDF IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.128" , ""},
{"1.2.840.10008.5.1.4.1.1.481.1" , ""},
{"1.2.840.10008.5.1.4.1.1.481.2" , ""},
{"1.2.840.10008.5.1.4.1.1.481.3" , ""},
{"1.2.840.10008.5.1.4.1.1.481.4" , ""},
{"1.2.840.10008.5.1.4.1.1.481.5" , ""},
{"1.2.840.10008.5.1.4.1.1.481.6" , ""},
{"1.2.840.10008.5.1.4.1.1.481.7" , ""},
{"1.2.840.10008.5.1.4.1.1.481.8" , "RT Ion Plan IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.481.9" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.5" , ""},
{"1.2.840.10008.5.1.4.1.1.6" , ""},
{"1.2.840.10008.5.1.4.1.1.3" , ""},
{"1.2.840.10008.5.1.4.1.1.12.3" , ""},

#if 0
{"1.2.840.10008.1.3.10" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.1" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.1.1" , "DX IOD"},
{"1.2.840.10008.5.1.4.1.1.1.1.1" , "DX IOD"},
{"1.2.840.10008.5.1.4.1.1.1.2" , "Digital Mammography IOD"},
{"1.2.840.10008.5.1.4.1.1.1.2.1" , "Digital Mammography IOD"},
{"1.2.840.10008.5.1.4.1.1.1.3" , "Digital Intra-oral X-Ray IOD"},
{"1.2.840.10008.5.1.4.1.1.1.3.1" , "Digital Intra-oral X-Ray IOD"},
{"1.2.840.10008.5.1.4.1.1.2" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.2.1" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.3.1" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.4" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.4.1" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.4.2" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.6.1" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.7" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.7.1" , "Multi-frame Single Bit Secondary Capture Image"},
{"1.2.840.10008.5.1.4.1.1.7.2" , "Multi-frame Grayscale Byte Secondary Capture Image"},
{"1.2.840.10008.5.1.4.1.1.7.3" , "Multi-frame Grayscale Word Secondary Capture Image"},
{"1.2.840.10008.5.1.4.1.1.7.4" , "Multi-frame True Color Secondary Capture Image"},
{"1.2.840.10008.5.1.4.1.1.9.1.1" , "12-lead ECG Waveform "},
{"1.2.840.10008.5.1.4.1.1.9.1.2" , "General ECG Waveform "},
{"1.2.840.10008.5.1.4.1.1.9.1.3" , "Ambulatory ECG Waveform"},
{"1.2.840.10008.5.1.4.1.1.9.2.1" , "Hemodynamic Waveform"},
{"1.2.840.10008.5.1.4.1.1.9.3.1" , "Cardiac Electrophysiology Waveform"},
{"1.2.840.10008.5.1.4.1.1.9.4.1" , "Basic Voice Audio Waveform"},
{"1.2.840.10008.5.1.4.1.1.11.1" , "Grayscale Softcopy Presentation State Storage"},
{"1.2.840.10008.5.1.4.1.1.11.2" , "Color Softcopy Presentation State"},
{"1.2.840.10008.5.1.4.1.1.11.3" , "Pseudo-Color Softcopy Presentation State"},
{"1.2.840.10008.5.1.4.1.1.11.4" , "Blending Softcopy Presentation State"},
{"1.2.840.10008.5.1.4.1.1.12.1" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.12.1.1" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.12.2" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.12.2.1" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.13.1.1" , "X-Ray 3D Angiographic Image"},
{"1.2.840.10008.5.1.4.1.1.13.1.2" , "X-Ray 3D Craniofacial Image"},
{"1.2.840.10008.5.1.4.1.1.20" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.66" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.66.1" , "Spatial Registration IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.66.2" , "Spatial Fiducials IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.66.3" , "Deformable Spatial Registration"},
{"1.2.840.10008.5.1.4.1.1.66.4" , "Segmentation IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.67" , "Real World Value Mapping"},
{"1.2.840.10008.5.1.4.1.1.77.1.1" , "VL Endoscopic Image"},
{"1.2.840.10008.5.1.4.1.1.77.1.1.1" , "Video Endoscopic Image"},
{"1.2.840.10008.5.1.4.1.1.77.1.2" , "VL Microscopic Image"},
{"1.2.840.10008.5.1.4.1.1.77.1.2.1" , "Video Microscopic Image"},
{"1.2.840.10008.5.1.4.1.1.77.1.3" , "VL Slide-Coordinates Microscopic Image"},
{"1.2.840.10008.5.1.4.1.1.77.1.4" , "VL Photographic Image"},
{"1.2.840.10008.5.1.4.1.1.77.1.4.1" , "Video Photographic Image"},
{"1.2.840.10008.5.1.4.1.1.77.1.5.1" , "Ophthalmic Photography 8 Bit Image"},
{"1.2.840.10008.5.1.4.1.1.77.1.5.2" , "Ophthalmic Photography 16 Bit Image"},
{"1.2.840.10008.5.1.4.1.1.77.1.5.3" , "Stereometric Relationship"},
{"1.2.840.10008.5.1.4.1.1.77.1.5.4" , "Ophthalmic Tomography Image"},
{"1.2.840.10008.5.1.4.1.1.88.11" , "Basic Text SR"},
{"1.2.840.10008.5.1.4.1.1.88.22" , "Enhanced SR"},
{"1.2.840.10008.5.1.4.1.1.88.33" , "Comprehensive SR IOD Modules"},
{"1.2.840.10008.5.1.4.1.1.88.40" , "Procedure Log"},
{"1.2.840.10008.5.1.4.1.1.88.50" , "Mammography CAD SR IOD"},
{"1.2.840.10008.5.1.4.1.1.88.59" , "Key Object Selection Document"},
{"1.2.840.10008.5.1.4.1.1.88.65" , "Chest CAD SR IOD"},
{"1.2.840.10008.5.1.4.1.1.88.67" , "X-Ray Radiation Dose SR"},
{"1.2.840.10008.5.1.4.1.1.104.1" , "Encapsulated PDF IOD"},
{"1.2.840.10008.5.1.4.1.1.128" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.481.1" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.481.2" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.481.3" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.481.4" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.481.5" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.481.6" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.481.7" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.481.8" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.1.1.481.9" , "IOD defined in PS 3.3"},
{"1.2.840.10008.5.1.4.38.1" , "Hanging Protocol IOD"},
{"1.2.840.10008.5.1.4.1.1.5" , ""},
{"1.2.840.10008.5.1.4.1.1.6" , ""},
{"1.2.840.10008.5.1.4.1.1.3" , ""},
{"1.2.840.10008.5.1.4.1.1.12.3" , ""},
#endif

{ 0, 0 }
};

unsigned int SOPClassUIDToIOD::GetNumberOfSOPClassToIOD()
{
  static const unsigned int n = sizeof( SOPClassToIOD ) / sizeof( *SOPClassToIOD );
  assert( n > 0 );
  return n - 1;
}

const char *SOPClassUIDToIOD::GetIOD(UIDs const & uid)
{
//  std::ifstream is(  );
//
//  char buf[BUFSIZ];
//  XML_Parser parser = XML_ParserCreate(NULL);
//  int done;
//  //int depth = 0;
//  XML_SetUserData(parser, this);
//  XML_SetElementHandler(parser, startElement, endElement);
//  XML_SetCharacterDataHandler(parser, characterDataHandler);
//  int ret = 0;
//  do {
//    is.read(buf, sizeof(buf));
//    size_t len = is.gcount();
//    done = len < sizeof(buf);
//    if (XML_Parse(parser, buf, len, done) == XML_STATUS_ERROR) {
//      fprintf(stderr,
//        "%s at line %" XML_FMT_INT_MOD "u\n",
//        XML_ErrorString(XML_GetErrorCode(parser)),
//        XML_GetCurrentLineNumber(parser));
//      ret = 1; // Mark as error
//      done = 1; // exit while
//    }
//  } while (!done);
//  XML_ParserFree(parser);
//  is.close();
  typedef const char* const (*SOPClassUIDToIODType)[2];
  SOPClassUIDToIODType p = SOPClassToIOD;
  const char *sopclassuid = uid.GetString();
  
  // FIXME I think we can do binary search
  while( (*p)[0] && strcmp( (*p)[0] , sopclassuid ) != 0 )
    {
    ++p;
    }
  return (*p)[1];
}

}

