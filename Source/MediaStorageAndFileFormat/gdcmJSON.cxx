/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmJSON.h"
#include "gdcmGlobal.h"
#include "gdcmDicts.h"

#ifdef GDCM_USE_SYSTEM_JSON
#include <json/json.h>
#endif

/*
 * Implementation is done based on Sup166, which may change in the future.
 */
namespace gdcm
{

class JSONInternal
{
public:
  JSONInternal():PrettyPrint(false){}
  bool PrettyPrint;
};

JSON::JSON()
{
  Internals = new JSONInternal;
}

JSON::~JSON()
{
  delete Internals;
}

void JSON::SetPrettyPrint(bool onoff)
{
  Internals->PrettyPrint = onoff;
}
bool JSON::GetPrettyPrint() const
{
  return Internals->PrettyPrint;
}
void JSON::PrettyPrintOn()
{
  Internals->PrettyPrint = true;
}
void JSON::PrettyPrintOff()
{
  Internals->PrettyPrint = false;
}

// Encode from DICOM to JSON
// TODO: do I really need libjson for this task ?
// FIXME: once again everything is loaded into memory
static void ProcessNestedDataSet( const DataSet & ds, json_object *my_object )
{
  const Global& g = GlobalInstance;
  const Dicts &dicts = g.GetDicts();
  const Dict &d = dicts.GetPublicDict(); (void)d;

  for( DataSet::ConstIterator it = ds.Begin();
    it != ds.End(); ++it )
    {
    const DataElement &de = *it;
    VR const & vr = de.GetVR();
    const Tag& t = de.GetTag();
    std::string strowner;
    const char *owner = 0;
    if( t.IsPrivate() && !t.IsPrivateCreator() )
      {
      strowner = ds.GetPrivateCreator(t);
      owner = strowner.c_str();
      }
    const DictEntry &entry = dicts.GetDictEntry(t,owner);
    const char *keyword = entry.GetKeyword();
    const std::string & str_tag = t.PrintAsContinuousString();
    const char * vr_str = VR::GetVRString(vr);

    json_object *my_object_cur;
    my_object_cur = json_object_new_object();
    json_object *my_array;
    my_array = json_object_new_array();

    json_object_object_add(my_object_cur, "Tag",
      json_object_new_string( str_tag.c_str()) );
    json_object_object_add(my_object_cur, "VR",
      json_object_new_string( vr_str ) );

    if( vr == VR::SQ )
      {
      SmartPointer<SequenceOfItems> sqi;
      sqi = de.GetValueAsSQ();
      if( sqi )
        {
        int nitems = sqi->GetNumberOfItems();
        for(int i = 1; i <= nitems; ++i)
          {
          const Item &item = sqi->GetItem( i );
          const DataSet &nested = item.GetNestedDataSet();

          json_object *my_object_sq;
          my_object_sq = json_object_new_object();

          ProcessNestedDataSet( nested, my_object_sq );
          json_object_array_add(my_array, my_object_sq );
          }
        json_object_object_add(my_object_cur, "Sequence", my_array );
        }
      }
    else if( VR::IsASCII( vr ) )
      {
      /*
      "StudyInstanceUID": {
      "Tag": "0020000D",
      "VR": "UI",
      "Value": [ "1.2.392.200036.9116.2.2.2.1762893313.1029997326.945873" ]
      },
       */
      if( de.IsEmpty() )
        {
        }
      else
        {
        const ByteValue * bv = de.GetByteValue();

        const char * value = bv->GetPointer();
        const size_t len = bv->GetLength();
        json_object_array_add(my_array, json_object_new_string_len(value, len));

        json_object_object_add(my_object_cur, "Value", my_array );
        }
      }
    else
      {
      switch( vr )
        {
      case VR::FL:
          {
          Element<VR::FL,VM::VM1_n> el;
          el.Set( de.GetValue() );
          int ellen = el.GetLength();
          for( int i = 0; i < ellen; ++i )
            {
            json_object_array_add(my_array, json_object_new_double( el.GetValue( i ) ));
            }
          }
        break;
      case VR::UL:
          {
          Element<VR::UL,VM::VM1_n> el;
          el.Set( de.GetValue() );
          int ellen = el.GetLength();
          for( int i = 0; i < ellen; ++i )
            {
            json_object_array_add(my_array, json_object_new_int( el.GetValue( i ) ));
            }
          }
        break;
      default:
        assert( 0 );
        }
      json_object_object_add(my_object_cur, "Value", my_array );
      }
    json_object_object_add(my_object, keyword, my_object_cur );
    }
}

bool JSON::Code(DataSet const & ds, std::ostream & os)
{
#ifdef GDCM_USE_SYSTEM_JSON
#if 0
  json_object *my_string;
  my_string = json_object_new_string("coucou");
//  printf("my_string=%s\n", json_object_get_string(my_string));
//  printf("my_string.to_string()=%s\n", json_object_to_json_string(my_string));

  const char* str = json_object_to_json_string( my_string );
  os << str;

  json_object_put(my_string); // free memory
#endif
  json_object *my_object;
  my_object = json_object_new_object();

  ProcessNestedDataSet( ds, my_object );

  const char* str = NULL;
  if( Internals->PrettyPrint )
    {
#ifdef JSON_C_VERSION
    str = json_object_to_json_string_ext(my_object, JSON_C_TO_STRING_PRETTY );
#else
    str = json_object_to_json_string( my_object );
#endif
    }
  else
    {
    str = json_object_to_json_string( my_object );
    }
  os << str;
  json_object_put(my_object); // free memory
  return true;
#else
  (void)file;
  (void)os;
  return false;
#endif
}

// Paranoid
static bool CheckTagKeywordConsistency( const char *name, const Tag & thetag )
{
  // Can be keyword or tag
  assert( name );

  // start with easy one:
  // only test first string character:
  bool istag = *name >= '0' && *name <= '9'; // should be relatively efficient
  if( istag )
    {
    assert( strlen(name) == 8 );
    Tag t;
    t.ReadFromContinuousString( name );
    return t == thetag;
    }
  // else keyword:
  const Global& g = GlobalInstance;
  const Dicts &dicts = g.GetDicts();
  const Dict &d = dicts.GetPublicDict();
  const char * keyword = d.GetKeywordFromTag(thetag);
  if( !keyword )
    {
    gdcmDebugMacro( "Unknown Keyword: " << name );
    return true;
    }
  // else
  return strcmp( name, keyword ) == 0;
}

static void ProcessJSONElement( const char *keyword, json_object * obj, DataElement & de )
{
  json_type jtype = json_object_get_type( obj );
  assert( jtype == json_type_object );
  //const char * dummy = json_object_to_json_string ( obj );
  //const char * dummy2 = json_object_to_json_string ( tag );
  json_object * jtag = json_object_object_get(obj, "Tag");
  json_object * jvr = json_object_object_get(obj, "VR");
  json_object * jvalue = json_object_object_get(obj, "Value");
  const char * tag_str = json_object_get_string ( jtag );
  const char * vr_str = json_object_get_string ( jvr );
  de.GetTag().ReadFromContinuousString( tag_str );
  assert( CheckTagKeywordConsistency( keyword, de.GetTag() ) );

  VR::VRType vrtype = VR::GetVRTypeFromFile( vr_str );
  assert( vrtype != VR::VR_END );
  de.SetVR( vrtype );
  if( vrtype == VR::SQ )
    {
    json_type jvaluetype = json_object_get_type( jvalue );
    assert( jvaluetype == json_type_null );
    json_object * jseq = json_object_object_get(obj, "Sequence");
    json_type jsqtype = json_object_get_type( jseq );
    assert( jsqtype == json_type_null || jsqtype == json_type_array );

    if( jsqtype == json_type_array )
      {
      // Create a Sequence
      gdcm::SmartPointer<gdcm::SequenceOfItems> sq = new gdcm::SequenceOfItems;
      sq->SetLengthToUndefined();

      int sqlen = json_object_array_length ( jseq );
      for( int itemidx = 0; itemidx < sqlen; ++itemidx )
        {
        json_object * jitem = json_object_array_get_idx ( jseq, itemidx );
        json_type jitemtype = json_object_get_type( jitem );
        assert( jitemtype == json_type_object );
        //const char * dummy = json_object_to_json_string ( jitem );

        // Create an item
        gdcm::Item item;
        item.SetVLToUndefined();
        gdcm::DataSet &nds = item.GetNestedDataSet();

#ifdef JSON_C_VERSION
        json_object_iterator it;
        json_object_iterator itEnd;
        it = json_object_iter_begin(jitem);
        itEnd = json_object_iter_end(jitem);

        while (!json_object_iter_equal(&it, &itEnd))
          {
          const char *name = json_object_iter_peek_name(&it);
          assert( name );
          json_object * value = json_object_iter_peek_value (&it);
          DataElement lde;
          ProcessJSONElement( name, value, lde );
          nds.Insert( lde );
          json_object_iter_next(&it);
          }
#endif
        sq->AddItem(item);
        }

      // Insert sequence into data set
      de.SetValue(*sq);
      de.SetVLToUndefined();
      }
    }
  else if( VR::IsASCII( vrtype ) )
    {
    json_type jvaluetype = json_object_get_type( jvalue );
    //const char * dummy = json_object_to_json_string ( jvalue );
    assert( jvaluetype == json_type_array || jvaluetype == json_type_null );
    if( jvaluetype == json_type_array )
      {
      int valuelen = json_object_array_length ( jvalue );
      assert( valuelen == 1 );
      json_object * value0 = json_object_array_get_idx ( jvalue, 0 );
      const char * value_str = json_object_get_string ( value0 );
      if( value_str )
        de.SetByteValue( value_str, strlen( value_str ) );
      }
    }
  else
    {
    json_type jvaluetype = json_object_get_type( jvalue );
    //const char * dummy = json_object_to_json_string ( jvalue );
    assert( jvaluetype == json_type_array || jvaluetype == json_type_null );
    if( jvaluetype == json_type_array )
      {
      DataElement locde;
      const int valuelen = json_object_array_length ( jvalue );
      const int vrsizeof = de.GetVR().GetSizeof();
      switch( vrtype )
        {
      case VR::FL:
          {
          Element<VR::FL,VM::VM1_n> el;
          el.SetLength( valuelen * vrsizeof );
          for( int validx = 0; validx < valuelen; ++validx )
            {
            json_object * value = json_object_array_get_idx ( jvalue, validx );
            assert( json_object_get_type( value ) == json_type_double );
            const double v = json_object_get_double ( value );
            el.SetValue(v, validx);
            }
          locde = el.GetAsDataElement();
          }
        break;
      case VR::UL:
          {
          Element<VR::UL,VM::VM1_n> el;
          el.SetLength( valuelen * vrsizeof );
          for( int validx = 0; validx < valuelen; ++validx )
            {
            json_object * value = json_object_array_get_idx ( jvalue, validx );
            assert( json_object_get_type( value ) == json_type_int );
            const int v = json_object_get_int( value );
            el.SetValue(v, validx);
            }
          locde = el.GetAsDataElement();
          }
        break;
      default:
        assert( 0 );
        }
      de.SetValue( locde.GetValue() );
      }
    }
}

bool JSON::Decode(std::istream & is, DataSet & ds)
{
#ifdef GDCM_USE_SYSTEM_JSON

#ifdef JSON_C_VERSION
  json_object *jobj = NULL;
  const char *mystring = NULL;
  int stringlen = 0;
  enum json_tokener_error jerr;
  std::string str;
  json_tokener * tok = json_tokener_new ();
  do
    {
    std::getline( is, str );
    mystring = str.c_str();
    stringlen = str.size();
    jobj = json_tokener_parse_ex(tok, mystring, stringlen);
    } while ((jerr = json_tokener_get_error(tok)) == json_tokener_continue);

  if (jerr != json_tokener_success)
    {
    fprintf(stderr, "Error: %s\n", json_tokener_error_desc(jerr));
    // Handle errors, as appropriate for your application.
    }
  if (tok->char_offset < stringlen) // XXX shouldn't access internal fields
    {
    // Handle extra characters after parsed object as desired.
    // e.g. issue an error, parse another object from that point, etc...
    }
  // Success, use jobj here.
  json_tokener_free( tok );
#else
  std::stringstream ss;
  std::string str;
  while( std::getline( is, str ) )
    {
    ss << str;
    }
  const std::string & wholestr = ss.str();
  json_object *obj;
  obj = json_tokener_parse( wholestr.c_str() );
#endif

#ifdef JSON_C_VERSION
  json_object_iterator it;
  json_object_iterator itEnd;
  it = json_object_iter_begin(jobj);
  itEnd = json_object_iter_end(jobj);

  while (!json_object_iter_equal(&it, &itEnd))
    {
    const char *name = json_object_iter_peek_name(&it);
    assert( name );
    json_object * value = json_object_iter_peek_value (&it);
    DataElement de;
    ProcessJSONElement( name, value, de );
    ds.Insert( de );
    json_object_iter_next(&it);
    }
#else
#endif

  return true;
#else
  (void)is;
  (void)file;
  return false;
#endif
}

} // end namespace gdcm
