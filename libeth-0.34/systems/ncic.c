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
#include "ncic.map"
#include "systems.h"
#include "base.h"


static int* HashTable;


FCHAR
NCICToUnicode ( void )
{

  HashTable = NCICHashTable;
  return ( ToUnicode() );

}


FCHAR
NCIC_ETToUnicode ( void )
{

  HashTable = NCICEjjiTsihufHashTable;
  return ( ToUnicode() );

}


FCHAR
ToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base, form; 
char formNumber;


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = HashTable[base-0x20]) == 0           /* ...rouges       */
       || fch <= SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }


  if ( fch <  WORDSPACE )      /* get diacritic mark */
    {
      if ( (HashTable[(form = getToken())-0x20]) == DIACRITIC )
        {
          formNumber = fch%8;  /* what is my vowel ? */
          fch -= formNumber;   /* normalize to ge'ez form to simplify following switch */   
          switch (form)
            {

              case NCC_u  :  if (fch == WAE)
                               fch += 5;
                             else
                               fch += 1;  break;

              case NCC_ir :
              case NCC_il :  fch += 2;  break;

              case NCC_Er :
              case NCC_El :  fch += 4;  break;

              case NCC_Wa :
                if ( NCICFidel[fch-UNIFIDEL+7].set == SETD )
                  fch += 11;  /* has 12 forms     */
                else
                  fch +=  7;  /* has only 8 forms */
                break;

/*
 *  There is not NCIC wordspace except maybe in Yegizu Bisrat  -check this
 *
 *            case '-'    :  if ( (fch+formNumber) == WORDSPACE) 
 *                             fch = PREFACECOLON; 
 *                           else
 *                              {
 *                                fch += formNumber;
 *                                ungetToken (form);
 *                              }
 *                           break;
 *
 *
 *            case NCC_WS:  if ( (fch+formNumber) == WORDSPACE )
 *                             fch = FULLSTOP;
 *                           else
 *                              {
 *                                fch += formNumber;
 *                                ungetToken (form);
 *                              }
 *                           break;
 */          
              default:  
                fch += formNumber;   /* no diacritic mark, restore value */   
                ungetToken (form);
                if ( NCICFidel[fch-UNIFIDEL].vowel != NOCH )
                     /*  I don't have a diacritic mark 
                      *  in the stream, but I do in the table.
                      *  this shouldn't happen with the hash buckets
                      *  but if it does echo a warning
                      */
                  {
                    fprintf (stderr, "ID Failure for NCI for char 0x%02x ", fch);
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
UnicodeToNCIC ( fch )
  FCHAR fch;
{


  FCHAR map;
  boolean special = CheckSpecialSets ( fch, NCICFidel, "NCIC" );


/* We are clear of bad characters, return then requested NCIC mapping */

  if ( special && NCICFidel[(map = MapFchar(fch))].set == SETW )
    {
      unsigned char* returnCh = (unsigned char *) malloc ( (strlen(NCICFidel[map].fidel)+strlen(NCICFidel[map].vowel)+1) * sizeof(unsigned char) );
      sprintf ( returnCh, "%s%s", NCICFidel[map].fidel, NCICFidel[map].vowel );
      return ( returnCh );
    }
  else
    return ( UnicodeToBase ( fch, NCICFidel, "NCIC" ) );



}


int
NCIC_get_setid ( fch )
  FCHAR fch;
{

  int setid = Base_get_setid ( fch, NCICFidel );

  return ( setid == SETX )
  ? SET1
  : setid
  ;

}


int
NCIC_ET_get_setid ( fch )
  FCHAR fch;
{

int setid;

  return ( (setid = NCIC_get_setid ( fch )) ? 0 : setid );

}


int
NCIC_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  if ( setid )
    fontFace = 2;  /*  Ejji Tsihuf */

  *setName = strdup ( NCICTTFNames[fontFace] );

  return ( NIL );

}


int
NCIC_ET_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  fontFace = 2;  /*  Ejji Tsihuf */

  *setName = strdup ( NCICTTFNames[fontFace] );

  return ( NIL );

}


int
NCIC_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{

  *RTFPrefix = strdup ( NCICTTFNames[0] );

  return ( NIL );

}


unsigned char
NCIC_isGoodANSI ( fch )
  FCHAR fch;
{

  if ( fch >= ANSI )
    return ( false );

  if ( NCICHashTable[fch - 0x20] == SAFEANSI )
    return ( (unsigned char)fch );

  if ( NCICHashTable[fch - 0x20] == NETEB )
    return ( 0x24 );

  return ( false );

}


boolean
NCIC_ET_isGoodANSI ( fch )
  FCHAR fch;
{

  if ( fch >= ANSI )
    return ( false );

  if ( NCICEjjiTsihufHashTable[fch - 0x20] )
    return ( (unsigned char)fch );

  if ( NCICHashTable[fch - 0x20] == NETEB )
    return ( 0x24 );

  return ( false );

}


char*
NCIC_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (NCIC_EMAIL);
        break;
      case LETH_WWW:
        return (NCIC_WWW);
        break;
      case LETH_FTP:
        return (NCIC_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
