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
#include "visgeez.map"
#include "systems.h"
#include "base.h"


FCHAR
VisualGeezToUnicode ( void )
{
FCHAR fch = NIL;
unsigned char base, form; 
char formNumber;


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = VisualGeezHashTable[base-0x20]) == 0     /* ...rouges       */
       || fch <= SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }

  if ( fch <= WORDSPACE )      /* get diacritic mark */
    {
      if ( VisualGeezHashTable[(form = getToken()) - 0x20] == DIACRITIC
           || form == VG_WS )
        {
          formNumber = fch%8;  /* what is my vowel ? */
          fch -= formNumber;   /* normalize to ge'ez form to simplify following switch */   
          switch (form)
            {
              case VG_ul :
              case VG_ur :  if (fch == WAE)
                               fch += SADS;
                             else
                               fch += KAIB;  break;

              case VG_il :
              case VG_ir :  fch += SALS;  break;

              case VG_El :
              case VG_Er :  fch += HAMS;  break;

              case VG_We :  if (fch == LAE) 
                               fch += SABI;
                             else
                               fch += DIQALA_GIZ;  break;

              case VG_Wi :  fch += DIQALA_SALS;  break;

              case VG_Wa :
                if ( VisualGeezFidel[fch-UNIFIDEL+DIQALA].set == SETD )
                  fch += DIQALA_RABI;  /* has 12 forms     */
                else
                  fch +=      DIQALA;  /* has only 8 forms */
                break;

              case VG_WEx :
              case VG_WEy : fch += DIQALA_HAMS;
                            if ( (base = getToken()) != VG_El
                                 || base != VG_Er)
                              ungetToken (base);
                            break;

              case VG_W  :  fch += DIQALA_SADS;  break;

              case '\x28':  if ( (fch+formNumber) == WORDSPACE )
                               fch = PREFACECOLON; 
                             else
                                {
                                  fch += formNumber;
                                  ungetToken (form);
                                }
                             break;


              case VG_WS :  if ( (fch+formNumber) == WORDSPACE )
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
                if ( VisualGeezFidel[fch-UNIFIDEL].set != NOCH )  
                     /*  I don't have a diacritic mark 
                      *  in the stream, but I do in the table...
                      *  this shouldn't happen with the hash buckets,
                      *  but if it does echo a warning 
                      */
                   {
                     fprintf (stderr, "ID Failure for VisualGeez for char 0x%02x", fch);
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
UnicodeToVisualGeez ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, VisualGeezFidel, "VisualGeez" ) );

}


int
VisualGeez_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid( fch, VisualGeezFidel ) );

}


int
VisualGeez_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{


  if ( setid )
    fontFace = NUM_VISUALGEEZ-1;

	 
  *setName = strdup ( VisualGeezTTFNames[fontFace] );

  /* the number font is the compliment to each, except self */

  if ( setid == NUM_VISUALGEEZ-1 )
    return ( NIL );
  else
    return ( NUM_VISUALGEEZ-1 );  

}


int
VisualGeez_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{

  *RTFPrefix = strdup ( VisualGeezRTFPrefix[0] );

  /* the number font is the compliment to each, except self */

  if ( setid == NUM_VISUALGEEZ-1 )
    return ( NIL );
  else
    return ( NUM_VISUALGEEZ-1 );  

}


unsigned char
VisualGeez_isGoodANSI ( fch )
  FCHAR fch;
{

  if ( fch >= ANSI )
    return ( false );

  if ( VisualGeezHashTable[fch - 0x20] == SAFEANSI
       ||  VisualGeezHashTable[fch - 0x20] == NETEB
       ||  VisualGeezHashTable[fch - 0x20] == EQUESTIONMARK )
    return ( (unsigned char)fch );

  return ( false );

}


FCHAR
VisualGeez2000ToUnicode ( void )
{
FCHAR fch = NIL;
unsigned char base, form; 
char formNumber;


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = VisualGeez2000HashTable[base-0x20]) == 0   /* ...rouges     */
       || fch <= SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }

  if ( fch <= WORDSPACE )      /* get diacritic mark */
    {
      if ( VisualGeez2000HashTable[(form = getToken()) - 0x20] == DIACRITIC
           || form == VG2K_WS )
        {
          formNumber = fch%8;  /* what is my vowel ? */
          fch -= formNumber;   /* normalize to ge'ez form to simplify following switch */   
          switch (form)
            {
              case VG2K_ul :
              case VG2K_ur :  if (fch == WAE)
                                fch += SADS;
                              else
                                fch += KAIB;  break;

              case VG2K_il :
              case VG2K_ir :
              case VG2K_ir2:  fch += SALS;  break;

              case VG2K_El :
              case VG2K_Er :  fch += HAMS;  break;

              case VG2K_We : if (fch == LAE) 
                                fch += SABI;
                              else
                                fch += DIQALA_GIZ;  break;

              case VG2K_Wi :  fch += DIQALA_SALS;  break;
              case VG2K_Wa :
                if ( VisualGeez2000Fidel[fch-UNIFIDEL+DIQALA].set == SETD )
                  fch += DIQALA_RABI;  /* has 12 forms     */
                else
                  fch +=      DIQALA;  /* has only 8 forms */
                break;

              /* case VG_WEx : fch += DIQALA_HAMS;
                            if ( (base = getToken()) != VG_El
                                 || base != VG_Er)
                              ungetToken (base);
                            break; */

              // case VG_W  :  fch += DIQALA_SADS;  break;

              case '\x28':  if ( (fch+formNumber) == WORDSPACE )
                               fch = PREFACECOLON; 
                             else
                                {
                                  fch += formNumber;
                                  ungetToken (form);
                                }
                             break;


              case VG2K_WS:   if ( (fch+formNumber) == WORDSPACE )
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
#ifndef RUN_QUIET
                if ( VisualGeez2000Fidel[fch-UNIFIDEL].set != NOCH )
                     /*  I don't have a diacritic mark 
                      *  in the stream, but I do in the table...
                      *  this shouldn't happen with the hash buckets,
                      *  but if it does echo a warning 
                      */
                   {
                     fprintf (stderr, "ID Failure for VisualGeez for char 0x%02x", fch);
                   }
#endif /* RUN_QUIET */
                 break;
             }
         }
       else
         ungetToken (form);
     }


  return (fch);

}



unsigned char*
UnicodeToVisualGeez2000 ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, VisualGeez2000Fidel, "VisualGeez2000" ) );

}



unsigned char
VisualGeez2000_isGoodANSI ( fch )
  FCHAR fch;
{

  if ( fch >= ANSI )
    return ( false );

  if ( VisualGeez2000HashTable[fch - 0x20] == SAFEANSI
       ||  VisualGeezHashTable[fch - 0x20] == NETEB
       ||  VisualGeezHashTable[fch - 0x20] == EQUESTIONMARK )
    return ( (unsigned char)fch );

  return ( false );

}


int
VisualGeez2000_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, VisualGeez2000Fidel ) );

}


char*
VisualGeez_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (VISUALGEEZ_EMAIL);
        break;
      case LETH_WWW:
        return (VISUALGEEZ_WWW);
        break;
      case LETH_FTP:
        return (VISUALGEEZ_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
