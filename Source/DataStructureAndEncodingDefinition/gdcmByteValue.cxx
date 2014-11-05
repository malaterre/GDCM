/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmByteValue.h"

#include <algorithm> // req C++11
#include <cstring> // memcpy
#include <math.h>

namespace gdcm
{

  void ByteValue::PrintASCII(std::ostream &os, VL maxlength ) const {
    VL length = std::min(maxlength, Length);
    // Special case for VR::UI, do not print the trailing \0
    if( length && length == Length )
      {
      if( Internal[length-1] == 0 )
        {
        length = length - 1;
        }
      }
    // I cannot check IsPrintable some file contains \2 or \0 in a VR::LO element
    // See: acr_image_with_non_printable_in_0051_1010.acr
    //assert( IsPrintable(length) );
    std::vector<char>::const_iterator it = Internal.begin();
    for(; it != Internal.begin()+length; ++it)
      {
      const char &c = *it;
      if ( !( isprint((unsigned char)c) || isspace((unsigned char)c) ) ) os << ".";
      else os << c;
      }
  }
  void ByteValue::PrintHex(std::ostream &os, VL maxlength ) const {
    VL length = std::min(maxlength, Length);
    // WARNING: Internal.end() != Internal.begin()+Length
    std::vector<char>::const_iterator it = Internal.begin();
    os << std::hex;
    for(; it != Internal.begin()+length; ++it)
      {
      //const char &c = *it;
      uint8_t v = *it;
      if( it != Internal.begin() ) os << "\\";
      os << std::setw( 2 ) << std::setfill( '0' ) << (uint16_t)v;
      //++it;
      //os << std::setw( 1 ) << std::setfill( '0' ) << (int)*it;
      }
    os << std::dec;
  }

  bool ByteValue::GetBuffer(char *buffer, unsigned long length) const {
    // SIEMENS_GBS_III-16-ACR_NEMA_1.acr has a weird pixel length
    // so we need an inequality
    if( length <= Internal.size() )
      {
      memcpy(buffer, &Internal[0], length);
      return true;
      }
    gdcmDebugMacro( "Could not handle length= " << length );
    return false;
    }

  void ByteValue::PrintPNXML(std::ostream &os) const
    {
    /*
    PersonName = element PersonName {
    Number,
    element SingleByte { NameComponents }?,
    element Ideographic { NameComponents }?,
    element Phonetic { NameComponents }?
    }

    NameComponents =
    element FamilyName {xsd:string}?,
    element GivenName {xsd:string}?,
    element MiddleName {xsd:string}?,
    element NamePrefix {xsd:string}?,
    element NameSuffix {xsd:string}?
     */
    int count1 , count2;
    count1=count2=1;
    os << "<PersonName number = \"" << count1 << "\" >\n" ;
    os << "<SingleByte>\n<FamilyName> " ;
    std::vector<char>::const_iterator it = Internal.begin();
    for(; it != (Internal.begin() + Length); ++it)
      {
      const char &c = *it;
      if ( c == '^' )
        {
        if(count2==1)
          {
          os << "</FamilyName>\n";
          os << "<GivenName> ";
          count2++;
          }
        if(count2==2)
          {
          os << "</GivenName>\n";
          os << "<MiddleName> ";
          count2++;
          }
        else if(count2==3)
          {
          os << "</MiddleName>\n";
          os << "<NamePrefix> ";
          count2++;
          }
        else if(count2==4)
          {
          os << "</NamePrefix>\n";
          os << "<NameSuffix> ";
          count2++;
          }
        else
          {
          //in the rare case there are more ^ characters
          assert("Name components exceeded");
          }
        }
      else if ( c == '=' )
        {
        if(count2==1)
          {
          os << "</FamilyName>\n";
          }
        if(count2==2)
          {
          os << "</GivenName>\n";
          }
        else if(count2==3)
          {
          os << "</MiddleName>\n";
          }
        else if(count2==4)
          {
          os << "</NamePrefix>\n";
          }
        else if(count2==5)
          {
          os << "</NameSuffix>\n";
          }
        /*----------------------------------------------------------------*/
        if(count1==1)
          {
          os << "</SingleByte>\n";
          os << "<Ideographic> \n<FamilyName> ";
          count1++;
          }
        else if(count1==2)
          {
          os << "</Ideographic>\n";
          os << "<Phonetic> \n<FamilyName> ";
          count1++;
          }
        else if(count1==3)
          {
          os << "</Phonetic> \n<FamilyName> \n";
          count1++;
          }
        else
          {
          assert("Impossible - only 3 names allowed");
          }
        count2=1;
        }
      else if ( !( isprint((unsigned char)c) ) )
        os << ".";
      else if(c == '&')
        os << "&amp;";
      else if(c == '<')
        os << "&lt;";
      else if(c == '>')
        os << "&gt;";
      else if(c == '\'')
        os << "&apos;";
      else if(c == '\"')
        os << "&quot;";
      else
        os << c;
      }
    if(count2==1)
      {
      os << "</FamilyName>\n";
      }
    if(count2==2)
      {
      os << "</GivenName>\n";
      }
    else if(count2==3)
      {
      os << "</MiddleName>\n";
      }
    else if(count2==4)
      {
      os << "</NamePrefix>\n";
      }
    else if(count2==5)
      {
      os << "</NameSuffix>\n";
      }
    if(count1==1)
      {
      os << "</SingleByte>\n";
      }
    else if(count1==2)
      {
      os << "</Ideographic>\n";
      }
    else if(count1==3)
      {
      os << "</Phonetic>\n";
      }
    os << "</PersonName>";
    }

