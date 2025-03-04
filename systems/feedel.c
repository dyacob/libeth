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
#include "feedel.map"
#include "systems.h"
#include "base.h"


FCHAR
GeezignaToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base, form; 
char formNumber;


  base = getToken();           /* read first char                            */
       
  if ( isspace(base)           /* don't wast time processing spaces...       */
       ||  base <= 0x20        /* or lesser chars that vendors don't use     */
       || (fch = GeezignaHashTable[base-0x20]) == 0       /* ...rouges       */
       || fch <= SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }

  if ( HAE <= fch && fch <= WORDSPACE )     /* get diacritic mark */
    {
  READNEXT:
      if ( (GeezignaHashTable[(form = getToken())-0x20]) == DIACRITIC 
           || form == FDL_WS )
        {
          formNumber = fch%8;  /* what is my vowel ? */
          fch -= formNumber;   /* normalize to ge'ez form to simplify following switch */   
          switch (form)
            {
              case FDL_ur :
              case FDL_ul :  if (fch == WAE)
                               fch += 5;
                             else
                               fch += 1;  break;
    
              case FDL_ir :
              case FDL_il :  fch += 2;  break;

              case FDL_Er :
              case FDL_El :  fch += 4;  break;

              case FDL_We :  if (fch == LAE) 
                               fch += 6;
                             else
                               fch += 8;  break;

              case FDL_War:  
              case FDL_Wal:  
                   if ( GeezignaFidel[fch-UNIFIDEL+7].set == SETD )
                     fch += 11;   /* has 12 forms */
                   else
                     fch +=  7;  /* has only 8 forms */
                   break;

              case FDL_Wr :
              case FDL_Wl :  fch += 13;  break;

              case FDL_Wi :  fch += 10;  break;
    
              case '-'    :  if ( (fch+formNumber) == WORDSPACE )
                                fch = PREFACECOLON;
                             else
                               {
                                 fch += formNumber;
                                 ungetToken (form);
                               }
                             break;


              case FDL_WS :  if ( (fch+formNumber) == WORDSPACE )
                                fch = FULLSTOP;
                             else
                               {
                                 fch += formNumber;
                                 ungetToken (form);
                               }
                             break;

              case FDL_Br :
              case FDL_Bm :
              case FDL_Bl :  if ( (fch+formNumber) == WORDSPACE )
                                fch = COMMA;
                             else if ( fch == BAE )
                               {
                                 fch = VAE + formNumber;
                                 goto READNEXT;
                               }
                             else if ( fch == QAE )
                               {
                                 fch = QXAE + formNumber;
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
                if ( GeezignaFidel[fch-UNIFIDEL].vowel != NOCH ) 
                     /*  I don't have a diacritic mark 
                      *  in the stream, but I do in the table...
                      *  this shouldn't happen with the hash buckets,
                      *  but if it does echo a warning 
                      */
                  {
                    fprintf (stderr, "ID Failure for Geezigna for char 0x%02x with form 0x%02x\n", fch, form);
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
UnicodeToGeezigna ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, GeezignaFidel, "Geezigna" ) );

}




FCHAR
GeezIToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base, form; 
char formNumber;



  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       ||  base <= 0x20        /* or lesser chars that vendors don't use     */
       || (fch = GeezIHashTable[base-0x20]) == 0          /* ...rouges       */
       || fch <= SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }

  if ( HAE <= fch && fch <= WORDSPACE )     /* get diacritic mark */
    {
  READNEXT:
      if ( (GeezIHashTable[(form = getToken())-0x20]) == DIACRITIC 
           || form == FDLG_WS )
        {
          formNumber = fch%8; /* what is my vowel ? */
          fch -= formNumber;  /* normalize to ge'ez form to simplify following switch */   
          switch (form)
            {
    
              case FDLG_ul:
              case FDLG_ur:  if (fch == WAE)
                               fch += 5;
                             else
                               fch += 1;  break;

              case FDLG_il:
              case FDLG_ir:  fch += 2;  break;

              case FDLG_El:
              case FDLG_Er:  fch += 4;  break;

              case FDLG_We:  if (fch == LAE) 
                               fch += 6;
                             else if (fch == CHAE) 
                               fch += 4;
                             else
                               fch += 8;  break;

              case FDLG_Wi :  fch += 10;  break;

              case FDLG_Wal:
              case FDLG_War:
                   if ( GeezIIFidel[fch-UNIFIDEL+7].set == SETD )
                     fch += 11;  /* has 12 forms     */
                   else
                     fch +=  7;  /* has only 8 forms */
                   break;

              case FDLG_Wu:
              case FDLG_Wd:  fch += 13;  break;

              case '-'    :  if ( (fch+formNumber) == WORDSPACE) 
                               fch = PREFACECOLON; 
                             else
                                {
                                  fch += formNumber;
                                  ungetToken (form);
                                }
                             break;

              case FDLG_WS:  if ( (fch+formNumber) == WORDSPACE )
                               fch = FULLSTOP;
                             else
                                {
                                  fch += formNumber;
                                  ungetToken (form);
                                }
                             break;
          
              case FDLG_B :  if ( (fch+formNumber) == WORDSPACE )
                                fch = COMMA;
                             else if ( fch == BAE )
                               {
                                 fch = VAE + formNumber;
                                 goto READNEXT;
                               }
                             else if ( fch == QAE )
                               {
                                 fch = QXAE + formNumber;
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
                if ( GeezIIFidel[fch-UNIFIDEL].vowel != NOCH )  
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




FCHAR
GeezIIToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base; 


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = GeezIIHashTable[base-0x20]) == NOCH     /* ...rouges        */
     )
    {
      return ( (FCHAR) base );
    }


  return (fch);

}



unsigned char*
UnicodeToGeezII ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, GeezIIFidel, "GeezII" ) );

}



