/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmDPath.h"

int TestDPath(int, char *[]) {
  gdcm::DPath tp;

#if 0
  {
    const char path[] = "10,10";
    if (!gdcm::DPath::IsValid(path)) {
      return 1;
    }
    if (!tp.ConstructFromString(path)) {
      return 1;
    }
    tp.Print(std::cout);
    std::cout << std::endl;
  }
#endif

  {
    const char path[] = "/0010,0010";
    if (!gdcm::DPath::IsValid(path)) {
      return 1;
    }
    if (!tp.ConstructFromString(path)) {
      return 1;
    }
    tp.Print(std::cout);
    std::cout << std::endl;
  }

  {
    const char path[] = "/0008,1120/*/0008,1155";
    if (!gdcm::DPath::IsValid(path)) {
      return 1;
    }
    if (!tp.ConstructFromString(path)) {
      return 1;
    }
    tp.Print(std::cout);
    std::cout << std::endl;
  }

  // contains a '/' in creator
  {
    const char path[] = "\\19,0,Siemens: Thorax/Multix FD Lab Settings";
    if (!gdcm::DPath::IsValid(path)) {
      return 1;
    }
    if (!tp.ConstructFromString(path)) {
      return 1;
    }
    tp.Print(std::cout);
    std::cout << std::endl;
  }
  {
    const char path[] = "\\019,0,PHILIPS MR R5.6/PART";
    if (!gdcm::DPath::IsValid(path)) {
      return 1;
    }
    if (!tp.ConstructFromString(path)) {
      return 1;
    }
    tp.Print(std::cout);
    std::cout << std::endl;
  }
  {
    const char path[] = "\\4109,2,Applicare/Centricity Radiology Web/Version 1.0";
    if (!gdcm::DPath::IsValid(path)) {
      return 1;
    }
    if (!tp.ConstructFromString(path)) {
      return 1;
    }
    tp.Print(std::cout);
    std::cout << std::endl;
  }

  // contains a ',' in creator
  {
    const char path[] = "/4453,1000,DR Systems, Inc.";
    if (!gdcm::DPath::IsValid(path)) {
      return 1;
    }
    if (!tp.ConstructFromString(path)) {
      return 1;
    }
    tp.Print(std::cout);
    std::cout << std::endl;
  }

  // wildcard '*' in item
  {
    const char path[] = "/29,2,SIEMENS SYNGO ADVANCED PRESENTATION/*/70,84";
    if (!gdcm::DPath::IsValid(path)) {
      return 1;
    }
    if (!tp.ConstructFromString(path)) {
      return 1;
    }
    tp.Print(std::cout);
    std::cout << std::endl;
  }

  // indexed:
  {
    const char path[] = "/40,100/1/40,6";
    if (!gdcm::DPath::IsValid(path)) {
      return 1;
    }
    if (!tp.ConstructFromString(path)) {
      return 1;
    }
    tp.Print(std::cout);
    std::cout << std::endl;
  }

  return 0;
}
