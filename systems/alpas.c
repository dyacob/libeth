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
#include "alpas.map"
#include "systems.h"
#include "base.h"


FCHAR
AlpasToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base, form; 
char formNumber;


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = AlpasHashTable[base-0x20]) == 0          /* ...rouges       */
       || fch <= SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }

  if ( fch <= WORDSPACE )      /* get diacritic mark */
    {
      if ( (AlpasHashTable[(form = getToken())-0x20]) == DIACRITIC
           || form == ALP_WS )
        {
          formNumber = fch%8;  /* what is my vowel ? */
          fch -= formNumber;   /* normalize to ge'ez form to simplify following switch */   
          switch (form)
            {
              case ALP_ull:
              case ALP_ul :
              case ALP_ur :
              case ALP_urr:  if (fch == WAE)
                               fch += SADS;
                             else
                               fch += KAIB;  break;

              case ALP_il :
              case ALP_im :
              case ALP_ir :  fch += SALS;  break;

              case ALP_El :
              case ALP_Em :
              case ALP_Er :  fch += HAMS;  break;

              case ALP_We :  if (fch == LAE) 
                               fch += SABI;
                             else
                               fch += DIQALA_GIZ;  break;

              case ALP_Wi :  fch += DIQALA_SALS;  break;

              case ALP_Wal:
              case ALP_Wam:
              case ALP_War:
                if ( AlpasFidel[fch-UNIFIDEL+DIQALA].set == SETD )
                  fch += DIQALA_RABI;  /* has 12 forms     */
                else
                  fch +=      DIQALA;  /* has only 8 forms */
                break;

              case ALP_WE :  fch += DIQALA_HAMS;  break;

              case ALP_W  :  fch += DIQALA_SADS;  break;

              case '-'    :  if ( (fch+formNumber) == WORDSPACE) 
                               fch = PREFACECOLON; 
                             else
                                {
                                  fch += formNumber;
                                  ungetToken (form);
                                }
                             break;


              case ALP_WS :  if ( (fch+formNumber) == WORDSPACE )
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
                if ( AlpasFidel[fch-UNIFIDEL].set != NOCH )  
                     /*  I don't have a diacritic mark 
                      *  in the stream, but I do in the table...
                      *  this shouldn't happen with the hash buckets,
                      *  but if it does echo a warning 
                      */
                   {
                     fprintf (stderr, "ID Failure for Alpas for char 0x%02x", fch);
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
UnicodeToAlpas ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, AlpasFidel, "Alpas" ) );

}


int
Alpas_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, AlpasFidel ) );

}


int
Alpas_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = strdup ( AlpasTTFNames[0] );

  return ( NIL );

}


int
Alpas_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{

  *RTFPrefix = strdup ( AlpasRTFPrefix[0] );

  return ( NIL );

}


unsigned char
Alpas_isGoodANSI ( fch )
  FCHAR fch;
{

  if ( fch >= ANSI )
    return ( false );

  if ( AlpasHashTable[fch - 0x20] == SAFEANSI
       || AlpasHashTable[fch - 0x20] == NETEB  
       || AlpasHashTable[fch - 0x20] == EQUESTIONMARK )
    return ( (unsigned char)fch );

  return ( false );

}


char*
Alpas_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (ALPAS_EMAIL);
        break;
      case LETH_WWW:
        return (ALPAS_WWW);
        break;
      case LETH_FTP:
        return (ALPAS_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
