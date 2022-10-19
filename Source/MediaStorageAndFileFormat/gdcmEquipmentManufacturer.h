/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef GDCMEQUIPMENTMANUFACTURER_H
#define GDCMEQUIPMENTMANUFACTURER_H

#include "gdcmTypes.h"

namespace gdcm {

class DataSet;
/**
 * \brief
 * \details
 * The intent is for private tags handling. This class is not meant to handle
 * all possible vendors in the world, simply those well known where we intend
 * to read private tags afterwards (typically SIEMENS+CSA, GEMS+PDB ...)
 */
class GDCM_EXPORT EquipmentManufacturer {
 public:
  typedef enum {
    UNKNOWN = 0,
    FUJI = 1,
    GEMS = 2,
    HITACHI = 3,
    KODAK = 4,
    MARCONI = 5,
    PMS = 6,
    SIEMENS = 7,
    TOSHIBA = 8,
    AGFA = 9,
    SAMSUNG = 10,
    UIH = 11
  } Type;

  static Type Compute(DataSet const &ds);

  static const char *TypeToString(Type type);

 private:
  static EquipmentManufacturer::Type GuessFromPrivateAttributes(
      DataSet const &ds);
};

}  // end namespace gdcm

#endif  // GDCMEQUIPMENTMANUFACTURER_H
