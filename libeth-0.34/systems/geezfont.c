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
#include "geezfont.map"
#include "systems.h"
#include "base.h"


FCHAR
GeezFontToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base, form; 
char formNumber;


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = GeezFontHashTable[base-0x20]) == 0       /* ...rouges       */
       || fch <= SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }
  if ( fch <= WORDSPACE )     /* get diacritic mark */
    {
  READNEXT:
      if ( (GeezFontHashTable[(form = getToken())-0x20]) == DIACRITIC )
        {
          formNumber = fch%8; /* what is my vowel ? */
          fch -= formNumber;  /* normalize to ge'ez form to simplify following switch */   
          switch (form)
            {
              case GF_ul  :
              case GF_ur  :
              case GF_uru :  if (fch == WAE)
                               fch += SADS;
                             else
                               fch += KAIB;  break;

              case GF_il  :
              case GF_ir  :  if (fch == WAE)        /* "u" in "wu" is lower */
                               fch = WAE + KAIB;
                             else
                               fch += SALS;  break;

              case GF_El  :
              case GF_Er  :  fch += HAMS;  break;

              case GF_Wel :
              case GF_Wer :  if (fch == LAE) 
                               fch += SABI;
                             else if (fch == CHAE || fch == YAE)
                               fch += HAMS;
                             else
                               fch += DIQALA_GIZ;  break;

              case GF_Wil :
              case GF_Wir :  fch += DIQALA_SALS; break;

              case GF_Wal :
              case GF_War :
                   if ( GeezFontFidel[fch-UNIFIDEL+DIQALA].set == SETD )
                     fch += DIQALA_RABI;  /* has 12 forms     */
                   else
                     fch += DIQALA;       /* has only 8 forms */
                   break;

              case GF_WEl :
              case GF_WEr :  fch += DIQALA_HAMS;  break;

              case GF_W   :  fch += DIQALA_SADS;  break;

              case GF_B   :  if ( (fch+formNumber) == WORDSPACE )
                                fch = COMMA;
                             else if ( fch == SAE )
                               {
                                 fch = SHAE + formNumber;
                                 if ( formNumber == RABI )
                                   {
                                     if ( ((form = getToken()) == GF_War)  ||  (form == GF_Wal) )
                                       fch = SHAE + DIQALA;
                                     else
                                       ungetToken ( form );
                                   }
                                 else
                                   goto READNEXT;
                               }
                             else if ( fch == BAE )
                               {
                                 fch = VAE + formNumber;
                                 if ( formNumber != RABI && formNumber != SABI )
                                   goto READNEXT;
                                 if ( formNumber == RABI )
                                   {
                                     if ( ((form = getToken()) == GF_War)  ||  (form == GF_Wal) )
                                       fch = VAE + DIQALA;
                                     else
                                       ungetToken ( form );
                                   }
                               }
                             else if ( fch == QAE )
                               {
                                 fch = QXAE + formNumber; 
                                 if ( formNumber != RABI )
                                   goto READNEXT;
                               }
                             else if ( fch == QAE + DIQALA_GIZ )
                               {
                                 fch = QXAE + DIQALA_RABI; 
                               }
                             else if ( fch == GAE )
                               {
                                 fch = GGAE + formNumber;
                                 if ( formNumber != RABI && formNumber != SABI )
                                   goto READNEXT;
                               }
                             else if ( fch == RAE || fch == AE )
                               {
                                 fch += DIQALA;
                               }
                             else
                               {
                                 fch += formNumber;
                                 ungetToken (form);
                               }
                             break;

              case GF_P   :  if ( fch == DAE ) 
                               fch = DHAE;
                             else  /* we don't know what to do with it */
                               {
                                 ungetToken ( form );
                                 break;
                               }

                             if ( formNumber == SABI )
                               {
                                 if ( ((form = getToken()) == GF_B) )
                                   fch = JAE;
                                 else
                                     ungetToken ( form );
                               }

                             fch += formNumber;

                             if ( formNumber == GIZ || formNumber == RABI )
                               goto READNEXT;

                             break;

              default:  
                ungetToken (form);
                fch += formNumber;   /* no diacritic mark, restore value */   
                if ( GeezFontFidel[fch-UNIFIDEL].vowel != NOCH )  
                     /*  I don't have a diacritic mark 
                      *  in the stream, but I do in the table...
                      *  this shouldn't happen with the hash buckets,
                      *  but if it does echo a warning 
                      */
                  {
                    fprintf (stderr, "ID Failure for GeezFont for char 0x%02x ", fch);
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
UnicodeToGeezFont ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, GeezFontFidel, "GeezFont" ) );

}


int
GeezFont_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, GeezFontFidel ) );

}


int
GeezFont_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  // *setName = (unsigned char *) malloc ( (strlen(GeezFontTTFNames[fontFace]) + 1) * sizeof(unsigned char) );
  // strcpy ( *setName, GeezFontTTFNames[fontFace] );

  *setName = strdup ( GeezFontTTFNames[fontFace] );

  return (NIL);

}


int
GeezFont_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{

  *RTFPrefix = strdup ( GeezFontRTFPrefix[0] );

  return (NIL);

}


unsigned char
GeezFont_isGoodANSI ( fch )
  FCHAR fch;
{

  return ( Base_isGoodANSI (fch, GeezFontHashTable) );

}


char*
GeezFont_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (GEEZFONT_EMAIL);
        break;
      case LETH_WWW:
        return (GEEZFONT_WWW);
        break;
      case LETH_FTP:
        return (GEEZFONT_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
