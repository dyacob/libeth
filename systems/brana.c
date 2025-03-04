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
#include "brana.map"
#include "systems.h"

#include <string.h>


FCHAR
BranaIToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base; 


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = BranaIHashTable[base-0x20]) == NOCH          /* ...rouges   */
       || fch == SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }


  return (fch);

}



FCHAR
BranaIIToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base; 

  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = BranaIIHashTable[base-0x20]) == NOCH         /* ...rouges   */
       || fch == SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }


  return (fch);

}



unsigned char*
UnicodeToBrana ( fch )
  FCHAR fch;
{

FCHAR uniFch = fch;
unsigned char* returnCh = NULL;


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
  if ( BranaFidel[fch].fidel == NOCH )
    {
      fprintf (stderr, "Brana[U+%04X]: No Unicode mapping found.\n", uniFch);
      return ( returnCh );
    } 



/* We are clear of bad characters, return then requested Brana mapping */

  returnCh = (unsigned char *) malloc ( 2 * sizeof(unsigned char) );
  returnCh[0] = BranaFidel[fch].fidel[0];
  returnCh[1] = '\0';

  return ( returnCh );

}


int
Brana_get_setid ( fch )
  FCHAR fch;
{

/* Detect Errors Here */

  if ( UNIFIDEL <= fch && fch <= EXTLAST )
    fch -= UNIFIDEL;
  else if ( PRIVATE_USE_BEGIN <= fch && fch <= PRIVATE_USE_END )
    fch  = (UNITOTAL - 1) + (fch - PRIVATE_USE_END);
  else 
    return ( NIL );
  if ( BranaFidel[fch].fidel == NOCH )
    return ( NIL );

  return ( BranaFidel[fch].set );

}


int
Brana_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = (char *) malloc ( (strlen(BranaTTFNames[setid]) + 1) * sizeof(char) );
  strcpy ( *setName, BranaTTFNames[setid] );

  if ( setid )
    return ( NIL );
  else
    return ( setid+1 );  

}


int
Brana_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{

  *RTFPrefix = (unsigned char *) malloc ( (strlen(BranaRTFPrefix[0]) + 1) * sizeof(unsigned char) );
  strcpy ( *RTFPrefix, BranaRTFPrefix[0] );

  if ( setid )
    return ( NIL );
  else
    return ( setid+1 );  

}


unsigned char
BranaI_isGoodANSI ( fch )
  FCHAR fch;
{

  if ( fch >= ANSI )
    return ( false );

  if ( BranaIHashTable[fch - 0x20] == SAFEANSI )
    return ( (unsigned char)fch );

  return ( false );

}


char*
Brana_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (BRANA_EMAIL);
        break;
      case LETH_WWW:
        return (BRANA_WWW);
        break;
      case LETH_FTP:
        return (BRANA_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
