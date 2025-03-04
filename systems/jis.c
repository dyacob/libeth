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
#ifdef SUPPORT_GREEK
#  include "greek.h"
#endif /* SUPPORT_GREEK */
#include "jis.h"
#include "systems.h"


unsigned char*
UnicodeToJIS ( fch )
  FCHAR fch;
{

boolean isFidel = true;
unsigned char* returnCh = NULL;
char ku, ten;


/* Detect Errors Here And Shift Addresses to Our Mapping System */

  if ( UNIFIDEL <= fch && fch <= EXTLAST )
    fch -= UNIFIDEL;
  else if ( PRIVATE_USE_BEGIN <= fch && fch <= PRIVATE_USE_END )
    fch  = (JISFIDELSIZE - 1) + (fch - PRIVATE_USE_END);
#ifdef SUPPORT_GREEK
  else if ( UNIGREEK <= fch && fch < UNIGREEK_END )
    {
      isFidel = false;
      fch -= UNIGREEK;
    }
#endif /* SUPPORT_GREEK */
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



/* We are clear of bad characters, return then requested JIS mapping */

  returnCh = (unsigned char *) malloc ( 3 * sizeof(unsigned char) );

  if ( isFidel )
    {
      ku  = fch/94 + 'Z';
      ten = fch%94 +  1;
      returnCh[0] = ku  + JISADJUST;
      returnCh[1] = ten + JISADJUST;
    }
#ifdef SUPPORT_GREEK
  else  
    /*  ...it's Greek to me...
     *  For anything else I should use a standard Unicode->JIS library
     *  ...I need to look for one.
     */
    {
      ku  = 6
      ten = fch;
      returnCh[0] = ku  + JISADJUST;
      returnCh[1] = ten + JISADJUST;
    }
#endif /* SUPPORT_GREEK */

  returnCh[2] = '\0';


  return ( returnCh );

}



char*
JIS_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (JIS_EMAIL);
        break;
      case LETH_WWW:
        return (JIS_WWW);
        break;
      case LETH_FTP:
        return (JIS_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
