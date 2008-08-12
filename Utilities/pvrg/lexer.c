/*************************************************************
Copyright (C) 1990, 1991, 1993 Andy C. Hung, all rights reserved.
PUBLIC DOMAIN LICENSE: Stanford University Portable Video Research
Group. If you use this software, you agree to the following: This
program package is purely experimental, and is licensed "as is".
Permission is granted to use, modify, and distribute this program
without charge for any purpose, provided this license/ disclaimer
notice appears in the copies.  No warranty or maintenance is given,
either expressed or implied.  In no event shall the author(s) be
liable to you or a third party for any special, incidental,
consequential, or other damages, arising out of the use or inability
to use the program for any purpose (or the loss of data), even if we
have been advised of such possibilities.  Any public reference or
advertisement of this source code should refer to it as the Portable
Video Research Group (PVRG) code, and not by any author(s) (or
Stanford University) name.
*************************************************************/
# include "stdio.h"
# define U(x) ((x)&0377)
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# define YYLMAX 200
# define output(c) putc(c,yyout)
# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
# define unput(c) {yytchar= (c);if(yytchar=='\n')yylineno--;*yysptr++=yytchar;}
# define yymore() (yymorfg=1)
# define ECHO fprintf(yyout, "%s",yytext)
# define REJECT { nstr = yyreject(); goto yyfussy;}
int yyleng; extern char yytext[];
int yymorfg;
extern char *yysptr, yysbuf[];
int yytchar;
FILE *yyin ={stdin}, *yyout ={stdout};
extern int yylineno;
struct yysvf { 
	struct yywork *yystoff;
	struct yysvf *yyother;
	int *yystops;};
struct yysvf *yyestate;
extern struct yysvf yysvec[], *yybgin;

/*LABEL lexer.c */

/* Redefine the yywrap so that we don't have
   to worry about lex library */

# define yywrap() (1)

static char *ReservedWords[] = {   /* Token names */
"COMPONENT",
"SCAN",
"QUANTIZATION",
"DCSPEC",
"ACCUSTOM",
"DCCUSTOM",
"PRINTSCAN",
"PRINTFRAME",
"PRINTIMAGE",
"OPENSCAN",
"ACSPEC",
"WRITESCAN",
"WRITEFRAME",
"WRITESOI",
"WRITEQUANTIZATION",
"WRITERESYNC",
"WRITEHUFFMAN",
"FREQUENCY",
"ACSEND",
"DCSEND",
"QSEND",
"STREAMNAME",
"IMAGEHEIGHT",
"IMAGEWIDTH",
"RESYNC",
"BUFFER",
"OPENSTREAM",
"CLOSESTREAM",
"FRAMEHEIGHT",
"FRAMEWIDTH",
"CLOSESCAN",
"WRITEEOI",
"ECHO",
"WRITESPECIAL",
"WRITEDIRECT",
"LUMINANCEDEFAULT",
"CHROMINANCEDEFAULT",
"ENABLE",
"SCANDNL",
"WRITEDNL",
"AUTO",
"EMPTY",
""};

#define R_COMPONENT 1           /* Token values mapped to token names */
#define R_SCAN 2
#define R_QUANTIZATION 3
#define R_DCSPEC 4
#define R_ACCUSTOM 5
#define R_DCCUSTOM 6
#define R_PRINTSCAN 7
#define R_PRINTFRAME 8
#define R_PRINTIMAGE 9
#define R_OPENSCAN 10
#define R_ACSPEC 11
#define R_WRITESCAN 12
#define R_WRITEFRAME 13
#define R_WRITESOI 14
#define R_WRITEQUANTIZATION 15
#define R_WRITERESYNC 16
#define R_WRITEHUFFMAN 17
#define R_FREQUENCY 18
#define R_ACSEND 19
#define R_DCSEND 20
#define R_QSEND 21
#define R_STREAMNAME 22
#define R_IMAGEHEIGHT 23
#define R_IMAGEWIDTH 24
#define R_RESYNC 25
#define R_BUFFER 26
#define R_OPENSTREAM 27
#define R_CLOSESTREAM 28
#define R_FRAMEHEIGHT 29
#define R_FRAMEWIDTH 30
#define R_CLOSESCAN 31
#define R_WRITEEOI 32
#define R_ECHO 33
#define R_WRITESPECIAL 34
#define R_WRITEDIRECT 35
#define R_LUMINANCEDEFAULT 36
#define R_CHROMINANCEDEFAULT 37
#define R_ENABLE 38
#define R_SCANDNL 39
#define R_WRITEDNL 40
#define R_AUTO 41
#define R_EMPTY 42

#define R_INTEGER 1000      /* Special TYPES for tokens */
#define R_LBRACKET 1001
#define R_RBRACKET 1002
#define R_ID 1003
#define R_STRING 1004

int CommentDepth = 0;  /* depth of comment nesting */
int yyint=0;           /* Return value for integers */
int LexDebug=0;        /* Status of lex debugging */

#define PRIME 211
#define EOS '\0'

#define MakeStructure(S) (S *) malloc(sizeof(S))
#define InsertLink(link,list){\
if(!list){list=link;}else{link->next=list;list=link;}}

#define LINK struct link_def
struct id {         /* Default id structure */
  char *name;       /* Key */
  int tokentype;    /* Token type */
  int count;        /* Count of # references */
};

LINK {              /* A link for the hash buckets */
struct id *lid;     /* Current id */
LINK *next;         /* Pointer to next id */
};

/*PUBLIC*/

extern void initparser();
extern void parser();

static int hashpjw();
static LINK * MakeLink();
static struct id * enter();
static int getint();
static char * getstr();

/*PRIVATE*/

/*NOPROTO*/

