/* This is part of the LibEth library, an ANSI C library for Ethiopic
   text and information processing (http://libeth.netpedia.net).
   Copyright (C) 1995-1998 Daniel Yacob.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "fidel.h"
#include "unicode.h"
#include "unicode.map"
#include "systems.h"
#include "etctype.h"

#define USE_TALIGENT 1

#ifdef USE_TALIGENT
#  include "taligent/cvtutf.h"
#  include "taligent/cvtutf7.h"
#endif /* USE_TALIGENT */


FCHAR
UTF16ToUnicode (void)
{
FCHAR fch = NIL;


  fch   = (FCHAR) getOneChar();         /* read first char */
  fch <<= 8;
  fch  |= (FCHAR) getOneChar();         /* read second char */


  return (fch);
}


FCHAR
UTF8ToUnicode (void)
{
#ifdef USE_TALIGENT
FCHAR fch = NIL;
register int i=0, j;
UTF8*  utf8Char;
UTF16* utf16Char;
unsigned char extraBytesToRead;


  utf8Char  = (UTF8  *) calloc ( 4 , sizeof (UTF8) );
  utf16Char = (UTF16 *) calloc ( 2 , sizeof (UTF16) );

  utf8Char[i++] = getOneChar();          /* read 1st char */
  extraBytesToRead = bytesFromUTF8[utf8Char[i-1]];
  for (j = 0; j < extraBytesToRead; j++)
    utf8Char[i++] = getOneChar();          /* read next char */

  ConvertUTF8toUTF16 ( &utf8Char, utf8Char+i, &utf16Char, utf16Char+1 );

  fch = (FCHAR) *--utf16Char;
  utf8Char -= i;

  free (utf8Char);
  free (utf16Char);


  return (fch);
#endif /* USE_TALIGENT */
}




unsigned char*
UnicodeToUTF8 ( fch )
  FCHAR fch;
{

#ifdef USE_TALIGENT
  UTF8*  utf8Char, *utf8CharStart;
  UTF16* utf16Char;
  char utf8CharLength;
#endif  /* USE_TALIGENT */
unsigned char* returnCh = NULL;


/* Detect Errors Here */



/* We are clear of bad characters, return then requested UNICODE mapping */

  returnCh = (unsigned char *) malloc ( 3 * sizeof(unsigned char) );

#ifdef USE_TALIGENT


   /*
    *  Since we do not know of any UTF-8 system using our private use
    *  extensions (well...maybe linux, but..) we remap the chars onto
    *  their Latin like counterparts and trash the rest.
    */
  switch ( fch )
    {
      case TEMHERTESLAQ:
           fch = 0xa1;
           break;
      case NETEB:
           fch = '.'; 
           break;
      case LEFTQUOTE:
           fch = 0xab;
           break;
      case RIGHTQUOTE:
           fch = 0xbb;
           break;
      case EQUESTIONMARK:
           fch = '?'; 
           break;
      default:
           break;
    }


  utf8CharStart =
  utf8Char  = (UTF8 *) malloc ( 4 * sizeof (UTF8) );
  utf16Char = (UTF16 *) malloc ( 2 * sizeof (UTF16) );

  utf16Char[0] = fch;

  ConvertUTF16toUTF8 ( &utf16Char, utf16Char+1, &utf8Char, utf8Char+3 );

  utf8CharLength = (utf8Char - utf8CharStart);

  utf8Char -= utf8CharLength;

  returnCh = (unsigned char *) malloc ( utf8CharLength * sizeof(unsigned char) );

  returnCh[0] = (unsigned char) utf8Char[0];

  if ( utf8CharLength > 1 )
    returnCh[1] = (unsigned char) utf8Char[1];
  if ( utf8CharLength > 2 )
    returnCh[2] = (unsigned char) utf8Char[2];

  returnCh[(int)utf8CharLength] = '\0';

  free (utf8Char);
  free (--utf16Char);

#else  /* Not using taligent codes for some reason... */

  if ( !(PRIVATE_USE_BEGIN <= fch && fch <= PRIVATE_USE_END) )
    {
      switch ( fch )
        {
          case TEMHERTESLAQ:
               returnCh[0] = ((0xa1 >> 6) & 0x03) | 0xc0;
               returnCh[1] = (0xa1 & 0x3f) | 0x80;
               break;
          case NETEB:
               returnCh[0] = '.'; 
               returnCh[1] = '\0'; 
               break;
          case LEFTQUOTE:
               returnCh[0] = ((0xab >> 6) & 0x03) | 0xc0;
               returnCh[1] = (0xab & 0x3f) | 0x80;
               break;
          case RIGHTQUOTE:
               returnCh[0] = ((0xbb >> 6) & 0x03) | 0xc0;
               returnCh[1] = (0xbb & 0x3f) | 0x80;
               break;
          case EQUESTIONMARK:
               returnCh[0] = '?'; 
               returnCh[1] = '\0'; 
               break;
          default:
               returnCh[0] = '\0';
               returnCh[1] = '\0';
               break;
        }
      returnCh[2] = '\0';
    }
  else
    {
      /* this assumes Ethiopic or 3 byte range, should update later */

      returnCh = (unsigned char *) malloc ( 4 * sizeof(unsigned char) );
      returnCh[0] = (fch >> 12)  | 0xe0;
      returnCh[1] = ((fch >>  6) & 0x3f) | 0x80; 
      returnCh[2] = (fch & 0x3f) | 0x80;
      returnCh[3] = '\0';
    }

#endif /* USE_TALIGENT */


  return ( returnCh );

}



