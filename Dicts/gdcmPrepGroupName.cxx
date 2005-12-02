/*
 * Executable meant to preprocess a GroupName dictionary, entry should look like this:
 * 0000 CMD Command
 * ...
 */

#include <iostream>
#include <fstream>
#include <sstream>  // for std::getline
#include <assert.h>
#include <stdio.h>

void write_header(std::ofstream &of)
{
  of << "#include \"gdcmType.h\"\n"
    "#include \"gdcmGroupDict.h\"\n\n"
    "namespace gdcm {\n\n"
    "typedef struct\n{\n"
    "  uint16_t group;\n"
    "  const char *abbreviation;\n"
    "  const char *name;\n"
    "} GROUP_ENTRY;\n\n"
    "static GROUP_ENTRY groupname[] = {\n";
}

void write_footer(std::ofstream &of)
{
  of << "\t{0xffff,0,0} // will not be added to the dict \n"
    "};\n\n"
    "void GroupDict::FillDefaultGroupName()\n"
    "{\n"
    "  unsigned int i = 0;\n"
    "  GROUP_ENTRY n = groupname[i];\n"
    "  while( n.name != 0 )\n"
    "  {\n"
    "    InsertGroupEntry( n.group, n.abbreviation, n.name );\n"
    "    n = groupname[++i];\n"
    "  }\n"
    "}\n\n"
    "} // namespace gdcm\n";
}

int main(int argc, char *argv[])
{
  if( argc < 3 )
    return 1;

  const char *filename = argv[1]; // Full path to the dict
  const char *outfilename = argv[2]; // Full path to output the dict
  //std::cerr << "open: " << filename << std::endl;
  std::ifstream from(filename, std::ios::binary);
  std::ofstream into(outfilename);
  if(!from)
    {
    std::cerr << "Problem opening the from file" << std::endl;
    return 1;
    }
  if(!into)
    {
    std::cerr << "Problem opening the into file" << std::endl;
    return 1;
    }

  write_header(into);
  int error = 0;
  std::string line;
  while(std::getline(from, line))
    {
     if( !line.empty() )
       {
       std::string::iterator e(line.end()-1);
       if( *e == '\r' ) line.erase(e);
       }
    unsigned int group; // Group Number
    char abbr[512]; // NHI Abbreviation (when known) - not part of DICOM standard -
    char meaning[512]; // Meaning          (when known) - not part of DICOM standard -
    //std::cout << line << std::endl;
    if ( sscanf(line.c_str(), "%04x %s %s", &group, abbr, meaning) != 3 )
      {
      error = 1;
      assert( 0 && "Should not happen" );
      }
    into << "\t{0x" << std::hex << group << ",\"" << abbr << "\",\"" << meaning << "\"},\n";
    }
  write_footer(into);

  from.close();
  into.close();

  return error;
}
