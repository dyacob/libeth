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
#include "powergez.map"
#include "systems.h"
#include "base.h"


FCHAR
PowerGeezToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base, form; 
char formNumber;


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = PowerGeezHashTable[base-0x20]) == 0      /* ...rouges       */
       || fch <= SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }

  if ( fch <= WORDSPACE )      /* get diacritic mark */
    {
      if ( (PowerGeezHashTable[(form = getToken())-0x20]) == DIACRITIC
           || form == PWRG_WS )
        {
          formNumber = fch%8;  /* what is my vowel ? */
          fch -= formNumber;   /* normalize to ge'ez form to simplify following switch */   
          switch (form)
            {
              case PWRG_u  :  if (fch == WAE)
                               fch += SADS;
                             else
                               fch += KAIB;  break;

              case PWRG_il :
              case PWRG_ir :  fch += SALS;  break;

              case PWRG_El :
              case PWRG_Er :  fch += HAMS;  break;

              case PWRG_We :  if (fch == LAE) 
                               fch += SABI;
                             else
                               fch += DIQALA_GIZ;  break;

              case PWRG_Wi :  fch += DIQALA_SALS;  break;

              case PWRG_Wal:
              case PWRG_War:
                if ( PowerGeezFidel[fch-UNIFIDEL+DIQALA].set == SETD )
                  fch += DIQALA_RABI;  /* has 12 forms     */
                else
                  fch +=      DIQALA;  /* has only 8 forms */
                break;

              case PWRG_WE :  fch += DIQALA_HAMS;  break;

              case PWRG_W  :  fch += DIQALA_SADS;  break;

              case '-'     :  if ( (fch+formNumber) == WORDSPACE )
                                fch = PREFACECOLON; 
                              else
                                 {
                                   fch += formNumber;
                                   ungetToken (form);
                                 }
                              break;


              case PWRG_WS :  if ( (fch+formNumber) == WORDSPACE )
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
                if ( PowerGeezFidel[fch-UNIFIDEL].set != NOCH )  
                     /*  I don't have a diacritic mark 
                      *  in the stream, but I do in the table...
                      *  this shouldn't happen with the hash buckets,
                      *  but if it does echo a warning 
                      */
                   {
                     fprintf (stderr, "ID Failure for PowerGeez for char 0x%02x", fch);
                   }
                 break;
             }
         }
       else
         ungetToken (form);
     }


  return (fch);

}



FCHAR
PowerGeezExtrasToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base, form; 


  fch  = getToken();           /* read first char                            */

  if ( isspace(fch)            /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
     )
    {
      return ( (FCHAR) fch );
    }



  switch ( fch )
    {
      case 0x2b:                                          /* loan diacritics */
      case 0x2c: return ( (FCHAR) fch );
                 break;

      case 0x2d: return ( (FCHAR) COLON );
                 break;

      case 0x2e: return ( (FCHAR) PREFACECOLON );
                 break;

      case 0x40:                                   /* Qe, get diacritic mark */

        fch = QXAE;
        switch ( (form = getToken()) )
          {
            case PWRG_iQ :  fch += SALS;  break;

            case PWRG_EQ :  fch += HAMS;  break;

            case PWRG_We :  fch += DIQALA_GIZ;  break;

            case PWRG_Wi :  fch += DIQALA_SALS;  break;

            case PWRG_Wal:
            case PWRG_War:  fch += DIQALA_RABI;  break;

            case PWRG_WE :  fch += DIQALA_HAMS;  break;

            case PWRG_W  :  fch += DIQALA_SADS;  break;

            default      :  break;
          }

      case 0x41:  fch = QXAE + SALS;  break;
      case 0x42:  fch = QXAE + RABI;  break;
      case 0x43:  fch = QXAE + SADS;  break;
      case 0x44:  fch = QXAE + SABI;  break;

      default  :  if ( '0' <= fch && fch <= '9' )  
                    fch += ONE - '0';
                  else if ( '!' <= fch && fch <= '*' )  
                    fch += TEN - '0';

                  return ( (FCHAR) fch );
                  break;
    }


  return (fch);

}



unsigned char*
UnicodeToPowerGeez ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, PowerGeezFidel, "PowerGeez") );

}


int
PowerGeez_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, PowerGeezFidel ) );

}


int
PowerGeez_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{
  if (setid == 1)
    fontFace = NUM_POWERGEEZ - 2;

  *setName = strdup ( PowerGeezTTFNames[setid + fontFace] );

  if ( setid )
    return ( NIL );
  else
    return ( 1 ); 

}


int
PowerGeez_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{


  *RTFPrefix = strdup ( PowerGeezRTFPrefix[0] );

  if ( setid )
    return ( NIL );
  else
    return ( 1 );  

}


unsigned char
PowerGeez_isGoodANSI ( fch )
  FCHAR fch;
{

  return ( Base_isGoodANSI ( fch, PowerGeezHashTable  ) );

}


char*
PowerGeez_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (POWERGEEZ_EMAIL);
        break;
      case LETH_WWW:
        return (POWERGEEZ_WWW);
        break;
      case LETH_FTP:
        return (POWERGEEZ_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
