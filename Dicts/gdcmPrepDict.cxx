/* Executable meant to preprocess the DICOM V3 Dictionary
 * CMake regular expression are great but as far as cmake 2.2 is concerned there is
 * no math operation which makes the preprocess stage extremely difficult to write
 * Therefore we write our own C++ code that will do the same, then cmake will generate the
 * executable which will generate the source code (and all dependencies are properly set).
 */

#include "gdcmVR.h"
#include "gdcmVM.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctype.h>

//#define DICT_DEBUG
//#define DICT_XML

//static const char DictFilename[] = "DataDict.dic";
void write_header(std::ofstream &of)
{
#ifdef DICT_DEBUG
  const char header[] =
   "#ifndef __gdcmDefaultDicts_cxx\n\
#define __gdcmDefaultDicts_cxx\n\n\
#include \"gdcmVR.h\"\n\
#include \"gdcmDict.h\"\n\
#include \"gdcmDictEntry.h\"\n\n\
namespace gdcm\n{\n\n\
typedef struct\n{\n\
  uint16_t group;\n\
  uint16_t element;\n\
  const char *vr;\n\
  const char *vm;\n\
  const char *name;\n\
} DICT_ENTRY;\n\n\
static DICT_ENTRY datadir[] = {\n";
#else
  const char header[] =
   "#ifndef __gdcmDefaultDicts_cxx\n\
#define __gdcmDefaultDicts_cxx\n\n\
#include \"gdcmVR.h\"\n\
#include \"gdcmDict.h\"\n\
#include \"gdcmDictEntry.h\"\n\
\nnamespace gdcm\n{\n\n\
typedef struct\n{\n\
  uint16_t group;\n\
  uint16_t element;\n\
  VR::VRType vr;\n\
  VM::VMType vm;\n\
  const char *name;\n\
} DICT_ENTRY;\n\n\
static DICT_ENTRY datadir[] = {\n";
#endif
  of << header;
}

void write_footer(std::ofstream &of)
{
  const char footer[] =
#ifdef DICT_DEBUG
"   {0,0,0,0,0}\n"
#else
"   {0,0,(VR::VRType)0,(VM::VMType)0,0}\n"
#endif
"};\n\n\
void Dict::FillDefaultDataDict()\n\
{\n\
   unsigned int i = 0;\n\
   DICT_ENTRY n = datadir[i];\n\
   while( n.name != 0 )\n\
   {  \n\
      Tag t(n.group, n.element);\n\
      DictEntry e( n.name, n.vr, n.vm );\n\
      AddDictEntry( t, e );\n\
      n = datadir[++i];\n\
   }\n\
   Tag t(0, 0);\n\
   DictEntry e( \"\", (VR::VRType)0, (VM::VMType)0);\n\
   AddDictEntry( t, e );\n\
}\n\n\
} //end gdcm namespace\n\
\n#endif\n";
  of << footer;
}

bool read_vr(const char *raw, gdcm::VR::VRType &type)
{
  int i = 0;
  while( !isdigit(*(raw+i)))
    ++i;
  std::string vm(raw, raw+i-1);
  type = gdcm::VR::GetVRType(vm.c_str());
  assert( type != gdcm::VR::VR_END );
  return true;
}

bool read_vm(const char *raw, gdcm::VM::VMType &type)
{
  char vm[8];
  int r = sscanf(raw, "%s", vm);
  (void)r;
  type = gdcm::VM::GetVMType(vm);
  assert( type != gdcm::VM::VM_END );
  return true;
}

bool read_uint16(const char *raw, uint16_t &ov)
{
  unsigned int v;
  int r = sscanf(raw, "%04x", &v);
  assert( r == 1 && "Wrong Value read for uint16");
  char sv[4+1];
  r = sprintf(sv, "%04x", v);
  assert( r == 4 && "Wrong Value printed for uint16");
  assert( strncmp(raw, sv, 4) == 0 );
  ov = v;
  return true;
}

// Takes as input a raw text file, and converts it into a xml line
// Template is:
// From
// 0000 0000 UL 1 Group Length
// into:
// <DataElement Tag="0000,0000" VR="UL" VM="1" Name="Group Length">
bool convert_to_xml(const char *raw, std::string &cxx)
{
  uint16_t group;
  uint16_t element;
  gdcm::VR::VRType vr;
  gdcm::VM::VMType vm;
  read_uint16(raw, group);
  assert( !(group%2) );
  read_uint16(raw+5, element);
  read_vr(raw+10, vr);
  int len = 11+strlen(gdcm::VR::GetVRString(vr));
  read_vm(raw+len, vm);
  len += strlen(gdcm::VM::GetVMString(vm))+1;
  std::ostringstream os;
  os << "  <DataElement Tag=\"" << std::hex << std::setw(4) << std::setfill('0') << group << "," 
    << std::setw(4) << std::setfill('0')
    << element << "\" VR=\"" << vr << "\" VM=\"" << vm << "\"\tName=\"" << (raw+len) << "\">";
  cxx = os.str();
  return true;
}

