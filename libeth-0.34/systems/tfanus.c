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
#include "tfanus.map"
#include "systems.h"
#include "base.h"


FCHAR
TFanusToUnicode ( mylflags )
  LibEthFlags* mylflags;
{
FCHAR fch = NIL, fchNext = NIL;
unsigned char base, form; 
char formNumber;


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = TFanusHashTable[base-0x20]) == 0         /* ...rouges       */
       || fch <= SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      if ( mylflags->csIn == ethiosoft )
        {
          if ( base == 0x2a )
            return ( CAE + DIQALA );
          else if ( base == 0x2e )
            return ( NYAE + DIQALA );
          else if ( base == 0xbb )
            return ( NAE + DIQALA );
        }
      else if ( mylflags->csIn == gezbausi )
        {
          if ( base == 0x24 )
            return ( CHAE + SALS );
          if ( base == 0x25 )
            return ( CHAE + RABI );
          if ( base == 0x2b )
            return ( TSZAE + SABI );
          if ( base == 0x2c )
            return ( FAE + KAIB );
        }
      return ( (FCHAR) base );
    }
  if ( fch <= WORDSPACE )     /* get diacritic mark */
    {
      if ( (TFanusHashTable[(form = getToken())-0x20]) == DIACRITIC
           || form == TF_WS
           || (TFanusHashTable[(form - 0x20)] == TF_WNew && mylflags->csOut == tfanusnew) )
        {
          formNumber = fch%8; /* what is my vowel ? */
          fch -= formNumber;  /* normalize to ge'ez form to simplify following switch */   
          switch (form)
            {
              case TF_ud  :
              case TF_uu  :  if (fch == WAE)
                               fch += SADS;
                             else
                               fch += KAIB;  break;

              case TF_il  :
              case TF_ir  :  fch += SALS;  break;

              case TF_El  :
              case TF_Er  :  fch += HAMS;  break;

              case TF_We  :  if (fch == LAE) 
                               fch += SABI;
                             else if (fch == CHAE) 
                               fch += HAMS;
                             else
                               fch += DIQALA_GIZ;  break;

              case TF_Wal :
              case TF_War :
                   if ( TFanusFidel[fch-UNIFIDEL+DIQALA].set == SETD )
                     fch += DIQALA_RABI;  /* has 12 forms     */
                   else
                     fch += DIQALA;       /* has only 8 forms */
                   break;

              case TF_WiES:  if ( mylflags->csIn == ethiosoft )
                               fch += DIQALA_SALS;
                             else
                               ungetToken (form);
                             break;

              case TF_WEl :
              case TF_WEr :  fch += DIQALA_HAMS;  break;

              case TF_W   :  fch += DIQALA_SADS;  break;

              case TF_WNew:  if ( mylflags->csIn == tfanusnew )
                               fch += DIQALA_SADS;
                             else
                               ungetToken (form);
                             break;

              case '-'    :  if ( (fch+formNumber) == WORDSPACE )
                               fch = PREFACECOLON; 
                             else
                               {
                                  fch += formNumber;
                                  ungetToken (form);
                               }
                             break;

              case TF_WS:    if ( (fch+formNumber) == WORDSPACE )
                               fch = FULLSTOP;
                             else
                               {
                                  fch += formNumber;
                                  ungetToken (form);
                               }
                             break;
          
              case TF_QM  :  if ( (fch+formNumber) == WORDSPACE )
                               {
                                 fchNext = getToken();
                                 if ( fchNext == WORDSPACE )
                                   fch = PARAGRAPH;
                                 else
                                   {
                                     ungetToken (fchNext);
                                     ungetToken (form);
                                   }
                               }
                             else
                               {
                                 fch += formNumber;
                                 ungetToken (form);
                               }
                             break;

              case TF_B :    if ( fch == RAE )
                               fch = RAE + DIQALA;
                             else if ( fch == AE )
                               fch = AE + DIQALA;
                             else
                               {
                                 fch += formNumber;
                                 ungetToken (form);
                               }
                             break;

              default:  
                ungetToken (form);
                fch += formNumber;   /* no diacritic mark, restore value */   
                if ( TFanusFidel[fch-UNIFIDEL].vowel != NOCH )  
                     /*  I don't have a diacritic mark 
                      *  in the stream, but I do in the table...
                      *  this shouldn't happen with the hash buckets,
                      *  but if it does echo a warning 
                      */
                  {
                    fprintf (stderr, "ID Failure for TFanus for char 0x%02x ", fch);
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
UnicodeToTFanus ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, TFanusFidel, "TFanus" ) );

}



unsigned char*
UnicodeToEthioSoft ( fch )
  FCHAR fch;
{

unsigned char* returnCh = NULL;


  returnCh = UnicodeToTFanus ( fch );

  if ( fch == CAE + DIQALA )
     returnCh[0] = 0x2a, returnCh[1] = '\0' ;
  else if ( fch == NYAE + DIQALA )
     returnCh[0] = 0x23, returnCh[1] = '\0' ;
  else if ( fch == NAE + DIQALA )
     returnCh[0] = 0xbb, returnCh[1] = '\0' ;
 

  return ( returnCh );
}



int
TFanus_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, TFanusFidel ) );

}



int
EthioSoft_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = strdup ( EthioSoftTTFNames[fontFace] );

  return ( NIL );

}



int
GeezBausi_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = strdup ( GeezBausiTTFNames[fontFace] );

  return ( NIL );

}



int
TFanus_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = strdup ( TFanusTTFNames[fontFace] );

  return ( NIL );

}



int
TFanusNew_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = strdup ( TFanusNewTTFNames[fontFace] );

  return ( NIL );

}


int
EthioSoft_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{

  *RTFPrefix = strdup ( EthioSoftRTFPrefix[0] );

  return ( NIL );

}


int
TFanus_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{

  *RTFPrefix = strdup ( TFanusRTFPrefix[0] );

  return ( NIL );

}


unsigned char
TFanus_isGoodANSI ( fch )
  FCHAR fch;
{

  if ( fch >= ANSI )
    return ( false );

  if ( TFanusHashTable[fch - 0x20] == SAFEANSI
       || TFanusHashTable[fch - 0x20] == NETEB 
       || TFanusHashTable[fch - 0x20] == EQUESTIONMARK )
    return ( (unsigned char)fch );

  return ( false );

}


unsigned char
EthioSoft_isGoodANSI ( fch )
  FCHAR fch;
{

  return ( fch == 0x2e || fch == 0x2a || fch == 0xbb || fch == TF_WiES )
         ? false : TFanus_isGoodANSI ( fch ) ;

}


unsigned char
GeezBausi_isGoodANSI ( fch )
  FCHAR fch;
{

  return ( fch == 0x2c || fch == 0x24 || fch == 0x25 || fch == 0x2b )
         ? false : TFanus_isGoodANSI ( fch ) ;

}


unsigned char
TFanusNew_isGoodANSI ( fch )
  FCHAR fch;
{

  return ( fch == TF_WNew ) ? false : TFanus_isGoodANSI ( fch ) ;

}


char*
TFanus_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (ETHIOSOFT_EMAIL);
        break;
      case LETH_WWW:
        return (ETHIOSOFT_WWW);
        break;
      case LETH_FTP:
        return (ETHIOSOFT_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}


char*
EthioSoft_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (ETHIOSOFT_EMAIL);
        break;
      case LETH_WWW:
        return (ETHIOSOFT_WWW);
        break;
      case LETH_FTP:
        return (ETHIOSOFT_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
