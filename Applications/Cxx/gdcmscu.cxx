/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2010 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include <socket++/echo.h>
#include <stdlib.h>

int main(int ac, char *av[])
{
 using namespace std;

  if (ac < 3) {
    cerr << "USAGE: " << av [0] << " remote-host portno string...\n";
    return 1;
  }

  int portno = atoi (av [2]);

  echo e(protocol::tcp);

  if (portno == 0)
    e->connect (av [1]);
  else
    e->connect (av [1], portno);

  const char s = '1';
  std::cout << "val:" << (int)s << std::endl;

  //cout << e->rfc_name () << ' ' << e->rfc_doc () << endl;
  const char msg[] = { 0x01  , 0x00  , 0x00  ,0x00  ,0x00  ,0xcd  ,0x00  ,0x01  ,0x00  ,0x00  ,0x41  ,0x4e  ,0x59  ,0x2d  ,0x53  ,0x43 };
  for (int i = 3; i < ac; i++) {
    char buf [256];

    //cout << "sending: " << av [i] << endl;

    //e << av [i] << endl;
    //e << msg << endl;
   // for(int j = 0; j < 255; ++j )
   // {
   //   e << (j+10); // << endl;
   // }
      e << 0xfe;
      e << 0;
      e << 0;
      e << 0;
      e << 0;
      e << endl;

    e.getline (buf, 255);
    buf [255] = 0;

    cout << "got back: " << buf << endl;
  }

  return 0;
}