# define NORMAL 2
# define COMMENT 4
# define YYNEWLINE 10
yylex(){
int nstr; extern int yyprevious;
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:
{}
break;
case 2:
{struct id *temp; temp = enter(0,yytext,yyleng); 
		 if (LexDebug)
		   {
		     printf("%s : %s (%d)\n",
			    yytext,
			    ((temp->tokentype) ? "RESERVED" : "IDENTIFIER"),
			    temp->count);
		   }
		 if (temp->tokentype)
		   {
		     return(temp->tokentype);
		   }
		 else
		   {
		     return(R_ID);
		   }
	       }
break;
case 3:
        {if (LexDebug)
			   {
			     printf("%s : %s\n", yytext, "REAL");
			   }
		       }
break;
case 4:
{if (LexDebug)
			   {             
			     printf("%s : %s\n", yytext, "INTEGER");
			   }
			 yyint = atoi(yytext);
			 return(R_INTEGER);}
break;
case 5:
{if (LexDebug)
			   {
			     printf("%s : %s\n", yytext, "(HEX)INTEGER");
			   }
			 yyint = strtol(yytext+2,NULL,16);
			 return(R_INTEGER);}
break;
case 6:
{if (LexDebug)
			   {
			     printf("%s : %s\n", yytext, "(HEX)INTEGER");
			   }
			 yyint = strtol(yytext,NULL,16);
			 return(R_INTEGER);}
break;
case 7:
{if (LexDebug)
			   {
			     printf("%s : %s\n", yytext, "(OCT)INTEGER");
			   }
			 yyint = strtol(yytext+2,NULL,8);
			 return(R_INTEGER);}
break;
case 8:
{if (LexDebug)
			   {
			     printf("%s : %s\n", yytext, "(OCT)INTEGER");
			   }
			 yyint = strtol(yytext,NULL,8);
			 return(R_INTEGER);}
break;
case 9:
{if (LexDebug)
			   {
			     printf("%s : %s\n", yytext, "(CHAR)INTEGER");
			   }
			 if (yyleng>4)
			   {
			     yyint = strtol(yytext+2,NULL,8);
			   }
			 else
			   {
			     if (*(yytext+1)=='\\')
			       {
				 switch(*(yytext+2))
				   {
				   case '0':
				     yyint=0;
				     break;
				   case 'b':
				     yyint = 0x8;
				     break;
				   case 'i':
				     yyint = 0x9;
				     break;
				   case 'n':
				     yyint = 0xa;
				     break;
				   case 'v':
				     yyint = 0xb;
				     break;
				   case 'f':
				     yyint = 0xc;
				     break;
				   case 'r':
				     yyint = 0xd;
				     break;
				   default:
				     yyint=(*yytext+2);
				     break;
				   }
			       }
			     else
			       {
				 yyint = *(yytext+1);
			       }
			   }
			 return(R_INTEGER);}
break;
case 10:
        {if (LexDebug)
			   {
			     printf("%s : %s\n", yytext, "LBRACKET");
			   }
			 return(R_LBRACKET);}
break;
case 11:
        {if (LexDebug)
			   {
			     printf("%s : %s\n", yytext, "RBRACKET");
			   }
			 return(R_RBRACKET);}
break;
case 12:
{if (LexDebug)
			   {
			     printf("%s : %s\n", yytext, "OPERATOR");
			   }
		       }
break;
case 13:
{if (LexDebug)
			   {
			     printf("%s : %s\n", yytext, "STRING");
			   }
			 return(R_STRING);}
break;
case 14:
{CommentDepth++; BEGIN COMMENT;}
break;
case 15:
	{CommentDepth--;if(!CommentDepth) BEGIN NORMAL;}
break;
case 16:
  	  	{
		  	    /* None of the above rules applicable, so
			       it's a bad symbol. */
                              printf("Bad input char '%c' on line %d\n",
  	  	  	  	    yytext[0],
  	  	  	  	    yylineno);
  	  	  	}
break;
case 17:
	{}
break;
case -1:
break;
default:
fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }
/* end of yylex */

/*PROTO*/
LINK *HashTable[PRIME];  /* My little hash table */

/*START*/

/*BFUNC

initparser() is used to place the Reserved Words into the hash table.
It must be called before the parser command is called.

EFUNC*/

void initparser()
{
  char i,**sptr;
  BEGIN NORMAL;

  for(i=1,sptr=ReservedWords;**sptr!='\0';i++,sptr++) 
    {     /* Add Reserved Words */
      enter(i,*sptr,strlen(*sptr));        /* Put reserved words in */
    }                                      /* hash table */
}

#undef BEGIN
#undef MakeStructure
#include "globals.h"
#include "stream.h"
#include "tables.h"

extern FRAME *CFrame;
extern IMAGE *CImage;
extern SCAN *CScan;
extern int ErrorValue;

/*BFUNC

hashpjw() returns a hash value for a string input.

EFUNC*/

static int hashpjw(s)
     char *s;
{
  BEGIN("hashpjw");
  char *p;
  unsigned int h=0,g;

  for(p=s;*p!=EOS;p++)       /* Taken from Aho Sethi Ullman Compilers book. */
    {
      h = (h << 4) + *p;
      if (g = h&0xf0000000)
	{
	  h = h ^(g >> 24);
	  h = h ^ g;
	}
    }
  return(h % PRIME);
}

/*BFUNC

MakeLink() is used to construct a link object. The link
is used for the hash table construct.

EFUNC*/


static LINK *MakeLink(tokentype,str,len)
     int tokentype;
     char *str;
     int len;
{
  BEGIN("MakeLink");
  LINK *temp;
  
  if (!(temp = MakeStructure(LINK)))            /* Make link */
    {
      WHEREAMI();
      printf("Cannot make a LINK.\n");
      exit(ERROR_MEMORY);
    }
  if (!(temp->lid = MakeStructure(struct id)))  /* Make id */
    {
      printf("Cannot make an id.\n");
      exit(ERROR_MEMORY);
    }
  temp->next = NULL;                            /* Set fields */
  if (!(temp->lid->name =(char *)calloc(len+1,sizeof(char))))
    {
      printf("Cannot make a string space for the link.\n");
      exit(ERROR_MEMORY);
    }
  strcpy(temp->lid->name,str);                 /* Copy key */
  temp->lid->tokentype = tokentype;
  temp->lid->count = 1; 
  return(temp);
}

/*BFUNC

enter() is used to enter a Reserved Word or ID into the hash table.

EFUNC*/

static struct id *enter(tokentype,str,len)
     int tokentype;
     char *str;
     int len;
{
  BEGIN("enter");
  int hashnum;
  LINK *temp,*current;
  char *ptr;

  for(ptr=str;*ptr!='\0';ptr++)          /* All capitals is fine */
    {
      if ((*ptr>='a') && (*ptr<='z'))
	{
	  *ptr = *ptr - ('a'-'A');
	}
    }
  hashnum = hashpjw(str);                /* Check if in hash table */
  for(temp=NULL,current=HashTable[hashnum];
      current!= NULL;
      current=current->next)
    {
      if (strcmp(str,current->lid->name) == 0)
	{
	  temp=current;
	  break;
	}
    }
  if (temp)                          /* Yes, found ID then return */
    {
      temp->lid->count++;
      return(temp->lid);
    }
  else                              /* Else make our own ID and return that*/
    {
      temp = MakeLink(tokentype,str,len);
      InsertLink(temp,HashTable[hashnum]);
      return(temp->lid);
    }
}

/*BFUNC

getint() takes an integer from the input.

EFUNC*/

static int getint()
{
  BEGIN("getint");
  int type;
  if ((type=yylex())!=R_INTEGER)
    {
      printf("Bad input, not integer, '%s' on line %d\n",
	     yytext,
	     yylineno);
      return(0);
    }
  return(yyint);
}

/*BFUNC

getstr() gets a string from the input. It copies the string to
temporary storage before it returns the pointer.

EFUNC*/

