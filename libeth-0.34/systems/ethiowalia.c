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
#include "ethiowalia.map"
#include "systems.h"
#include "base.h"


FCHAR
EthioWaliaToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base, form; 
char formNumber;


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = EthioWaliaHashTable[base-0x20]) == 0     /* ...rouges       */
       || fch <= SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }

  if ( fch <= WORDSPACE )      /* get diacritic mark */
    {
      if ( (EthioWaliaHashTable[(form = getToken())-0x20]) == DIACRITIC )
        {
          formNumber = fch%8;  /* what is my vowel ? */
          fch -= formNumber;   /* normalize to ge'ez form to simplify following switch */   
          switch (form)
            {
              case ETWAL_Urd :
              case ETWAL_Uru :
              case ETWAL_Urux:
              case ETWAL_Ul  :  if (fch == WAE)
                                  fch += SADS;
                                else
                                  fch += KAIB;  break;

              case ETWAL_Il :
              case ETWAL_Ir :  fch += SALS;  break;

              case ETWAL_El :
              case ETWAL_Er :  fch += HAMS;  break;

              case ETWAL_Wel:
              case ETWAL_Wer:  if (fch == LAE) 
                                 fch += SABI;
                               else
                                 fch += DIQALA_GIZ;  break;

              case ETWAL_Wi :  fch += DIQALA_SALS;  break;

              case ETWAL_Wal:
              case ETWAL_War:
                if ( EthioWaliaFidel[fch-UNIFIDEL+DIQALA].set == SETD )
                  fch += DIQALA_RABI;  /* has 12 forms     */
                else
                  fch +=      DIQALA;  /* has only 8 forms */
                break;

              case ETWAL_WEl:
              case ETWAL_WEr:  fch += DIQALA_HAMS;  break;

              case ETWAL_Wr :
              case ETWAL_Wrd:
              case ETWAL_Wl :  fch += DIQALA_SADS;  break;

              default:  
                ungetToken (form);
                fch += formNumber;   /* no diacritic mark, restore value */   
                if ( EthioWaliaFidel[fch-UNIFIDEL].set != NOCH )  
                     /*  I don't have a diacritic mark 
                      *  in the stream, but I do in the table...
                      *  this shouldn't happen with the hash buckets,
                      *  but if it does echo a warning 
                      */
                   {
                     fprintf (stderr, "ID Failure for EthioWalia for char 0x%02x", fch);
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
UnicodeToEthioWalia ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, EthioWaliaFidel, "EthioWalia" ) );

}


int
EthioWalia_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, EthioWaliaFidel ) );

}


int
EthioWalia_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{
  if (setid == 1)
    fontFace = NUM_ETHIOWALIA - 2;

  *setName = strdup ( EthioWaliaTTFNames[setid + fontFace] );

  if ( setid )
    return ( NIL );
  else
    return ( 1 ); 

}


int
EthioWalia_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{


  *RTFPrefix = strdup ( EthioWaliaRTFPrefix[0] );

  if ( setid )
    return ( NIL );
  else
    return ( 1 );  

}


unsigned char
EthioWalia_isGoodANSI ( fch )
  FCHAR fch;
{

  return ( Base_isGoodANSI ( fch, EthioWaliaHashTable ) );

}


char*
EthioWalia_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (ETHIOWALIA_EMAIL);
        break;
      case LETH_WWW:
        return (ETHIOWALIA_WWW);
        break;
      case LETH_FTP:
        return (ETHIOWALIA_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
