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
#include "iso.map"
#include "systems.h"

#include <string.h>


unsigned char*
UnicodeToISOTC46SC2 ( fch, mylflags )
  FCHAR fch;
  LibEthFlags* mylflags;
{

unsigned char *returnCh = NULL, *holdCh = NULL;
FCHAR uch = fch;
int base;
char form;


/* Detect Errors Here */

  if ( UNIFIDEL <= fch && fch <= EXTLAST )
    fch -= UNIFIDEL;
  else if ( PRIVATE_USE_BEGIN <= fch && fch <= PRIVATE_USE_END )
    fch  = (UNITOTAL - 1) + (fch - PRIVATE_USE_END);
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



/* We are clear of bad characters, return then requested ISOTC46SC2 mapping */

  holdCh = (unsigned char *) malloc ( (6 + 1) * sizeof(unsigned char) );


  form = uch % 8;
  base = uch - form;

  if ( HAE <= base && base < MYA )                /*  Basic Range Syllables  */
    {
      if ( base == AE )
        {
          if (form == DIQALA)
            strcpy ( holdCh, "ea" );
          else
            strcpy ( holdCh, ISOTC46SC2VowelHash[(int)form] );
        }
      else if ( base == OAE )
        sprintf ( holdCh, "`%s", ISOTC46SC2VowelHash[(int)form] );
      else if ( form != SADS )
        sprintf ( holdCh, "%s%s", ISOTC46SC2FidelHash[(fch/8)], ISOTC46SC2VowelHash[(int)form] );
      else
        strcpy ( holdCh, ISOTC46SC2FidelHash[(fch/8)] );
    }
  else if ( SPACE <= uch                                    /*  Punctuation  */
            && uch <= TENTHOUSAND )                         /*  Numerals     */
    {
      free ((unsigned char *)holdCh);
      return ( _UnicodeToSERA ( uch, mylflags ) );
    }
  else switch ( uch )
    {
    	case MYA: strcpy ( holdCh, "mya" );
    	          break;
    	case RYA: strcpy ( holdCh, "rya" );
    	          break;
    	case FYA: strcpy ( holdCh, "fya" );
    	          break;
        default : if ( ORNAMENT <= uch && uch <= PRIVATE_USE_END )
                    strcpy ( holdCh, ISOTC46SC2ExtHash[(uch-ORNAMENT+NUM_EXTENDED)] );
                  else if ( QYAE <= uch && uch <= (QYAE+NUM_EXTENDED) )
                    strcpy ( holdCh, ISOTC46SC2ExtHash[uch-QYAE] );
                  else
                    fprintf (stderr, "ISOTC46SC2: No Unicode mapping found.\n");
    	          break;
    }

  returnCh = (unsigned char*) malloc ( (strlen (holdCh) + 1) * sizeof(holdCh) );
  strcpy ( returnCh, holdCh );
  free ( (unsigned char*) holdCh );


  return ( returnCh );

}


char*
ISO_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (ISO_EMAIL);
        break;
      case LETH_WWW:
        return (ISO_WWW);
        break;
      case LETH_FTP:
        return (ISO_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
