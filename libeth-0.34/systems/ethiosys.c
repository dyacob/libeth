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
#include "ethiosys.map"
#include "systems.h"
#include "base.h"


FCHAR
EthioSysPrimaryToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base; 


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = EthioSysPrimaryHashTable[base-0x20]) == NOCH /* ...rouges   */
       || fch == SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }


  return (fch);

}



FCHAR
EthioSysSecondaryToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base; 


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = EthioSysSecondaryHashTable[base-0x20]) == NOCH /* ...rouges */
     )
    {
      return ( (FCHAR) base );
    }


  return (fch);

}



unsigned char*
UnicodeToEthioSys ( fch )
  FCHAR fch;
{


  FCHAR map;
  boolean special = CheckSpecialSets ( fch, EthioSysFidel, "EthioSys" );

  if ( special && EthioSysFidel[(map = MapFchar(fch))].set == SETW )
    {
      unsigned char* returnCh = (unsigned char *) malloc ( 3 * sizeof(unsigned char) );
      returnCh[0] = EthioSysFidel[map].fidel[0];
      returnCh[1] = EthioSysFidel[map].vowel[0];
      returnCh[2] = '\0';
      return ( returnCh );
    }
  else
    return ( UnicodeToBase ( fch, EthioSysFidel, "EthioSys" ) );

}



int
EthioSys_get_setid ( fch )
  FCHAR fch;
{

  FCHAR map = MapFchar ( fch );

  return ( EthioSysFidel[map].set == SETW )
  ? SET0
  : ( EthioSysFidel[map].set == SETX )
    ? SET1
    : Base_get_setid ( fch, EthioSysFidel )
  ;

}


int
EthioSys_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = strdup ( EthioSysTTFNames[setid+fontFace] );

  if ( setid )
    return ( NIL );
  else
    return ( setid+1 );  

}


int
EthioSys_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{

  *RTFPrefix = strdup ( EthioSysRTFPrefix[0] );

  if ( setid )
    return ( NIL );
  else
    return ( setid+1 );  

}


unsigned char
EthioSys_isGoodANSI ( fch )
  FCHAR fch;
{

  return ( Base_isGoodANSI ( fch, EthioSysPrimaryHashTable ) );

}


char*
EthioSys_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (ETHIOSYS_EMAIL);
        break;
      case LETH_WWW:
        return (ETHIOSYS_WWW);
        break;
      case LETH_FTP:
        return (ETHIOSYS_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
