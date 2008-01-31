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
#include "gdcmAttribute.h"

#include <limits>
#include <math.h> // fabs

int TestAttributeAE() { return 0; }
int TestAttributeAS() { return 0; }
int TestAttributeAT() { return 0; }
int TestAttributeCS() { return 0; }
int TestAttributeDA() { return 0; }

int TestAttributeDS()
{
  // (0008,0008) CS [DERIVED\PRIMARY\AXIAL]                  #  22, 3 ImageType
  // (0020,0032) DS [-158.135803\-179.035797\-75.699997]     #  34, 3 ImagePositionPatient
  const float values[] = {-158.135803,-179.035797,-75.699997};
  const float newvalues[] = {12.34,56.78,90.0};
  const unsigned int numvalues = sizeof(values) / sizeof(values[0]);

  gdcm::Attribute<0x0020,0x0032> ipp = {-158.135803,-179.035797,-75.699997};
  // FIXME HARDCODED:
  if( ipp.GetVM() != gdcm::VM::VM3 ) return 1;
  if( ipp.GetVR() != gdcm::VR::DS ) return 1;
  // END FIXME
  if( ipp.GetNumberOfValues() != numvalues ) return 1;

  for(unsigned int i = 0; i < numvalues; ++i)
    if( fabs(ipp.GetValue(i) - values[i]) > std::numeric_limits<float>::epsilon() ) return 1;

  ipp.Print( std::cout );
  std::cout << std::endl;

  gdcm::DataElement de = ipp.GetAsDataElement();
  std::cout << de << std::endl;

  // new values:
  ipp.SetValues( newvalues );
  if( ipp.GetNumberOfValues() != numvalues ) return 1;
    
  for(unsigned int i = 0; i < numvalues; ++i)
    if( fabs(ipp.GetValue(i) - newvalues[i]) > std::numeric_limits<float>::epsilon() ) return 1;

  ipp.Print( std::cout );
  std::cout << std::endl;

  de = ipp.GetAsDataElement();
  std::cout << de << std::endl;

  return 0;
}

int TestAttributeDT() { return 0; }
int TestAttributeFL() { return 0; }
int TestAttributeFD() { return 0; }
int TestAttributeIS() { return 0; }
int TestAttributeLO() { return 0; }
int TestAttributeLT() { return 0; }
int TestAttributeOB() { return 0; }
int TestAttributeOF() { return 0; }
int TestAttributeOW() { return 0; }
int TestAttributePN() { return 0; }
int TestAttributeSH() { return 0; }
int TestAttributeSL() { return 0; }
int TestAttributeSQ() { return 0; }
int TestAttributeSS() { return 0; }
int TestAttributeST() { return 0; }
int TestAttributeTM() { return 0; }
int TestAttributeUI() { return 0; }
int TestAttributeUL() { return 0; }
int TestAttributeUN() { return 0; }
int TestAttributeUS() { return 0; }
int TestAttributeUT() { return 0; }
 

int TestAttribute(int argc, char *argv[])
{
  int numerrors = 0;
  numerrors += TestAttributeAE();
  numerrors += TestAttributeAS();
  numerrors += TestAttributeAT();
  numerrors += TestAttributeCS();
  numerrors += TestAttributeDA();
  numerrors += TestAttributeDS();
  numerrors += TestAttributeDT();
  numerrors += TestAttributeFL();
  numerrors += TestAttributeFD();
  numerrors += TestAttributeIS();
  numerrors += TestAttributeLO();
  numerrors += TestAttributeLT();
  numerrors += TestAttributeOB();
  numerrors += TestAttributeOF();
  numerrors += TestAttributeOW();
  numerrors += TestAttributePN();
  numerrors += TestAttributeSH();
  numerrors += TestAttributeSL();
  numerrors += TestAttributeSQ();
  numerrors += TestAttributeSS();
  numerrors += TestAttributeST();
  numerrors += TestAttributeTM();
  numerrors += TestAttributeUI();
  numerrors += TestAttributeUL();
  numerrors += TestAttributeUN();
  numerrors += TestAttributeUS();
  numerrors += TestAttributeUT();

  return numerrors;
}

