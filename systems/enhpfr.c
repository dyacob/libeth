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
#include "enhpfr.map"
#include "systems.h"
#include "base.h"


unsigned char*
UnicodeToENHPFR_he ( fch )
  FCHAR fch;
{

FCHAR uniFch = fch;
unsigned char* returnCh = NULL;


/* Detect Errors Here */

  if ( UNIFIDEL <= fch && fch <= UNILAST )
    fch -= 0x11df;
  else if ( (UNILAST <= fch && fch <= EXTLAST) 
            || (PRIVATE_USE_BEGIN <= fch && fch <= PRIVATE_USE_END) )
    return ( returnCh );
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


/* We are clear of bad characters, return then requested ENHPFR mapping */

  if ( uniFch >= BAE )
    fch += 4*ROW;
  if ( uniFch >= TAE )
    fch -= 1;
  if ( uniFch == VAE + DIQALA )
    fch = 0xff;

/*  fch =  ( uniFch >= TAE ) ?  fch + 4*ROW : (uniFch >= BAE) ? fch + 4*ROW + 1 : ( uniFch == VAE + DIQALA ) ? 0xff : fch ; */

  returnCh = (unsigned char *) malloc ( 2 * sizeof(unsigned char) );
  returnCh[0] = (unsigned char) fch;
  returnCh[1] = '\0';

  return ( returnCh );

}



unsigned char*
UnicodeToENHPFR_le ( fch )
  FCHAR fch;
{

FCHAR uniFch = fch;
unsigned char* returnCh = NULL;


/* Detect Errors Here */

  if ( UNIFIDEL <= fch && fch <= UNILAST )
    fch -= (KHAE + DIQALA) - 0x20;
  else if ( (UNILAST <= fch && fch <= EXTLAST) 
            || (PRIVATE_USE_BEGIN <= fch && fch <= PRIVATE_USE_END) )
    return ( returnCh );
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


/* We are clear of bad characters, return then requested ENHPFR mapping */

  if ( GGAE <= uniFch && uniFch < THAE )
    fch -= 1;
  if ( uniFch >= THAE )
    fch += 4*ROW;

  returnCh = (unsigned char *) malloc ( 2 * sizeof(unsigned char) );
  returnCh[0] = (unsigned char) fch;
  returnCh[1] = '\0';

  return ( returnCh );

}



int
ENHPFR_get_setid ( fch )
  FCHAR fch;
{

/* Detect Errors Here */

  if ( UNIFIDEL <= fch && fch < KHAE+DIQALA )
    return (SET0);
  if ( KHAE+DIQALA <= fch && fch <= UNILAST )
    return (SET1);

  return ( NIL );

}



int
ENHPFR_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = strdup ( ENHPFRTTFNames[setid+fontFace] );

  return (NIL);

}



unsigned char
ENHPFR_isGoodANSI ( fch )
  FCHAR fch;
{
  return ( false );
}



char*
ENHPFR_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (ENHPFR_EMAIL);
        break;
      case LETH_WWW:
        return (ENHPFR_WWW);
        break;
      case LETH_FTP:
        return (ENHPFR_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
