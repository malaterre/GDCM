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
#include "gdcmImageHelper.h"
#include "gdcmMediaStorage.h"
#include "gdcmFile.h"
#include "gdcmDataSet.h"
#include "gdcmDataElement.h"
#include "gdcmItem.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmGlobal.h"
#include "gdcmDictEntry.h"
#include "gdcmDicts.h"
#include "gdcmAttribute.h"

namespace gdcm
{

bool GetOriginValueFromSequence(const DataSet& ds, const Tag& tfgs, std::vector<double> &ori)
{
    //  (0028,9110) SQ (Sequence with undefined length #=1)     # u/l, 1 PixelMeasuresSequence
    //      (fffe,e000) na (Item with undefined length #=2)         # u/l, 1 Item
    //        (0018,0050) DS [0.5]                                    #   4, 1 SliceThickness
    //        (0028,0030) DS [0.322\0.322]                            #  12, 2 PixelSpacing
    // <entry group="5200" element="9229" vr="SQ" vm="1" name="Shared Functional Groups Sequence"/>
    //const Tag tfgs(0x5200,0x9229);
    //const Tag tfgs(0x5200,0x9230);
    //assert( ds.FindDataElement( tfgs ) );
    if( !ds.FindDataElement( tfgs ) ) return false;
    const SequenceOfItems * sqi = ds.GetDataElement( tfgs ).GetSequenceOfItems();
    assert( sqi );
    // Get first item:
    const Item &item = sqi->GetItem(1);
    const DataSet & subds = item.GetNestedDataSet();
    // Plane position Sequence
    const Tag tpms(0x0020,0x9113);
    if( !subds.FindDataElement(tpms) ) return false;
    const SequenceOfItems * sqi2 = subds.GetDataElement( tpms ).GetSequenceOfItems();
    assert( sqi2 );
    const Item &item2 = sqi2->GetItem(1);
    const DataSet & subds2 = item2.GetNestedDataSet();
    // 
    const Tag tps(0x0020,0x0032);
    if( !subds2.FindDataElement(tps) ) return false;
    const DataElement &de = subds2.GetDataElement( tps );
    //assert( bv );
    gdcm::Attribute<0x0020,0x0032> at;
    at.SetFromDataElement( de );
    //at.Print( std::cout );
    ori.push_back( at.GetValue(0) );
    ori.push_back( at.GetValue(1) );
    ori.push_back( at.GetValue(2) );


    return true;
}

bool GetDirectionCosinesValueFromSequence(const DataSet& ds, const Tag& tfgs, std::vector<double> &dircos)
{
    //  (0028,9110) SQ (Sequence with undefined length #=1)     # u/l, 1 PixelMeasuresSequence
    //      (fffe,e000) na (Item with undefined length #=2)         # u/l, 1 Item
    //        (0018,0050) DS [0.5]                                    #   4, 1 SliceThickness
    //        (0028,0030) DS [0.322\0.322]                            #  12, 2 PixelSpacing
    // <entry group="5200" element="9229" vr="SQ" vm="1" name="Shared Functional Groups Sequence"/>
    //const Tag tfgs(0x5200,0x9229);
    //const Tag tfgs(0x5200,0x9230);
    //assert( ds.FindDataElement( tfgs ) );
    if( !ds.FindDataElement( tfgs ) ) return false;
    const SequenceOfItems * sqi = ds.GetDataElement( tfgs ).GetSequenceOfItems();
    assert( sqi );
    // Get first item:
    const Item &item = sqi->GetItem(1);
    const DataSet & subds = item.GetNestedDataSet();
    // Plane position Sequence
    const Tag tpms(0x0020,0x9116);
    if( !subds.FindDataElement(tpms) ) return false;
    const SequenceOfItems * sqi2 = subds.GetDataElement( tpms ).GetSequenceOfItems();
    assert( sqi2 );
    const Item &item2 = sqi2->GetItem(1);
    const DataSet & subds2 = item2.GetNestedDataSet();
    // 
    const Tag tps(0x0020,0x0037);
    if( !subds2.FindDataElement(tps) ) return false;
    const DataElement &de = subds2.GetDataElement( tps );
    //assert( bv );
    gdcm::Attribute<0x0020,0x0037> at;
    at.SetFromDataElement( de );
    //at.Print( std::cout );
    dircos.push_back( at.GetValue(0) );
    dircos.push_back( at.GetValue(1) );
    dircos.push_back( at.GetValue(2) );
    dircos.push_back( at.GetValue(3) );
    dircos.push_back( at.GetValue(4) );
    dircos.push_back( at.GetValue(5) );


    return true;
}

bool GetSpacingValueFromSequence(const DataSet& ds, const Tag& tfgs, std::vector<double> &sp)
{
    //  (0028,9110) SQ (Sequence with undefined length #=1)     # u/l, 1 PixelMeasuresSequence
    //      (fffe,e000) na (Item with undefined length #=2)         # u/l, 1 Item
    //        (0018,0050) DS [0.5]                                    #   4, 1 SliceThickness
    //        (0028,0030) DS [0.322\0.322]                            #  12, 2 PixelSpacing
    // <entry group="5200" element="9229" vr="SQ" vm="1" name="Shared Functional Groups Sequence"/>
    //const Tag tfgs(0x5200,0x9229);
    //const Tag tfgs(0x5200,0x9230);
    //assert( ds.FindDataElement( tfgs ) );
    if( !ds.FindDataElement( tfgs ) ) return false;
    const SequenceOfItems * sqi = ds.GetDataElement( tfgs ).GetSequenceOfItems();
    assert( sqi );
    // Get first item:
    const Item &item = sqi->GetItem(1);
    const DataSet & subds = item.GetNestedDataSet();
    // <entry group="0028" element="9110" vr="SQ" vm="1" name="Pixel Measures Sequence"/>
    const Tag tpms(0x0028,0x9110);
    if( !subds.FindDataElement(tpms) ) return false;
    const SequenceOfItems * sqi2 = subds.GetDataElement( tpms ).GetSequenceOfItems();
    assert( sqi2 );
    const Item &item2 = sqi2->GetItem(1);
    const DataSet & subds2 = item2.GetNestedDataSet();
    // <entry group="0028" element="0030" vr="DS" vm="2" name="Pixel Spacing"/>
    const Tag tps(0x0028,0x0030);
    if( !subds2.FindDataElement(tps) ) return false;
    const DataElement &de = subds2.GetDataElement( tps );
    //assert( bv );
    gdcm::Attribute<0x0028,0x0030> at;
    at.SetFromDataElement( de );
    //at.Print( std::cout );
    sp.push_back( at.GetValue(0) );
    sp.push_back( at.GetValue(1) );

    // Do the 3rd dimension zspacing:
    // <entry group="0018" element="0050" vr="DS" vm="1" name="Slice Thickness"/>
    const Tag tst(0x0018,0x0050);
    if( !subds2.FindDataElement(tst) ) return false;
    const DataElement &de2 = subds2.GetDataElement( tst );
    gdcm::Attribute<0x0018,0x0050> at2;
    at2.SetFromDataElement( de2 );
    //at2.Print( std::cout );
    sp.push_back( at2.GetValue(0) );

    return true;
}


/* Enhanced stuff looks like:

    (0020,9113) SQ (Sequence with undefined length #=1)     # u/l, 1 PlanePositionSequence
      (fffe,e000) na (Item with undefined length #=1)         # u/l, 1 Item
        (0020,0032) DS [73.5100815890831\-129.65028828174\189.777023529388] #  50, 3 ImagePositionPatient
      (fffe,e00d) na (ItemDelimitationItem)                   #   0, 0 ItemDelimitationItem
    (fffe,e0dd) na (SequenceDelimitationItem)               #   0, 0 SequenceDelimitationItem
    (0020,9116) SQ (Sequence with undefined length #=1)     # u/l, 1 PlaneOrientationSequence
      (fffe,e000) na (Item with undefined length #=1)         # u/l, 1 Item
        (0020,0037) DS [0.01604138687252\0.99942564964294\-0.0298495516180\0.0060454937629... # 102, 6 ImageOrientationPatient
      (fffe,e00d) na (ItemDelimitationItem)                   #   0, 0 ItemDelimitationItem
    (fffe,e0dd) na (SequenceDelimitationItem)               #   0, 0 SequenceDelimitationItem
    (0028,9110) SQ (Sequence with undefined length #=1)     # u/l, 1 PixelMeasuresSequence
      (fffe,e000) na (Item with undefined length #=2)         # u/l, 1 Item
        (0018,0050) DS [1]                                      #   2, 1 SliceThickness
        (0028,0030) DS [0.83333331346511\0.83333331346511]      #  34, 2 PixelSpacing
      (fffe,e00d) na (ItemDelimitationItem)                   #   0, 0 ItemDelimitationItem
    (fffe,e0dd) na (SequenceDelimitationItem)               #   0, 0 SequenceDelimitationItem
*/

std::vector<double> ImageHelper::GetOriginValue(File const & f)
{
  std::vector<double> ori;
  MediaStorage ms;
  ms.SetFromFile(f);
  const DataSet& ds = f.GetDataSet();

  if( ms == MediaStorage::EnhancedCTImageStorage
    ||  ms == MediaStorage::EnhancedMRImageStorage )
    {
    const Tag t1(0x5200,0x9229);
    const Tag t2(0x5200,0x9230);
    if( GetOriginValueFromSequence(ds,t1, ori) 
     || GetOriginValueFromSequence(ds, t2, ori) )
      {
      assert( ori.size() == 3 );
      return ori;
      }
    abort();
    }
  ori.resize( 3 );

  // else
  const Tag timagepositionpatient(0x0020, 0x0032);
  if( ds.FindDataElement( timagepositionpatient ) )
    {
    const DataElement& de = ds.GetDataElement( timagepositionpatient );
    Attribute<0x0020,0x0032> at = {{0,0,0}}; // default value if empty
    at.SetFromDataElement( de );
    for( unsigned int i = 0; i < at.GetNumberOfValues(); ++i )
      {
      ori[i] = at.GetValue(i);
      }
    }
  else
    {
    ori[0] = 0;
    ori[1] = 0;
    ori[2] = 0;
    }
  assert( ori.size() == 3 );
  return ori;
}

std::vector<double> ImageHelper::GetDirectionCosinesValue(File const & f)
{
  std::vector<double> dircos;
  MediaStorage ms;
  ms.SetFromFile(f);
  const DataSet& ds = f.GetDataSet();

  if( ms == MediaStorage::EnhancedCTImageStorage
    ||  ms == MediaStorage::EnhancedMRImageStorage )
    {
    const Tag t1(0x5200,0x9229);
    const Tag t2(0x5200,0x9230);
    if( GetDirectionCosinesValueFromSequence(ds,t1, dircos) 
     || GetDirectionCosinesValueFromSequence(ds, t2, dircos) )
      {
      assert( dircos.size() == 6 );
      return dircos;
      }
    abort();
    }
  dircos.resize( 6 );

  // else
  const Tag timageorientationpatient(0x0020, 0x0037);
  if( ds.FindDataElement( timageorientationpatient ) )
    {
    const DataElement& de = ds.GetDataElement( timageorientationpatient );
    Attribute<0x0020,0x0037> at = {{1,0,0,0,1,0}}; // default value if empty
    at.SetFromDataElement( de );
    for( unsigned int i = 0; i < at.GetNumberOfValues(); ++i )
      {
      dircos[i] = at.GetValue(i);
      }
    }
  else
    {
    dircos[0] = 1;
    dircos[1] = 0;
    dircos[2] = 0;
    dircos[3] = 0;
    dircos[4] = 1;
    dircos[5] = 0;
    }
  assert( dircos.size() == 6 );
  return dircos;
}

Tag ImageHelper::GetSpacingTagFromMediaStorage(MediaStorage const &ms)
{
  Tag t;

  switch(ms)
    {
  case MediaStorage::EnhancedMRImageStorage:
  case MediaStorage::EnhancedCTImageStorage:
    gdcmWarningMacro( "Enhanced image are not currently supported. Spacing will be wrong" );
  case MediaStorage::CTImageStorage:
  case MediaStorage::MRImageStorage:
    // (0028,0030) DS [2.0\2.0]                                #   8, 2 PixelSpacing
    t = Tag(0x0028,0x0030);
    break;
  case MediaStorage::ComputedRadiographyImageStorage:
  case MediaStorage::DigitalXRayImageStorageForPresentation:
  case MediaStorage::DigitalXRayImageStorageForProcessing:
  case MediaStorage::DigitalMammographyImageStorageForPresentation:
  case MediaStorage::DigitalMammographyImageStorageForProcessing:
  case MediaStorage::DigitalIntraoralXrayImageStorageForPresentation:
  case MediaStorage::DigitalIntraoralXRayImageStorageForProcessing:
  case MediaStorage::XRayAngiographicImageStorage:
  case MediaStorage::XRayRadiofluoroscopingImageStorage:
  case MediaStorage::XRayAngiographicBiPlaneImageStorageRetired:
    // (0018,1164) DS [0.5\0.5]                                #   8, 2 ImagerPixelSpacing
    t = Tag(0x0018,0x1164);
    break;
  default:
    gdcmWarningMacro( "Do not handle: " << ms );
    t = Tag(0xffff,0xffff);
    break;
    }
  return t;
}

Tag ImageHelper::GetZSpacingTagFromMediaStorage(MediaStorage const &ms)
{
  Tag t;

  switch(ms)
    {
  case MediaStorage::MRImageStorage:
  case MediaStorage::EnhancedMRImageStorage: // FIXME ERROR
    // (0018,0088) DS [3]                                      #   2, 1 SpacingBetweenSlices
    t = Tag(0x0018,0x0088);
    break;
  default:
    gdcmWarningMacro( "Do not handle Z spacing for: " << ms );
    t = Tag(0xffff,0xffff);
    break;
    }
  return t;
}

std::vector<double> ImageHelper::GetSpacingValue(File const & f)
{
  std::vector<double> sp;
  MediaStorage ms;
  ms.SetFromFile(f);
  const DataSet& ds = f.GetDataSet();

  if( ms == MediaStorage::EnhancedCTImageStorage
    ||  ms == MediaStorage::EnhancedMRImageStorage )
    {
    // <entry group="5200" element="9230" vr="SQ" vm="1" name="Per-frame Functional Groups Sequence"/>
    const Tag t1(0x5200,0x9229);
    const Tag t2(0x5200,0x9230);
    if( GetSpacingValueFromSequence(ds,t1, sp) 
      || GetSpacingValueFromSequence(ds, t2, sp) )
      {
      assert( sp.size() == 3 );
      return sp;
      }
    abort();
    }

  Tag spacingtag = GetSpacingTagFromMediaStorage(ms);
  if( spacingtag != Tag(0xffff,0xffff) && ds.FindDataElement( spacingtag ) )
    {
    const DataElement& de = ds.GetDataElement( spacingtag );
    const Global &g = GlobalInstance;
    const Dicts &dicts = g.GetDicts();
    const DictEntry &entry = dicts.GetDictEntry(de.GetTag());
    const VR & vr = entry.GetVR();
    assert( de.GetVR() == vr || de.GetVR() == VR::INVALID );
    switch(vr)
      {
    case VR::DS:
        {
        Element<VR::DS,VM::VM1_n> el;
        std::stringstream ss;
        const ByteValue *bv = de.GetByteValue();
        assert( bv );
        std::string s = std::string( bv->GetPointer(), bv->GetLength() );
        ss.str( s );
        // Stupid file: ct-mono2-8bit.dcm
        // The spacing is something like that: [0.2\0\0.200000]
        // I would need to throw an expection that VM is not compatible
        el.SetLength( entry.GetVM().GetLength() * entry.GetVR().GetSizeof() );
        el.Read( ss );
        for(unsigned long i = 0; i < el.GetLength(); ++i) 
          sp.push_back( el.GetValue(i) );
        assert( sp.size() == (unsigned int)entry.GetVM() );
        }
      break;
    default:
      abort();
      break;
      }
    }
  else
    {
    sp.push_back( 1.0 );
    sp.push_back( 1.0 );
    }
  assert( sp.size() == 2 );
  // Do Z:
  Tag zspacingtag = ImageHelper::GetZSpacingTagFromMediaStorage(ms);
  if( zspacingtag != Tag(0xffff,0xffff) && ds.FindDataElement( zspacingtag ) )
    {
    const DataElement& de = ds.GetDataElement( zspacingtag );
    if( de.IsEmpty() )
      {
      sp.push_back( 0.0 );
      }
    else
      {
      const Global &g = GlobalInstance;
      const Dicts &dicts = g.GetDicts();
      const DictEntry &entry = dicts.GetDictEntry(de.GetTag());
      const VR & vr = entry.GetVR();
      assert( de.GetVR() == vr || de.GetVR() == VR::INVALID );
      assert( entry.GetVM() == VM::VM1 );
      switch(vr)
        {
      case VR::DS:
          {
          Element<VR::DS,VM::VM1_n> el;
          std::stringstream ss;
          const ByteValue *bv = de.GetByteValue();
          assert( bv );
          std::string s = std::string( bv->GetPointer(), bv->GetLength() );
          ss.str( s );
          el.SetLength( entry.GetVM().GetLength() * entry.GetVR().GetSizeof() );
          el.Read( ss );
          for(unsigned long i = 0; i < el.GetLength(); ++i) 
            sp.push_back( el.GetValue(i) );
          //assert( sp.size() == entry.GetVM() );
          }
        break;
      default:
        abort();
        break;
        }
      }
    }
  else if( ds.FindDataElement( Tag(0x0028,0x0009) ) ) // Frame Increment Pointer
    {
    const DataElement& de = ds.GetDataElement( Tag(0x0028,0x0009) );
    gdcm::Attribute<0x0028,0x0009> at;
    at.SetFromDataElement( de );
    if( ds.FindDataElement( at.GetValue() ) )
      {
/*
$ dcmdump D_CLUNIE_NM1_JPLL.dcm" | grep 0028,0009
(0028,0009) AT (0054,0010)\(0054,0020)                  #   8, 2 FrameIncrementPointer
*/
      const DataElement& de2 = ds.GetDataElement( at.GetValue() );
      if( at.GetValue() == Tag(0x0018,0x1063) && at.GetNumberOfValues() == 1 )
        {
        Attribute<0x0018,0x1063> at2;
        at2.SetFromDataElement( de2 );
        sp.push_back( at2.GetValue() );
        }
      else
        {
        gdcmWarningMacro( "Dont know how to handle spacing for: " << de );
        sp.push_back( 0.0 );
        }
      }
    }
  else
    {
    sp.push_back( 0.0 );
    }

  assert( sp.size() == 3 );
  return sp;
}

void ImageHelper::SetSpacingValue(DataSet & ds, const std::vector<double> & spacing)
{
  MediaStorage ms;
  ms.SetFromDataSet(ds);
  assert( MediaStorage::IsImage( ms ) );

//  if( ms == MediaStorage::EnhancedMRImageStorage )
//    {
//    // <entry group="5200" element="9230" vr="SQ" vm="1" name="Per-frame Functional Groups Sequence"/>
//    const Tag tfgs(0x5200,0x9230);
//    if( !ds.FindDataElement( tfgs ) )
//      {
//      abort();
//      }
//    const SequenceOfItems * sqi = ds.GetDataElement( tfgs ).GetSequenceOfItems();
//    assert( sqi );
//    // Get first item:
//    const Item &item = sqi->GetItem(1);
//    const DataSet & subds = item.GetNestedDataSet();
//    // <entry group="0028" element="9110" vr="SQ" vm="1" name="Pixel Measures Sequence"/>
//    const Tag tpms(0x0028,0x9110);
//    if( !subds.FindDataElement(tpms) ) return sp;
//    const SequenceOfItems * sqi2 = subds.GetDataElement( tpms ).GetSequenceOfItems();
//    assert( sqi2 );
//    const Item &item2 = sqi2->GetItem(1);
//    const DataSet & subds2 = item2.GetNestedDataSet();
//    // <entry group="0028" element="0030" vr="DS" vm="2" name="Pixel Spacing"/>
//    const Tag tps(0x0028,0x0030);
//    if( !subds2.FindDataElement(tps) ) return sp;
//    const DataElement &de = subds2.GetDataElement( tps );
//    //assert( bv );
//    gdcm::Attribute<0x0028,0x0030> at;
//    at.SetFromDataElement( de );
//    //at.Print( std::cout );
//    sp.push_back( at.GetValue(0) );
//    sp.push_back( at.GetValue(1) );
//
//    // Do the 3rd dimension zspacing:
//    // <entry group="0018" element="0050" vr="DS" vm="1" name="Slice Thickness"/>
//    const Tag tst(0x0018,0x0050);
//    if( !subds2.FindDataElement(tst) ) return sp;
//    const DataElement &de2 = subds2.GetDataElement( tst );
//    gdcm::Attribute<0x0018,0x0050> at2;
//    at2.SetFromDataElement( de2 );
//    //at2.Print( std::cout );
//    sp.push_back( at2.GetValue(0) );
//
//    return;
//    }


  Tag spacingtag = GetSpacingTagFromMediaStorage(ms);
  Tag zspacingtag = GetZSpacingTagFromMediaStorage(ms);
  //std::vector<Tag> spacingtags;
  //spacingtags.push_back( spacingtag );
  //spacingtags.push_back( zspacingtag );
    {
    const Tag &currentspacing = spacingtag;
    if( currentspacing != Tag(0xffff,0xffff) )
      {
      DataElement de( currentspacing );
      const Global &g = GlobalInstance;
      const Dicts &dicts = g.GetDicts();
      const DictEntry &entry = dicts.GetDictEntry(de.GetTag());
      const VR & vr = entry.GetVR();
      const VM & vm = entry.GetVM(); (void)vm;
      assert( de.GetVR() == vr || de.GetVR() == VR::INVALID );
      switch(vr)
        {
      case VR::DS:
          {
          Element<VR::DS,VM::VM1_n> el;
          el.SetLength( entry.GetVM().GetLength() * vr.GetSizeof() );
          assert( entry.GetVM() == VM::VM2 );
          for( unsigned int i = 0; i < entry.GetVM().GetLength(); ++i)
            {
            el.SetValue( spacing[i], i );
            }
          //assert( el.GetValue(0) == spacing[0] && el.GetValue(1) == spacing[1] );
          std::stringstream os;
          el.Write( os );
          de.SetVR( VR::DS );
          de.SetByteValue( os.str().c_str(), os.str().size() );
          ds.Replace( de );
          }
        break;
      default:
        abort();
        }
      }
    }
    {
    const Tag &currentspacing = zspacingtag;
    if( currentspacing != Tag(0xffff,0xffff) )
      {
      DataElement de( currentspacing );
      const Global &g = GlobalInstance;
      const Dicts &dicts = g.GetDicts();
      const DictEntry &entry = dicts.GetDictEntry(de.GetTag());
      const VR & vr = entry.GetVR();
      const VM & vm = entry.GetVM(); (void)vm;
      assert( de.GetVR() == vr || de.GetVR() == VR::INVALID );
      switch(vr)
        {
      case VR::DS:
          {
          Element<VR::DS,VM::VM1_n> el;
          el.SetLength( entry.GetVM().GetLength() * vr.GetSizeof() );
          assert( entry.GetVM() == VM::VM1 );
          for( unsigned int i = 0; i < entry.GetVM().GetLength(); ++i)
            {
            el.SetValue( spacing[i+2], i );
            }
          //assert( el.GetValue(0) == spacing[0] && el.GetValue(1) == spacing[1] );
          std::stringstream os;
          el.Write( os );
          de.SetVR( VR::DS );
          de.SetByteValue( os.str().c_str(), os.str().size() );
          ds.Replace( de );
          }
        break;
      default:
        abort();
        }
      }
    }

}

bool ImageHelper::ComputeSpacingFromImagePositionPatient(const std::vector<double> & imageposition, std::vector<double> & spacing)
{
  if( imageposition.size() % 3 != 0 )
    {
    return false;
    }
  std::vector<double>::const_iterator it = imageposition.begin();
  //const double x0 = *it++;
  //const double y0 = *it++;
  //const double z0 = *it++;
  spacing[0] = spacing[1] = spacing[2] = 0.;
  for( ; it != imageposition.end(); ++it)
    {
    const double x = *it++;
    const double y = *it++;
    const double z = *it;
    spacing[0] += x;
    spacing[1] += y;
    spacing[2] += z;
    }
  int n = imageposition.size() / 3;
  spacing[0] /= n;
  spacing[1] /= n;
  spacing[2] /= n;

  return true;
}


}