// Takes as input a raw text file, and converts it into a c++ line
// Template is:
// From
// 0000 0000 UL 1 Group Length
// into:
// {0x0000, 0x0000, "UL" , "1" , "Group Length"},
bool convert_to_cxx(const char *raw, std::string &cxx)
{
  uint16_t group;
  uint16_t element;
  gdcm::VR::VRType vr;
  gdcm::VM::VMType vm;
  read_uint16(raw, group);
  assert( !(group%2) );
  read_uint16(raw+5, element);
  read_vr(raw+10, vr);
  int len = 11+strlen(gdcm::VR::GetVRString(vr));
  read_vm(raw+len, vm);
  len += strlen(gdcm::VM::GetVMString(vm))+1;
  std::ostringstream os;
  os << "   {0x" << std::hex << std::setw(4) << std::setfill('0') << group << ", 0x" 
    << std::setw(4) << std::setfill('0')
#ifdef DICT_DEBUG
    << element << ", \"" << vr << "\" , \"" << vm << "\" , \"" << (raw+len) << "\"}, ";
#else
    << element << std::dec << ",(VR::VRType)" << (int)vr << ",(VM::VMType)" << (int)vm << ",\"" << (raw+len) << "\"},";
#endif
  cxx = os.str();
  return true;
}

// Remove the first \0
void clean_string(const char *no_clean, char *raw)
{
  if( *no_clean == '\0' )
    {
    strcpy( raw, no_clean+1);
    }
  else
    strcpy( raw, no_clean);
}

void add_group_lenght(std::ifstream &from, std::ofstream &into)
{
  std::streampos p = from.tellg();
  char group[5];
  from.get(group, 5);
  std::string in = group;
  const char group_str[] = " 0000 UL 1 Group Length";
  std::ostringstream os;
  std::string out;
  if( in[2] == 'x' && in[3] == 'x' )
    {
    std::string line = in;
    if(line[0] == '5')
      {
      uint16_t start = 0x5000;
      uint16_t end   = 0x50ff;
      for(uint16_t i= start; i<=end; i+=2)
        {
        os.str("");
        os << std::hex << i << group_str;
#ifndef DICT_XML
        convert_to_cxx(os.str().c_str(), out);
        into << out << std::endl;
#endif
        }
      }
    else if(line[0] == '6')
      {
      uint16_t start = 0x6000;
      uint16_t end   = 0x60ff;
      for(uint16_t i= start; i<=end; i+=2)
        {
        os.str("");
        os << std::hex << i << group_str;
#ifndef DICT_XML
        convert_to_cxx(os.str().c_str(), out);
        into << out << std::endl;
#endif
        }
      }
    }
  else
    {
    in += group_str;
#ifdef DICT_XML
    convert_to_xml(in.c_str(), out);
#else
    convert_to_cxx(in.c_str(), out);
#endif
    into << out << std::endl;
    }
  // seek back
  from.seekg(p);
}

int main(int argc, char *argv[])
{
  if( argc < 3 )
    return 1;

  // // Can use GDCM_SOURCE_DIR
  // std::string path = GDCM_SOURCE_DIR;
  // path += "/Dicts/";
  // path += DictFilename;
  // std::cerr << "open: " << path << std::endl;
  const char *filename = argv[1]; // Full path to the dict
  const char *outfilename = argv[2]; // Full path to output the dict
  //std::cerr << "open: " << filename << std::endl;
  std::ifstream from(filename);
  std::ofstream into(outfilename);
  if(!from)
    {
    std::cerr << "Problem opening the file" << std::endl;
    return 1;
    }
  write_header(into);

  std::string line;
//   DictEntry *newEntry;
   //while (!from.eof() && from)
   //while (from >> line)
   //while (from.getline(iline, 512))
   std::ostringstream os;
   while(std::getline(from, line))
     {
     if( *(line.c_str()) == '\0' )
       {
       // If an empty line is found then a new group starts
       add_group_lenght(from, into);
       continue;
       }
     if( line[2] == 'x' && line[3] == 'x' )
       {
       if(line[0] == '5')
         {
         uint16_t start = 0x5000;
         uint16_t end   = 0x50ff;
         for(uint16_t i= start; i<=end; i+=2)
           {
           std::string s1 = line.c_str()+4;
           os.str("");
           os << std::hex << i << s1;
#ifdef DICT_XML
           convert_to_xml(os.str().c_str(), s1);
#else
           convert_to_cxx(os.str().c_str(), s1);
#endif
           into << s1 << std::endl;
           }
         }
       else if(line[0] == '6')
         {
         uint16_t start = 0x6000;
         uint16_t end   = 0x60ff;
         for(uint16_t i= start; i<=end; i+=2)
           {
           std::string s1 = line.c_str()+4;
           os.str("");
           os << std::hex << i << s1;
#ifdef DICT_XML
           convert_to_xml(os.str().c_str(), s1);
#else
           convert_to_cxx(os.str().c_str(), s1);
#endif
           into << s1 << std::endl;
           }
         }
       else
         return 1;
       //std::cout << line << std::endl;
       }
     else if ( line[7] == 'x' && line[8] == 'x' )
       {
       if( line[5] == '3' && line[6] == '1' )
         {
         uint16_t start = 0x3100;
         uint16_t end   = 0x31ff;
         for(uint16_t i= start; i<=end; ++i)
           {
           std::string s1(line.c_str(), line.c_str()+5);
           std::string s = line.c_str()+9;
           os.str("");
           os << s1 << std::hex << i << s;
#ifdef DICT_XML
           convert_to_xml(os.str().c_str(), s);
#else
           convert_to_cxx(os.str().c_str(), s);
#endif
           into << s << std::endl;
           }
         //std::cout << line << std::endl;
         }
       else
         return 1;
       }
     else
       {
       std::string s;
#ifdef DICT_XML
       convert_to_xml(line.c_str(), s);
#else
       convert_to_cxx(line.c_str(), s);
#endif
       into << s << std::endl;
       }
     }

  write_footer(into);
  return 0;
}