static char *getstr()
{
  BEGIN("getstr");
  char *tmp,*ptr,*bptr;
  int i,accum,flag;
  if (yylex() != R_STRING)                      /* Check if string */
    {
      printf("String expected.\n");
      if (!(tmp=(char *) malloc(sizeof(char))))
	{
	  WHEREAMI();
	  printf("Cannot allocate for null string.\n");
	  exit(ERROR_MEMORY);
	}
      *tmp='\0';
      return(tmp);
    }
  if (!(tmp=(char *)calloc(strlen(yytext)+1,sizeof(char)))) /* Make space */
    {
      WHEREAMI();
      printf("Cannot allocate %d string space.\n",yyleng);
      exit(ERROR_MEMORY);
    }
  for(bptr=yytext+1,ptr=tmp;*bptr!='"';bptr++,ptr++)   /* Copy to string */
    {
      if (*bptr=='\\')
	{
	  bptr++;
	  for(flag=0,accum=0,i=0;i<3;i++)  /* Octal character lookahead */
	    {
	      if ((*bptr>='0')&&(*bptr<='7'))
		{
		  accum = (accum<<3)+(*bptr-'0');
		  bptr++;
		  flag=1;
		}
	      else
		{
		  break;
		}
	    }
	  if (flag)
	    {
	      bptr--;
	      *ptr=accum;
	    }
	  else                           /* Do conversions, if necessary */
	    {
	      switch(*(bptr))
		{
		case '0':
		  *ptr = 0;
		  break;
		case 'b':
		  *ptr = 0x8;
		  break;
		case 'i':
		  *ptr = 0x9;
		  break;
		case 'n':
		  *ptr = 0xa;
		  break;
		case 'v':
		  *ptr = 0xb;
		  break;
		case 'f':
		  *ptr = 0xc;
		  break;
		case 'r':
		  *ptr = 0xd;
		  break;
		default:
		  *ptr=(*bptr);
		}
	    }
	}
      else
	{
	  *ptr = (*bptr);
	}
    }
  *ptr='\0';
  return(tmp);
}

/*BFUNC

parser() handles all of the parsing required for the Command
Interpreter.  It is basically a while statement with a very large case
statement for every input. The Command Interpreter is essentially
driven by the keywords. All unmatched values such as integers,
strings, and brackets, are ignored.

EFUNC*/

#define ARRAYBEGIN if (ntoken==R_LBRACKET)\
	    {\
	      arrayflag=1;\
	      ntoken=yylex();\
	    }\
	  if (ntoken!=R_INTEGER)\
	    {\
	      WHEREAMI();\
	      printf("Expected integer.\n");\
	      break;\
	    }\
	  while(1)\
	    {

#define ARRAYEND  if (arrayflag)\
		{\
		  if ((ntoken=yylex())==R_RBRACKET) break;\
		  else if (ntoken!=R_INTEGER)\
		    {\
		      WHEREAMI();\
		      printf("Expected integer or right bracket.\n");\
		      break;\
		    }\
		}\
	      else break;\
	      }

