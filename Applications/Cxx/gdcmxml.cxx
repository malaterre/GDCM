/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "gdcmFilename.h"
#include "gdcmReader.h"
#include "gdcmVersion.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmDataSet.h"
#include "gdcmDataElement.h"
#include "gdcmAttribute.h"
#include "gdcmPrivateTag.h"
#include "gdcmValidate.h"
#include "gdcmWriter.h"
#include "gdcmSystem.h"
#include "gdcmDirectory.h"
#include "gdcmCSAHeader.h"
#include "gdcmPDBHeader.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmASN1.h"
#include "gdcmFile.h"
#include "gdcmXMLPrinter.h"
#include "gdcmPrinter.h"

#ifdef GDCM_USE_SYSTEM_LIBXML2
#include <libxml/xmlreader.h>
#endif

#include <string>
#include <iostream>
#include <fstream>

#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
#include <string.h>

using namespace gdcm;

// This is a very dumb implementation for getData handling
// by default GDCM simply drop the BulkData so we need to store
// the actual BulkData somewhere for proper implementation of getData
class SimpleFileXMLPrinter : public XMLPrinter
{
public:
  void HandleBulkData(const char *uuid,
    const char *bulkdata, size_t bulklen)
    {
    std::ofstream out( uuid, std::ios::binary );
    out.write( bulkdata, bulklen );
    out.close();
    }
};

void PrintVersion()
{
  std::cout << "gdcmxml: gdcm " << gdcm::Version::GetVersion() << " ";
  const char date[] = "$Date$";
  std::cout << date << std::endl;
}

void PrintHelp()
{
  PrintVersion();
  std::cout << "Usage: gdcmxml [OPTION]... FILE..." << std::endl;
  std::cout << "Convert a DICOM file into an XML file or vice-versa \n";
  std::cout << "Parameter (required):" << std::endl;
  std::cout << "  -i --input     Filename1" << std::endl;
  std::cout << "  -o --output    Filename2" << std::endl;
  std::cout << "General Options:" << std::endl;
  std::cout << "  -B --loadBulkData   for DICOM -> XML, loads all bulk data like Pixel Data (by default UUID are written)." << std::endl;
  std::cout << "  -V --verbose        more verbose (warning+error)." << std::endl;
  std::cout << "  -W --warning        print warning info." << std::endl;
  std::cout << "  -D --debug          print debug info." << std::endl;
  std::cout << "  -E --error          print error info." << std::endl;
  std::cout << "  -h --help           print help." << std::endl;
  std::cout << "  -v --version        print version." << std::endl;
}

#ifdef GDCM_USE_SYSTEM_LIBXML2
void HandlePN()
	{
	}
