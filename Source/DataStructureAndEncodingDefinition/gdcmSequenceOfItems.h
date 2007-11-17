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
class GDCM_EXPORT SequenceOfItems : public Value
{
public:
  // Typdefs:
  typedef std::vector< Item > ItemVector;

/// \brief constructor (UndefinedLength by default)
  //SequenceOfItems(VL const &vl = 0xFFFFFFFF):SequenceLengthField(vl),NType(type) { }
  SequenceOfItems() { }

  /// \brief Returns the SQ length, as read from disk
  VL GetLength() const { return SequenceLengthField; }
  /// \brief Sets the actual SQ length
  void SetLength(VL length) {
    SequenceLengthField = length;
  }
  template <typename TDE>
  VL ComputeLength() const;
  void Clear() {}

  /// \brief Appends an Item to the already added ones
  void AddItem(Item const &item);

  SequenceOfItems &operator=(const SequenceOfItems &val) {
    SequenceLengthField = val.SequenceLengthField;
    Items = val.Items;
    return *this;
    }


  template <typename TDE, typename TSwap>
  std::istream &Read(std::istream &is)
    {
    if( SequenceLengthField.IsUndefined() )
      {
      Item item;
      const Tag seqDelItem(0xfffe,0xe0dd);
      do
        {
        item.Read<TDE,TSwap>(is);
        //std::cout << "Item: " << item << std::endl;
        Items.push_back( item );
        }
      while( item.GetTag() != seqDelItem );
      }
    else
      {
      Item item;
      VL l = 0;
      while( l != SequenceLengthField )
        {
        item.Read<TDE,TSwap>(is);
        Items.push_back( item );
        l += item.template GetLength<TDE>();
        assert( l <= SequenceLengthField );
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
        // MR_Philips_Intera_No_PrivateSequenceImplicitVR.dcm
        // (0x2005, 0x1080): for some reason computation of length fails...
        if( SequenceLengthField == 778 && l == 774 )
          {
          gdcmWarningMacro( "PMS: Super bad hack" );
          SequenceLengthField = l;
          throw Exception( "Wrong Length" );
          //l = SequenceLengthField;
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

  template <typename TDE,typename TSwap>
  std::ostream const &Write(std::ostream &os) const
    {
    typename ItemVector::const_iterator it = Items.begin();
    for(;it != Items.end(); ++it)
      {
      it->Write<TDE,TSwap>(os);
      }
    return os;
    }

protected:
  void Print(std::ostream &os) const {
    os << "\n\tSQ L= " << SequenceLengthField << "\n";
    ItemVector::const_iterator it =
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
};

} // end namespace gdcm

#include "gdcmSequenceOfItems.txx"

#endif //__gdcmSequenceOfItems_h

