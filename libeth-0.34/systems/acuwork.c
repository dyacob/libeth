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
#include "acuwork.map"
#include "systems.h"
#include "base.h"


FCHAR
AcuworkToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base, form; 
char formNumber;


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = ALXEtHashTable[base-0x20]) == 0          /* ...rouges       */
       || fch <= SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }

  if ( fch <= WORDSPACE )  /* get diacritic mark */
    {
      if ( (ALXEtHashTable[(form = getToken())-0x20]) == DIACRITIC 
           || form == ALX_WS )
        {
          formNumber = fch%8;  /* what is my vowel ? */
          fch -= formNumber;   /* normalize to ge'ez form to simplify following switch */   
          switch (form)
            {

              case ALX_ur  :
              case ALX_uru :
              case ALX_urc :
              case ALX_ulc :
              case ALX_ul  :  if (fch == WAE)
                                fch += 5;
                              else
                                fch += 1;  break;

              case ALX_ir :
              case ALX_im :
              case ALX_il :  fch += 2;  break;

              case ALX_Er :
              case ALX_Em :
              case ALX_El :  fch += 4;  break;

              case ALX_War:
              case ALX_Wam:
              case ALX_Wal:
                   if ( ALXEtFidel[fch-UNIFIDEL+7].set == SETD )
                     fch += 11;   /* has 12 forms */
                   else
                     fch +=  7;  /* has only 8 forms */
                   break;

              case ALX_WS :  if ( (fch+formNumber) == WORDSPACE )
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
                if ( ALXEtFidel[fch-UNIFIDEL].vowel != NOCH )  
                     /*  I don't have a diacritic mark 
                      *  in the stream, but I do in the table...
                      *  this shouldn't happen with the hash buckets,
                      *  but if it does echo a warning 
                      */
                  {
                    fprintf (stderr, "ID Failure for ALX for char 0x%02x ", fch);
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
UnicodeToAcuwork ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, ALXEtFidel, "Acuwork" ) );

}


int
Acuwork_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, ALXEtFidel ) );

}


int
Acuwork_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = strdup ( AcuWorkTTFNames[0] );

  return ( NIL );

}


int
Acuwork_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{

  *RTFPrefix = strdup ( AcuWorkTTFNames[0] );

  return ( NIL );

}


unsigned char
Acuwork_isGoodANSI ( fch )
  FCHAR fch;
{

  if ( fch >= ANSI )
    return ( false );

  if ( ALXEtHashTable[fch - 0x20] == SAFEANSI
       || ALXEtHashTable[fch - 0x20] == NETEB )
    return ( (unsigned char)fch );

  return ( false );

}


char*
Acuwork_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (ACUWORK_EMAIL);
        break;
      case LETH_WWW:
        return (ACUWORK_WWW);
        break;
      case LETH_FTP:
        return (ACUWORK_FTP);
        break;
      default:
        break;
    }

  return (NULL);
  
}
