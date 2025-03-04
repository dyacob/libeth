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
#include "phonetic.map"
#include "systems.h"
#include "base.h"



FCHAR
GeezTypeToUnicode ( void )
{
FCHAR fch = NIL;
unsigned char base ;


  base = getToken();           /* read first char                            */

  if ( base == GT_S || base == GT_P )
    {
      fch = GeezTypeHashTable[getToken()-0x20];
      ungetToken (base);
    }
  else if ( isspace(base)      /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = GeezTypeHashTable[base-0x20]) == 0       /* ...rouges       */
       || fch <= SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }


  return ( PhoneticToUnicode ( fch, geztype ) );
}



FCHAR
GeezTypeNetToUnicode ( void )
{
FCHAR fch = NIL;
unsigned char base ;


  base = getToken();           /* read first char                            */

  if ( base == GT_S || base == GT_P )
    {
      fch = GeezTypeHashTable[getToken()-0x20];
      ungetToken (base);
    }
  else if ( isspace(base)      /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = GeezTypeHashTable[base-0x20]) == 0       /* ...rouges       */
       || fch <= SAFEANSI      /* a lone diacritc or safe ASCII character    */
     )
    {
      return ( (FCHAR) base );
    }

  switch ( fch )
    {
      case QXAE:       fch = WAE + RABI;
                       break;

      case TSZAE+SADS: return (WAE + SABI);
                       break;

      case KHAE+SADS : fch = NYAE;
                       break;

      case KHAE+SABI : fch = ZHAE + RABI;
                       break;

      case CAE       : fch = ZAE;
                       break;

/*
      case KHAE      : fch = GeezTypeHashTable[getToken()-0x20];
                       ungetToken (base);  // but this won't be read as a diacritic
                       break;
*/
      case CAE+RABI  :
      case NYAE      :
      case KHAE+RABI :
      case WAE+RABI  :
      case WAE+SABI  :
      case ZHAE+RABI : return ( (FCHAR) base );
                       break;

      default  : break;
    }

  return ( PhoneticToUnicode ( fch, geztypenet ) );
}




FCHAR
PhoneticToUnicode ( fch, sys )
  FCHAR fch;
  enum CharacterSet sys;
{

unsigned char form; 
char formNumber;