void HandleSequence(SequenceOfItems &sqi,xmlTextReaderPtr reader,DataSet &DS,int depth);
void PopulateDataSet(xmlTextReaderPtr reader,DataSet &DS, int depth, bool SetSQ )
{		
	 int ret;	
   //int ret = xmlTextReaderRead(reader);/**/
   //ret = xmlTextReaderRead(reader); /* moving past tag <NativeDicomModel> */
   const char *name = (const char*)xmlTextReaderConstName(reader);
	 //printf("%s\n",name);				

#define LoadValueASCII(type) \
  case type: \
    		{ \
      	int count =0; \
      	name = (const char*)xmlTextReaderConstName(reader); \
      	if(strcmp(name,"DicomAttribute") == 0 && xmlTextReaderNodeType(reader) == 15)\
      		break;\
      	char values[10][100] = {"","","","","","","","","",""}; \
      	Element<type,VM::VM1_n> el; \
    		while(strcmp(name,"Value") == 0) \
    			{ \
    			ret = xmlTextReaderRead(reader); \
    			char *value = (char*)xmlTextReaderConstValue(reader); \
    			strcpy((char *)values[count++],value); \
    			ret = xmlTextReaderRead(reader);/*Value ending tag*/ \
    			name = (const char*)xmlTextReaderConstName(reader); \
    			ret = xmlTextReaderRead(reader);ret = xmlTextReaderRead(reader); \
    			name = (const char*)xmlTextReaderConstName(reader); \
    			} \
    		el.SetLength( (count) * vr.GetSizeof() ); \
    		int total = 0; \
    		while(total < count) \
    			{ \
    			el.SetValue(/*(typename VRToType<VR::CS>::Type)*/values[total],total); \
    			total++; \
    			} \
    		de = el.GetAsDataElement(); \
    		}break

#define LoadValueInteger(type) \
  case type: \
    		{ \
      	int count =0; \
      	name = (const char*)xmlTextReaderConstName(reader); \
      	if(strcmp(name,"DicomAttribute") == 0 && xmlTextReaderNodeType(reader) == 15)\
      		break;\
      	int values[10]; \
      	Element<type,VM::VM1_n> el; \
    		while(strcmp(name,"Value") == 0) \
    			{ \
    			ret = xmlTextReaderRead(reader); \
    			char *value_char = (char*)xmlTextReaderConstValue(reader); \
    			sscanf(value_char,"%d",&(values[count++]));  \
    			ret = xmlTextReaderRead(reader);/*Value ending tag*/ \
    			name = (const char*)xmlTextReaderConstName(reader); \
    			ret = xmlTextReaderRead(reader);ret = xmlTextReaderRead(reader); \
    			name = (const char*)xmlTextReaderConstName(reader); \
    			} \
    		el.SetLength( (count) * vr.GetSizeof() ); \
    		int total = 0; \
    		while(total < count) \
    			{ \
    			el.SetValue(values[total],total); \
    			total++; \
    			} \
    		de = el.GetAsDataElement(); \
    		}break

#define LoadValueFloat(type) \
  case type: \
    		{ \
      	int count =0; \
      	name = (const char*)xmlTextReaderConstName(reader); \
      	if(strcmp(name,"DicomAttribute") == 0 && xmlTextReaderNodeType(reader) == 15)\
      		break;\
      	float values[10]; \
      	Element<type,VM::VM1_n> el; \
    		while(strcmp(name,"Value") == 0) \
    			{ \
    			ret = xmlTextReaderRead(reader); \
    			char *value_char = (char*)xmlTextReaderConstValue(reader); \
    			sscanf(value_char,"%f",&(values[count++]));  \
    			ret = xmlTextReaderRead(reader);/*Value ending tag*/ \
    			name = (const char*)xmlTextReaderConstName(reader); \
    			ret = xmlTextReaderRead(reader);ret = xmlTextReaderRead(reader); \
    			name = (const char*)xmlTextReaderConstName(reader); \
    			} \
    		el.SetLength( (count) * vr.GetSizeof() ); \
    		int total = 0; \
    		while(total < count) \
    			{ \
    			el.SetValue(values[total],total); \
    			total++; \
    			} \
    		de = el.GetAsDataElement(); \
    		}break

#define LoadValueDouble(type) \
  case type: \
    		{ \
      	int count =0; \
      	name = (const char*)xmlTextReaderConstName(reader); \
      	if(strcmp(name,"DicomAttribute") == 0 && xmlTextReaderNodeType(reader) == 15)\
      		break;\
      	double values[10]; \
      	Element<type,VM::VM1_n> el; \
    		while(strcmp(name,"Value") == 0) \
    			{ \
    			ret = xmlTextReaderRead(reader); \
    			char *value_char = (char*)xmlTextReaderConstValue(reader); \
    			sscanf(value_char,"%lf",&(values[count++]));  \
    			ret = xmlTextReaderRead(reader);/*Value ending tag*/ \
    			name = (const char*)xmlTextReaderConstName(reader); \
    			ret = xmlTextReaderRead(reader);ret = xmlTextReaderRead(reader); \
    			name = (const char*)xmlTextReaderConstName(reader); \
    			} \
    		el.SetLength( (count) * vr.GetSizeof() ); \
    		int total = 0; \
    		while(total < count) \
    			{ \
    			el.SetValue(values[total],total); \
    			total++; \
    			} \
    		de = el.GetAsDataElement(); \
    		}break
    		
          
   while(  (xmlTextReaderDepth(reader)!=0) && !(SetSQ && (xmlTextReaderDepth(reader)==depth) && (strcmp(name,"Item")==0)  )  )
		{
   	if(strcmp(name,"DicomAttribute") == 0)
			{
			DataElement de;
			
			/* Reading Tag */
			char *tag_read =(char *)xmlTextReaderGetAttribute(reader,(const unsigned char*)"tag");
  		Tag t;
  		if(!t.ReadFromContinuousString((const char *)tag_read))
  			assert(0 && "Invalid Tag!");
		  
		  /* Reading VR */
		  char vr_read[3] = "";
		  strcpy(vr_read, (const char *)xmlTextReaderGetAttribute(reader,(const unsigned char*)"vr"));
		  vr_read[2]='\0';
  		const gdcm::VR vr = gdcm::VR::GetVRType(vr_read);
  		
  		ret=xmlTextReaderRead(reader);// at 14 NodeType
  		
		  ret=xmlTextReaderRead(reader);// should be at value tag or BulkData tag or Item Tag
		  /* Load Value */
		  switch(vr)
		  	{
		  	LoadValueASCII(VR::AE);
		  	LoadValueASCII(VR::AS);
				LoadValueASCII(VR::CS);
				LoadValueASCII(VR::DA);
				LoadValueFloat(VR::DS);
				LoadValueASCII(VR::DT);
				LoadValueInteger(VR::IS);
				LoadValueASCII(VR::LO);
				LoadValueASCII(VR::LT);				
				LoadValueASCII(VR::SH);
				LoadValueASCII(VR::ST);
				LoadValueASCII(VR::TM);
				LoadValueASCII(VR::UI);
				LoadValueASCII(VR::UT);
				LoadValueInteger(VR::SS);
    		LoadValueInteger(VR::UL);
 				LoadValueInteger(VR::SL);
    		LoadValueInteger(VR::US);
    		LoadValueFloat(VR::FL);
    		LoadValueDouble(VR::FD);
    		case VR::SQ:
    			{
    			SequenceOfItems sqi;
    			HandleSequence(sqi,reader,DS,xmlTextReaderDepth(reader));
    			de.SetValue(sqi);
    			}break;
    		
    		case VR::PN:
    			{
    			HandlePN();
    			}break;	
    			
    		default:
    			assert(0 && "Unknown VR");	
		  	};
		  
		  /*Modify de to insert*/
		  
		  de.SetTag(t);	  
		  
		  DS.Insert(de);
		  /*
		  while(xmlTextReaderNodeType(reader) != 15)
		  	ret = xmlTextReaderRead(reader);
		  
		  if(strcmp((const char*)xmlTextReaderConstName(reader),"DicomAttribute") == 0)
		  	{
		  	while(xmlTextReaderNodeType(reader) != 15 && strcmp((const char*)xmlTextReaderConstName(reader),"DicomAttribute") == 0)
		  		{
		  		if(xmlTextReaderDepth(reader) == 0)
		  			return;
		  		}
		  	}
		  else
		  	assert("No proper end tag" && 0);		
		  */
		  /*Read Next DataElement*/
		  
		  
			}
		//ret = xmlTextReaderRead(reader);	
		//name = (const char*)xmlTextReaderConstName(reader);
			   	
   	}
}