void parser()
{
  BEGIN("parser");
  int i,dest,value,token,ntoken,arrayflag;
  int accum;
  int Start,End;
  int *ptr,*ptr2;

  while(token=yylex())        /* The code handling is simple enough. */
    {                         /* just read the code and documentation */
      ErrorValue=0;           /* book... */
      arrayflag=0;
      switch(token)
	{
	case R_ECHO:
	  printf("%s\n",getstr());
	  break;
	case R_PRINTIMAGE:
	  PrintImage();
	  break;
	case R_PRINTFRAME:
	  PrintFrame();
	  break;
	case R_PRINTSCAN:
	  PrintScan();
	  break;
	case R_COMPONENT:
	  ntoken=yylex();
	  ARRAYBEGIN;
	  dest = yyint;
	  InBounds(dest,0,MAXIMUM_COMPONENTS-1,"Bad component reference");
	  if (ErrorValue) break;
	  if (yylex()!=R_LBRACKET)
	    {
	      WHEREAMI();
	      printf("Expected left bracket.\n");
	      break;
	    }
	  CFrame->ComponentFileName[dest] = getstr();
	  value=getint();
	  InBounds(value,0,MAXIMUM_HORIZONTAL_FREQUENCY,
		   "Bad horizontal frequency");
	  if (ErrorValue) break;
	  CFrame->hf[dest]=value;
	  value=getint();
	  InBounds(value,0,MAXIMUM_VERTICAL_FREQUENCY,
		   "Bad vertical frequency");
	  if (ErrorValue) break;
	  CFrame->vf[dest]=value;
	  value=getint();
	  InBounds(value,0,MAXIMUM_DEVICES-1,"Bad device reference");
	  if (ErrorValue) break;
	  CFrame->tq[dest]=value;
	  CFrame->cn[CFrame->GlobalNumberComponents++]=dest;/*Know to use it*/
	  if (yylex()!=R_RBRACKET)
	    {
	      WHEREAMI();
	      printf("Expected right bracket.\n");
	      break;
	    }
	  ARRAYEND;
	  break;
	case R_SCAN:
	  CScan->NumberComponents=0;
	  ntoken=yylex();
	  ARRAYBEGIN;
	  if (CScan->NumberComponents>=MAXIMUM_SOURCES)
	    {
	      WHEREAMI();
	      printf("Exceeded number of sources per scan.\n");
	      break;
	    }
	  InBounds(yyint,0,MAXIMUM_COMPONENTS-1,"Bad component reference");
	  if (ErrorValue) break;
	  for(i=0;i<CFrame->GlobalNumberComponents;i++)  /* Check there */
            if (CFrame->cn[i]==yyint) break;
	  if (i==CFrame->GlobalNumberComponents)
	    {
	      WHEREAMI();
	      printf("Scan index not defined in frame yet.\n");
	      break;
	    }
	  CScan->ci[CScan->NumberComponents] = yyint;
	  if (yylex()!=R_LBRACKET)
	    {
	      WHEREAMI();
	      printf("Expected left bracket.\n");
	      break;
	    }
	  value=getint();
	  InBounds(value,0,MAXIMUM_DEVICES-1,"Bad device reference");
	  if (ErrorValue) break;
	  CScan->td[CScan->NumberComponents]=value;
	  value=getint();
	  InBounds(value,0,MAXIMUM_DEVICES-1,"Bad device reference");
	  if (ErrorValue) break;
	  CScan->ta[CScan->NumberComponents]=value;
	  CScan->NumberComponents++;
	  if (yylex()!=R_RBRACKET)
	    {
	      WHEREAMI();
	      printf("Expected right bracket.\n");
	      break;
	    }
	  ARRAYEND;
	  break;
	case R_QUANTIZATION:
	  ntoken=yylex();
	  ARRAYBEGIN;
	  dest = yyint;
	  InBounds(dest,0,MAXIMUM_DEVICES-1,
		   "Bad quantization reference.");
	  if (ErrorValue) break;
	  ntoken=yylex();
	  if (ntoken==R_LUMINANCEDEFAULT)
	    {
	      CImage->QuantizationMatrices[dest]=LuminanceQuantization;
	      break;
	    }
	  else if (ntoken==R_CHROMINANCEDEFAULT)
	    {
	      CImage->QuantizationMatrices[dest]=ChrominanceQuantization;
	      break;
	    }
	  else if (ntoken!=R_LBRACKET)
	    {
	      WHEREAMI();
	      printf("Expected left bracket.\n");
	      break;
	    }
	  CImage->NumberQuantizationMatrices =
	    MAX(CImage->NumberQuantizationMatrices,(dest+1));
	  if (!(ptr=(int *)calloc(64,sizeof(int))))
	    {
	      WHEREAMI();
	      printf("Cannot allocate quantization matrix.\n");
	      exit(ERROR_MEMORY);
	    }
	  CImage->NumberQuantizationMatrices =
	    MAX(CImage->NumberQuantizationMatrices,(dest+1));
	  CImage->QuantizationMatrices[dest]=ptr;
	  for(i=0;i<64;i++)
	    {
	      ptr[i]=16;
	    }
	  for(i=0;i<65;i++,ptr++) /* One additional to force r-bracket */
	    {
	      if ((ntoken=yylex())!=R_INTEGER) break;
	      InBounds(yyint,1,65535,"Integer out of bounds");
	      if (ErrorValue) yyint=16;
	      *ptr = yyint;
	    }
	  if (ntoken!=R_RBRACKET)
	    {
	      WHEREAMI();
	      printf("Expected integer or right bracket.\n");
	      break;
	    }
	  ARRAYEND;
	  break;
	case R_ACSEND:
	  ntoken=yylex();
	  if (ntoken==R_EMPTY)
	    {
	      CScan->NumberACTablesSend = 0;
	      break;
	    }
	  ARRAYBEGIN;
	  if (CScan->NumberACTablesSend>=MAXIMUM_DEVICES)
	    {
	      WHEREAMI();
	      printf("AC Huffman queue full.\n");
	      break;
	    }
	  InBounds(yyint,0,MAXIMUM_DEVICES-1,"Bad device reference");
	  if (ErrorValue) break;
	  CScan->sa[CScan->NumberACTablesSend++] = yyint;
	  ARRAYEND;
	  break;
	case R_DCSEND:
	  ntoken=yylex();
	  if (ntoken==R_EMPTY)
	    {
	      CScan->NumberDCTablesSend = 0;
	      break;
	    }
	  ARRAYBEGIN;
	  if (CScan->NumberDCTablesSend>=MAXIMUM_DEVICES)
	    {
	      WHEREAMI();
	      printf("DC Huffman queue full.\n");
	      break;
	    }
	  InBounds(yyint,0,MAXIMUM_DEVICES-1,"Bad device reference");
	  if (ErrorValue) break;
	  CScan->sd[CScan->NumberDCTablesSend++] = yyint;
	  ARRAYEND;
	  break;
	case R_QSEND:
	  ntoken=yylex();
	  if (ntoken==R_EMPTY)
	    {
	      CScan->NumberQTablesSend = 0;
	      break;
	    }
	  ARRAYBEGIN;
	  if (CScan->NumberQTablesSend>=MAXIMUM_DEVICES)
	    {
	      WHEREAMI();
	      printf("Quantization queue full.\n");
	      break;
	    }
	  InBounds(yyint,0,MAXIMUM_DEVICES-1,"Bad device reference");
	  if (ErrorValue) break;
	  CScan->sq[CScan->NumberQTablesSend++] = yyint;
	  ARRAYEND;
	  break;
	case R_STREAMNAME:
	  CImage->StreamFileName = getstr();
	  break;
	case R_IMAGEWIDTH:
	  value=getint();
	  InBounds(value,0,MAXIMUM_IMAGE_WIDTH,"Bad image width");
	  CFrame->GlobalWidth = value;
	  break;
	case R_IMAGEHEIGHT:
	  value=getint();
	  InBounds(value,0,MAXIMUM_IMAGE_HEIGHT,"Bad image height");
	  CFrame->GlobalHeight = value;
	  break;
	case R_SCANDNL:
	  ntoken=yylex();
	  switch(ntoken)
	    {
	    case R_AUTO:
	      CFrame->InsertDnl= -2;
	      break;
	    case R_ENABLE:
	      CFrame->InsertDnl= -1;
	      break;
	    case R_INTEGER:
	      CFrame->InsertDnl = yyint;
	      break;
	    default:
	      WHEREAMI();
	      printf("Expected integer.\n");
	      break;
	    }
	  break;
	case R_FRAMEWIDTH:
	  ntoken=yylex();
	  ARRAYBEGIN;
	  dest = yyint;
	  InBounds(dest,0,MAXIMUM_COMPONENTS-1,"Bad component destination");
	  if (ErrorValue) break;
	  value=getint();
	  InBounds(value,0,MAXIMUM_IMAGE_WIDTH,"Bad frame width");
	  if (ErrorValue) break;
	  CFrame->Width[dest] = value;
	  ARRAYEND;
	  break;
	case R_FRAMEHEIGHT:
	  ntoken=yylex();
	  ARRAYBEGIN;
	  dest = yyint;
	  InBounds(dest,0,MAXIMUM_COMPONENTS-1,"Bad component destination");
	  if (ErrorValue) break;
	  value=getint();
	  InBounds(value,0,MAXIMUM_IMAGE_HEIGHT,"Bad frame height");
	  if (ErrorValue) break;
	  CFrame->Height[dest] = value;
	  ARRAYEND;
	  break;
	case R_RESYNC:
	  value = getint();
	  InBounds(value,0,MAXIMUM_RESYNC_INTERVAL,"Bad resync interval");
	  if (ErrorValue) break;
	  CFrame->ResyncInterval = value;
	  break;
	case R_BUFFER:
	  value = getint();
	  InBounds(value,MINIMUM_BUFFERSIZE,
		   MAXIMUM_BUFFERSIZE,"Bad buffersize");
	  if (ErrorValue) break;
	  CFrame->BufferSize = value;
	  break;
	case R_OPENSCAN:
	  CheckValidity();
	  CheckBaseline();
	  ConfirmFileSize();
	  MakeIob(IOB_BLOCK,O_RDONLY,1);
	  break;
	case R_CLOSESCAN:
	  for(i=0;i<CScan->NumberComponents;i++)  /* Close all components */
	    {
	      InstallIob(i);
	      CloseIob();
	    }
	  break;
	case R_OPENSTREAM:
	  if (CImage->StreamFileName)
	    {
	      swopen(CImage->StreamFileName,0);  /* Index 0 open */
	    }
	  else
	    {
	      printf("StreamFileName: Null. Failed\n");
	    }
	  break;
	case R_CLOSESTREAM:
	  swclose();
	  break;
	case R_FREQUENCY:
	  JpegFrequencyScan();
	  break;
	case R_WRITESPECIAL:
	  ntoken=yylex();
	  ARRAYBEGIN;
	  value = yyint;
	  swbytealign();
	  bputc(0xFF);  /* Marker */
	  bputc(value&0xff);
	  Start = swtell();
	  bputw(0);
	  if (yylex()!=R_LBRACKET)
	    {
	      WHEREAMI();
	      printf("Expected left bracket.\n");
	      End = swtell();
	      swseek(Start);
	      bputw((End-Start) >> 3);
	      swseek(End);
	      break;
	    }
	  while((ntoken=yylex())==R_INTEGER)
	    {
	      bputc(yyint&0xff);
	    }
	  if (ntoken!=R_RBRACKET)
	    {
	      WHEREAMI();
	      printf("Expected integer or right bracket.\n");
	      End = swtell();
	      swseek(Start);
	      bputw((End-Start) >> 3);
	      swseek(End);
	      break;
	    }
	  End = swtell();
	  swseek(Start);
	  bputw((End-Start) >> 3);
	  swseek(End);
	  ARRAYEND;
	  break;
	case R_WRITEDIRECT:
	  swbytealign();
	  if (yylex()!=R_LBRACKET)
	    {
	      WHEREAMI();
	      printf("Expected left bracket.\n");
	      break;
	    }
	  while((ntoken=yylex())==R_INTEGER)
	    {
	      bputc(yyint&0xff);
	    }
	  if (ntoken!=R_RBRACKET)
	    {
	      WHEREAMI();
	      printf("Expected integer or right bracket.\n");
	      break;
	    }
	  break;
	case R_WRITESCAN:
	  JpegEncodeScan();
	  break;
	case R_WRITEFRAME:
	  MakeConsistentFrameSize();  /* Do it here when everything defined */
	  WriteSof();
	  break;
	case R_WRITESOI:
	  WriteSoi();
	  break;
	case R_WRITEEOI:
	  WriteEoi();
	  break;
	case R_WRITEQUANTIZATION:
	  WriteDqt();
	  break;
	case R_WRITERESYNC:
	  WriteDri();
	  break;
	case R_WRITEDNL:
	  WriteDnl();
	  break;
	case R_WRITEHUFFMAN:
	  WriteDht();
	  break;
	case R_ACCUSTOM:
	  ntoken=yylex();
	  ARRAYBEGIN;
	  dest = yyint;
	  InBounds(dest,0,MAXIMUM_DEVICES-1,"Bad device reference");
	  if (ErrorValue) break;
	  if (yylex()!=R_LBRACKET)
	    {
	      WHEREAMI();
	      printf("Expected left bracket.\n");
	      break;
	    }
	  MakeXhuff();
	  MakeEhuff();
	  if (!(ptr=(int *)calloc(257,sizeof(int))))
	    {
	      WHEREAMI();
	      printf("Out of custom frequency space.\n");
	      exit(ERROR_MEMORY);
	    }
	  for(i=0;i<257;i++)
	    {
	      ptr[i]=0;
	    }
	  while((ntoken=yylex())==R_INTEGER)
	    {
	      InBounds(yyint,0,MAXIMUM_SOURCES-1,"Bad frequency reference");
	      if(ErrorValue) yyint=0;
	      AddFrequency(ptr,CScan->ACFrequency[yyint]);
	    }
	  if (ntoken!=R_RBRACKET)
	    {
	      WHEREAMI();
	      printf("Expected right bracket.\n");
	      break;
	    }
	  MakeHuffman(ptr);
	  SetACHuffman(dest);
	  CImage->NumberACTables = 
	    MAX(CImage->NumberACTables,(dest+1));
	  ARRAYEND;
	  break;
	case R_DCCUSTOM:
	  ntoken=yylex();
	  ARRAYBEGIN;
	  dest = yyint;
	  InBounds(dest,0,MAXIMUM_DEVICES-1,"Bad device reference");
	  if (ErrorValue) break;
	  if (yylex()!=R_LBRACKET)
	    {
	      WHEREAMI();
	      printf("Expected left bracket.\n");
	      break;
	    }
	  MakeXhuff();
	  MakeEhuff();
	  if (!(ptr=(int *)calloc(257,sizeof(int))))
	    {
	      WHEREAMI();
	      printf("Out of custom frequency space.\n");
	      exit(ERROR_MEMORY);
	    }
	  for(i=0;i<257;i++)
	    {
	      ptr[i]=0;
	    }
	  while((ntoken=yylex())==R_INTEGER)
	    {
	      InBounds(yyint,0,MAXIMUM_SOURCES-1,"Bad frequency reference");
	      if(ErrorValue) yyint=0;
	      AddFrequency(ptr,CScan->DCFrequency[yyint]);
	    }
	  if (ntoken!=R_RBRACKET)
	    {
	      WHEREAMI();
	      printf("Expected right bracket.\n");
	      break;
	    }
	  MakeHuffman(ptr);
	  SetDCHuffman(dest);
	  CImage->NumberDCTables = 
	    MAX(CImage->NumberDCTables,(dest+1));
	  ARRAYEND;
	  break;
	case R_ACSPEC:
	  ntoken=yylex();
	  ARRAYBEGIN;
	  dest = yyint;
	  InBounds(dest,0,MAXIMUM_DEVICES-1,"Bad device reference");
	  if (ErrorValue) break;
	  MakeXhuff();
	  MakeEhuff();
	  if ((ntoken=yylex())==R_LBRACKET)
	    {
	      if (!(ptr=(int *)calloc(38,sizeof(int)))) /* Get bits */
		{
		  WHEREAMI();
		  printf("Out of custom bits space.\n");
		  exit(ERROR_MEMORY);
		}
	      for(i=0;i<32;i++)
		{
		  ptr[i]=0;
		}
	      for(accum=0,i=0;i<17;i++) /* First index is bitlength of 1. */
		{                 /* One additional to force r-bracket. */
		  ntoken=yylex();
		  if (ntoken==R_INTEGER)
		    {
		      accum+=yyint;
		      ptr[i]=yyint;
		    }
		  else break;
		}
	      if (ntoken!=R_RBRACKET)
		{
		  WHEREAMI();
		  printf("Expected integer or right bracket.\n");
		  break;
		}
	      if (yylex()!=R_LBRACKET)  /* Get values */
		{
		  WHEREAMI();
		  printf("Expected left bracket.\n");
		  break;
		}
	      if (!(ptr2=(int *)calloc(257,sizeof(int))))
		{
		  WHEREAMI();
		  printf("Out of custom Huffman value space.\n");
		  exit(ERROR_MEMORY);
		}
	      for(i=0;i<257;i++)
		{
		  ptr2[i]=0;
		}
	      for(i=0;i<257;i++) /* One additinal to force r-bracket */
		{
		  ntoken=yylex();
		  if (ntoken==R_INTEGER)
		    {
		      ptr2[i]=yyint;
		    }
		  else break;
		}
	      if (i!=accum)
		{
		  WHEREAMI();
		  printf("Number of bitlengths != number of values.");
		}
	      if (ntoken!=R_RBRACKET)
		{
		  WHEREAMI();
		  printf("Expected integer or right bracket.\n");
		  break;
		}
	      SpecifiedHuffman(ptr,ptr2);
	    }
	  else if (ntoken==R_CHROMINANCEDEFAULT)
	    {
	      SpecifiedHuffman(ChrominanceACBits,ChrominanceACValues);
	    }
	  else if (ntoken==R_LUMINANCEDEFAULT)
	    {
	      SpecifiedHuffman(LuminanceACBits,LuminanceACValues);
	    }
	  else
	    {
	      WHEREAMI();
	      printf("Expected left bracket or ACDEFAULT.\n");
	      break;
	    }
	  SetACHuffman(dest);
	  CImage->NumberACTables = 
	    MAX(CImage->NumberACTables,(dest+1));
	  ARRAYEND;
	  break;
	case R_DCSPEC:
	  ntoken=yylex();
	  ARRAYBEGIN;
	  dest = yyint;
	  InBounds(dest,0,MAXIMUM_DEVICES-1,"Bad device reference");
	  if (ErrorValue) break;
	  MakeXhuff();
	  MakeEhuff();
	  if ((ntoken=yylex())==R_LBRACKET)
	    {
	      if (!(ptr=(int *)calloc(38,sizeof(int)))) /* Get bits */
		{
		  WHEREAMI();
		  printf("Out of custom bits space.\n");
		  exit(ERROR_MEMORY);
		}
	      for(i=0;i<32;i++)
		{
		  ptr[i]=0;
		}
	      for(accum=0,i=0;i<17;i++) /* First index is bitlength of 1. */
		{                /* 0-16 to force right bracket. */
		  ntoken=yylex();
		  if (ntoken==R_INTEGER)
		    {
		      accum+=yyint;
		      ptr[i]=yyint;
		    }
		  else break;
		}
	      if (ntoken!=R_RBRACKET)
		{
		  WHEREAMI();
		  printf("Expected integer or right bracket.\n");
		  break;
		}
	      if (yylex()!=R_LBRACKET)  /* Get values */
		{
		  WHEREAMI();
		  printf("Expected left bracket.\n");
		  break;
		}
	      if (!(ptr2=(int *)calloc(257,sizeof(int))))
		{
		  WHEREAMI();
		  printf("Out of custom Huffman value space.\n");
		  exit(ERROR_MEMORY);
		}
	      for(i=0;i<257;i++)
		{
		  ptr2[i]=0;
		}
	      for(i=0;i<257;i++) /*One additional to force r-bracket.*/
		{
		  ntoken=yylex();
		  if (ntoken==R_INTEGER)
		    {
		      ptr2[i]=yyint;
		    }
		  else break;
		}
	      if (i!=accum)
		{
		  WHEREAMI();
		  printf("Number of bitlengths != number of values.");
		}
	      if (ntoken!=R_RBRACKET)
		{
		  WHEREAMI();
		  printf("Expected integer or right bracket.\n");
		  break;
		}
	      SpecifiedHuffman(ptr,ptr2);
	    }
	  else if (ntoken==R_CHROMINANCEDEFAULT)
	    {
	      SpecifiedHuffman(ChrominanceDCBits,ChrominanceDCValues);
	    }
	  else if (ntoken==R_LUMINANCEDEFAULT)
	    {
	      SpecifiedHuffman(LuminanceDCBits,LuminanceDCValues);
	    }
	  else
	    {
	      WHEREAMI();
	      printf("Expected left bracket or DCDEFAULT.\n");
	      break;
	    }
	  SetDCHuffman(dest);
	  CImage->NumberDCTables = 
	    MAX(CImage->NumberDCTables,(dest+1));
	  ARRAYEND;
	  break;
	}
    }
}

