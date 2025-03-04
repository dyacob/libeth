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
#include "absha.map"
#include "systems.h"
#include "base.h"

extern LibEthFlags* FidelFlags;  /* in lib-src/etstdlib.c */

FCHAR
GeezEditToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base, form; 
char formNumber;


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = GeezEditHashTable[base-0x20]) == 0       /* ...rouges       */
       || fch <= SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }

  if ( fch < WORDSPACE )       /* get diacritic mark */
    {
      if ( (GeezEditHashTable[(form = getToken())-0x20]) == DIACRITIC
            /* || form == GE_WS */ )
        {
          formNumber = fch%8;  /* what is my vowel ? */
          fch -= formNumber;   /* normalize to ge'ez form to simplify following switch */   
          switch (form)
            {

              case GE_urr:
              case GE_ull:
              case GE_ur :
              case GE_ul :  if (fch == WAE)
                              fch += 5;
                            else
                              fch += 1;  break;

              case GE_ir :
              case GE_il :  fch += 2;  break;

              case GE_Er :
              case GE_El :  fch += 4;  break;

              case GE_Wer:
              case GE_Wel:  if (fch == LAE) 
                              fch += 6;
                            else
                              fch += 8;  break;

              case GE_War :  
              case GE_Wal :  
              case GE_Walw:  
                    if ( GeezEditFidel[fch-UNIFIDEL+7].set == SETD )
			       fch += 11;   /* has 12 forms */

              case GE_Wir:  
              case GE_Wil:  fch += 10;  break;
          
              case GE_W  :  fch += 13;  break;

/**
 *  handle shortly
 *
 *            case GE_yo : 
 *            case GE_P  : 
 *            case GE_S  : 
 *            case GE_BW : 
 *            case GE_Bj : 
 *            case GE_B  : 
 *            case GE_WEx: 
 */
              default:  
                ungetToken (form);
                fch += formNumber;   /* no diacritic mark, restore value */   
                if ( GeezEditFidel[fch-UNIFIDEL].vowel != NOCH ) 
                     /*  I don't have a diacritic mark 
                      *  in the stream, but I do in the table...
                      *  this shouldn't happen with the hash buckets,
                      *  but if it does echo a warning 
                      */
                  {
                    fprintf (stderr, "ID Failure for Geezigna for char 0x%02x ", fch);
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
UnicodeToGeezEdit ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, GeezEditFidel, "GeezEdit" ) );

}


int
GeezEdit_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, GeezEditFidel ) );

}


int
GeezEdit_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  if ( fontFace == 0 && FidelFlags && FidelFlags->cstOut == rtf )
    /*  We pray that FidelFlags has been set.  This is not a great
     *  solution, the Content-Sub-Type should be passed to
     *  get_setName.  At the moment the conflict between HTML
     *  and RTF names is unique to GeezEdit.
     */
    {
      setName = malloc ( sizeof (unsigned char) * 22 );
      strcpy ( (char *)setName, "Ge\\'e8zEdit Amharic P");
    }
  else
    {
      *setName = (char *) malloc ( (strlen(AbshaTTFNames[fontFace]) + 1) * sizeof(char) );
      strcpy ( *setName, AbshaTTFNames[fontFace] );
    }

  return ( NIL );

}


int
GeezEdit_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{

  *RTFPrefix = strdup ( AbshaRTFPrefix[0] );

  return ( NIL );

}


unsigned char
GeezEdit_isGoodANSI ( fch )
  FCHAR fch;
{

  return ( Base_isGoodANSI ( fch, GeezEditHashTable) );

}


char*
Absha_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (ABSHA_EMAIL);
        break;
      case LETH_WWW:
        return (ABSHA_WWW);
        break;
      case LETH_FTP:
        return (ABSHA_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