unsigned char*
UnicodeToUTF16 ( fch )
  FCHAR fch;
{

unsigned char* returnCh = NULL;


/* Detect Errors Here */


/* We are clear of bad characters, return then requested UNICODE mapping */

  returnCh = (unsigned char *) malloc ( 3 * sizeof(unsigned char) );
  returnCh[0] = (fch >> 8);
  returnCh[1] = (fch & 255);
  returnCh[2] = '\0';


  return ( returnCh );

}


char*
Unicode_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (UNICODE_EMAIL);
        break;
      case LETH_WWW:
        return (UNICODE_WWW);
        break;
      case LETH_FTP:
        return (UNICODE_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}


unsigned char*
UnicodeToUTF7 ( fch )
  FCHAR fch;
{

#ifdef USE_TALIGENT
UTF7*  utf7Char, *utf7CharStart;
UTF16* utf16Char;
char utf7CharLength;
unsigned char* returnCh = NULL;
int optional = 0, verbose = 0, i = 0;


/* Detect Errors Here */

  switch ( fch )
    {
      case TEMHERTESLAQ:
           fch = 0xa1;
           break;
      case NETEB:
           fch = '.'; 
           break;
      case LEFTQUOTE:
           fch = 0xab;
           break;
      case RIGHTQUOTE:
           fch = 0xbb;
           break;
      case EQUESTIONMARK:
           fch = '?'; 
           break;
      default:
           break;
    }


/* We are clear of bad characters, return then requested UNICODE mapping */


  utf7CharStart =
  utf7Char  = (UTF8 *) calloc ( 8 , sizeof (UTF8) );
  utf16Char = (UTF16 *) malloc ( 2 * sizeof (UTF16) );

  utf16Char[0] = fch;

  ConvertUCS2toUTF7 ( &utf16Char, utf16Char+1, &utf7Char, utf7Char+7,
                      optional, verbose );

  utf7CharLength = (utf7Char - utf7CharStart);

  utf7Char -= utf7CharLength;

  returnCh = (unsigned char *) malloc ( utf7CharLength * sizeof(unsigned char) );

  for ( i=0; i <= utf7CharLength; i++ )
    returnCh[i] = (unsigned char) utf7Char[i];


  free (utf7Char);
  free (--utf16Char);


  return ( returnCh );

#endif /* USE_TALIGENT */
}


FCHAR
UTF7ToUnicode (void)
{

#ifdef USE_TALIGENT
FCHAR fch = NIL;
UTF16 *utf16Char;



  utf16Char = (UTF16 *) LibEthConvertUTF7toUCS2 ();

  fch = (FCHAR) *utf16Char;
  free (utf16Char);


  return (fch);
#endif /* USE_TALIGENT */
}


unsigned char*
UnicodeToName ( fch )
  FCHAR fch;
{

unsigned char holdCh[44];
unsigned char *returnCh = NULL;
FCHAR uch = fch;
char form;


/* Detect Errors Here */

  if ( UNIFIDEL <= fch && fch <= EXTLAST )
    fch -= UNIFIDEL;
  else if ( fch > 0xff )  /* bail, we shouldn't be here */
    {
      returnCh = (unsigned char *) malloc ( 3 * sizeof(unsigned char) );
      returnCh[0] = (fch >> 8);
      returnCh[1] = (fch & 255);
      returnCh[2] = '\0';
      return ( returnCh );
    }
  else  /* no more than 8 bits */
    {
      returnCh = (unsigned char *) malloc ( 2 * sizeof(unsigned char) );
      returnCh[0] = (unsigned char) fch;
      returnCh[1] = '\0';
      return ( returnCh );
    }



/* We are clear of bad characters, return then requested UNICODE mapping */

  form = uch % 8;

  if ( uch < MYA )                                           /* Syllables     */
    sprintf ( holdCh, "ETHIOPIC SYLLABLE %s%s",
              EthiopicSyllableNames[(fch/8)], EthiopicVowelNames[(int)form] );
  else if ( uch < WORDSPACE )
    switch ( uch )
      {
    	case MYA: strcpy ( holdCh, "MYA" );
    	          break;
    	case RYA: strcpy ( holdCh, "RYA" );
    	          break;
    	case FYA: strcpy ( holdCh, "FYA" );
    	          break;
        default : fprintf (stderr, "Ethiopic Names: No Unicode mapping found.\n");
    	          break;
      }
  else if ( uch <  ONE )                                     /*  Punctuation  */
    sprintf ( holdCh, "ETHIOPIC %s", EthiopicPunctuationNames[uch-WORDSPACE] );
  else if ( uch < TEN )                                      /*  Digits       */
    sprintf ( holdCh, "ETHIOPIC DIGIT %s",  EthiopicNumberNames[uch-ONE] );
  else if ( uch <= TENTHOUSAND )                             /*  Numerals     */
    sprintf ( holdCh, "ETHIOPIC NUMBER %s", EthiopicNumberNames[uch-ONE] );
  else switch ( uch )
    {
      case TEMHERTESLAQ:
           strcpy ( holdCh, "ETHIOPIC SARCASM MARK" );
           break;
      case NETEB:
           strcpy ( holdCh, "ETHIOPIC STYLIZED DOT" );
           break;
      case LEFTQUOTE:
           strcpy ( holdCh, "ETHIOPIC STYLIZED LEFT GUILLEMETS" );
           break;
      case RIGHTQUOTE:
           strcpy ( holdCh, "ETHIOPIC STYLIZED RIGHT GUILLEMETS" );
           break;
      case EQUESTIONMARK:
           strcpy ( holdCh, "ETHIOPIC STYLIZED QUESTION MARK" );
           break;
      default:
           fprintf (stderr, "Ethiopic Names: No Unicode mapping found.\n");
           break;
    }


  returnCh = (unsigned char*) malloc ( (strlen (holdCh) + 1) * sizeof(holdCh) );
  strcpy ( returnCh, holdCh );

  return ( returnCh );

}
