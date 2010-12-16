// 
// (C) Jan de Vaan 2007-2010, all rights reserved. See the accompanying "License.txt" for licensed use. 
// 

#ifndef TEST_CONFIG
#define TEST_CONFIG

#if defined(_MSC_VER)
#pragma warning (disable: 4996)
#endif

// enable ASSERT() on linux 
#ifndef _WIN32
#ifndef _DEBUG
#define _DEBUG
#endif

#else
#include <assert.h>

#endif

#include <stdio.h>

typedef unsigned char BYTE;
typedef unsigned short USHORT;

#endif
