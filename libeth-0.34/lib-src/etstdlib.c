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
#include "lethutil.h"
#include "fidel.map"

#ifndef LNS
# define LNS 1
  LS LnS[NUMLANGS+1] = LSDEFS;
#endif /* LNS */

char* ISO639_3Names[NUMLANGS] = ISO639_3;
char* ISO639_2Names[NUMLANGS] = ISO639_2;

LibEthFlags* FidelFlags;


float
LibEthVersion (void)
{
  return ( (float)(LIBETH_VERSION_MAJOR + LIBETH_VERSION_MINOR) );
}


unsigned char*
LibEthVersionName (void)
{

unsigned char* version = (unsigned char *) malloc ( 120 * sizeof(unsigned char) );

  sprintf ( version, "This is LibEth Version %.3f \"%s\"", LibEthVersion(),
            LIBETH_VERSION_NAME );

  return (version);

}


char*
LibEthVersionDate (void)
{

char* date = (char *) malloc ( 120 * sizeof(char) );

  strcpy ( date, LIBETH_EXPORT_DATE );

  return (date);

}



LibEthFlags*
SetDefaultLibEthFlags (major, minor, top)
  enum Languages major; 
  enum Languages minor;
  enum Languages top;
{

char* envlang = NULL;
enum Languages lang = NIL;
LibEthFlags* lethFlags;



  envlang = (char *)getenv("LANG");

  if ( envlang != NULL ) 
    {
      if ( !strcmp(envlang, ISO639_3Names[amh]) || !strcmp(envlang, ISO639_2Names[amh]) 
            || !strcmp(envlang, "Amharic") || !strcmp(envlang, "amharic") )
        lang = amh;
      else if ( !strcmp(envlang, ISO639_3Names[tir]) || !strcmp(envlang, ISO639_2Names[tir]) 
                 || !strcmp(envlang, "Tigrigna") || !strcmp(envlang, "tigrigna") )
        lang = tir;
      else if ( !strcmp(envlang, ISO639_3Names[gez]) || !strcmp(envlang, ISO639_2Names[gez]) 
                 || !strcmp(envlang, "Ge'ez") || !strcmp(envlang, "ge'ez") )
        lang = gez;
    }


  lethFlags              =  (LibEthFlags *) malloc ( sizeof(LibEthFlags) );

  if ( top != NIL )
    lethFlags->out       =  lethFlags->top  =& LnS[top];
  else if ( lang != NIL )
    lethFlags->out       =  lethFlags->top  =& LnS[lang];
  else
    lethFlags->out       =  lethFlags->top  =& LnS[LETLANGMAJOR];


  if ( minor == NIL )
    lethFlags->minor     =&  LnS[LETLANGMINOR];
  else
    lethFlags->minor     =&  LnS[minor]; 


  if ( major != NIL )
    lethFlags->major     =&  LnS[major];
  else if ( lang != NIL )
    lethFlags->major     =&  LnS[lang];
  else
    lethFlags->major     =&  LnS[LETLANGMAJOR];


  lethFlags->lastChar    =    '\0';  /* these preserve state     */ 
  lethFlags->lastPunct   =   false;
  lethFlags->lexerState  =       0;
  lethFlags->form        =     NIL;

  lethFlags->fontFaceIn  =       0;  /* these are I/O settings   */
  lethFlags->fontFaceOut =       0;

  lethFlags->ctIn        =    text;
  lethFlags->ctOut       =    text;
  lethFlags->cstIn       =   plain;
  lethFlags->cstOut      =   plain;
  lethFlags->csIn        =    sera;
  lethFlags->csOut       = unicode;
  lethFlags->tvIn        =    notv;
  lethFlags->tvOut       =    utf8;

  lethFlags->options     =   noOps;

  lethFlags->holdChars   =    NULL;
  lethFlags->stringTop   =    NULL;

  return (lethFlags); 

}



LibEthFlags*
checkLibEthFlags (mylflags)
  LibEthFlags* mylflags;
{

  if ( mylflags == NULL )                  /* create or use internal   */
    {
	  if ( FidelFlags == NULL )
        FidelFlags =  SetDefaultLibEthFlags (LETLANGMAJOR, LETLANGMINOR, LETLANGMAJOR);
	  mylflags = FidelFlags;
    }

  return (mylflags);

}
