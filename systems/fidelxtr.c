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
#include "fidelxtr.map"
#include "systems.h"
#include "base.h"


FCHAR
FidelExtra1ToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base; 


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = FidelExtra1HashTable[base-0x20]) == NOCH     /* ...rouges   */
     )
    {
      return ( (FCHAR) base );
    }


  return (fch);

}




FCHAR
FidelExtra2ToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base; 


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = FidelExtra2HashTable[base-0x20]) == NOCH     /* ...rouges   */
     )
    {
      return ( (FCHAR) base );
    }


  return (fch);

}



unsigned char*
UnicodeToFidelExtra ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, FidelExtraFidel, "FidelExtra" ) );

}


int
FidelExtra_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, FidelExtraFidel ) );

}


int
FidelExtra_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = strdup ( FidelExtraTTFNames[setid] );

  if ( setid  )
    return ( NIL );
  else
    return ( setid+1 );  

}


int
FidelExtra_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{

  *RTFPrefix = strdup ( FidelExtraRTFPrefix[0] );

  if ( setid )
    return ( NIL );
  else
    return ( setid+1 );  

}


char*
FidelExtra_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (FIDELXTRA_EMAIL);
        break;
      case LETH_WWW:
        return (FIDELXTRA_WWW);
        break;
      case LETH_FTP:
        return (FIDELXTRA_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
