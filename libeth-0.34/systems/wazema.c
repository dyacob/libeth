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
#include "wazema.map"
#include "systems.h"
#include "base.h"


FCHAR
WazemaA1ToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base; 


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = WazemaA1HashTable[base-0x20]) == NOCH /* ...rouges   */
       || fch == SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }


  return (fch);

}



FCHAR
WazemaA2ToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base; 


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = WazemaA2HashTable[base-0x20]) == NOCH /* ...rouges */
     )
    {
      return ( (FCHAR) base );
    }


  return (fch);

}



unsigned char*
UnicodeToWazema ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, WazemaFidel, "Wazema" ) );

}



int
Wazema_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, WazemaFidel ) );

}


int
Wazema_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = strdup ( WazemaTTFNames[setid+fontFace] );

  if ( setid )
    return ( NIL );
  else
    return ( setid+1 );  

}


int
Wazema_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{

  *RTFPrefix = strdup ( WazemaRTFPrefix[0] );

  if ( setid )
    return ( NIL );
  else
    return ( setid+1 );  

}


/* when ready make a WazemaA1_isGoodANSI and Wazema_isGoodANSI */
unsigned char
WazemaA1_isGoodANSI ( fch )
  FCHAR fch;
{

  if ( fch >= ANSI )
    return ( false );

  if ( WazemaA1HashTable[fch - 0x20] == SAFEANSI )
    return ( (unsigned char)fch );


  return ( false );

}


unsigned char
WazemaA2_isGoodANSI ( fch )
  FCHAR fch;
{

  if ( fch >= ANSI )
    return ( false );

  switch ( fch )
    {
      case '/'  :  fch = 'n';
                   break;

      case '*'  :  fch = 'o';
                   break;

      case '\\' :  fch = 0xba;
                   break;

      case '|'  :  fch = 0xb6;
                   break;

      case '('  :  fch = 0xbe;
                   break;

      case ')'  :  fch = 0xbf;
                   break;

      case '['  :  fch = 0xc0;
                   break;

      case ']'  :  fch = 0xc1;
                   break;

      case '{'  :  fch = 0xc2;
                   break;

      case '}'  :  fch = 0xc3;
                   break;

      case 0xb1 :  fch = 'm';
                   break;

      case 0xab :  fch = '|';
                   break;

      case 0xbb :  fch = '~';
                   break;

      case '<'  :  fch = 0x99;
                   break;

      case '>'  :  fch = 0x9a;
                   break;

      case '!'  :  fch = 0xb3;
                   break;

      case 0xa1 :  fch = 0xb7;
                   break;

      case '?'  :  fch = 0xb6;
                   break;

      case 0xbf :  fch = 0xb5;
                   break;

      case '"'  :
      case '\'' :
      case '$'  :
      case '%'  :
      case '+'  :
      case '-'  :
      case '.'  :
      case '='  :
                   break;

      default   :  fch = false;
                   break;
    }

    return ( (unsigned char)fch );
}


char*
Wazema_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (WAZEMA_EMAIL);
        break;
      case LETH_WWW:
        return (WAZEMA_WWW);
        break;
      case LETH_FTP:
        return (WAZEMA_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
