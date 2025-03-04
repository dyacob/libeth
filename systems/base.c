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
#include "base.h"
#include "systems.h"


FCHAR
MapFchar ( fch )
  FCHAR fch;
{


  if ( UNIFIDEL <= fch && fch <= EXTLAST )
    fch -= UNIFIDEL;
  else if ( PRIVATE_USE_BEGIN <= fch && fch <= PRIVATE_USE_END )
    fch  = (UNITOTAL - 1) + (fch - PRIVATE_USE_END);
  else
    fch  = 0xffff;  /* meaning out of range */

  return (fch);
}



boolean
CheckSpecialSets ( fch, Fidel, FidelName )
  FCHAR fch;
  LETCHAR * Fidel;
  char * FidelName;
{
  boolean test = false;

  FCHAR map = MapFchar ( fch );

  if ( map < 0xffff && ( Fidel[map].set == SETX || Fidel[map].set == SETW ) )
    {

#ifndef RUNSILENT 
      fprintf (stderr, "%s[U+%04X]: No Unicode mapping found, using substitution.\n", FidelName, fch);
#endif /* RUNSILENT */
      test = true;
    }

    return ( test );
}



FCHAR
ValidateChar ( fch, Fidel, returnCh )
  FCHAR fch;
  LETCHAR * Fidel;
  unsigned char ** returnCh;
{
/* Detect Errors Here */


  if ( UNIFIDEL <= fch && fch <= EXTLAST )
    fch -= UNIFIDEL;
  else if ( PRIVATE_USE_BEGIN <= fch && fch <= PRIVATE_USE_END )
    fch  = (UNITOTAL - 1) + (fch - PRIVATE_USE_END);
  else if ( fch > 0xff )  /* bail, we shouldn't be here */
    {
      *returnCh = (unsigned char *) malloc ( 3 * sizeof(unsigned char) );
      (*returnCh)[0] = (fch >> 8);
      (*returnCh)[1] = (fch & 255);
      (*returnCh)[2] = '\0';
      return ( 0xffff );
    }
  else  /* no more than 8 bits */
    {
      *returnCh = (unsigned char *) malloc ( 2 * sizeof(unsigned char) );
      (*returnCh)[0] = (unsigned char) fch;
      (*returnCh)[1] = '\0';
      return ( 0xffff );
    }


   return ( fch );

}



unsigned char*
UnicodeToBase ( fch, Fidel, FidelName )
  FCHAR fch;
  LETCHAR * Fidel;
  char * FidelName;
{

unsigned char* returnCh = NULL;


  fch = ValidateChar ( fch, Fidel, &returnCh );

  if ( fch == 0xffff )
    return ( returnCh );

  if ( Fidel[fch].fidel == NOCH )
    {
#ifndef RUNSILENT 
      fprintf (stderr, "%s[U+%04X]: No Unicode mapping found.\n", FidelName, uniFch);
#endif /* RUNSILENT */
      return ( returnCh );
    }



/* We are clear of bad characters, return then requested GeezFont mapping */

  if (Fidel[fch].vowel != NOCH)
    {
      returnCh = (unsigned char *) malloc ( (strlen(Fidel[fch].fidel)+strlen(Fidel[fch].vowel)+1) * sizeof(unsigned char) );
      sprintf ( returnCh, "%s%s", Fidel[fch].fidel, Fidel[fch].vowel );
    } 
  else 
    {
      returnCh = (unsigned char *) malloc ( (strlen(Fidel[fch].fidel) + 1) * sizeof(unsigned char) );
      strcpy ( returnCh, Fidel[fch].fidel );
    } 


  return ( returnCh );

}


int
Base_get_setid ( fch, Fidel )
  FCHAR fch;
  LETCHAR * Fidel;
{

  FCHAR map = MapFchar ( fch );

  if ( map == 0xffff || Fidel[map].fidel == NOCH )
    return ( NIL );

  return ( Fidel[map].set );

}


unsigned char
Base_isGoodANSI ( fch, Hash )
  FCHAR fch;
  int * Hash;
{
unsigned char check = 0x0;

  if ( fch >= ANSI )
    return ( false );

  check = Hash[fch - 0x20];
  if ( check == SAFEANSI || ( ' ' < check && check < ANSI ) )
    return ( (unsigned char)fch );

  return ( false );

}
