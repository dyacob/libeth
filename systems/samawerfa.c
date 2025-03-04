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
#include "samawerfa.map"
#include "systems.h"
#include "base.h"


FCHAR
SamawerfaToUnicode ( mylflags )
  LibEthFlags* mylflags;
{

FCHAR fch = NIL;
unsigned char base, form; 
char formNumber;


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = SamawerfaHashTable[base-0x20]) <= SAFEANSI
                       /* rogues, a lone diacritc or safe ASCII character    */
     )
    {
      if ( mylflags->csIn == samwp )
        {
          if ( base == 0x80 )
            fch = NAE + SADS;
          else if ( base == 0x9e )
            fch = ZHAE;
          else if ( base == 0x8e )
            fch = KHAE;
          else 
            return ( (FCHAR) base );
        }
      else
        return ( (FCHAR) base );
    }
 if ( mylflags->csIn == samwp )
   {
     if ( base == 0xbf )
       fch = CHAE + KAIB;
     else if ( base == 0xfe || base == 0xff ) 
       return ( (FCHAR) base );
   }

  if ( fch <= WORDSPACE )      /* get diacritic mark */
    {
  READNEXT:
      if ( (SamawerfaHashTable[(form = getToken())-0x20]) == DIACRITIC
           || form == SAM_WS || form == '-' )
        {
          formNumber = fch%8;  /* what is my vowel ? */
          fch -= formNumber;   /* normalize to ge'ez form to simplify following switch */   
          switch (form)
            { 
              case SAM_ullu:
              case SAM_ulld:
              case SAM_ul  :
              case SAM_ur  :
              case SAM_urr : if (fch == WAE)
                               fch += SADS;
                             else
                               fch += KAIB;  break;

              case SAM_irr:
              case SAM_ir :
              case SAM_im :
              case SAM_il :
              case SAM_ill:  fch += SALS;  break;

              case SAM_Err:
              case SAM_Er :
              case SAM_Em :
              case SAM_El :
              case SAM_Ell:  fch += HAMS;  break;


              case SAM_B  :  if ( fch == QAE )
                               {
                                 fch = QXAE + formNumber;
                                 goto READNEXT;
                               }
                             else if ( fch == GAE )
                               {
                                 fch = GGAE + formNumber;
                                 goto READNEXT;
                               }
                             else if ( (fch+formNumber) == WORDSPACE )
                                fch = COMMA;
                             else
                               {
                                 fch += formNumber;
                                 ungetToken (form);
                               }
                             break;

              case SAM_Wel:
              case SAM_Wer:  if (fch == LAE) 
                               fch += SABI;
                             else
                               fch += DIQALA_GIZ;  break;

              case SAM_Wi :  fch += DIQALA_SALS;  break;

              case SAM_Wal:
              case SAM_Wam:
              case SAM_War:
                if ( SamawerfaFidel[fch-UNIFIDEL+DIQALA].set == SETD )
                  fch += DIQALA_RABI;  /* has 12 forms     */
                else
                  fch +=      DIQALA;  /* has only 8 forms */
                break;

              case SAM_WEl:
              case SAM_WEr:  fch += DIQALA_HAMS;  break;

              case SAM_W  :  fch += DIQALA_SADS;  break;

              case '-'    :  if ( (fch+formNumber) == WORDSPACE )
                               fch = PREFACECOLON; 
                             else
                               {
                                 fch += formNumber;
                                 ungetToken (form);
                               }
                             break;


              case SAM_WS :  if ( (fch+formNumber) == WORDSPACE )
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
                if ( SamawerfaFidel[fch-UNIFIDEL].set != NOCH )  
                     /*  I don't have a diacritic mark 
                      *  in the stream, but I do in the table...
                      *  this shouldn't happen with the hash buckets,
                      *  but if it does echo a warning 
                      */
                   {
                     fprintf (stderr, "ID Failure for Samawerfa for char 0x%02x", fch);
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
UnicodeToSamawerfa98 ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, SamawerfaFidel, "Samawerfa" ) );

}



unsigned char*
UnicodeToSamawerfaWP ( fch )
  FCHAR fch;
{

unsigned char* returnCh = NULL;
unsigned int form;


/* Detect Errors Here */

  if ( (returnCh = UnicodeToSamawerfa98 ( fch )) )
    {
      if ( fch == NAE + SADS )
        returnCh[0] = '\x80';
      else if ( fch == CHAE + KAIB )
        returnCh[0] = '\xbf';
      else if ( (form = (unsigned int)(fch - ZHAE)) <= HAMS && form != RABI )
        returnCh[0] = '\x9e';
      else if ( ((form = (unsigned int)(fch - KHAE)) <= HAMS && form != RABI)
                || form == DIQALA_GIZ
                || form == DIQALA_SALS
                || form == DIQALA_SADS
              )
        returnCh[0] = '\x8e';
    }   /* "(unsigned int)(fch - ZHAE)" is, hopefully,  "abs(fch -ZHAE)" */
  return ( returnCh );

}


int
Samawerfa_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, SamawerfaFidel ) );

}


int
Samawerfa_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = strdup ( SamawerfaTTFNames[ fontFace ] );

  if ( setid )
    return ( NIL );
  else
    return ( 1 ); 

}


int
Samawerfa_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{


  *RTFPrefix = strdup ( SamawerfaRTFPrefix[0] );

  if ( setid )
    return ( NIL );
  else
    return ( 1 );  

}


unsigned char
Samawerfa_isGoodANSI ( fch )
  FCHAR fch;
{

  return ( Base_isGoodANSI ( fch, SamawerfaHashTable ) );

}


char*
Samawerfa_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (SAMAWERFA_EMAIL);
        break;
      case LETH_WWW:
        return (SAMAWERFA_WWW);
        break;
      case LETH_FTP:
        return (SAMAWERFA_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