void HandleSequence(SequenceOfItems &sqi, xmlTextReaderPtr reader,DataSet &DS,int depth)
{
	int ret;	
  const char *name = (const char*)xmlTextReaderConstName(reader);// Should be item
    
  ret = xmlTextReaderRead(reader);
  ret = xmlTextReaderRead(reader);//at /Dicom
  name = (const char*)xmlTextReaderConstName(reader);
  /*if((strcmp(name,"Item") == 0) && (xmlTextReaderDepth(reader) == depth) && (xmlTextReaderNodeType(reader) == 15) )
  	{
  	ret = xmlTextReaderRead(reader);ret = xmlTextReaderRead(reader);ret = xmlTextReaderRead(reader);
  	name = (const char*)xmlTextReaderConstName(reader);
   	return;// Empty SQ
   	}*/  
  
  do  
  	{
  	Item item;
  	DataSet NestedDS;
  	PopulateDataSet(reader,NestedDS,depth,true);
  	item.SetNestedDataSet(NestedDS);
  	sqi.AddItem(item);
  	ret = xmlTextReaderRead(reader);
  	ret = xmlTextReaderRead(reader);
  	name = (const char*)xmlTextReaderConstName(reader);
  	}while(!(strcmp(name,"Item") == 0) && (xmlTextReaderDepth(reader) == depth));
  ret = xmlTextReaderRead(reader);
  ret = xmlTextReaderRead(reader);	
}

void WriteDICOM(xmlTextReaderPtr reader, gdcm::Filename file2)
{
	//populate DS
	int ret = xmlTextReaderRead(reader);
	if(ret == -1)
		assert(0 && "unable to read");
	//while(xmlTextReaderDepth(reader) != 1)
	//ret = xmlTextReaderRead(reader);
	ret = xmlTextReaderRead(reader);
	ret = xmlTextReaderRead(reader);// at first element
	
	DataSet DS;
	if(xmlTextReaderDepth(reader) == 1 && strcmp((const char*)xmlTextReaderConstName(reader),"DicomAttribute") == 0)  
  	PopulateDataSet(reader,DS,1,false);
  
  //add to File 
  File F;
  F.SetDataSet(DS);
  
  //Validate - possibly from gdcmValidate Class
  
  
  Printer printer;
  printer.SetFile ( F );
  //printer.SetColor( color != 0);
  printer.Print( std::cout );
  //add to Writer
  Writer W;
  W.SetFile(F);  
  W.CheckFileMetaInformationOff();
  W.SetFileName(file2.GetFileName());
  
  //finally write to file
  W.Write(); 
  
}