/*NOPROTO*/
/*END*/
int yyvstop[] ={
0,

16,
0,

1,
16,
0,

1,
0,

16,
0,

12,
16,
0,

16,
0,

12,
16,
0,

12,
16,
0,

4,
16,
0,

4,
16,
0,

4,
16,
0,

12,
16,
0,

12,
16,
0,

12,
16,
0,

2,
16,
0,

2,
16,
0,

10,
12,
16,
0,

11,
12,
16,
0,

17,
0,

17,
0,

17,
0,

13,
0,

12,
0,

3,
0,

14,
0,

3,
0,

4,
0,

4,
0,

8,
0,

6,
0,

8,
0,

8,
0,

2,
0,

2,
0,

2,
6,
0,

15,
0,

13,
0,

9,
0,

3,
0,

3,
0,

7,
0,

5,
0,

3,
0,

3,
0,

3,
0,

3,
0,
0};
# define YYTYPE unsigned char
struct yywork { YYTYPE verify, advance; } yycrank[] ={
0,0,	0,0,	3,7,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	3,8,	3,9,	
0,0,	0,0,	8,9,	8,9,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	3,10,	
3,11,	8,9,	0,0,	3,11,	
3,12,	3,11,	3,11,	3,11,	
3,11,	3,11,	30,50,	3,13,	
3,14,	3,15,	3,16,	3,16,	
3,16,	3,16,	3,16,	3,16,	
3,16,	3,17,	14,35,	3,18,	
3,11,	3,19,	3,11,	3,20,	
6,26,	26,49,	3,21,	3,21,	
31,51,	6,27,	18,33,	0,0,	
3,22,	3,22,	19,33,	19,33,	
0,0,	54,63,	0,0,	0,0,	
3,22,	43,58,	43,58,	43,58,	
43,58,	43,58,	43,58,	43,58,	
43,58,	3,22,	0,0,	0,0,	
3,23,	3,7,	3,24,	3,11,	
4,11,	0,0,	0,0,	4,11,	
4,12,	4,11,	4,11,	4,11,	
0,0,	4,11,	0,0,	4,13,	
4,14,	0,0,	4,16,	4,16,	
4,16,	4,16,	4,16,	4,16,	
4,16,	0,0,	0,0,	4,18,	
4,11,	4,19,	4,11,	4,20,	
3,11,	3,11,	3,11,	3,11,	
5,25,	52,51,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
5,25,	5,25,	52,60,	52,60,	
52,60,	52,60,	52,60,	52,60,	
52,60,	52,60,	0,0,	10,28,	
0,0,	0,0,	0,0,	0,0,	
4,23,	0,0,	4,24,	10,28,	
10,28,	0,0,	12,31,	0,0,	
0,0,	5,25,	0,0,	0,0,	
0,0,	0,0,	12,31,	12,31,	
0,0,	5,26,	5,25,	0,0,	
0,0,	0,0,	5,27,	5,25,	
0,0,	0,0,	0,0,	0,0,	
10,29,	0,0,	0,0,	5,25,	
4,11,	4,11,	4,11,	4,11,	
0,0,	10,28,	0,0,	12,31,	
5,25,	5,25,	10,28,	0,0,	
0,0,	0,0,	5,25,	5,25,	
12,31,	0,0,	10,28,	0,0,	
0,0,	12,31,	5,25,	0,0,	
0,0,	0,0,	0,0,	10,28,	
10,28,	12,31,	0,0,	5,25,	
0,0,	10,28,	10,28,	5,25,	
0,0,	5,25,	12,31,	12,31,	
0,0,	10,28,	0,0,	0,0,	
12,31,	12,31,	0,0,	0,0,	
0,0,	0,0,	10,28,	0,0,	
12,31,	0,0,	10,30,	0,0,	
10,28,	0,0,	0,0,	0,0,	
0,0,	12,31,	0,0,	0,0,	
0,0,	12,32,	13,33,	12,31,	
13,34,	13,34,	13,34,	13,34,	
13,34,	13,34,	13,34,	13,34,	
13,34,	13,34,	15,36,	0,0,	
15,37,	15,37,	15,37,	15,37,	
15,37,	15,37,	15,37,	15,37,	
15,38,	15,38,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	15,39,	15,40,	15,40,	
15,39,	15,41,	15,39,	0,0,	
15,42,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	15,43,	
60,31,	60,31,	60,31,	60,31,	
60,31,	60,31,	60,31,	60,31,	
15,44,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	15,39,	15,40,	15,40,	
15,39,	15,39,	15,39,	0,0,	
15,42,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	15,43,	
0,0,	0,0,	0,0,	32,31,	
0,0,	0,0,	0,0,	16,36,	
15,44,	16,37,	16,37,	16,37,	
16,37,	16,37,	16,37,	16,37,	
16,37,	16,38,	16,38,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	16,39,	16,40,	
16,40,	16,39,	16,41,	16,39,	
0,0,	16,42,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
16,45,	32,52,	32,52,	32,52,	
32,52,	32,52,	32,52,	32,52,	
32,52,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	16,39,	16,40,	
16,40,	16,39,	16,39,	16,39,	
0,0,	16,42,	0,0,	0,0,	
0,0,	0,0,	0,0,	17,36,	
16,45,	17,38,	17,38,	17,38,	
17,38,	17,38,	17,38,	17,38,	
17,38,	17,38,	17,38,	0,0,	
0,0,	0,0,	0,0,	32,31,	
0,0,	0,0,	17,39,	17,39,	
17,39,	17,39,	17,41,	17,39,	
0,0,	17,42,	34,34,	34,34,	
34,34,	34,34,	34,34,	34,34,	
34,34,	34,34,	34,34,	34,34,	
56,66,	56,66,	56,66,	56,66,	
56,66,	56,66,	56,66,	56,66,	
56,66,	56,66,	0,0,	34,53,	
0,0,	0,0,	17,39,	17,39,	
17,39,	17,39,	17,39,	17,39,	
0,0,	17,42,	21,46,	21,46,	
21,46,	21,46,	21,46,	21,46,	
21,46,	21,46,	21,46,	21,46,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	21,46,	
21,46,	21,46,	21,46,	21,46,	
21,46,	21,47,	21,48,	21,47,	
21,47,	21,47,	21,47,	21,47,	
21,47,	21,47,	21,47,	21,47,	
21,47,	21,47,	21,47,	21,47,	
21,47,	21,47,	21,47,	21,47,	
21,47,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	21,46,	
21,46,	21,46,	21,46,	21,46,	
21,46,	21,47,	21,48,	21,47,	
21,47,	21,47,	21,47,	21,47,	
21,47,	21,47,	21,47,	21,47,	
21,47,	21,47,	21,47,	21,47,	
21,47,	21,47,	21,47,	21,47,	
21,47,	22,47,	22,47,	22,47,	
22,47,	22,47,	22,47,	22,47,	
22,47,	22,47,	22,47,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	22,47,	22,47,	
22,47,	22,47,	22,47,	22,47,	
0,0,	22,47,	36,54,	36,54,	
36,54,	36,54,	36,54,	36,54,	
36,54,	36,54,	36,54,	36,54,	
57,57,	57,57,	57,57,	57,57,	
57,57,	57,57,	57,57,	57,57,	
57,57,	57,57,	0,0,	36,55,	
0,0,	0,0,	22,47,	22,47,	
22,47,	22,47,	22,47,	22,47,	
0,0,	22,47,	39,39,	39,39,	
39,39,	39,39,	39,39,	39,39,	
39,39,	39,39,	39,39,	39,39,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	39,39,	
39,39,	39,39,	39,39,	39,39,	
39,39,	41,56,	39,42,	41,56,	
0,0,	0,0,	41,57,	41,57,	
41,57,	41,57,	41,57,	41,57,	
41,57,	41,57,	41,57,	41,57,	
61,62,	61,62,	61,62,	61,62,	
61,62,	61,62,	61,62,	61,62,	
61,62,	61,62,	0,0,	39,39,	
39,39,	39,39,	39,39,	39,39,	
39,39,	0,0,	39,42,	44,59,	
44,59,	44,59,	44,59,	44,59,	
44,59,	44,59,	44,59,	44,59,	
44,59,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
44,59,	44,59,	44,59,	44,59,	
44,59,	44,59,	47,47,	47,47,	
47,47,	47,47,	47,47,	47,47,	
47,47,	47,47,	47,47,	47,47,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	47,47,	
47,47,	47,47,	47,47,	47,47,	
47,47,	0,0,	47,47,	0,0,	
44,59,	44,59,	44,59,	44,59,	
44,59,	44,59,	53,61,	0,0,	
53,61,	0,0,	0,0,	53,62,	
53,62,	53,62,	53,62,	53,62,	
53,62,	53,62,	53,62,	53,62,	
53,62,	0,0,	0,0,	47,47,	
47,47,	47,47,	47,47,	47,47,	
47,47,	0,0,	47,47,	48,47,	
48,47,	48,47,	48,47,	48,47,	
48,47,	48,47,	48,47,	48,47,	
48,47,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
48,47,	48,47,	48,47,	48,47,	
48,47,	48,47,	55,64,	48,47,	
55,64,	0,0,	0,0,	55,65,	
55,65,	55,65,	55,65,	55,65,	
55,65,	55,65,	55,65,	55,65,	
55,65,	64,65,	64,65,	64,65,	
64,65,	64,65,	64,65,	64,65,	
64,65,	64,65,	64,65,	0,0,	
48,47,	48,47,	48,47,	48,47,	
48,47,	48,47,	63,67,	48,47,	
63,67,	0,0,	0,0,	63,68,	
63,68,	63,68,	63,68,	63,68,	
63,68,	63,68,	63,68,	63,68,	
63,68,	67,68,	67,68,	67,68,	
67,68,	67,68,	67,68,	67,68,	
67,68,	67,68,	67,68,	0,0,	
0,0};
struct yysvf yysvec[] ={
0,	0,	0,
yycrank+0,	0,		0,	
yycrank+0,	0,		0,	
yycrank+-1,	0,		0,	
yycrank+-61,	yysvec+3,	0,	
yycrank+-127,	0,		0,	
yycrank+-22,	yysvec+5,	0,	
yycrank+0,	0,		yyvstop+1,
yycrank+5,	0,		yyvstop+3,
yycrank+0,	yysvec+8,	yyvstop+6,
yycrank+-146,	0,		yyvstop+8,
yycrank+0,	0,		yyvstop+10,
yycrank+-157,	0,		yyvstop+13,
yycrank+204,	0,		yyvstop+15,
yycrank+16,	0,		yyvstop+18,
yycrank+216,	0,		yyvstop+21,
yycrank+289,	0,		yyvstop+24,
yycrank+353,	0,		yyvstop+27,
yycrank+9,	0,		yyvstop+30,
yycrank+13,	0,		yyvstop+33,
yycrank+0,	yysvec+18,	yyvstop+36,
yycrank+410,	0,		yyvstop+39,
yycrank+485,	yysvec+21,	yyvstop+42,
yycrank+0,	0,		yyvstop+45,
yycrank+0,	0,		yyvstop+49,
yycrank+0,	0,		yyvstop+53,
yycrank+18,	0,		yyvstop+55,
yycrank+0,	yysvec+14,	yyvstop+57,
yycrank+0,	yysvec+10,	0,	
yycrank+0,	0,		yyvstop+59,
yycrank+-12,	yysvec+10,	0,	
yycrank+29,	0,		0,	
yycrank+321,	0,		0,	
yycrank+0,	0,		yyvstop+61,
yycrank+378,	0,		yyvstop+63,
yycrank+0,	0,		yyvstop+65,
yycrank+510,	0,		yyvstop+67,
yycrank+0,	yysvec+16,	yyvstop+69,
yycrank+0,	yysvec+17,	yyvstop+71,
yycrank+542,	0,		0,	
yycrank+0,	yysvec+39,	yyvstop+73,
yycrank+570,	yysvec+39,	0,	
yycrank+0,	0,		yyvstop+75,
yycrank+33,	0,		yyvstop+77,
yycrank+599,	0,		0,	
yycrank+0,	0,		yyvstop+79,
yycrank+0,	yysvec+21,	yyvstop+81,
yycrank+622,	yysvec+21,	yyvstop+83,
yycrank+679,	yysvec+21,	yyvstop+85,
yycrank+0,	0,		yyvstop+88,
yycrank+0,	yysvec+10,	yyvstop+90,
yycrank+0,	0,		yyvstop+92,
yycrank+90,	0,		0,	
yycrank+659,	0,		0,	
yycrank+8,	yysvec+36,	yyvstop+94,
yycrank+707,	0,		0,	
yycrank+388,	0,		0,	
yycrank+520,	yysvec+39,	yyvstop+96,
yycrank+0,	yysvec+43,	yyvstop+98,
yycrank+0,	yysvec+44,	yyvstop+100,
yycrank+248,	yysvec+52,	0,	
yycrank+580,	0,		0,	
yycrank+0,	yysvec+61,	yyvstop+102,
yycrank+739,	0,		0,	
yycrank+717,	0,		0,	
yycrank+0,	yysvec+64,	yyvstop+104,
yycrank+0,	yysvec+56,	yyvstop+106,
yycrank+749,	0,		0,	
yycrank+0,	yysvec+67,	yyvstop+108,
0,	0,	0};
struct yywork *yytop = yycrank+806;
struct yysvf *yybgin = yysvec+1;
char yymatch[] ={
00  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,011 ,012 ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
011 ,01  ,'"' ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,'+' ,01  ,'+' ,01  ,01  ,
'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,
'8' ,'8' ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,'A' ,'B' ,'B' ,'A' ,'A' ,'A' ,'G' ,
'H' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'O' ,
'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,
'X' ,'G' ,'G' ,01  ,0134,01  ,'^' ,01  ,
01  ,'A' ,'B' ,'B' ,'A' ,'A' ,'A' ,'G' ,
'H' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'O' ,
'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,
'X' ,'G' ,'G' ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
0};
char yyextra[] ={
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0};
/*	ncform	4.1	83/08/11	*/

