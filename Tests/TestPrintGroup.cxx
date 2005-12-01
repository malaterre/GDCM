// generated file
#include "gdcmDataImages.h"

#include "gdcmType.h"
#include "gdcmGroup.txx"
#include "gdcmByteSwap.txx"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"

uint32_t ReadLength(const char *value, gdcm::SC::SwapCodeType swapcode)
{
  // ok there is group length, save it to compare later
  uint32_t group_length = 0;
  char str[4];
  memcpy( str, value, 4);
  gdcm::ByteSwap<uint32_t>::
    SwapRangeFromSwapCodeIntoSystem((uint32_t*)(&str), swapcode, 1);
  memcpy(&group_length, str, 4);
  std::cerr << "Group Length read:" << group_length << std::endl;
  return group_length;
}

template<class DEType>
int PrintGroup(gdcm::DICOMIStream &is, int group_number)
{
  DEType de;
  gdcm::DataElement &de_tag = de;
  gdcm::Group<DEType> group(group_number);
  bool group_length_present = false;
  uint32_t group_length = 0;

  while( !is.eof() && is >> de_tag )
    {
    is >> de;
    if ( de.GetTag().GetGroup() == group_number )
      {
      if( de.GetTag().GetElement() == 0x0000 )
        {
        group_length_present = true;
        group_length = ReadLength(de.GetValue().GetPointer(), is.GetSwapCode());
        }
      std::cout << de << std::endl;
      group.AddDataElement( de );
      }
    }
  //std::cout << group << std::endl;
  //std::cout << "Length: " << group.GetLength() << std::endl;
  if( group_length_present )
    return group.GetLength() == group_length;

  return 0;
}

int PrintFileGroup(const char *filename, int group_number)
{
  std::cerr << filename << std::endl;
  std::cerr << std::hex << group_number << std::endl;
  gdcm::DICOMIStream Is;
  Is.SetFileName(filename);
  Is.Open();
  Is.Initialize();

  if( Is.GetNegociatedTS() == gdcm::DICOMIStream::Explicit )
    {
    return PrintGroup<gdcm::ExplicitDataElement>(Is, group_number);
    }
  else
    {
    return PrintGroup<gdcm::ImplicitDataElement>(Is, group_number);
    }
}

int TestPrintGroup(int argc, char *argv[])
{
  if(argc == 3)
    {
    const char *filename = argv[1];
    unsigned int group_number;
    sscanf(argv[2], "%04x", &group_number);

    return PrintFileGroup(filename, group_number);
    }
  else if (argc == 2 )
    return 1; // just in case

  //else loop all over the filename and print let say group 0008
  int i = 0;
  const char *filename;
  int r = 0;
  while( (filename = gdcmDataImages[i]) )
    {
    r += PrintFileGroup( filename, 0x0008 );
    ++i;
    }

  return r;
}