  void ByteValue::PrintASCIIXML(std::ostream &os) const
    {
    //VL length = std::min(maxlength, Length);
    // Special case for VR::UI, do not print the trailing \0

    /*if(Length && Internal[Length-1] == 0 )
      {
      Length = Length - 1;
      }
     */
    // Check for non printable characters

    int count = 1;
    os << "<Value number = \"" << count << "\" >";
    std::vector<char>::const_iterator it = Internal.begin();

    for(; it != (Internal.begin() + Length); ++it)
      {
      const char &c = *it;
      if ( c == '\\' )
        {
        count++;
        os << "</Value>\n";
        os << "<Value number = \"" << count << "\" >";
        }
      else if ( !c )
        {
        // \0 is found ...
        }
      else if(c == '&')
        os << "&amp;";
      else if(c == '<')
        os << "&lt;";
      else if(c == '>')
        os << "&gt;";
      else if(c == '\'')
        os << "&apos;";
      else if(c == '\"')
        os << "&quot;";
      else
        os << c;
      }
    os << "</Value>\n";
    }

  void ByteValue::PrintASCIIJSON(std::ostream &os) const
    {
    //VL length = std::min(maxlength, Length);
    // Special case for VR::UI, do not print the trailing \0

    /*if(Length && Internal[Length-1] == 0 )
      {
      Length = Length - 1;
      }
     */
    // Check for non printable characters
    std::string s = "";
    bool isvector = false;

    std::vector<char>::const_iterator it = Internal.begin();
    for(; it != (Internal.begin() + Length); ++it)
      {
      const char &c = *it;
      if ( c == '\\' )
        {
        isvector = true;
        }

      if(c == '\0'){
        break;
      }else if(c < 32 || c > 126){
          s += " ";
      }else if(c == '\"'){
          s += "\\\"";
      }else{
        s += c;
      }
    }

    if(isvector){
        std::vector< std::string > vect;
        int start = 0;
        int next = s.find("\\");
        while(next != -1){
            vect.push_back(s.substr(start, next-start));
            start = next + 1;
            next = s.find("\\", start);
            if(next == -1){
                vect.push_back(s.substr(start));
            }
        }
        std::string res = "";
        for(int i = 0; i< vect.size(); i++){
            if(isFloat(vect[i])){
                res+=vect[i];
            }else{
                res+= "\"" + vect[i] + "\"";
            }
            if(i < vect.size() - 1)
                res += ",";
        }
        if(vect.size() == 1){
            os<<res;
        }else{
            os<<"["<<res<<"]";
        }
    }else{
        try{
            if(isFloat(s)){
                double v = atof(s.c_str());
                if(ceil(v) == v && floor(v) == v){
                    int t = (int)v;
                    os<<t;
                }else{
                    os<<std::setprecision( 6 )<<v;
                }

            }else{
                os<<"\""<<s<<"\"";
            }

        }catch(Exception* e){
            os<<"\""<<s<<"\"";
        }

    }

  }

bool ByteValue::isFloat( std::string& s ) const {
    //Delete all empty spaces from end
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    //Delete all empty spaces from begin
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    std::istringstream iss(s);
    float f;
    iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}


  void ByteValue::PrintHexXML(std::ostream &os ) const
    {
    //VL length = std::min(maxlength, Length);
    // WARNING: Internal.end() != Internal.begin()+Length

    std::vector<char>::const_iterator it = Internal.begin();
    os << std::hex;
    for(; it != Internal.begin() + Length; ++it)
      {
      //const char &c = *it;
      uint8_t v = *it;
      if( it != Internal.begin() ) os << "\\";
      os << std::setw( 2 ) << std::setfill( '0' ) << (uint16_t)v;
      //++it;
      //os << std::setw( 1 ) << std::setfill( '0' ) << (int)*it;
      }
    os << std::dec;
    }
   
  void ByteValue::Append(ByteValue const & bv)
    {
    //Internal.resize( Length + bv.Length );
    Internal.insert( Internal.end(), bv.Internal.begin(), bv.Internal.end());
    Length += bv.Length;
    // post condition
    assert( Internal.size() % 2 == 0 && Internal.size() == Length );
    }
   
}
