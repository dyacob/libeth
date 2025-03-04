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

#include "doctypes.h"
#include "sysinfo.h"
#include "tex.h"
#include "tex.map"
#include "../systems/systems.h"


unsigned char*
UnicodeToTeX ( fch )
  FCHAR fch;
{
FCHAR uniFch = fch;
unsigned char* returnCh = NULL;


/* Detect Errors Here */

  if ( UNIFIDEL <= fch && fch <= EXTLAST )
    fch -= UNIFIDEL;
  else if ( PRIVATE_USE_BEGIN <= fch && fch <= PRIVATE_USE_END )
    fch  = (UNITOTAL-1) + (fch - PRIVATE_USE_END);
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
  if ( TeXFidel[fch] == NULL )
    {
      fprintf (stderr, "TeX[U+%04X]: No Unicode mapping found.\n", uniFch);
      return ( returnCh );
    } 



/* We are clear of bad characters, return then requested TeX mapping */

  returnCh = (unsigned char *) malloc ( strlen(TeXFidel[fch]) * sizeof(unsigned char) );
  sprintf ( returnCh, "%s", TeXFidel[fch] );


  return ( returnCh );

}


/*
 *  Simple routine to write files with tex macros for Ethiopic.
 *  This escapes correspond to those in the "fidelmap.tex" file.
 *  La/TeX support is limited at this time, some formatting will
 *  suffer or need revision afterwards.
 *
 *   texOut MUST be an unassigned pointer!!!!!!!!!!
 */
int
fidel_TeX_sputs (fstring, texOut, mylflags)
  FCHAR* fstring;
  char** texOut;
  LibEthFlags* mylflags;
{
register int i=-1;
int outTop=0;
FCHAR fch;
unsigned char* outString, *holdCh;


  if ( fstring == NULL )
    return ( _LET_FAIL );
  mylflags = checkLibEthFlags ( mylflags );
  
  outString = (char *) malloc ( (fidel_strlen(fstring) * 10) * sizeof(char) );

  while ( (fch = fstring[++i]) )
    if ( fch < ANSI )
      outString[outTop++] = (unsigned char)fch;
    else
      {
        holdCh = fidel_sputc (fch, mylflags); 
        if ( fstring[i+1] == GEMINATION )
          {
            if ( mylflags->csOut == ies )     /*  double the consonant  */
              sprintf ( &outString[outTop], "%c%s", holdCh[0], holdCh );
            else
              sprintf ( &outString[outTop], "\\geminateG{\\%s}", holdCh );
            i++;
          }
        else
          {
            if ( mylflags->csOut == muletex ) /*  double the consonant  */
              sprintf ( &outString[outTop], "{\\%s}", holdCh );
            else
              sprintf ( &outString[outTop], "%s", holdCh );
          }

        outTop += strlen ( &outString[outTop] );
        free ( (unsigned char *)holdCh );
      }


  outString[outTop] = '\0';
  *texOut = (char *) malloc ( (strlen(outString) +1) * sizeof(char) );
  strcpy (*texOut, outString);
  free ((char *) outString);

  return ( outTop );

}


int
fidel_TeX_fputs (fstring, fp, mylflags)
  FCHAR* fstring;
  FILE* fp;
  LibEthFlags* mylflags;
{

char* pstring;


  if ( fp == NULL || feof(fp) || fstring == NULL )
    return ( _LET_FAIL );
  mylflags = checkLibEthFlags ( mylflags );
  
  fidel_TeX_sputs (fstring, &pstring, mylflags);
  
  fprintf (fp, "%s", pstring);

  free (pstring);

  return ( _LET_SUCCESS );

}


char*
TeX_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (TEX_EMAIL);
        break;
      case LETH_WWW:
        return (TEX_WWW);
        break;
      case LETH_FTP:
        return (TEX_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
