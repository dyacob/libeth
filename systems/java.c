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
#include "java.h"
#include "systems.h"


unsigned char*
UnicodeToJava ( fch, lower )
  FCHAR fch;
  boolean lower;
{

unsigned char* returnCh = NULL;


  if ( fch <= 0x7f )
    {
      returnCh = (unsigned char *) malloc ( 2 * sizeof(unsigned char) );
      returnCh[0] = (unsigned char) fch;
      returnCh[1] = '\0';
      return ( returnCh );
    }
  else if ( fch <= 0xff )
    {
      returnCh = (unsigned char *) malloc ( (5) * sizeof(unsigned char) );
      if ( lower )
        sprintf ( returnCh, "\\u%2x", fch );   /* lowercase */
      else
        sprintf ( returnCh, "\\u%2X", fch );   /* UPPERCASE */
      return ( returnCh );
    }



/* We are clear of bad characters, return then requested Java mapping */

   returnCh = (unsigned char *) malloc ( (7) * sizeof(unsigned char) );
   if ( lower )
     sprintf ( returnCh, "\\u%4x", fch );   /* lowercase */
   else
     sprintf ( returnCh, "\\u%4X", fch );   /* UPPERCASE */


  return ( returnCh );

}


char*
Java_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (JAVA_EMAIL);
        break;
      case LETH_WWW:
        return (JAVA_WWW);
        break;
      case LETH_FTP:
        return (JAVA_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
