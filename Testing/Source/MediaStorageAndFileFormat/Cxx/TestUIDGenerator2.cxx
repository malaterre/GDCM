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
#include "gdcmUIDGenerator.h"

#include <iostream>

#include <pthread.h> 

void* func (void* argc)
{
  gdcm::UIDGenerator g;
  const char *s = g.Generate();
  std::cout << s << std::endl;
  return NULL;
}

int TestUIDGenerator2(int argc, char *argv[])
{
pthread_t th[2];
        int i, ret;
        //printf("main posix tid: %u\n", pthread_self());
        //printf("main pid: %u\n", getpid());
        //printf("main tid: %u\n", gettid());
        for (i = 0; i < 2; i++)
                ret = pthread_create (&th[i], NULL, func, (void*)&i);
        for (i = 0; i < 2; i++)
                pthread_join (th[i], NULL); 
  return 0;
}
