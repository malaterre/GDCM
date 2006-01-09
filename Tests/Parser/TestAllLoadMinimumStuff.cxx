// generated file
#include "gdcmDataImages.h"

#include "gdcmDirectory.h"
#include "gdcmFileSeeker.h"
#include "gdcmDict.h"

// Just to remember the tag we''ll *have* to load
// - to read the pixels
// - to made a true DICOM browser

void TestLoadMinimumStuff(const std::string &filename)
{
  std::cerr << "UID of file: " << filename << std::endl;
  gdcm::FileSeeker f;
  f.SetFileName(filename);
  f.Open();
  f.Initialize();
  
/*
// Needed to be able to Load the Pixels

   0002 0010 UI 1 Transfer Syntax UID

   0028 0002                     // Samples per Pixel
   0028 0004                     // Photometric Interpretation
   0028 0006                     // Planar Configuration
   0028 0008                     // Number of Frames
   0028 0010                     // Rows
   0028 0011                     // Columns
   0028 0012                     // Planes
   0028 0030                     // Pixel Spacing
   0028 0100                     // Bits Allocated
   0028 0101                     // Bits Stored
   0028 0102                     // High Bit    
   0028 0103                     // Pixel Representation 
*/
  const gdcm::Tag siUID(0x0020,0x000d);
  
  const gdcm::Tag samplesPerPixel(0x0028,0x0002);
  const gdcm::Tag photomInterp(0x0028,0x0004); 
  const gdcm::Tag planConfig(0x0028,0x0006); 
  const gdcm::Tag nFrames(0x0028,0x0008);
  const gdcm::Tag nRows(0x0028,0x0010);
  const gdcm::Tag nCol(0x0028,0x0011);
  const gdcm::Tag nPlanes(0x0028,0x0012);
  const gdcm::Tag pixelSpacing(0x0028,0x0030);
  const gdcm::Tag bitsAllocated(0x0028,0x0100);
  const gdcm::Tag bitsStored(0x0028,0x0101);
  const gdcm::Tag highBit(0x0028,0x0102);
  const gdcm::Tag pixelRepresentation(0x0028,0x0103);
         
/*
// Needed whenever there is a Palette Color

0028 1100 US 3 Gray Lookup Table Descriptor (RET)
0028 1101 US 3 Red Palette Color Lookup Table Descriptor
0028 1102 US 3 Green Palette Color Lookup Table Descriptor
0028 1103 US 3 Blue Palette Color Lookup Table Descriptor
0028 1199 UI 1 Palette Color Lookup Table UID
0028 1200 OW 1 Gray Lookup Table Data (RET)
0028 1201 OW 1 Red Palette Color Lookup Table Data
0028 1202 OW 1 Green Palette Color Lookup Table Data
0028 1203 OW 1 Blue Palette Color Lookup Table Data
0028 1221 OW 1 Segmented Red Palette Color Lookup Table Data
0028 1222 OW 1 Segmented Green Palette Color Lookup Table Data
0028 1223 OW 1 Segmented Blue Palette Color Lookup Table Data
*/
  const gdcm::Tag grayLUTdescr(0x0028,0x1100);
  const gdcm::Tag redLUTdescr(0x0028,0x1101);
  const gdcm::Tag greenLUTdescr(0x0028,0x1102);
  const gdcm::Tag blueLUTdescr(0x0028,0x1103);
  const gdcm::Tag paletteColorLUT(0x0028,0x1199);
  const gdcm::Tag grayLUT(0x0028,0x1200);
  const gdcm::Tag redLUT(0x0028,0x1201);
  const gdcm::Tag greenLUT(0x0028,0x1202);
  const gdcm::Tag blueLUT(0x0028,0x1203);
  const gdcm::Tag segRedLUT(0x0028,0x1221);
  const gdcm::Tag segGreenLUT(0x0028,0x1222);
  const gdcm::Tag segBlueLUT(0x0028,0x1223);
  
/*
// Needed to display correctly grey-level images

0028 1050 DS 1-n Window Center
0028 1051 DS 1-n Window Width
0028 1052                    // Rescale Intercept
0028 1053                    // Rescale Slope
*/

  const gdcm::Tag windowCenter(0x0028,0x1050);
  const gdcm::Tag windowWidth(0x0028,0x1051);
  const gdcm::Tag rescaleSolpe(0x0028,0x1052);
  const gdcm::Tag rescaleInt(0x0028,0x1053);

/*
// Needed to create a DICOMDIR (or to browse a directory)

0010 0010 ""                     // Patient's Name
0010 0020 ""                     // Patient ID
0010 0030 ""                     // Patient's Birthdate
0010 0040 ""                     // Patient's Sex
0008 0020                        // Study Date       // Type 1C Conditional Element
0008 0030                        // Study Time       // Type 1C Conditional Element
0008 0050                        // Accession Number // Type 1C Conditional Element
0008 1030 ""                     // Study Description
0020 000d ""                     // Study Instance UID :
0020 0010 ""                     // Study ID :          
0008 0021 ""                     // Series Date
0008 0031 ""                     // Series Time
0008 0060 ""                     // Modality
0008 0080 ""                     // Institution Name  :  
0008 0081 ""                     // Institution Address :
0008 1010 ""                     // Station Name
0008 1050 ""                     // Performing Physician's Name
0008 103e ""                     // Series Description : 
0018 1030 ""                     // Protocol Name
0020 000e ""                     // Studys Instance UID :
0020 0011 "0"                    // Series Number :        
0008 0008 ""                     // Image Type
0008 0016 ""                     // SOP Class UID :   
0008 0018 ""                     // SOP Instance UID :
0008 0023 ""                     // Content Date
0008 0033 ""                     // Content Time
0018 1060 "0"                    // Trigger Time
0020 0013 "0"                    // Image Number
0020 0032 "1.0\1.0\1.0 "         // Image Position Patient
0020 0037 "1\0\0\0\1\0 "         // Image Orientation Patient
0020 0052 "0"                    // Frame of Reference UID
0020 1041 "0.0"                  // Slice Location
0020 4000 ""                     // Image Comments

0050 0004 "0"                    // Calibration Image
*/

  const gdcm::Tag patientName(0x0010,0x0010); // Patient's Name
  const gdcm::Tag patientID(0x0010,0x0020); // Patient ID
  const gdcm::Tag patientBirthDate(0x0010,0x0030); // Patient's Birthdate
  const gdcm::Tag patientSex(0x0010,0x0040); // Patient's Sex
  const gdcm::Tag studyDate(0x0008,0x0020);
  const gdcm::Tag studyTime(0x0008,0x0030);  
  const gdcm::Tag accessionNumber(0x0028,0x0002);
  const gdcm::Tag studyDescription(0x0008,0x1030);
  const gdcm::Tag studyInstanceUID(0x0020,0x000d);
  const gdcm::Tag studyID(0x0020,0x0010);
  const gdcm::Tag seriesDate(0x0020,0x0021);
  const gdcm::Tag seriesTime(0x0020,0x0031);
  const gdcm::Tag modality(0x0008,0x0060);
  const gdcm::Tag institutionName(0x0008,0x0080);
  const gdcm::Tag institutionAdress(0x0008,0x0081);
  const gdcm::Tag stationName(0x0008,0x1010);
  const gdcm::Tag performingPhysiciansName(0x0008,0x1050);
  const gdcm::Tag protocolName(0x0018,0x1030);
  const gdcm::Tag studysInstanceUID(0x0020,0x000e);
  const gdcm::Tag seriesNumber(0x0020,0x0011);
  const gdcm::Tag imageType(0x0008,0x0008);
  const gdcm::Tag sopClassUID(0x0008,0x0016);
  const gdcm::Tag sopInstanceUID(0x0008,0x0018);
  const gdcm::Tag contentTime(0x0008,0x0033);
  const gdcm::Tag contentDate(0x0008,0x0023);
  const gdcm::Tag triggerTime(0x0018,0x0002);
  const gdcm::Tag imageNumber(0x0020,0x0013);
  const gdcm::Tag imagePositionPatient(0x0020,0x0032);
  const gdcm::Tag imageOrientationPatient(0x0020,0x0037);
  const gdcm::Tag frameOfReferenceUID(0x0020,0x0052);
  const gdcm::Tag sliceLocation(0x0020,0x1041);
  const gdcm::Tag calibrationImage(0x0020,0x4000);


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

int TestAllLoadMinimumStuff(int argc, char *argv[])
{
  std::cerr << std::endl;
  if( argc == 2 )
    {
    const char *filename = argv[1];
    TestLoadMinimumStuff(filename);
    return 0;
    }

  // else
  int i = 0;
  const char *filename;
  while( (filename = gdcmDataImages[i]) )
    {
    TestLoadMinimumStuff( filename );
    ++i;
    }

  return 0;
}

/*
int TestAllLoadMinimumStuff_old(int argc, char *argv[])
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
*/
