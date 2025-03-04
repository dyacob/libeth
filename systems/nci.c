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
#include "nci.map"
#include "systems.h"
#include "base.h"


FCHAR
NCIToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base, form; 
char formNumber;


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = NCIHashTable[base-0x20]) == 0            /* ...rouges       */
       || fch <= SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }

  if ( fch <= WORDSPACE )      /* get diacritic mark */
    {
      if ( (NCIHashTable[(form = getToken())-0x20]) == DIACRITIC
           || form == NCI_WS )
        {
          formNumber = fch%8;  /* what is my vowel ? */
          fch -= formNumber;   /* normalize to ge'ez form to simplify following switch */   
          switch (form)
            {
              case NCI_u  :  if (fch == WAE)
                               fch += SADS;
                             else
                               fch += KAIB;  break;

              case NCI_il :
              case NCI_ir :  fch += SALS;  break;

              case NCI_El :
              case NCI_Er :  fch += HAMS;  break;

              case NCI_We :  if (fch == LAE) 
                               fch += SABI;
                             else
                               fch += DIQALA_GIZ;  break;

              case NCI_Wi :  fch += DIQALA_SALS;  break;

              case NCI_Wal:
              case NCI_War:
                if ( NCIFidel[fch-UNIFIDEL+DIQALA].set == SETD )
                  fch += DIQALA_RABI;  /* has 12 forms     */
                else
                  fch +=      DIQALA;  /* has only 8 forms */
                break;

              case NCI_WE :  fch += DIQALA_HAMS;  break;

              case NCI_W  :  fch += DIQALA_SADS;  break;

              case '-'    :  if ( (fch+formNumber) == WORDSPACE )
                               fch = PREFACECOLON; 
                             else
                                {
                                  fch += formNumber;
                                  ungetToken (form);
                                }
                             break;


              case NCI_WS :  if ( (fch+formNumber) == WORDSPACE )
                                fch = FULLSTOP;
                              else
                                {
                                  fch += formNumber;
                                  ungetToken (form);
                                }
                              break;

              default:  
                ungetToken (form);
                fch += formNumber;   /* no diacritic mark, restore value */   
                if ( NCIFidel[fch-UNIFIDEL].set != NOCH )  
                     /*  I don't have a diacritic mark 
                      *  in the stream, but I do in the table...
                      *  this shouldn't happen with the hash buckets,
                      *  but if it does echo a warning 
                      */
                   {
                     fprintf (stderr, "ID Failure for NCI for char 0x%02x", fch);
                   }
                 break;
             }
         }
       else
         ungetToken (form);
     }


  return (fch);

}




unsigned char*
UnicodeToNCI ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, NCIFidel, "NCI" ) );

}


int
NCI_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, NCIFidel ) );

}


int
NCI_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = strdup ( NCITTFNames[setid+fontFace] );

  return ( NIL );

}


int
NCI_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{

  *RTFPrefix = strdup( NCIRTFPrefix[0] );

  return ( NIL );
  
}


unsigned char
NCI_isGoodANSI ( fch )
  FCHAR fch;
{

  if ( fch >= ANSI )
    return ( false );

  if ( NCIHashTable[fch - 0x20] == SAFEANSI
       ||  NCIHashTable[fch - 0x20] == NETEB
       ||  NCIHashTable[fch - 0x20] == EQUESTIONMARK )
    return ( (unsigned char)fch );

  return ( false );

}


char*
NCI_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (NCI_EMAIL);
        break;
      case LETH_WWW:
        return (NCI_WWW);
        break;
      case LETH_FTP:
        return (NCI_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
