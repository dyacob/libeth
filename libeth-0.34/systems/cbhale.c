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
#include "cbhale.map"
#include "systems.h"
#include "base.h"


FCHAR
CBHaleAToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base; 


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = CBHaleAHashTable[base-0x20]) == NOCH         /* ...rouges   */
       || fch == SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }


  return (fch);

}



FCHAR
CBHaleBToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base; 


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = CBHaleBHashTable[base-0x20]) == NOCH           /* ...rouges */
     )
    {
      return ( (FCHAR) base );
    }


  return (fch);

}



unsigned char*
UnicodeToCBHale ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, CBHaleFidel, "CBHale" ) );

}



int
CBHale_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, CBHaleFidel ) );

}


int
CBHale_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName =  strdup ( CBHaleTTFNames[setid+fontFace] );

  if ( setid == NUM_CBHALE-1 )
    return ( NIL );
  else
    return ( NUM_CBHALE-1 );  

}


int
CBHale_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{

  *RTFPrefix = strdup ( CBHaleRTFPrefix[0] );

  if ( setid == NUM_CBHALE-1 )
    return ( NIL );
  else
    return ( NUM_CBHALE-1 );  


}


unsigned char
CBHaleA_isGoodANSI ( fch )
  FCHAR fch;
{

  return ( Base_isGoodANSI ( fch, CBHaleAHashTable ) );

}


char*
CBHale_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (CBHALE_EMAIL);
        break;
      case LETH_WWW:
        return (CBHALE_WWW);
        break;
      case LETH_FTP:
        return (CBHALE_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
