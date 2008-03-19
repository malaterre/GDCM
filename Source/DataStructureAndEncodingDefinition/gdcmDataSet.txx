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
#ifndef __gdcmDataSet_txx
#define __gdcmDataSet_txx

#include "gdcmByteValue.h"
#include "gdcmParseException.h"

namespace gdcm
{
  template <typename TDE, typename TSwap>
  std::istream &DataSet::ReadNested(std::istream &is) {
    DataElement de;
    const Tag itemDelItem(0xfffe,0xe00d);
    assert( de.GetTag() != itemDelItem ); // precondition before while loop
    try
      {
      while( de.Read<TDE,TSwap>(is) && de.GetTag() != itemDelItem  ) // Keep that order please !
        {
        //std::cerr << "DEBUG Nested: " << de << std::endl;
        DES.insert( de );
        }
      }
    catch(ParseException &pe)
      {
      if( pe.GetLastElement().GetTag() == Tag(0xfffe,0xe0dd) )
        {
        //  BogusItemStartItemEnd.dcm
        gdcmWarningMacro( "SQ End found but no no Item end found" );
        de.SetTag( itemDelItem );
        is.seekg( -4, std::ios::cur );
        }
      else
        {
        // MR_Philips_Intera_PrivateSequenceExplicitVR_in_SQ_2001_e05f_item_wrong_lgt_use_NOSHADOWSEQ.dcm
        // Need to rethrow the exception...sigh
        throw pe;
        }
      }
    assert( de.GetTag() == itemDelItem );
    //std::cerr << "Finish nested" << std::endl;
    return is;
}

  template <typename TDE, typename TSwap>
  std::istream &DataSet::Read(std::istream &is) {
    DataElement de;
    while( !is.eof() && de.Read<TDE,TSwap>(is) )
      {
      //std::cerr << "DEBUG:" << de << std::endl;
      //assert( de.GetTag() != Tag(0,0) );
      DES.insert( de );
      //if ( de.GetTag() == Tag(0x0020,0x000e) ) break;
      }
      //std::cerr << "finsih"  << std::endl;
    return is;
  }

  template <typename TDE, typename TSwap>
  std::istream &DataSet::ReadUpToTag(std::istream &is, const Tag &t) {
    DataElement de;
    while( !is.eof() && de.Read<TDE,TSwap>(is) )
      {
      //assert( de.GetTag() != Tag(0,0) );
      DES.insert( de );
      // tag was found, we can exit the loop:
      if ( de.GetTag() == t ) break;
      }
    return is;
  }

