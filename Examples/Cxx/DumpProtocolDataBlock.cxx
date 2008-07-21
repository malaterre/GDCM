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
 * In some GE MEDICAL SYSTEMS image one can find a Data Element: 0025,xx10,GEMS_SERS_01
 * which is documented as Protocol Data Block (compressed).
 * in fact this is a simple text format compressed using the gzip algorithm
 *
 * Typically one could do:
 *
 *   $ gdcmraw -i input.dcm -o output.raw -t 0025,101b 
 *
 * Skip the binary length (little endian encoding):
 *
 *   $ dd bs=4 skip=1 if=output.raw of=foo 
 *
 * Check file type:
 *
 *   $ file foo
 *   foo: gzip compressed data, was "Ex421Ser8Scan1", from Unix
 *
 * Gunzip !
 *   $ gzip -dc < foo > bar
 *   $ cat bar
 *
 * THANKS to: John Reiser (BitWagon.com) for hints
 */
#include "gdcmReader.h"
#include "gdcmTag.h"
#include "gdcmDataSet.h"
#include "gdcmPrivateTag.h"

#include "gdcmDeflateStream.h"

int readprotocoldatablock(const char *input, size_t inputlen)
{
  // First 4 bytes are the length (again)
  uint32_t len = *(uint32_t*)input;
  std::cout << len << "," << inputlen << std::endl;
  if( len + 4 == inputlen + 1 )
    {
    std::cout << "gzip stream was padded with an extra 0 \n";
    }
  else if( len + 4 == inputlen )
    {
    std::cout << "gzip stream was not padded with an extra 0 \n";
    }
  else
    {
    return 1;
    }
  // Alright we need to check if the binary blob was padded, if padded we need to 
  // discard the trailing \0 to please gzip:
  std::string str( input + 4, input + len );
  std::istringstream is( str );

  zlib_stream::zip_istream gzis( is );

//  if (gzis.is_gzip())
//    {
//    std::cout<<"crc check: "<<( gzis.check_crc() ? "ok" : "failed");
//    std::cout << std::endl;
//    }

  std::string out;
  //while( gzis >> out )
  while( std::getline(gzis , out ) )
    {
    std::cout << out << std::endl;
    }
  //std::cout << out.size();

  return 0;
}

int main(int argc, char *argv [])
{
  if( argc < 2 ) return 1;
  const char *filename = argv[1];
  gdcm::Reader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }
  const gdcm::DataSet& ds = reader.GetFile().GetDataSet();

  const gdcm::PrivateTag tprotocoldatablock(0x0025,0x1b,"GEMS_SERS_01");
  if( !ds.FindDataElement( tprotocoldatablock) ) return 1;
  const gdcm::DataElement& protocoldatablock= ds.GetDataElement( tprotocoldatablock);
  if ( protocoldatablock.IsEmpty() ) return 1;
  const gdcm::ByteValue * bv = protocoldatablock.GetByteValue();

  std::cout << "Dumping: " << tprotocoldatablock << std::endl;
  int ret = readprotocoldatablock( bv->GetPointer(), bv->GetLength() );

  return ret;
}

