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
#include "etstdlib.h"
#include "etstdio.h"
#include "etctype.h"
#include "etstring.h"
#include "sysinfo.h"
#include "etmath.h"
#include "ettime.h"
#include "../doctypes/html.h"
#include "../systems/filters.h"
#include "langxs.h"

extern void lexer_reset ( LibEthFlags* lethFlags );


unsigned char*
ArabToEthiopic (Enumber, system, xfer, font, iPath)
  char* Enumber;
  int system;
  int xfer;
  int font;
  char* iPath;
{
	LibEthFlags* mylflags = SetDefaultLibEthFlags (NIL, eng, NIL);
	FCHAR* uniString;
	int setId = NIL, nestLevel = 0;
	enum HTMLEscapes TagOn = Off;
	unsigned char* outString;


	mylflags->cstIn       = mylflags->cstOut = html;
	mylflags->csOut       = system;
	mylflags->tvOut       = xfer;
	mylflags->fontFaceOut = font;

	uniString = arabtof ( Enumber );
	if ( mylflags->csOut == jis && mylflags->cstOut == html )
	  jis_remap_space ( uniString );
	if ( mylflags->csOut == image )
	  image_sputs (uniString, (char **)&outString, iPath, mylflags);
	else if ( isFidelTrueType( system ) )
	  fidel_HTML_sputs (uniString, &outString, setId, &TagOn, CLOSESTRING | NESTONCE,  &nestLevel, mylflags);
	else
	   fidel_sputs (uniString, &outString, mylflags);

	free ((FCHAR *)uniString); 
	free ((LibEthFlags *)mylflags);


	return ( outString );

}



unsigned char*
ConvertEthiopicString (string, sysIn, xferIn, sysOut, xferOut, fontOut, langOut, iPath, options, closing)
  char* string;
  int sysIn;
  int xferIn;
  int sysOut;
  int xferOut;
  int fontOut;
  enum Languages langOut;
  char* iPath;
  unsigned int options;
  int closing;
{
	LibEthFlags* mylflags;
	unsigned char* outString = NULL;
	FCHAR* uniString = NULL;
	int setId = NIL, nestLevel = 0;
	enum HTMLEscapes TagOn = Off;
	int closeString;

	mylflags = ( sysOut == sera ) 
	         ? SetDefaultLibEthFlags (eng,     langOut, langOut)
	         : SetDefaultLibEthFlags (langOut, eng,     langOut)
	         ;

	mylflags->cstIn       = mylflags->cstOut = html;
	mylflags->csIn        = sysIn;
	mylflags->tvIn        = xferIn;
	mylflags->csOut       = sysOut;
	mylflags->tvOut       = xferOut;
	mylflags->fontFaceOut = fontOut;
	mylflags->options     = options;


	closeString = (closing) ? CLOSESTRING : 0x00;

	uniString   = sget_fstring ( string, mylflags );


	if ( mylflags->options & aynIsZero )
	  ayn2zero ( uniString );
	if ( mylflags->csOut == jis && mylflags->cstOut == html )
	  jis_remap_space ( uniString );
	if ( mylflags->csOut == image )
	  image_sputs (uniString, (char **)&outString, iPath, mylflags);
	else if ( isFidelTrueType( sysOut ) )
	  fidel_HTML_sputs (uniString, &outString, setId, &TagOn, closeString | NESTONCE,  &nestLevel, mylflags);
	else
	   fidel_sputs (uniString, &outString, mylflags);


	if ( sysIn == sera )
	  lexer_reset ( mylflags );


	free ((FCHAR *)uniString);
	free ((LibEthFlags *)mylflags);


	return ( outString );
}



/*  The string here is automatically closed.  Check later if this is happening
 *  for each line of a file or just at the end of the file.
 */