int yylineno =1;
# define YYU(x) x
# define NLSTATE yyprevious=YYNEWLINE
char yytext[YYLMAX];
struct yysvf *yylstate [YYLMAX], **yylsp, **yyolsp;
char yysbuf[YYLMAX];
char *yysptr = yysbuf;
int *yyfnd;
extern struct yysvf *yyestate;
int yyprevious = YYNEWLINE;
yylook(){
	register struct yysvf *yystate, **lsp;
	register struct yywork *yyt;
	struct yysvf *yyz;
	int yych;
	struct yywork *yyr;
# ifdef LEXDEBUG
	int debug;
# endif
	char *yylastch;
	/* start off machines */
# ifdef LEXDEBUG
	debug = 0;
# endif
	if (!yymorfg)
		yylastch = yytext;
	else {
		yymorfg=0;
		yylastch = yytext+yyleng;
		}
	for(;;){
		lsp = yylstate;
		yyestate = yystate = yybgin;
		if (yyprevious==YYNEWLINE) yystate++;
		for (;;){
# ifdef LEXDEBUG
			if(debug)fprintf(yyout,"state %d\n",yystate-yysvec-1);
# endif
			yyt = yystate->yystoff;
			if(yyt == yycrank){		/* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == yycrank)break;
				}
			*yylastch++ = yych = input();
		tryagain:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"unsigned char ");
				allprint(yych);
				putchar('\n');
				}
# endif
			yyr = yyt;
			if ( (int)yyt > (int)yycrank){
				yyt = yyr + yych;
				if (yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
# ifdef YYOPTIM
			else if((int)yyt < (int)yycrank) {		/* r < yycrank */
				yyt = yyr = yycrank+(yycrank-yyt);
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"compressed state\n");
# endif
				yyt = yyt + yych;
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
# endif
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt= yystate->yystoff) != yycrank){
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"fall back to state %d\n",yystate-yysvec-1);
# endif
				goto tryagain;
				}
