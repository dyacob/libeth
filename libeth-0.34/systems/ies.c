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
#include "ies.map"
#include "systems.h"

#include <string.h>


unsigned char*
UnicodeToIESGeez ( fch )
  FCHAR fch;
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



/* We are clear of bad characters, return then requested IES mapping */

  holdCh = (unsigned char *) malloc ( (6 + 1) * sizeof(unsigned char) );


  form = uch % 8;
  base = uch - form;

  if ( HAE <= base && base < MYA )                /*  Basic Range Syllables  */
    {
      if ( base == AE )
        {
          if (form == GIZ)
            form = RABI;
          if (form == DIQALA)
            form = GIZ;

            sprintf ( holdCh, "%s", IESVowelHash[(int)form] );
        }
      else if ( base == (QAE + DIQALA_GIZ)
                || base == (QXAE + DIQALA_GIZ)
                || base == (HZAE + DIQALA_GIZ)
                || base == (KAE + DIQALA_GIZ)
                || base == (KHAE + DIQALA_GIZ)
                || base == (GAE + DIQALA_GIZ)
              )
        sprintf ( holdCh, "%s%s", IESFidelHash[(fch/8)], IESLabialHash[(int)form] );
      
      else if ( form != SADS )
        sprintf ( holdCh, "%s%s", IESFidelHash[(fch/8)], IESVowelHash[(int)form] );
      else
        strcpy ( holdCh, IESFidelHash[(fch/8)] );
    }
  else if ( SPACE <= uch && uch <  ONE )                    /*  Punctuation  */
    sprintf ( holdCh, "%s", IESPunctHash[(int)(uch%16)] );
  else if ( ONE <= uch && uch <= TENTHOUSAND )              /*  Numerals     */
    {
      if ( uch < TEN )
        sprintf ( holdCh, "%i", (uch - (ONE - 1)) );
      else if ( uch < HUNDRED )
        sprintf ( holdCh, "%i0",(HUNDRED - uch)  );
      else if ( uch == HUNDRED )
        strcpy ( holdCh, "100" );
      else
        strcpy ( holdCh, "10,000" );
    }
  else switch ( uch )
    {
    	case MYA: strcpy ( holdCh, "mya" );
    	          break;
    	case RYA: strcpy ( holdCh, "rya" );
    	          break;
    	case FYA: strcpy ( holdCh, "fya" );
    	          break;
        default : /* if ( ORNAMENT <= uch && uch <= PRIVATE_USE_END )
                    strcpy ( holdCh, SERAExtHash[(uch-ORNAMENT+NUM_EXTENDED)] );
                  else if ( QYAE <= uch && uch <= (QYAE+NUM_EXTENDED) )
                    strcpy ( holdCh, SERAExtHash[uch-QYAE] );
                  else */
                    fprintf (stderr, "SERA: No Unicode mapping found.\n");
    	          break;
    }

  returnCh = (unsigned char*) malloc ( (strlen (holdCh) + 1) * sizeof(holdCh) );
  strcpy ( returnCh, holdCh );
  free ( (unsigned char*) holdCh );


  return ( returnCh );

}


unsigned char*
UnicodeToIESAmharic ( fch )
  FCHAR fch;
{

unsigned char *returnCh = NULL;
char form = fch % 8;
int base = fch - form;


  if ( base == HHAE )
    fch -= (HHAE-HAE);
  else if ( base == HZAE )
    fch -= (HZAE-HAE);
  else if ( base == KHAE )
    fch -= (KHAE-HAE);
  else if ( base == TSZAE )
    fch -= ROW;  /* TSAE */
  else if ( base == OAE )
    fch -= (OAE-AE);

  if ( fch == HAE || fch == AE )
    fch += RABI;

  if ( ( (HZAE + DIQALA_GIZ) < fch && fch < (HZAE + DIQALA_SADS) )
       || ( (KHAE + DIQALA_GIZ) < fch && fch < (KHAE + DIQALA_SADS) ) )
    {
        returnCh = (unsigned char *) malloc ( ( strlen ( IESFidelHash[(fch-UNIFIDEL)] ) + strlen ( IESLabialHash[(int)form] ) + 1 ) * sizeof (unsigned char) );
        sprintf ( returnCh, "%s%s", IESFidelHash[(HAE-UNIFIDEL)], IESLabialHash[(int)form] );
        return ( returnCh );
    }
  else
    return ( UnicodeToIESGeez ( fch ) );

}


unsigned char*
UnicodeToIESTigrigna ( fch )
  FCHAR fch;
{

char form = fch % 8;
int base = fch - form;


  if ( base == HZAE )
    fch = HAE;
  else if ( base == TSZAE )
    fch = TSAE;


  return ( UnicodeToIESGeez ( fch ) );

}


char*
IES_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (IES_EMAIL);
        break;
      case LETH_WWW:
        return (IES_WWW);
        break;
      case LETH_FTP:
        return (IES_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
