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
#include "acis.map"
#include "systems.h"
#include "base.h"


FCHAR
ACISToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base, form; 
char formNumber;


  base = getToken();           /* read first char                            */
       
  if ( isspace(base)           /* don't wast time processing spaces...       */
       ||  base <= 0x20        /* or lesser chars that vendors don't use     */
       || (fch = ACISHashTable[base-0x20]) == 0           /* ...rouges       */
       || fch <= SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }

  if ( fch <= WORDSPACE )   /* get diacritic mark */
    {
  READNEXT:
      if ( (ACISHashTable[(form = getToken())-0x20]) == DIACRITIC 
           || form == ACIS_WS )
        {
          formNumber = fch%8;  /* what is my vowel ? */
          fch -= formNumber;   /* normalize to ge'ez form to simplify following switch */   
          switch (form)
            {
              case ACIS_ur :
              case ACIS_ul :  if (fch == WAE)
                               fch += 5;
                             else
                               fch += 1;  break;
    
              case ACIS_ir :
              case ACIS_il :  fch += 2;  break;

              case ACIS_Er :
              case ACIS_El :  fch += 4;  break;

              case ACIS_We :  if (fch == LAE) 
                               fch += 6;
                             else
                               fch += 8;  break;

              case ACIS_War:  
              case ACIS_Wal:  
                   if ( ACISFidel[fch-UNIFIDEL+7].set == SETD )
                     fch += 11;   /* has 12 forms */
                   else
                     fch +=  7;  /* has only 8 forms */
                   break;

              case ACIS_W  :  fch += 13;  break;

              case ACIS_Wi :  fch += 10;  break;
    
              case '-'     : if ( (fch+formNumber) == WORDSPACE )
                                fch = PREFACECOLON;
                             else
                               {
                                 fch += formNumber;
                                 ungetToken (form);
                               }
                             break;


              case ACIS_WS :  if ( (fch+formNumber) == WORDSPACE )
                                fch = FULLSTOP;
                             else
                               {
                                 fch += formNumber;
                                 ungetToken (form);
                               }
                             break;

              case ACIS_Br :
              case ACIS_Bm :
              case ACIS_Bl :  if ( (fch+formNumber) == WORDSPACE )
                                fch = COMMA;
                             else if ( fch == BAE )
                               {
                                 fch = VAE + formNumber;
                                 goto READNEXT;
                               }
                             else if ( fch == QAE )
                               {
                                 fch = QXAE + formNumber;
                                 goto READNEXT;
                               }
                             else if ( fch == GAE )
                               {
                                 fch = GGAE + formNumber;
                                 goto READNEXT;
                               }
                             else
                               {
                                 fch += formNumber;
                                 ungetToken (form);
                               }
                             break;

              default:  
                ungetToken (form);
                fch += formNumber;   /* no diacritic mark, restore value */
                if ( ACISFidel[fch-UNIFIDEL].vowel != NOCH ) 
                     /*  I don't have a diacritic mark 
                      *  in the stream, but I do in the table...
                      *  this shouldn't happen with the hash buckets,
                      *  but if it does echo a warning 
                      */
                  {
                    fprintf (stderr, "ID Failure for ACIS for char 0x%02x with form 0x%02x\n", fch, form);
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
UnicodeToACIS ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, ACISFidel, "ACIS" ) );

}




int
ACIS_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{

  *RTFPrefix = strdup ( ACISRTFPrefix[0] );

  return (NIL);

}


int
ACIS_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, ACISFidel ) );

}


unsigned char
ACIS_isGoodANSI ( fch )
  FCHAR fch;
{

  if ( fch >= ANSI )
    return ( false );

  if ( ACISHashTable[fch - 0x20] == SAFEANSI 
       || ACISHashTable[fch - 0x20] == NETEB  
       || ACISHashTable[fch - 0x20] == EQUESTIONMARK )
    return ( (unsigned char)fch );

  return ( false );

}


int
ACIS_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = strdup ( ACISTTFNames[0 + fontFace] );

  return (NIL);

}


char*
ACIS_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (ACIS_EMAIL);
        break;
      case LETH_WWW:
        return (ACIS_WWW);
        break;
      case LETH_FTP:
        return (ACIS_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
