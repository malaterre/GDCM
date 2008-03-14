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
#include "gdcmCSAHeader.h"
#include "gdcmDataElement.h"

namespace gdcm
{
/*
 * http://www.enac.northwestern.edu/~tew/archives/2003/02/25/incomplete-dicom-headers/
 * http://www.nmr.mgh.harvard.edu/~rudolph/software/vox2ras/download/vox2ras_rsolve.m
 * http://www.mail-archive.com/freesurfer@nmr.mgh.harvard.edu/msg03409.html
 *
 * Pretty good link:
 * http://www.mmrrcc.upenn.edu/CAMRIS/cfn/dicomhdr.html
 */

struct equ
{ 
  uint32_t syngodt;
  const char vr[2+1];
};

// Looks like there is mapping in between syngodt and vr...
//  O <=> UN
//  3 <=> DS
//  4 <=> FD
//  5 <=> FL
//  6 <=> IS
//  9 <=> UL
// 10 <=> US
// 16 <=> CS
// 19 <=> LO
// 20 <=> LT
// 22 <=> SH
// 25 <=> UI
static equ mapping[] = {
  {  0 , "UN" },
  {  3 , "DS" },
  {  4 , "FD" },
  {  5 , "FL" },
  {  6 , "IS" },
  {  7 , "SL" },
  {  8 , "SS" },
  {  9 , "UL" },
  { 10 , "US" },
  { 16 , "CS" },
  { 19 , "LO" },
  { 20 , "LT" },
  { 22 , "SH" },
  { 23 , "ST" },
  { 25 , "UI" },
  { 27 , "UT" }
};

bool check_mapping(uint32_t syngodt, const char *vr)
{
  static const unsigned int max = sizeof(mapping) / sizeof(equ);
  const equ *p = mapping;
  assert( syngodt <= mapping[max-1].syngodt );
  while(p->syngodt < syngodt )
  {
    //std::cout << "mapping:" << p->vr << std::endl;
    ++p;
  }
  assert( p->syngodt == syngodt ); // or else need to update mapping
  const char* lvr = p->vr;
  int check = strcmp(vr, lvr) == 0;
  assert( check );
  return true;
}

// dcmInfo.exe print like this:
// 67 - 'SlicePosition_PCS' VM 3, VR FD, SyngoDT 4, NoOfItems 6, Data '-185.77913332'\'-163.80459213'\'72.73944092'
void CSAHeader::Print(DataElement const &de) const
{
  gdcm::Tag t1(0x0029,0x1010);
  gdcm::Tag t2(0x0029,0x1020);
  if( de.GetTag() == t1 )
    {
    std::cout << "Image shadow data (0029,xx10)\n\n";
    }
  else if( de.GetTag() == t2 )
    {
    std::cout << "Series shadow data (0029,xx20)\n\n";
    }
  else
    {
    std::cerr << "Unhandled tag: " << de.GetTag() << std::endl;
    }
 
  const ByteValue *bv = de.GetByteValue();
  assert( bv );
  const char *p = bv->GetPointer();
  assert( p );
  std::string s( bv->GetPointer(), bv->GetLength() );
  std::stringstream ss;
  ss.str( s );
  char dummy[4+1];
  dummy[4] = 0;
  ss.read(dummy, 4);
  //std::cout << dummy << std::endl;
  assert( strcmp( dummy, "SV10" ) == 0 );
  ss.read(dummy, 4);
  assert( strcmp( dummy, "\4\3\2\1" ) == 0 );

  uint32_t n;
  ss.read((char*)&n, sizeof(n));
  uint32_t unused;
  ss.read((char*)&unused, sizeof(unused));
  assert( unused == 77 ); // 'M' character...

  for(uint32_t i = 0; i < n; ++i)
    {
    std::cout << i;
    std::cout << " - ";
    char name[64+1];
    name[64] = 0; // security
    ss.read(name, 64);
    std::cout << "'" << name << "' ";
    uint32_t vm;
    ss.read((char*)&vm, sizeof(vm));
    std::cout << "VM " << vm <<  ", ";
    char vr[4];
    ss.read(vr, 4);
    assert( vr[2] == vr[3] && vr[2] == 0 );
    std::cout << "VR " << vr << ", ";
    uint32_t syngodt;
    ss.read((char*)&syngodt, sizeof(syngodt));
    check_mapping(syngodt, vr);
    std::cout << "SyngoDT " << syngodt << ", ";
    uint32_t nitems;
    ss.read((char*)&nitems, sizeof(nitems));
    std::cout << "NoOfItems " << nitems << ", ";
    uint32_t xx;
    ss.read((char*)&xx, sizeof(xx));
    //std::cout << "xx=" << xx<< std::endl;
    assert( xx == 77 || xx == 205 );

    std::cout << "Data ";
    for( uint32_t j = 0; j < nitems; ++j)
      {
      uint32_t item_xx[4];
      ss.read((char*)&item_xx, 4*sizeof(uint32_t));
      assert( item_xx[2] == 77 || item_xx[2] == 205 );
      uint32_t len = item_xx[1]; // 2nd element
      assert( item_xx[0] == item_xx[1] && item_xx[1] == item_xx[3] );
      if( len )
        {
        char *val = new char[len+1];
        val[len] = 0; // security
        ss.read(val,len);
        // WARNING vr does not means anything AFAIK, 
        // simply print the value as if it was IS/DS or LO (ASCII)
        if( j ) std::cout << '\\';
        std::cout << "'" << val << "'";

        char dummy[4];
        uint32_t dummy_len = (4 - len % 4) % 4;
        ss.read(dummy, dummy_len );

        for(uint32_t d= 0; d < dummy_len; ++d)
          {
          // I think dummy should always be 0
          assert( dummy[d] == 0 );
          }
        delete[] val;     
        }
      }
    std::cout << std::endl;
    }
 
}

} // end namespace gdcm

