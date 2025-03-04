/* This is part of the LibEth library, an ANSI C library for Qubeeic
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
#include "qubee.map"
#include "systems.h"

#include <string.h>


FCHAR
QubeeToUnicode ( void )
{
  return (1);
}


unsigned char*
UnicodeToQubee ( fch )
  FCHAR fch;
{

FCHAR uch = fch;
unsigned char *returnCh = NULL, *holdCh = NULL;
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



/* We are clear of bad characters, return then requested QUBEE mapping */


  holdCh = (unsigned char *) malloc ( (14 + 1) * sizeof(unsigned char) );


  form = uch % 8;
  base = uch - form;

  if ( HAE <= base && base < MYA )                /*  Basic Range Syllables  */
    {
      if ( base == AE && form == DIQALA )
        strcpy ( holdCh, QubeeVowelHash[0] );
      else
        sprintf ( holdCh, "%s%s", QubeeFidelHash[(fch/8)], QubeeVowelHash[(int)form] );
    }
  else if ( WORDSPACE <= uch && uch <  ONE )                /*  Punctuation  */
    sprintf ( holdCh, "%s", QubeePunctHash[(int)form] );
  else if ( ONE <= uch && uch <= TENTHOUSAND )              /*  Numerals     */
    {
      if ( uch < TEN )
        sprintf ( holdCh, "%i", (uch - (ONE - 1)) );
      else if ( uch < HUNDRED )
        sprintf ( holdCh, "%i0", (uch - (TEN - 1))  );
      else if ( uch == HUNDRED )
        strcpy ( holdCh, "100" );
      else
        strcpy ( holdCh, "10,000" );
    }
  else switch ( uch )
    {
    	case MYA: strcpy ( holdCh, "myaa" );
    	          break;
    	case RYA: strcpy ( holdCh, "ryaa" );
    	          break;
    	case FYA: strcpy ( holdCh, "fyaa" );
    	          break;
        default : if ( ORNAMENT <= uch && uch <= PRIVATE_USE_END )
                    strcpy ( holdCh, QubeeExtHash[uch-ORNAMENT+NUM_EXTENDED] );
                  else if ( QYAE <= uch && uch <= (QYAE+NUM_EXTENDED) )
                    strcpy ( holdCh, QubeeExtHash[uch-QYAE] );
                  else
                    fprintf (stderr, "Qubee: No Unicode mapping found.\n");
    	          break;
    }

  returnCh = (unsigned char*) malloc ( (strlen (holdCh) + 1) * sizeof(holdCh) );
  strcpy ( returnCh, holdCh );
  free ( (unsigned char*) holdCh );


  return ( returnCh );

}


char*
Qubee_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (QUBEE_EMAIL);
        break;
      case LETH_WWW:
        return (QUBEE_WWW);
        break;
      case LETH_FTP:
        return (QUBEE_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
