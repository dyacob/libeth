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
#include "mainz.map"
#include "systems.h"

#ifdef USEME
FCHAR
MainzToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base, form; 
char formNumber;


  base = getToken();           /* read first char                            */
       
  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = (int) MainzHashTable[base-0x20]) == 0          /* ...rouges */
     )
    {
      return ( (FCHAR) base );
    }

  switch (fch) 
    {
      case DIACRITIC :              /* convert diacritic back into vowel */
        switch (base)
          {
            case MAINZGIZ  :  fch = AE +  GIZ;  break;
            case MAINZKAIB :  fch = AE + KAIB;  break;
            case MAINZSALS :  fch = AE + SALS;  break;
            case MAINZRABI :  fch = AE + RABI;  break;
            case MAINZHAMS :  fch = AE + HAMS;  break;
            case MAINZSADS :  fch = AE + SADS;  break;
            case MAINZSABI :  fch = AE + SABI;  break;
            default   :  break;                   /* shouldn't happen... */
          }
        break;

             
      default:
        if ( fch <= WORDSPACE )     /* get diacritic mark */
          {
           if ( (MainzHashTable[(form = getToken())-0x20]) == DIACRITIC )
             {
               formNumber = fch%8;  /* what is my vowel ? */
               fch -= formNumber;   /* normalize to ge'ez form to simplify following switch */   
               switch (form)
                 {
                   case MAINZGIZ :  break;

                   case MAINZKAIB:  if (fch == WAE)
                                    fch += SADS;
                                  else
                                    fch += KAIB;  break;

                   case MAINZSALS  :  fch += SALS;  break;

                   case MAINZRABI  :  fch += RABI;  break;

                   case MAINZHAMS  :  fch += HAMS;  break;

                   case MAINZSADS  :  fch += SADS;  break;

                   case MAINZSABI  :  fch += SABI;  break;

                   case MAINZDIQALA: 
                     form = getToken();
                     switch (form)
                       {
                         case MAINZGIZ :  fch += DIQALA_GIZ;    break;
                         case MAINZSALS:  fch += DIQALA_SALS;   break;
                         default       :
                         case MAINZRABI:  if ( MainzFidel[fch-UNIFIDEL+7].set == SETD )
                                            fch += DIQALA_RABI;
                                          else 
                                            fch += DIQALA;
                                          break;
                         case MAINZHAMS:  fch += DIQALA_HAMS;   break;
                         case MAINSADS :  fch += DIQALA_SADS; 
                                          ungetToken (form);
                                          break;
                       }
                     break;
          
                   default:  
                     ungetToken (form);
                     fch += formNumber;   /* no diacritic mark, restore value */   
                     if ( MainzFidel[fch-UNIFIDEL].vowel != NOCH ) 
                          /*  I don't have a diacritic mark 
                           *  in the stream, but I do in the table.
                           *  this shouldn't happen with the hash buckets,
                           *  but if it does echo a warning 
                           */
                       {
                         fprintf (stderr, "ID Failure for ED for char 0x%02x with form 0x%02x (%c)\n", fch, form, form);
                       }
                     break;
                 }
             }
           else
             ungetToken (form);
         }
           break;
    }  /* end switch */


  return (fch);

}
#endif



unsigned char*
UnicodeToMainz ( fch, mylflags )
  FCHAR fch;
  LibEthFlags* mylflags;
{

FCHAR uch = fch;
unsigned char* returnCh = NULL;
char form;

/* Detect Errors Here */

  if ( UNIFIDEL <= fch && fch <= EXTLAST )
    fch -= UNIFIDEL;
  else if ( PRIVATE_USE_BEGIN <= fch && fch <= PRIVATE_USE_END )
    fch  = (UNITOTAL - 1) + (fch - PRIVATE_USE_END);
  else if ( fch > 0xff )  /* bail, we shouldn't be here */
    {
      returnCh = (unsigned char *) malloc ( 3 * sizeof(unsigned char) );
      returnCh[0] = (fch >> 8);
      returnCh[1] = (fch & 255);
      returnCh[2] = '\0';
      return ( returnCh );
    }
  else  /* no more than 8 bits */
    {
      returnCh = (unsigned char *) malloc ( 2 * sizeof(unsigned char) );
      returnCh[0] = (unsigned char) fch;
      returnCh[1] = '\0';
      return ( returnCh );
    }



/* We are clear of bad characters, return then requested Mainz mapping */



  form = uch % 8;

  if ( HAE <= uch && uch < MYA )                   /*  Basic Range Syllables  */
    {
      if ( form < DIQALA )
        {
          returnCh = (unsigned char *) malloc ( 3 * sizeof(unsigned char) );
          sprintf ( returnCh, "%s%c",
                    MainzFidelHash[(fch/8)],
                    MainzVowelHash[(int)form] );
        }
      else
        {
          returnCh = (unsigned char *) malloc ( 4 * sizeof(unsigned char) );
          sprintf ( returnCh, "%s%c%c",
                    MainzFidelHash[(fch/8)],
                    MainzVowelHash[DIQALA],
                    MainzVowelHash[RABI] );
        }
    }
  else 
  /* We have reached the end of Mainz definitions or we now overlap with SERA */
    returnCh = _UnicodeToSERA ( uch, mylflags );




  return ( returnCh );

}


char*
Mainz_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (MAINZ_EMAIL);
        break;
      case LETH_WWW:
        return (MAINZ_WWW);
        break;
      case LETH_FTP:
        return (MAINZ_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