FCHAR
GeezNewAToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base, form; 
char formNumber;


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       ||  base <= 0x20        /* or lesser chars that vendors don't use     */
       || (fch = GeezNewAHashTable[base-0x20]) == 0       /* ...rouges       */
       || fch <= SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }

  if ( HAE <= fch && fch <= WORDSPACE )     /* get diacritic mark */
    {
  READNEXT:
      if ( (GeezNewAHashTable[(form = getToken())-0x20]) == DIACRITIC 
           || form == FDLN_WS )
        {
          formNumber = fch%8; /* what is my vowel ? */
          fch -= formNumber;  /* normalize to ge'ez form to simplify following switch */   
          switch (form)
            {
              case FDLN_ul:
              case FDLN_ur:  if (fch == WAE)
                               fch += 5;
                             else
                               fch += 1;  break;

              case FDLN_il:
              case FDLN_ir:  fch += 2;  break;

              case FDLN_El:
              case FDLN_Er:  fch += 4;  break;

              case FDLN_We:  if (fch == LAE) 
                               fch += 6;
                             else if (fch == CHAE) 
                               fch += 4;
                             else
                               fch += 8;  break;

              case FDLN_Wi :  fch += 10;  break;

              case FDLN_Wal:
              case FDLN_War:
                   if ( GeezNewABFidel[fch-UNIFIDEL+7].set == SETD )
                     fch += 11;  /* has 12 forms     */
                   else
                     fch +=  7;  /* has only 8 forms */
                   break;

              case FDLN_Wu:
              case FDLN_Wd:  fch += 13;  break;

              case '-'    :  if ( (fch+formNumber) == WORDSPACE) 
                               fch = PREFACECOLON; 
                             else
                                {
                                  fch += formNumber;
                                  ungetToken (form);
                                }
                             break;

              case FDLN_WS:  if ( (fch+formNumber) == WORDSPACE )
                               fch = FULLSTOP;
                             else
                                {
                                  fch += formNumber;
                                  ungetToken (form);
                                }
                             break;
          
              case FDLN_B :  if ( (fch+formNumber) == WORDSPACE )
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



FCHAR
GeezNewBToUnicode ( void )
{

FCHAR fch = NIL;
unsigned char base; 


  base = getToken();           /* read first char                            */

  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = GeezNewBHashTable[base-0x20]) == NOCH        /* ...rouges   */
     )
    {
      return ( (FCHAR) base );
    }


  return (fch);

}



unsigned char*
UnicodeToGeezNewAB ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, GeezNewABFidel, "GeezNewAB" ) );

}



int
Geezigna_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, GeezignaFidel ) );

}


int
Geezigna_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = strdup ( FeedelTTFNames[0] );

  return (NIL);

}


int
GeezII_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, GeezIIFidel ) );

}


int
GeezII_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = strdup ( FeedelTTFNames[ setid + 1 ] );

  if (setid)
    return (NIL);
  else
    return (setid+1);

}


unsigned char
GeezI_isGoodANSI ( fch )
  FCHAR fch;
{

  if ( fch >= ANSI )
    return ( false );

  if ( GeezIHashTable[fch - 0x20] == SAFEANSI 
       || GeezIHashTable[fch - 0x20] == NETEB )
    return ( (unsigned char)fch );

  return ( false );

}


int
GeezNewAB_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, GeezNewABFidel ) );

}


int
GeezNewAB_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  if ( setid < SET0 || SET1 < setid )
    return (0);


  *setName = strdup ( FeedelTTFNames[ 3 + setid + fontFace ] );

  if (setid)
    return (NIL);
  else
    return (setid+1);

}


int
Feedel_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{
int isGeezABC = ( 6 < fontFace && fontFace < 12 ) ? 1 : 0;

  *RTFPrefix = strdup ( FeedelRTFPrefix[0 + isGeezABC] );

  if ( setid || fontFace > 9 || fontFace == 0 )
    return (NIL);
  else
    return ( setid+1 );  

}


boolean
GeezNewA_isGoodANSI ( fch )
  FCHAR fch;
{

  if ( fch >= ANSI )
    return ( false );

  if ( GeezNewAHashTable[fch - 0x20] == SAFEANSI  
       || GeezNewAHashTable[fch - 0x20] == NETEB 
       || GeezNewAHashTable[fch - 0x20] == EQUESTIONMARK )
    return ( (unsigned char)fch );

  return ( false );

}


char*
Feedel_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (FEEDEL_EMAIL);
        break;
      case LETH_WWW:
        return (FEEDEL_WWW);
        break;
      case LETH_FTP:
        return (FEEDEL_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
