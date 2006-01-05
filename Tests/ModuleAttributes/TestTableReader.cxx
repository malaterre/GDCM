// generated file:
#include "gdcmTables.h"

#include "gdcmTableReader.h"

void TestReadTable(const char *filename)
{
  gdcm::TableReader tr;
  tr.SetFilename(filename);
  tr.Read();
}

int TestTableReader(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    TestReadTable(filename);
    return 0;
    }

  // else
  int i = 0;
  const char *filename;
  while( (filename = gdcmTables[i]) )
    {
    TestReadTable( filename );
    ++i;
    }

  return 0;
}
