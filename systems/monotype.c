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
#include "monotype.map"
#include "systems.h"
#include "base.h"


FCHAR
MonoType1ToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base; 


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = MonoType1HashTable[base-0x20]) == NOCH         /* ...rouges */
     )
    {
      return ( (FCHAR) base );
    }


  return (fch);

}



FCHAR
MonoType2ToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base; 


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = MonoType2HashTable[base-0x20]) == NOCH         /* ...rouges */
     )
    {
      return ( (FCHAR) base );
    }


  return (fch);

}



FCHAR
MonoType3ToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base; 


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = MonoType3HashTable[base-0x20]) == NOCH         /* ...rouges */
     )
    {
      return ( (FCHAR) base );
    }


  return (fch);

}



FCHAR
MonoTypeNToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base; 


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = MonoTypeNHashTable[base-0x20]) == NOCH         /* ...rouges */
     )
    {
      return ( (FCHAR) base );
    }


  return (fch);

}



FCHAR
MonoTypeAltToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base, form; 
char formNumber;


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = MonoTypeAltHashTable[base-0x20]) == 0    /* ...rouges       */
       || fch <= SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }

  if ( fch <= WORDSPACE )      /* get diacritic mark */
    {
      if ( (MonoTypeAltHashTable[(form = getToken())-0x20]) == DIACRITIC
           || form == MTA_WS )
        {
          formNumber = fch%8;  /* what is my vowel ? */
          fch -= formNumber;   /* normalize to ge'ez form to simplify following switch */   
          switch (form)
            {
              case MTA_ul :
              case MTA_um :
              case MTA_ur :
              case MTA_ulc:
              case MTA_urc:  if (fch == WAE)
                               fch += SADS;
                             else
                               fch += KAIB;  break;

              case MTA_ill:
              case MTA_il :
              case MTA_ir :
              case MTA_irr:  fch += SALS;  break;

              case MTA_El :
              case MTA_Em :
              case MTA_Er :  fch += HAMS;  break;

              case MTA_yor:
              case MTA_yol:  fch += SABI;  break;

              case MTA_Welld:
              case MTA_Wel:
              case MTA_Wer:  if (fch == LAE) 
                               fch += SABI;
                             else
                               fch += DIQALA_GIZ;  break;

              case MTA_Wi :  fch += DIQALA_SALS;  break;

              case MTA_Wal:
              case MTA_War:
                if ( MonoTypeAltFidel[fch-UNIFIDEL+DIQALA].set == SETD )
                  fch += DIQALA_RABI;  /* has 12 forms     */
                else
                  fch +=      DIQALA;  /* has only 8 forms */
                break;

              case MTA_W  :  fch += DIQALA_SADS;  break;

              case '-'    :  if ( (fch+formNumber) == WORDSPACE )
                               fch = PREFACECOLON; 
                             else
                                {
                                  fch += formNumber;
                                  ungetToken (form);
                                }
                             break;


              case MTA_WS :  if ( (fch+formNumber) == WORDSPACE )
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
                if ( MonoTypeAltFidel[fch-UNIFIDEL].set != NOCH )  
                     /*  I don't have a diacritic mark 
                      *  in the stream, but I do in the table...
                      *  this shouldn't happen with the hash buckets,
                      *  but if it does echo a warning 
                      */
                   {
                     fprintf (stderr, "ID Failure for MonoTypeAlt for char 0x%02x", fch);
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
UnicodeToMonoType ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, MonoTypeFidel, "MonoType" ) );

}



unsigned char*
UnicodeToMonoTypeAlt ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, MonoTypeAltFidel, "MonoTypeAlt" ) );

}


int
MonoType_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, MonoTypeFidel ) );

}


int
MonoType_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = strdup ( MonoTypeTTFNames[setid+fontFace] );

  if ( setid == NUM_MONOTYPE-1 )
    return (NIL);
  else
    return ( setid+1 );  

}


int
MonoTypeAlt_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, MonoTypeAltFidel ) );

}


int
MonoTypeAlt_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = strdup ( MonoTypeTTFNames[setid+6] );

  if ( setid )
    return ( NIL );
  else
    return ( setid+1 );  

}


int
MonoType_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{
int prefix = (fontFace == 7) ? 1 : 0;


  *RTFPrefix = strdup ( MonoTypeRTFPrefix[prefix] );

  if ( setid == NUM_MONOTYPE-1 )
    return ( NIL );
  else if ( setid == 2 || (setid == 0 && fontFace == 6) )
    return ( NUM_MONOTYPE-1 );  
  else
    return ( setid+1 );  

}


char*
MonoType_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (MONOTYPE_EMAIL);
        break;
      case LETH_WWW:
        return (MONOTYPE_WWW);
        break;
      case LETH_FTP:
        return (MONOTYPE_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