/*
 * Harvested data:
 * A lot of them are still non-obvisous (ETL -> Echo Train Length...)
 
ANREF "IC"
ANREF "NA"
ANREF "SN"
AUTOCF "Water"
AUTOSCIC "0"
AUTOSCIC "2"
AUTOSHIM "Auto"
AUTOSHIM "Off"
AUTOSHIM "Yes"
AUTOSUBOPTIONS "0"
AUTOTRGTYPE "0"
AUTOTRIGWIN "0"
AUTOVOICE "0"
B4PAUSE "0"
BPMMODE "0"
BWRT "0"
BWRT "-1"
CLOC1 "0.0"
CLOC1 "L4.7"
CLOC1 "L5.9"
CLOC2 "0.0"
CLOC2 "P20.0"
CLOC2 "P42.2"
CLOC2 "P44.5"
CLOC3 "0.0"
CLOC3 "S7.0"
CLOC3 "S8.2"
COIL "5GP"
COIL "8HRBRAIN"
COIL "HEAD"
COIL "LOOP2CM"
CONTAG "GAD"
CONTAM "10    GAD"
CONTAM "No    "
CONTAM "Yes   "
CONTRAST "No"
CONTRAST "Yes"
DELACQ "Minimum"
DUMACQ "0"
ELOC1 "L12.4"
ELOC1 "L142.9"
ELOC1 "L1.6"
ELOC1 "L2.2"
ELOC1 "L4.9"
ELOC1 "L5.9"
ELOC1 "L80.1"
ELOC1 "L84.1"
ELOC1 "L99.3"
ELOC1 "S65.4"
ELOC1 "S66.5"
ELOC1 "S89.0"
ELOC2 "0.0"
ELOC2 "A18.3"
ELOC2 "A43.5"
ELOC2 "A79.2"
ELOC2 "A87.6"
ELOC2 "L6.9"
ELOC2 "P27.4"
ELOC2 "P38.8"
ELOC2 "P48.8"
ELOC2 "P49.4"
ELOC3 "A12.8"
ELOC3 "I111.9"
ELOC3 "I27.7"
ELOC3 "I7.1"
ELOC3 "P21.2"
ELOC3 "P31.1"
ELOC3 "S12.3"
ELOC3 "S1.7"
ELOC3 "S31.8"
ELOC3 "S5.4"
ELOC3 "S7.0"
ELOC3 "S9.8"
ENTRY "Head First"
ETL "17"
ETL "2"
ETL "24"
ETL "3"
ETL "6"
ETL "8"
ETL "9"
FILTCHOICE "None"
FLDIR "Slice"
FLIPANG "12"
FLIPANG "17"
FLIPANG "20"
FLIPANG "36"
FLIPANG "8"
FLIPANG "90"
FOV "12"
FOV "14"
FOV "24"
FOV "24.0"
FOV "3"
FOV "30"
FOV "4"
FOV "6"
FOV "8"
FOVCNT1 "0.0"
FOVCNT2 "0.0"
FOVCNT2 "P21.2"
FOVCNT2 "P31.1"
GRADMODE "WHOLE"
GRADMODE "ZOOM"
GRIP_NUMPSCVOL "0"
GRIP_NUMSLGROUPS "0"
GRIP_NUMSLGROUPS "1"
GRIP_PSCVOL1 "0"
GRIP_PSCVOL2 "0"
GRIP_PSCVOLFOV "0"
GRIP_PSCVOLFOV "0.000000"
GRIP_PSCVOLTHICK "0"
GRIP_PSCVOLTHICK "0.000000"
GRIP_SATGROUP1 "0"
GRIP_SATGROUP2 "0"
GRIP_SATGROUP3 "0"
GRIP_SATGROUP4 "0"
GRIP_SATGROUP5 "0"
GRIP_SATGROUP6 "0"
GRIP_SLGROUP1 "0.000000 -21.170785 -13.463666 0.000000 0.000000 1.000000 1.000000 0.000000 0.000000 0.000000 -1.000000 0.000000 1 0.000000 1 0"
GRIP_SLGROUP1 "0.000000 -31.122005 2.926577 0.000000 0.000000 1.000000 0.000000 1.000000 0.000000 1.000000 0.000000 0.000000 26 0.000000 1 0"
GRIP_SLGROUP1 "-13.163267 0.000000 25.592358 0.005670 0.000000 -0.999984 0.999984 0.000000 0.005670 0.000000 -1.000000 0.000000 56 0.000000 1 0 1"
GRIP_SLGROUP1 "3.135807 14.667716 -32.340976 -0.997518 0.043626 0.055276 -0.056814 -0.962372 -0.265728 0.041603 -0.268209 0.962462 1 0.000000 1 0 1"
GRIP_SPECTRO "0"
GRIP_TRACKER "0"
GRXOPT "0"
GRXOPT "2"
IEC_ACCEPT "ON"
IMODE "2D"
IMODE "3D"
INITSTATE "0"
IOPT "EDR, Fast, IrP"
IOPT "EPI, FMRI"
IOPT "Fast, IrP"
IOPT "Fast, ZIP512, FR"
IOPT "FC, EDR, TRF, Fast, ZIP512"
IOPT "FC, VBw, EDR"
IOPT "None"
IOPT "NPW, Seq, VBw, TRF, Fast"
IOPT "NPW, TRF, Fast, ZIP512, FR"
IOPT "NPW, VBw, EDR, Fast, ZIP2"
IOPT "NPW, VBw, Fast"
IOPT "NPW, ZIP512"
IOPT "TRF, Fast"
IOPT "VBw, EDR, Fast"
IOPT "VBw, Fast"
MASKPAUSE "0"
MASKPHASE "0"
MATRIXX "192"
MATRIXX "256"
MATRIXX "288"
MATRIXX "320"
MATRIXX "416"
MATRIXX "512"
MATRIXX "64"
MATRIXY "128"
MATRIXY "160"
MATRIXY "192"
MATRIXY "224"
MATRIXY "256"
MATRIXY "320"
MATRIXY "64"
MONSAR "y"
NECHO "1"
NEX "1.00"
NEX "1.50"
NEX "2.00"
NEX "3.00"
NEX "4.00"
NOSLC "1"
NOSLC "12"
NOSLC "15"
NOSLC "19"
NOSLC "20"
NOSLC "21"
NOSLC "24"
NOSLC "26"
NOSLC "56"
NOTES ".pn/_2"
NOTES ".pn/_3"
NOTES ".pn/_4"
NUMACCELFACTOR "1.00"
NUMACCELFACTOR "Recommended"
NUMACQS "0"
NUMACQS "2"
NUMSHOTS "1"
OVLPLOC "0"
PAUSEDELMASKACQ "1"
PDGMSTR "None"
PHASEASSET "1.00"
PHASECORR "No"
PHASECORR "Yes"
PHASEFOV "0.75"
PHASEFOV "1.00"
PLANE "3-PLANE"
PLANE "AXIAL"
PLANE "OBLIQUE"
PLUG "0"
PLUG "11"
PLUG "14"
PLUG "22"
PLUG "23"
PLUG "45"
PLUG "5"
PLUG "6"
PLUG "9"
POSITION "Prone"
POSITION "Supine"
PRESETDELAY "0.0"
PSDNAME "fse-xl"
PSDTRIG "0"
PSEQ "FRFSE-XL"
PSEQ "FSE-XL"
PSEQ "Gradient Echo"
PSEQ "IR"
PSEQ "Localizer"
PSEQ "SPGR"
PSEQ "Spin Echo"
RBW "12.50"
RBW "14.71"
RBW "15.63"
RBW "17.86"
RBW "20.83"
RBW "22.73"
RBW "25.00"
RBW "31.25"
SATLOCZ1 "9990"
SATLOCZ2 "9990"
SATTHICKZ1 "40.0"
SATTHICKZ2 "40.0"
SEDESC "3D FSPGR IR"
SEDESC "3DIR PREP"
SEDESC "3 plane loc"
SEDESC "AX FSE T1"
SEDESC "AX FSE T2"
SEDESC "AX T2*"
SEDESC "FATSAT T2 FSE Scout"
SEDESCFLAG "1"
SEDESC "LOCALIZER-RATCOIL"
SEDESC "O-Ax FATSAT T2 FSE high Res"
SEDESC "Oblique PD AX"
SEDESC "Oblique STIR"
SEDESC "Oblique T1 AX +C"
SEDESC "Oblique T1-SAG"
SEDESC "Oblique T1-SAG+C"
SEDESC "Oblique T2 AX."
SEDESC "O-Cor T1 "
SEDESC "RUN 1"
SEDESC "SPGR3D-HRES-Brasch"
SEDESC "SPGR3D-LRES-Brasch"
SEPSERIES "0"
SL3PLANE "0"
SL3PLANE "1"
SL3PLANE1 "0"
SL3PLANE1 "5"
SL3PLANE2 "0"
SL3PLANE2 "5"
SL3PLANE3 "0"
SL3PLANE3 "5"
SLABLOC "128"
SLABLOC "144"
SLABLOC "64"
SLABLOC "80"
SLICEASSET "1.00"
SLICEORDER "1"
SLOC1 "I35.2"
SLOC1 "I59.6"
SLOC1 "I93.4"
SLOC1 "L13.9"
SLOC1 "L1.6"
SLOC1 "L2.1"
SLOC1 "L5.0"
SLOC1 "L5.9"
SLOC1 "L84.1"
SLOC1 "L85.9"
SLOC1 "L99.2"
SLOC1 "R86.3"
SLOC2 "0.0"
SLOC2 "A11.0"
SLOC2 "A115.0"
SLOC2 "A79.2"
SLOC2 "A80.8"
SLOC2 "P34.4"
SLOC2 "P37.0"
SLOC2 "P46.5"
SLOC2 "P50.2"
SLOC3 "I27.8"
SLOC3 "I37.0"
SLOC3 "I7.1"
SLOC3 "S12.3"
SLOC3 "S163.1"
SLOC3 "S1.7"
SLOC3 "S5.4"
SLOC3 "S7.0"
SLPERLOC "274"
SLTHICK "0.2"
SLTHICK "0.7"
SLTHICK "1.2"
SLTHICK "1.3"
SLTHICK "3.0"
SLTHICK "4.0"
SLTHICK "5.0"
SLTHICK "5.5"
SPC "0.0"
SPC "1.5"
SPCPERPLANE1 "0.0"
SPCPERPLANE1 "1.5"
SPCPERPLANE2 "0.0"
SPCPERPLANE2 "1.5"
SPCPERPLANE3 "0.0"
SPCPERPLANE3 "1.5"
STATION "0"
SUPPTQ "1"
SWAPPF "A/P"
SWAPPF "R/L"
SWAPPF "S/I"
SWAPPF "Unswap"
TAG_SPACE "7"
TAG_TYPE "None"
TBLDELTA "0.00"
TE "100.0"
TE "102.0"
TE "15.0"
TE "30.0"
TE "50.0"
TE "Min Full"
TE "Minimum"
TI "150"
TI "450"
TI "500"
TOTALNOSTATION "0"
TR "2000.0"
TR "3000.0"
TR "4000.0"
TR "4125.0"
TR "4575.0"
TR "475.0"
TR "500.0"
TR "5200.0"
TR "525.0"
TR "5325.0"
TR "6600.0"
TRACKLEN "200.0"
TRACKTHICK "20.0"
TRACTIVE "0"
TRACTIVE "4"
TRICKSIMG "1"
TRREST "0"
TRREST "4"
USERCV0 "0.00"
USERCV0 "1.00"
USERCV21 "0.00"
USERCV23 "100.00"
USERCV4 "0.00"
USERCV6 "0.00"
USERCV7 "0.00"
USERCV_MASK "0"
USERCV_MASK "1"
USERCV_MASK "128"
USERCV_MASK "192"
USERCV_MASK "2097344"
USERCV_MASK "6144"
USERCV_MASK "64"
USERCV_MASK "8388688"
VIEWORDER "1"

*/