  if ( fch <= WORDSPACE )      /* get diacritic mark */
    {
    HERE:
      if ( (GeezTypeHashTable[(form = getToken())-0x20]) == DIACRITIC
           || (sys == geztypenet && (form == GTN_B3 || form == GTN_B2 || form == GTN_TSZAE)) || form == GT_WS  )
        {
          formNumber = fch%8;  /* what is my vowel ? */
          fch -= formNumber;   /* normalize to ge'ez form to simplify following switch */   
          switch (form)
            {
              case GT_uru  :
              case GT_ul   :
              case GT_uld  :
              case GT_ull  :
              case GT_ulll : if (fch == WAE)
                               fch += SADS;
                             else
                               fch += KAIB;  break;

              case GT_il  :
              case GT_im  :
              case GT_ir  : fch += SALS;  break;

              case GT_Er  :
              case GT_Erf :
              case GT_El  :
              case GT_Ell :
              case GT_Elll: fch += HAMS;  break;

              case GT_Weu :
              case GT_Wed : if (fch == LAE) 
                               fch += SABI;
                             else
                               fch += DIQALA_GIZ;  break;

              case GT_Wi :  fch += DIQALA_SALS;  break;

              case GT_Wal:
              case GT_Wam:
              case GT_War:
                if ( GeezTypeFidel[fch-UNIFIDEL+DIQALA].set == SETD )
                  fch += DIQALA_RABI;  /* has 12 forms     */
                else
                  fch +=      DIQALA;  /* has only 8 forms */
                break;

              case GT_WEl:
              case GT_WEr:  fch += DIQALA_HAMS;  break;

              case GT_Wu :
              case GT_Wd :  fch += DIQALA_SADS;  break;

              case '-'   :  if ( (fch+formNumber) == WORDSPACE )
                              fch = PREFACECOLON; 
                            else
                              {
                                fch += formNumber;
                                ungetToken (form);
                              }
                            break;

              case GT_yo :  if (fch == YAE)
                               fch += SABI;
                            else if (fch == DAE || fch == PHAE || fch == TSAE || fch == DHAE)
                               fch += SADS;
                            break;


              case GT_S  :  if (fch == BAE)
                              {
                                fch += SADS;
                                if ( (form = getToken()) == GT_B )  /* check for "v" */
                                  fch = VAE + SADS;
                                else
                                  ungetToken (form);
                              }
                            else if (fch == NAE)
                               fch = HZAE + SABI;
			    else
                              {
                                fch += formNumber;
                                ungetToken (form);
                              }
                            break;


              case GT_P  :  if (fch == TSAE)
                               fch = PHAE + formNumber;
			    else if (fch == DAE)
                               fch = DHAE + formNumber;

                            if (formNumber == GIZ || formNumber == RABI)
                              goto HERE;

                            break;


              case GT_B  :  if (fch == BAE)
                               fch = VAE + formNumber;
			    else if (fch == GAE)
                               fch = GGAE + formNumber;

                            if (formNumber == GIZ || formNumber == RABI)
                              goto HERE;

                            break;


              case GT_WS :  if ( (fch+formNumber) == WORDSPACE )
                                fch = FULLSTOP;
                            else
                              {
                                fch += formNumber;
                                ungetToken (form);
                              }
                            break;

              case GTN_B2:  if ( fch == QAE )
                              fch = QXAE + formNumber;
			    else if ( fch == TAE )
                              fch = CAE + formNumber;

                            if (formNumber == GIZ)
                              goto HERE;

                            break;

              case GTN_B3:  fch = KHAE + formNumber;

                            if (formNumber == GIZ || formNumber == RABI)
                              goto HERE;
                            break;

              case GTN_TSZAE:
                            if ( fch == OAE )
                              fch = TSZAE + formNumber;

                            if (formNumber == GIZ)
                              goto HERE;
                            break;

              default:  
                ungetToken (form);
                fch += formNumber;   /* no diacritic mark, restore value */   
                if ( GeezTypeFidel[fch-UNIFIDEL].set != NOCH )  
                     /*  I don't have a diacritic mark 
                      *  in the stream, but I do in the table...
                      *  this shouldn't happen with the hash buckets,
                      *  but if it does echo a warning 
                      */
                   {
                     fprintf (stderr, "ID Failure for GeezType for char 0x%02x", fch);
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
UnicodeToGeezType ( fch )
  FCHAR fch;
{

  return ( UnicodeToBase ( fch, GeezTypeFidel, "GeezType" ) );

}


int
GeezType_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, GeezTypeFidel ) );

}


int
GeezType_get_setName (setid, fontFace, setName)
  int setid;
  int fontFace;
  unsigned char** setName;
{

  *setName = strdup ( PhoneticTTFNames[fontFace] );

  return ( NIL );

}


int
GeezType_get_setRTFPrefix (setid, fontFace, RTFPrefix)
  int setid;
  int fontFace;
  char** RTFPrefix;
{

  *RTFPrefix = strdup ( PhoneticRTFPrefix[0] );

  return ( NIL );

}


unsigned char
GeezType_isGoodANSI ( fch )
  FCHAR fch;
{

  if ( fch >= ANSI )
    return ( false );

  if ( GeezTypeHashTable[fch - 0x20] == SAFEANSI
       || GeezTypeHashTable[fch - 0x20] == NETEB 
       || GeezTypeHashTable[fch - 0x20] == EQUESTIONMARK )
    return ( (unsigned char)fch );

  return ( false );

}


int
GeezTypeNet_get_setid ( fch )
  FCHAR fch;
{

  return ( Base_get_setid ( fch, GeezTypeFidel ) );

}


unsigned char*
UnicodeToGeezTypeNet ( fch )
  FCHAR fch;
{
unsigned char * returnCh = NULL;
unsigned char * tempCh = NULL;

  returnCh = UnicodeToBase ( fch, GeezTypeFidel, "GeezTypeNet" );

  if ( returnCh ) switch ( returnCh[0] )
    {
      case 0x73 :  /* ce */
           // tempCh = (unsigned char *) calloc ( (strlen(returnCh) + 2), sizeof(unsigned char) );
           tempCh = (unsigned char *) calloc ( 4, sizeof(unsigned char) );
	   /*
	   tempCh[0]   = GTN_B2;
	   returnCh[0] = 0x6f;
	   */
	   tempCh[0] = 0x6f;
	   tempCh[1] = GTN_B2; 
	   tempCh[2] = returnCh[1]; 
	   // strcat ( tempCh, returnCh );
	   break;

      case 0x74 :  /* ca */
           tempCh = (unsigned char *) malloc ( sizeof(unsigned char) * 3 );
	   tempCh[0] = 0x70;
	   tempCh[1] = GTN_B2;
	   tempCh[2] = '\0';
	   break;

      case 0x67 :  /* Qe */
           // tempCh = (unsigned char *) calloc ( (strlen(returnCh) + 2), sizeof(unsigned char) );
           tempCh = (unsigned char *) calloc ( 4, sizeof(unsigned char) );
	   tempCh[0] = 0x63;
	   tempCh[1] = GTN_B2; 
	   tempCh[2] = returnCh[1]; 
	   // strcat ( tempCh, returnCh );
	   break;

      case 0x68 :  /* Qa */
           tempCh = (unsigned char *) malloc ( sizeof(unsigned char) * 3 );
	   tempCh[0] = 0x64;
	   tempCh[1] = GTN_B2;
	   tempCh[2] = '\0';
	   break;

      case 0x80 :  /* Ne */
           returnCh[0] = 0x8f;
	   break;

      case 0x8d :  /* Ke */
           tempCh = (unsigned char *) calloc ( 4, sizeof(unsigned char) );
	   tempCh[0] = 0x89;
	   tempCh[1] = GTN_B3; 
	   tempCh[2] = returnCh[1]; 
	   break;

      case 0x8e :  /* Ka */
           tempCh      = (unsigned char *) calloc ( (strlen(returnCh) + 2), sizeof(unsigned char) );
           tempCh[0]   = 0x8a;
           tempCh[1]   = GTN_B3;
           if ( fch == KHAE + DIQALA_RABI )
             tempCh[2]   = GT_War;
	   break;

      case 0x8f :  /* K  */
           tempCh    = (unsigned char *) malloc ( sizeof(unsigned char) * 3 );
	   tempCh[0] = 0x8b;
	   tempCh[1] = GTN_B3;
	   tempCh[2] = '\0';
	   break;

      case 0x90 :  /* Ko */
           tempCh    = (unsigned char *) malloc ( sizeof(unsigned char) * 3 );
	   tempCh[0] = 0x8c;
	   tempCh[1] = GTN_B3;
	   tempCh[2] = '\0';
	   break;

      case 0x93 :  /* wa */
           returnCh[0] = 0x67;
	   break;

      case 0x94 :  /* wo */
           returnCh[0] = 0xc8;
	   break;

      case 0x99 :  /* ze */
           returnCh[0] = 0x73;
	   break;

      case 0x9e :  /* Za */
           returnCh[0] = 0x90;
	   break;

      case 0xc6 :  /* `Se */
           tempCh    = (unsigned char *) calloc ( (strlen(returnCh) + 2), sizeof(unsigned char) );
	   tempCh[0] = 0x95;
	   tempCh[1] = GTN_TSZAE;
	   strcat ( tempCh, returnCh );
	   break;

      case 0xc8 :  /* `S  */
           tempCh    = (unsigned char *) malloc ( sizeof(unsigned char) * 3 );
	   tempCh[0] = 0x97;
	   tempCh[1] = GTN_TSZAE;
	   tempCh[2] = '\0';
	   break;

      default: break;
    }

  if ( tempCh )
    {
      free ( returnCh );
      returnCh = tempCh;
    }

  return ( returnCh );

}


unsigned char
GeezTypeNet_isGoodANSI ( fch )
  FCHAR fch;
{

  if ( fch >= ANSI )
    return ( false );

  if ( GeezTypeHashTable[fch - 0x20] == SAFEANSI
       || GeezTypeHashTable[fch - 0x20] == NETEB 
       || GeezTypeHashTable[fch - 0x20] == EQUESTIONMARK )
    return ( (unsigned char)fch );

  return ( false );

}


char*
GeezType_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (PHONETIC_EMAIL);
        break;
      case LETH_WWW:
        return (PHONETIC_WWW);
        break;
      case LETH_FTP:
        return (PHONETIC_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
