/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
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
  template <typename TSwap> friend class IOSerialize;
public:
  // Typdefs:
  typedef std::vector<Item> ItemVector;

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

template <typename TSwap>
  IStream &Read(IStream &is);
template <typename TSwap>
  OStream const & Write(OStream &os) const;

  /// \brief Appends an Item to the already added ones
  void AddItem(Item const &item);

  SequenceOfItems &operator=(const SequenceOfItems &val) {
    SequenceLengthField = val.SequenceLengthField;
    Items = val.Items;
    NType = val.NType;
    return *this;
    }

  TS::NegociatedType GetType() const { return NType; }

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
  TS::NegociatedType NType;
};

} // end namespace gdcm

#endif //__gdcmSequenceOfItems_h