  template <typename TDE, typename TSwap>
  std::istream &DataSet::ReadWithLength(std::istream &is, VL &length) {
    //return is.seekg(length, std::ios::cur);
    DataElement de;
    VL l = 0;
    //std::cout << "ReadWithLength Length: " << length << std::endl;
    VL locallength = length;
    try
      {
      while( l != locallength && de.Read<TDE,TSwap>(is))
        {
        //std::cout << "Nested: " << de << std::endl;
#ifndef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
        assert( de.GetTag() != Tag(0xfffe,0xe000) ); // We should not be reading the next item...
#endif
        DES.insert( de );
        l += de.GetLength<TDE>();
        //std::cout << "l:" << l << std::endl;
        //assert( !de.GetVL().IsUndefined() );
        //std::cerr << "DEBUG: " << de.GetTag() << " "<< de.GetLength() << 
        //  "," << de.GetVL() << "," << l << std::endl;
        // Bug_Philips_ItemTag_3F3F
        //  (0x2005, 0x1080): for some reason computation of length fails...
        if( l == 70 && locallength == 63 )
          {
          gdcmWarningMacro( "PMS: Super bad hack. Changing length" );
          length = locallength = 140;
          }
        if( l > locallength )
          {
          throw Exception( "Out of Range" );
          }
        }
    }
    catch(ParseException &pe)
      {
      if( pe.GetLastElement().GetTag() == Tag(0xfffe,0xe000) )
        {
        // gdcm-MR-PHILIPS-16-Multi-Seq.dcm
        // Long story short, I think Philips engineer inserted 0xfffe,0x0000 instead of an item start element
        // assert( FindDataElement( Tag(0xfffe,0x0000) ) == false );
        is.seekg(-6, std::ios::cur );
        length = locallength = l;
        }
      else
        {
        // Could be the famous :
        // gdcmDataExtra/gdcmBreakers/BuggedDicomWorksImage_Hopeless.dcm
        // let's just give up:
        throw Exception( "Unhandled" );
        }
      }
    catch(Exception &pe)
      {
      assert( strcmp( pe.GetDescription(), "Out of Range" ) == 0);
      // BogugsItemAndSequenceLength.dcm
      // This is most likely the "Out of Range" one
      // Cautiously read until we find the next item starter and then stop.
      //std::cout << "Length read was:" << l << " should be at most:" <<  locallength ;
      while( de.Read<TDE,TSwap>(is) && de.GetTag() != Tag(0xfffe,0xe000) && de.GetTag().GetElement() != 0x0 )
        {
        //std::cout << "Nested2: " << de << std::endl;
        DES.insert( de );
        l += de.GetLength<TDE>();
        //std::cout << l << std::endl;
        }
      // seek back since we read the next item starter:
      int iteml = de.GetLength<TDE>();
      //assert( de.GetTag().GetElement() );
      if( !de.GetTag().GetElement() )
        {
        assert( iteml == 12 ); (void)iteml;
        is.seekg( -12, std::ios::cur );
        }
      else
        {
        assert( de.GetTag() == Tag(0xfffe,0xe000) );
        is.seekg( -4, std::ios::cur );
        }
      // let's fix the length now:
      length = locallength = l;
      gdcmWarningMacro( "Item length is wrong" );
      throw Exception( "Changed Length" );
      }

    assert( l == locallength );
    return is;
  }

  template <typename TDE, typename TSwap>
  std::ostream const &DataSet::Write(std::ostream &os) const {
    typename DataSet::ConstIterator it = DES.begin();
    for( ; it != DES.end(); ++it)
      {
      //std::cerr << "DEBUG:" << *it << std::endl;
      const DataElement & de = *it;
      // If this is a group length make sure this is consistant
      if( false && ( /*de.GetTag().GetGroup() >= 0x0000
         &&*/ de.GetTag().GetGroup() <  0x0008) )
        {
        gdcmWarningMacro( "DataSet contains illegal Tags. "
          "Those elements will be discarded:" << de.GetTag() );
        }
      // After that we are sure the elements are valid
      else if( false && de.GetTag().GetElement() == 0x0 )
        {
		// FIXME
		// This is not a good design !
		// A Writer should not have this kind of knowledge.
		// writting is simply serializing on disk !
        Element<VR::UL, VM::VM1> el;
        std::stringstream sst;
        //sst.SetSwapCode( os.GetSwapCode() );
        const Value &v = de.GetValue();
        const Value *pv = &v;
        const ByteValue *bv = dynamic_cast<const ByteValue*>(pv);
	      bv->Write<TSwap>(sst);
        el.Read( sst ); // FIXME endianness is not used !!
        //std::cerr << "GL=";
        //el.Print( std::cerr );
        //std::cerr << std::endl;
        unsigned int len = ComputeGroupLength<TDE>( de.GetTag() );
        //std::cerr << len << std::endl;
        if( len != el.GetValue() )
          {
          gdcmWarningMacro( "Wrong group length for " << de.GetTag() << ":"
            << el.GetValue() << " should be " << len << ". Corrected." );
          DataElement correct(de);
          // Set correct value:
          el.SetValue( len );
          el.Write( sst );
          // Pass it to the ByteValue
          ByteValue *bv2 = new ByteValue;
          bv2->SetLength(4);
          bv2->Read<TSwap>(sst);
          correct.SetValue( *bv2 );
          correct.Write<TDE,TSwap>(os);
          }
        else
          {
          // okay good value
          de.Write<TDE,TSwap>(os);
          }
        }
      else // well simply writes it
        {
        de.Write<TDE,TSwap>(os);
        }
      }
    return os;
  }
} // end namespace gdcm

#endif // __gdcmDataSet_txx

