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
#include "etctype.h"
#include "feedel.h"
#include "ethcita.map"
#include "systems.h"


FCHAR
EthCITAUniToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base, form; 
char formNumber;


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       ||  base <= 0x20        /* or lesser chars that vendors don'e use     */
       || (fch = GeezNewAHashTable[base-0x20]) == 0       /* ...rouges       */
       || fch <= SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }

  if ( fch <= WORDSPACE )     /* get diacritic mark */
    {
  READNEXT:
      if ( (GeezNewAHashTable[(form = getToken())-0x20]) == DIACRITIC 
           || form == ECU_WS )
        {
          formNumber = fch%8; /* what is my vowel ? */
          fch -= formNumber;  /* normalize to ge'ez form to simplify following switch */   
          switch (form)
            {


              case ECU_ul:
              case ECU_ur:  if (fch == WAE)
                              fch += 5;
                            else
                              fch += 1;  break;

              case ECU_il:
              case ECU_ir:  fch += 2;  break;

              case ECU_El:
              case ECU_Er:  fch += 4;  break;

              case ECU_We:  if (fch == LAE) 
                              fch += 6;
                            else if (fch == CHAE) 
                              fch += 4;
                            else
                              fch += 8;  break;

              case ECU_Wi :  fch += 10;  break;

              case ECU_Wal:
              case ECU_War:
                   if ( GeezNewABFidel[fch-UNIFIDEL+7].set == SETD )
                     fch += 11;  /* has 12 forms     */
                   else
                     fch +=  7;  /* has only 8 forms */
                   break;

              case ECU_Wu:
              case ECU_Wd:  fch += 13;  break;

              case '-'   :  if ( (fch+formNumber) == WORDSPACE) 
                              fch = PREFACECOLON; 
                            else
                              {
                                fch += formNumber;
                                ungetToken (form);
                              }
                            break;

              case ECU_WS:  if ( (fch+formNumber) == WORDSPACE )
                              fch = FULLSTOP;
                            else
                              {
                                fch += formNumber;
                                ungetToken (form);
                              }
                            break;
          
              case ECU_B :  if ( (fch+formNumber) == WORDSPACE )
                              fch = COMMA;
                            else if ( fch == BAE )
                              {
                                fch = VAE + formNumber;
                                goto READNEXT;
                              }
                            else if ( fch == QAE )
                              {
                                fch = QYAE + formNumber;
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
                if ( GeezNewABFidel[fch-UNIFIDEL].vowel != NOCH )  
                     /*  I don't have a diacritic mark 
                      *  in the stream, but I do in the table...
                      *  this shouldn't happen with the hash buckets,
                      *  but if it does echo a warning 
                      */
                  {
                    fprintf (stderr, "ID Failure for GeezI,II for char 0x%02x ", fch);
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
UnicodeToEthCITAUni ( fch )
  FCHAR fch;
{

unsigned char* returnCh = NULL;


  returnCh = UnicodeToGeezNewAB ( fch );

  if ( fch == QAE + DIQALA_HAMS )
    strcpy ( returnCh, "\x6d\xf0" );

  return ( returnCh );

}



int
EthCITAUni_get_setid ( fch )
  FCHAR fch;
{
  return ( GeezNewAB_get_setid ( fch ) );
}


int
EthCITAUni_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  if ( setid < SET0 || SET1 < setid )
    return (0);


  *setName = (unsigned char *) malloc ( (strlen(EthCITAUniTTFNames[ 3 + setid + fontFace ]) + 1) * sizeof(unsigned char) );
  strcpy ( *setName, EthCITAUniTTFNames[ 3 + setid + fontFace ] );

  if (setid)
    return (NIL);
  else
    return (setid+1);

}


int
EthCITAUni_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{
  *RTFPrefix = (unsigned char *) malloc ( (strlen(EthCITAUniRTFPrefix[0]) + 1) * sizeof(unsigned char) );
  strcpy ( *RTFPrefix, EthCITAUniRTFPrefix[0] );

  if ( setid || fontFace > 9 || fontFace == 0 )
    return (NIL);
  else
    return ( setid+1 );  

}


unsigned char
EthCITAUni_isGoodANSI ( fch )
  FCHAR fch;
{
  return ( GeezNewA_isGoodANSI ( fch ) );
}


unsigned char*
UnicodeToEthCITABi ( fch )
  FCHAR fch;
{

unsigned char* returnCh = NULL;


  returnCh = UnicodeToEthioSys ( fch );

  if ( DIQALA < get_formNumber (fch) && fch%8 != DIQALA )
      returnCh[0] += EthiopianASCIIToEthCITABi[fch%8];

  return ( returnCh );

}



FCHAR
EthCITABiPToUnicode ( void )
{
  return ( EthioSysPrimaryToUnicode ( ) );
}



FCHAR
EthCITABiSToUnicode ( void )
{

FCHAR fch = NIL;


  fch =  EthioSysSecondaryToUnicode ( );

  if ( DIQALA < get_formNumber (fch) && fch%8 != DIQALA )
  /*
   *  This second test is necessary because all Wa's become DIQALA_RABI
   *  because libeth is not locale aware, we need to fix this...
   */
    fch -= EthiopianASCIIToEthCITABi[fch%8];

  return ( fch );
}



int
EthCITABi_get_setid ( fch )
  FCHAR fch;
{
  return ( EthioSys_get_setid ( fch ) );
}


int
EthCITABi_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = (unsigned char *) malloc ( (strlen(EthCITABiTTFNames[setid+fontFace]) + 1) * sizeof(unsigned char) );
  strcpy ( *setName, EthCITABiTTFNames[setid+fontFace] );

  if ( setid )
    return ( NIL );
  else
    return ( setid+1 );  

}


int
EthCITABi_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{

  *RTFPrefix = (unsigned char *) malloc ( (strlen(EthCITABiRTFPrefix[0]) + 1) * sizeof(unsigned char) );
  strcpy ( *RTFPrefix, EthCITABiRTFPrefix[0] );

  if ( setid )
    return ( NIL );
  else
    return ( setid+1 );  

}


boolean
EthCITABi_isGoodANSI ( fch )
  FCHAR fch;
{

  return (  EthioSys_isGoodANSI ( fch ) );

}


char*
EthCITA_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (ETHCITA_EMAIL);
        break;
      case LETH_WWW:
        return (ETHCITA_WWW);
        break;
      case LETH_FTP:
        return (ETHCITA_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
