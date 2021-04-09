/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmStringFilter.h"
#include "gdcmAttribute.h"
#include "gdcmSmartPointer.h"

// https://sourceforge.net/p/gdcm/bugs/485/
int TestStringFilter4(int , char *[])
{
  gdcm::SmartPointer<gdcm::File> f = new gdcm::File;
  gdcm::DataSet & ds = f->GetDataSet();

    {
    gdcm::Element<gdcm::VR::LO,gdcm::VM::VM1> priv_creator;
    priv_creator.SetValue( "SIEMENS MED SP DXMG WH AWS 1" );
    gdcm::DataElement de1 = priv_creator.GetAsDataElement();
    de1.SetTag( gdcm::Tag(0x19,0x10) );
    ds.Insert( de1 );

    gdcm::Element<gdcm::VR::ST,gdcm::VM::VM1> el;
    el.SetValue( "TestStringFilter4" );
    gdcm::DataElement de2 = el.GetAsDataElement();
    de2.SetTag( gdcm::Tag(0x19,0x1010) );
    ds.Insert( de2 );
    // std::cout << ds << std::endl;

    gdcm::StringFilter filter;
    filter.SetFile(*f);

    gdcm::PrivateTag privTag(0x0019, 0x10, "SIEMENS MED SP DXMG WH AWS 1");

    // Works as intended
    std::string privTagValue1 = filter.ToString(ds.GetDataElement(privTag));
    std::cout << privTagValue1 << std::endl;

    // Does not work, returns string value of the private creator instead of the actual tag
    std::string privTagValue2 = filter.ToString(privTag);
    std::cout << privTagValue2 << std::endl;
    }

  return 0;
}
