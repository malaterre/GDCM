/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef __gdcmSequenceOfItems_h
#define __gdcmSequenceOfItems_h

#include "gdcmValue.h"
#include "gdcmItem.h"
#include "gdcmTS.h"

#include <vector>

namespace gdcm
{

/**
 * \brief Class to represent a Sequence Of Items
 * (value representation : SQ)
 *  - a Value Representation for Data Elements that contains a sequence of Data Sets.
 *  - Sequence of Item allows for Nested Data Sets
 *
 * See PS 3.5, 7.4.6 Data Element Type Within a Sequence
 * \note
 * SEQUENCE OF ITEMS (VALUE REPRESENTATION SQ)
 * A Value Representation for Data Elements that contain a sequence of 
 * Data Sets. Sequence of Items allows for Nested Data Sets.
 */
template <typename DEType>
class GDCM_EXPORT SequenceOfItems : public Value
{
public:
  // Typdefs:
  typedef std::vector< Item<DEType> > ItemVector;

/// \brief constructor (UndefinedLength by default)
  //SequenceOfItems(VL const &vl = 0xFFFFFFFF):SequenceLengthField(vl),NType(type) { }
  SequenceOfItems(TS::NegociatedType type = TS::Explicit):NType(type) { }

  /// \brief Returns the SQ length, as read from disk
  VL GetLength() const { return SequenceLengthField; }
  /// \brief Sets the actual SQ length
  void SetLength(VL length) {
    SequenceLengthField = length;
  }
  VL ComputeLength() const;
  void Clear() {}

//template <typename TSwap>
//  IStream &Read(IStream &is);
//template <typename TSwap>
//  OStream const & Write(OStream &os) const;

  /// \brief Appends an Item to the already added ones
  void AddItem(Item<DEType> const &item);

  SequenceOfItems &operator=(const SequenceOfItems &val) {
    SequenceLengthField = val.SequenceLengthField;
    Items = val.Items;
    NType = val.NType;
    return *this;
    }

  TS::NegociatedType GetType() const { return NType; }

template <typename TSwap>
IStream &Read(IStream &is)
{
	//std::cerr << "SequenceLengthField: " << SequenceLengthField << std::endl;
  if( SequenceLengthField.IsUndefined() )
    {
    Item<DEType> item;
//    item.SetType( GetType() );
    const Tag seqDelItem(0xfffe,0xe0dd);
    do
      {
      item.Read<TSwap>(is);
      //std::cout << "Item: " << item << std::endl;
      Items.push_back( item );
      }
    while( item.GetTag() != seqDelItem );
    }
  else
    {
    Item<DEType> item;
//    item.SetType( GetType() );
    VL l = 0;
    //std::cout << "l: " << l << std::endl;
    while( l != SequenceLengthField )
      {
      item.Read<TSwap>(is);
      //std::cout << "Item: " << item << std::endl;
      Items.push_back( item );
      l += item.GetLength();
      //std::cerr << "l=" << l << std::endl;
      //assert( !item.GetVL().IsUndefined() );
      assert( l <= SequenceLengthField );
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
      // MR_Philips_Intera_No_PrivateSequenceImplicitVR.dcm
      // (0x2005, 0x1080): for some reason computation of length fails...
      if( SequenceLengthField == 778 && l == 774 )
        {
        gdcmWarningMacro( "PMS: Super bad hack" );
        l = SequenceLengthField;
        }
      // Bug_Philips_ItemTag_3F3F
      // (0x2005, 0x1080): Because we do not handle fully the bug at the item
      // level we need to check here too
      else if ( SequenceLengthField == 444 && l == 3*71 )
        {
        // This one is a double bug. Item length is wrong and impact SQ length
        gdcmWarningMacro( "PMS: Super bad hack" );
        l = SequenceLengthField;
        }
#endif
      }
    assert( l == SequenceLengthField );
    }
  return is;
}

template <typename TSwap>
OStream const &Write(OStream &os) const
{
  typename ItemVector::const_iterator it = Items.begin();
  for(;it != Items.end(); ++it)
    {
    it->Write<TSwap>(os);
    }
  //if( SequenceLengthField.IsUndefined() )
  //  {
  //  const Tag seqDelItem(0xfffe,0xe0dd);
  //  const ImplicitDataElement ide(seqDelItem);
  //  assert( ide.GetVL() == 0 );
  //  ide.Write(os);
  //  }
  return os;
}

protected:
  void Print(std::ostream &os) const {
    os << "\n\tSQ L= " << SequenceLengthField << "\n";
    typename ItemVector::const_iterator it =
      Items.begin();
    for(;it != Items.end(); ++it)
      {
      os << "  " << *it << "\n";
      }
  }

private:
public:
  /// \brief Total length of the Sequence (or 0xffffffff) if undefined
  VL SequenceLengthField;
  /// \brief Vector of Sequence Items
  ItemVector Items;
  TS::NegociatedType NType;
};

} // end namespace gdcm

#include "gdcmSequenceOfItems.txx"

#endif //__gdcmSequenceOfItems_h