unsigned char*
ConvertEthiopicFileToString (fileP, sysIn, xferIn, sysOut, xferOut, fontOut, langOut, iPath, options)
  FILE* fileP;
  int sysIn;
  int xferIn;
  int sysOut;
  int xferOut;
  int fontOut;
  enum Languages langOut;
  char* iPath;
  unsigned int options;
{
	LibEthFlags* mylflags;
	unsigned char *outString = NULL, *returnString = NULL;
	unsigned char *fileString = NULL, *tempString = NULL;
	FCHAR* uniString = NULL;
	int setId = NIL, nestLevel = 0;
	enum HTMLEscapes TagOn = Off;
	int top = 0, newStringLength = 0, end = 50000;


	if ( feof(fileP) )
	  return ( NULL );

	fileString = (unsigned char*) calloc ( end, sizeof (unsigned char)  );

	mylflags = ( sysOut == sera ) 
	         ? SetDefaultLibEthFlags (eng,     langOut, langOut)
	         : SetDefaultLibEthFlags (langOut, eng,     langOut)
	         ;

	mylflags->cstIn       = mylflags->cstOut = html;
	mylflags->csIn        = sysIn;
	mylflags->tvIn        = xferIn;
	mylflags->csOut       = sysOut;
	mylflags->tvOut       = xferOut;
	mylflags->fontFaceOut = fontOut;
	mylflags->options     = options;


	do 
	  {
		// if ( (uniString = fidel_fgets (NULL, WSIZE, fileP, mylflags)) == NULL )
		if ( (uniString = fidel_fgets (NULL, 2000, fileP, mylflags)) == NULL )
		  break;

		if ( mylflags->options & aynIsZero )
		  ayn2zero ( uniString );
    		if ( mylflags->csOut == jis && mylflags->cstOut == html )
		  jis_remap_space ( uniString );
		if ( mylflags->csOut == image )
		  image_sputs (uniString, (char **)&outString, iPath, mylflags);
		else if ( isFidelTrueType ( sysOut ) )
		  setId = fidel_HTML_sputs (uniString, &outString, setId, &TagOn, 0x00 | NESTONCE, &nestLevel, mylflags);
		else
		  fidel_sputs (uniString, &outString, mylflags);

		newStringLength = strlen ( outString );

		if ( (top + newStringLength) < end )
		  {
			strcat ( fileString, outString );
		  }
		else
		  {
			end *= 1.5;
			tempString = (unsigned char*) calloc ( end, sizeof (unsigned char)  );
			strcpy ( tempString, fileString );
			strcat ( tempString, outString );
			free ((unsigned char *)outString); 
			outString = fileString;
			fileString = tempString;
		  }

		top += newStringLength;


		free ((unsigned char *)outString); 
		free ((FCHAR *)uniString); 
	  }
	while (!feof(fileP));


	free ((LibEthFlags *)mylflags);

	returnString = (unsigned char*) malloc ( (top+1) * sizeof (unsigned char)  );
	strcpy ( returnString, fileString );
	free ((unsigned char *)fileString); 


	return ( returnString );
}



void
ConvertEthiopicFile (fileIn, fileOut, sysIn, xferIn, sysOut, xferOut, fontOut, langOut, iPath, options)
  FILE* fileIn;
  FILE* fileOut;
  int sysIn;
  int xferIn;
  int sysOut;
  int xferOut;
  int fontOut;
  enum Languages langOut;
  char* iPath;
  unsigned int options;
{
	LibEthFlags* mylflags;
	unsigned char* outString = NULL;
	FCHAR* uniString = NULL;
	int setId = NIL, nestLevel = 0;
	enum HTMLEscapes TagOn = Off;


	if ( feof(fileIn) )
	  return;


	mylflags = ( sysOut == sera ) 
	         ? SetDefaultLibEthFlags (eng,     langOut, langOut)
	         : SetDefaultLibEthFlags (langOut, eng,     langOut)
	         ;

	mylflags->cstIn       = mylflags->cstOut = html;
	mylflags->csIn        = sysIn;
	mylflags->tvIn        = xferIn;
	mylflags->csOut       = sysOut;
	mylflags->tvOut       = xferOut;
	mylflags->csOut       = sysOut;
	mylflags->tvOut       = xferOut;
	mylflags->fontFaceOut = fontOut;
	mylflags->options     = options;


	do 
	  {
		if ( (uniString = fidel_fgets (NULL, WSIZE, fileIn, mylflags)) == NULL )
		  break;

		if ( mylflags->options & aynIsZero )
		  ayn2zero ( uniString );
		if ( mylflags->csOut == jis && mylflags->cstOut == html )
	    	  jis_remap_space ( uniString );
    		if ( mylflags->csOut == image )
		  image_sputs (uniString, (char **)&outString, iPath, mylflags);
    		else if ( isFidelTrueType( sysOut ) )
		  setId = fidel_HTML_sputs (uniString, &outString, setId, &TagOn, NESTONCE, &nestLevel, mylflags);
		else
		   fidel_sputs (uniString, &outString, mylflags);

		fprintf ( fileOut, "%s", outString );

		free ((unsigned char *)outString); 
		free ((FCHAR *)uniString); 
	  }
	while (!feof(fileIn));


	free ((LibEthFlags *)mylflags);

}