static void XMLtoDICOM(gdcm::Filename file1, gdcm::Filename file2)
{
  xmlTextReaderPtr reader;  
  FILE *in;
  char *buffer;
  long numBytes;
  in = fopen(file1.GetFileName(), "r");
  
  if(in == NULL)
    return ;
    
  fseek(in, 0L, SEEK_END);
  numBytes = ftell(in);
  fseek(in, 0L, SEEK_SET);
  buffer = (char*)calloc(numBytes, sizeof(char));

  if(buffer == NULL)
    return ;

  fread(buffer, sizeof(char), numBytes, in);
  fclose(in);
  reader = xmlReaderForMemory  (buffer, numBytes, NULL, NULL, 0);
  //reader = xmlReaderForFile(filename, "UTF-8", 0);
  if (reader != NULL) 
    {
    WriteDICOM(reader, file2);
    } 
  else 
    {
    fprintf(stderr, "Unable to open %s\n", file1.GetFileName());
     }
}
#endif // GDCM_USE_SYSTEM_LIBXML2

int main (int argc, char *argv[])
{
  int c;
  //int digit_optind = 0;
  gdcm::Filename file1;
  gdcm::Filename file2;
  int loadBulkData = 0;
  int verbose = 0;
  int warning = 0;
  int debug = 0;
  int error = 0;
  int help = 0;
  int version = 0;
  while (1) {

    int option_index = 0;

    static struct option long_options[] = {
        {"input", 1, 0, 0},
        {"output", 1, 0, 0},
        {"loadBulkData", 0, &loadBulkData, 1},
        {"verbose", 0, &verbose, 1},
        {"warning", 0, &warning, 1},
        {"debug", 0, &debug, 1},
        {"error", 0, &error, 1},
        {"help", 0, &help, 1},
        {"version", 0, &version, 1},
        {0, 0, 0, 0} // required
    };
    static const char short_options[] = "i:o:BVWDEhv";
    c = getopt_long (argc, argv, short_options,
      long_options, &option_index);
    if (c == -1)
      {
      break;
      }

    switch (c)
      {
    case 0:
    case '-':
        {
        const char *s = long_options[option_index].name;
        if (optarg)
          {
          if( option_index == 0 ) /* input */
            {
            assert( strcmp(s, "input") == 0 );
            assert( file1.IsEmpty() );
            file1 = optarg;
            }
          }
        }
      break;

    case 'i':
      //printf ("option i with value '%s'\n", optarg);
      assert( file1.IsEmpty() );
      file1 = optarg;
      break;

    case 'o':
      assert( file2.IsEmpty() );
      file2 = optarg;
      break;

    case 'B':
      loadBulkData = 1;
      break;

    case 'V':
      verbose = 1;
      break;

    case 'W':
      warning = 1;
      break;

    case 'D':
      debug = 1;
      break;

    case 'E':
      error = 1;
      break;

    case 'h':
      help = 1;
      break;

    case 'v':
      version = 1;
      break;

    case '?':
      break;

    default:
      printf ("?? getopt returned character code 0%o ??\n", c);
      }
  }

  if (optind < argc)
    {
    int v = argc - optind;
    if( v == 2 )
      {
      file1 = argv[optind];
      file2 = argv[optind+1];
      }
    else if( v == 1 )
      {
      file1 = argv[optind];
      }
    else
      {
      PrintHelp();
      return 1;
      }
    }

  if( file1.IsEmpty() )
    {
    PrintHelp();
    return 1;
    }

  if( version )
    {
    PrintVersion();
    return 0;
    }

  if( help )
    {
    PrintHelp();
    return 0;
    }
  
  const char *file1extension = file1.GetExtension();
  //const char *file2extension = file2.GetExtension();

  if(gdcm::System::StrCaseCmp(file1extension,".xml") != 0)// by default we assume it is a DICOM file-- as no extension is required for it
    {
    gdcm::Reader reader;
    reader.SetFileName( file1.GetFileName() );
    bool success = reader.Read();
    if( !success )//!ignoreerrors )
      {
      std::cerr << "Failed to read: " << file1 << std::endl;
      return 1;
      }

    //SimpleFileXMLPrinter printer;
    XMLPrinter printer;
    printer.SetFile ( reader.GetFile() );
    printer.SetStyle ( (XMLPrinter::PrintStyles)loadBulkData );

    if( file2.IsEmpty() )
      {
      printer.Print( std::cout );
      }
    else
      {
      std::ofstream outfile;
      outfile.open (file2.GetFileName());
      printer.Print( outfile );
      outfile.close();
      }
    return 0;
    }
  else
    {
#ifdef GDCM_USE_SYSTEM_LIBXML2
    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    XMLtoDICOM(file1,file2);

    /*
     * Cleanup function for the XML library.
     */
    xmlCleanupParser();
    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();
#else
		printf("\nPlease configure Cmake options with GDCM_USE_SYSTEM_LIBXML2 as ON and compile!\n");    
#endif
    }
}
