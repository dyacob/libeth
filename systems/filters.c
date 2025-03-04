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
#include "libeth.h"
#include "etctype.h"
#include "etstring.h"
#include "etstdio.h"
#include "sysinfo.h"
#include "filters.h"
#include <stdlib.h>

/* because some "isdigit"s choke on int values > 255 */
#define myIsdigit(fch)	('0' <= fch && fch <= '9')

FCHAR*
ayn2zero (fstring)
  FCHAR* fstring;
{
int i = -1;


  while ( fstring[++i] )
    {
      if ( fstring[i] == OAE  
           &&  ( (i && (myIsdigit(fstring[i-1]) || fstring[i-1] == ',' || fstring[i-1] == '.'))
                 || (fstring[i+1] != '\0' && myIsdigit(fstring[i+1])) 
                )
         )
        fstring[i] = '0';
    }


  return (fstring);

}



FCHAR*
jis_remap_space (fstring)
  FCHAR* fstring;
{
int i = -1;


  while ( fstring[++i] )
    {
      if ( fstring[i] == ' ' && (i && isethiopic(fstring[i-1])) )
        /* don't check fstring[i+1] for now */
        fstring[i] = SPACE;
    }


  return (fstring);

}


int
image_sputs (uniString, outString, iPath, mylflags)
  FCHAR* uniString;
  char** outString;
  char* iPath;
  LibEthFlags* mylflags;
{

register int i=-1, j=0, count=0;
int uniAddr;
unsigned char* fidelName;
char* tempString = (char*) malloc ( 20 * (fidel_strlen (uniString) + 1) * sizeof (char));


  while ( (uniAddr = uniString[++i]) )
    if ( uniString[i] < ANSI )
      tempString[j++] = uniString[i];
    else if ( isethiopic (uniAddr) )
        {
          count++;
          mylflags->csOut = ( uniAddr > FYA ) ? muletex : sera ;

          fidelName = fidel_sputc ( uniAddr, mylflags );

          if ( fidelName[0] == '`' )
            {
              fidelName[0] = fidelName[1];
              fidelName[1] = '2';
            }
          else if ( uniAddr > FYA )
            {
              fidelName[strlen(fidelName)-1] = '\0';  /* kill the 'G' */
            }

/*        Our images use Tigrigna names, so we need to switch names back
 *        if we used an Amharic file.
 */
          if ( !isfdigit(uniAddr) && mylflags->out->l == amh )
            {
              if ( fidelName[0] == 'a' && fidelName[1] != '2' )
                fidelName[0] = 'e';
              else if ( fidelName[0] == 'A' )
                fidelName[0] = 'a';
            }


          sprintf ( &tempString[j], "<img src=%s/%s>", iPath, fidelName );
          j = strlen ( tempString );
          free (fidelName);
        }
      else
        tempString[j++] = uniString[i];


  *outString = (char *) malloc ( (strlen ( tempString ) + 1) * sizeof (char) );
  strcpy ( *outString, tempString );
  free ( (char *)tempString );

  mylflags->csOut = image;


  return ( count );
}
