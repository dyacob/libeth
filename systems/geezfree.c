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
#include "geezfree.map"
#include "systems.h"
#include "base.h"


FCHAR
GeezFree2ToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base; 


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = GeezFree2HashTable[base-0x20]) == NOCH         /* ...rouges */
     )
    {
      return ( (FCHAR) base );
    }


  return (fch);

}



unsigned char*
UnicodeToGeezFree ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, GeezFreeFidel, "GeezFree" ) );

}


int
GeezFree_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, GeezFreeFidel ) );

}


int
GeezFree_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = strdup ( GeezFreeTTFNames[setid] );


  /* the number font is the compliment to each, except self */

  if ( setid  )
    return ( NIL );
  else
    return ( setid+1 );  

}


int
GeezFree_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{

  *RTFPrefix = strdup ( GeezFreeRTFPrefix[0] );


  /* the number font is the compliment to each, except self */

  if ( setid  )
    return ( NIL );
  else
    return ( setid+1 );  

}


char*
GeezFree_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (GEEZFREE_EMAIL);
        break;
      case LETH_WWW:
        return (GEEZFREE_WWW);
        break;
      case LETH_FTP:
        return (GEEZFREE_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