# endif
			else
				{unput(*--yylastch);break;}
		contin:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
# endif
			;
			}
# ifdef LEXDEBUG
		if(debug){
			fprintf(yyout,"stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
# endif
		while (lsp-- > yylstate){
			*yylastch-- = 0;
			if (*lsp != 0 && (yyfnd= (*lsp)->yystops) && *yyfnd > 0){
				yyolsp = lsp;
				if(yyextra[*yyfnd]){		/* must backup */
					while(yyback((*lsp)->yystops,-*yyfnd) != 1 && lsp > yylstate){
						lsp--;
						unput(*yylastch--);
						}
					}
				yyprevious = YYU(*yylastch);
				yylsp = lsp;
				yyleng = yylastch-yytext+1;
				yytext[yyleng] = 0;
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"\nmatch ");
					sprint(yytext);
					fprintf(yyout," action %d\n",*yyfnd);
					}
# endif
				return(*yyfnd++);
				}
			unput(*yylastch);
			}
		if (yytext[0] == 0  /* && feof(yyin) */)
			{
			yysptr=yysbuf;
			return(0);
			}
		yyprevious = yytext[0] = input();
		if (yyprevious>0)
			output(yyprevious);
		yylastch=yytext;
# ifdef LEXDEBUG
		if(debug)putchar('\n');
# endif
		}
	}
yyback(p, m)
	int *p;
{
if (p==0) return(0);
while (*p)
	{
	if (*p++ == m)
		return(1);
	}
return(0);
}
	/* the following are only used in the lex library */
yyinput(){
	return(input());
	}
yyoutput(c)
  int c; {
	output(c);
	}
yyunput(c)
   int c; {
	unput(c);
	}
