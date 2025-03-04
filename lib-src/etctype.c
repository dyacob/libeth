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

#include <stdlib.h>
#include "fidel.h"
#include "etctype.h"
#include "fidelexp.h"


 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//
//  The following Are Character Classification Routines
//
//  Analagous To:  isalfa  -> isfidel 
//                 isdigit -> isfdigit
//                 isalnum -> isflnum
//                 ispunct -> isfpunct
//                 iscntrl -> isfcntrl  (True for empty address cells)
//                 isprint -> isfprint  (False if isfcntrl is True)
//                 isspace -> isfspace  (True for SPACE, ESPACE, TAB, RETURN,
//                                       NEWLINE, FORMFEED)
//                 isascii -> isethio
//                 isgraph -> isfgraph
//                            isprivate
//
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/

boolean
isfidel (fchar)
  FCHAR fchar;
{

/*
 *  Note:  The Unicode Fidel detectection doesn't
 *         trap for dead space at this time.
 *
 */


  if ( fchar == '\0' )
    return ( _LET_FAIL );

  if ( (HAE <= fchar && fchar <= FYA)               /* base */
       || ( QYAE <= fchar && fchar <= GYAE+ROW+5 )  /* extensions */
       || ( WWAE <= fchar && fchar <= WWAE+5 )      /* private */
     )
    return (true);

  return (false); 

}


boolean
isfdigit (fchar)
  FCHAR fchar;
{

  if ( fchar == '\0' )
    return ( _LET_FAIL );

  if ( ONE <= fchar && fchar <= TENTHOUSAND )
    return (true);

  return (false); 

}


boolean
isethiopic (fchar)
  FCHAR fchar;
{

  if ( fchar == '\0' )
    return ( _LET_FAIL );

  if ( UNIFIDEL <= fchar && fchar <= UNIFIDEL+UNITOTAL )
    return (true);

  if ( isprivate(fchar) )
    return (true);

  return (false);

}


boolean
isethiopicdefined (fchar)
  FCHAR fchar;
{

  if ( fchar == '\0' )
    return ( _LET_FAIL );

  if ( !isethiopic ( fchar ) )
    return (false);

  switch ( fchar )
    {
    	case 0x1207:   /*  ho + 1 */
    	case 0x1247:   /*  qo + 1 */
    	case 0x1249:   /* qWe + 1 */
    	case 0x124e:   /* qWE + 1 */
    	case 0x124f:   /* qWE + 2 */
    	case 0x1257:   /*  Qo + 1 */
    	case 0x1259:   /* QWe + 1 */
    	case 0x125e:   /* QWE + 1 */
    	case 0x125f:   /* QWE + 2 */
    	case 0x1287:   /* `ho + 1 */
    	case 0x1289:   /*`hWe + 1 */
    	case 0x128e:   /*`hWE + 1 */
    	case 0x128f:   /*`hWE + 2 */
    	case 0x12af:   /*  ko + 1 */
    	case 0x12b1:   /* kWe + 1 */
    	case 0x12b6:   /* kWE + 1 */
    	case 0x12b7:   /* kWE + 2 */
    	case 0x12bf:   /*  Ko + 1 */
    	case 0x12c1:   /* KWe + 1 */
    	case 0x12c6:   /* KWE + 1 */
    	case 0x12c7:   /* KWE + 2 */
    	case 0x12cf:   /*  wo + 1 */
    	case 0x12d7:   /*  `o + 1 */
    	case 0x12ef:   /*  yo + 1 */
    	case 0x130f:   /*  go + 1 */
    	case 0x1311:   /* gWe + 1 */
    	case 0x1316:   /* gWE + 1 */
    	case 0x1317:   /* gWE + 2 */
    	case 0x131f:   /*  Go + 1 */
    	case 0x1347:   /* `So + 1 */
    	case 0x135b:   /* fYa + 1 */
    	case 0x135c:   /* fYa + 2 */
    	case 0x135d:   /* fYa + 3 */
    	case 0x135e:   /* fYa + 4 */
    	case 0x135f:   /* fYa + 5 */
    	case 0x1360:   /*  WS - 1 */
    	case 0x137d:   /* 10k + 1 */
    	case 0x137e:   /* 10k + 2 */
    	case 0x137f:   /* 10k + 3 */
			 return (false);

    	default:
	    	 return (true);
    }

}


boolean
isfamily (fchar1, fchar2)
  FCHAR fchar1;
  FCHAR fchar2;
{

  if ( fchar1 == '\0' || fchar2 == '\0' )
    return ( _LET_FAIL );

  if ( (FYA <= fchar1 || fchar1 <= HAE) 
      || (FYA <= fchar2 || fchar2 <= HAE) )
    return (false);

  if ( set_formNumber(fchar1, GIZ) == set_formNumber(fchar2, GIZ) )
    return (true);

/* this doesn't work for mod 12 
 * fidels or Unicode Extensions
    if ( (fchar1 - get_fmodulo(fchar1)) 
       == (fchar2 - get_fmodulo(fchar2)) )
    return (true);
 */

  return (false); 

}


boolean
isfpunct (fchar)
  FCHAR fchar;
{

  if ( fchar == '\0' )
    return ( _LET_FAIL );

  if ( (SPACE <= fchar && fchar <= PARAGRAPH)
      || (GEMINATION <= fchar && fchar <= EQUESTIONMARK) )
    return (true);

  return (false);

}


boolean
isflnum (fchar)
  FCHAR fchar;
{

  if ( fchar == '\0' )
    return ( _LET_FAIL );

  return ( isfidel(fchar) | isfdigit(fchar) );

}


boolean
isfcntrl (fchar)
  FCHAR fchar;
{

  if ( fchar == '\0' )
    return ( _LET_FAIL );

  if ( FYA < fchar && fchar < WORDSPACE )
    return (true);

  switch ( fchar )
    {
      case NIL:
      case HAE   + DIQALA:
      case QAE   + DIQALA:
      case   QAE + DIQALA_GIZ  + 1:
      case   QAE + DIQALA_SADS + 1:
      case   QAE + DIQALA_SADS + 2:
      case QXAE  + DIQALA:
      case   QXAE+ DIQALA_GIZ  + 1:
      case   QXAE+ DIQALA_SADS + 1:
      case   QXAE+ DIQALA_SADS + 2:
      case HZAE  + DIQALA:
      case   HZAE+ DIQALA_GIZ  + 1:
      case   HZAE+ DIQALA_SADS + 1:
      case   HZAE+ DIQALA_SADS + 2:
      case KAE   + DIQALA:
      case   KAE + DIQALA_GIZ  + 1:
      case   KAE + DIQALA_SADS + 1:
      case   KAE + DIQALA_SADS + 2:
      case KHAE  + DIQALA:
      case   KHAE+ DIQALA_GIZ  + 1:
      case   KHAE+ DIQALA_SADS + 1:
      case   KHAE+ DIQALA_SADS + 2:
      case WAE   + DIQALA:
      case OAE   + DIQALA:
      case GAE   + DIQALA:
      case   GAE + DIQALA_GIZ  + 1:
      case   GAE + DIQALA_SADS + 1:
      case   GAE + DIQALA_SADS + 2:
      case TSZAE + DIQALA: 

      case QYAE  + DIQALA:
      case KYAE  + DIQALA:
      case XYAE  + DIQALA:
      case GYAE  + DIQALA:

        break;


      default:
        return (false);
    }


  return (true);

}


boolean
isfprint (fchar)
  FCHAR fchar;
{

  if ( fchar == '\0' )
    return ( _LET_FAIL );

  return ( !(iscntrl(fchar)) );

}


boolean
isfgraph (fchar)
  FCHAR fchar;
{


  if ( fchar == '\0' )
    return ( _LET_FAIL );

 if ( ORNAMENT <= fchar && fchar <= INVAFRICA )
   return (true);


  return (false);

}


boolean
isfspace (fchar)
  FCHAR fchar;
{

  if ( fchar == '\0' )
    return ( _LET_FAIL );

  if (fchar < ANSI)
    return ( isspace(fchar) );

  if (fchar == WORDSPACE)
    return (true);

  return (false);

}


boolean
isprivate (fchar)
  FCHAR fchar;
{

  if ( fchar == '\0' )
    return ( _LET_FAIL );

  if ( PRIVATE_USE_BEGIN <= fchar && fchar <= PRIVATE_USE_END )
    return (true);

  return (false);

}


 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  get_fmodulo (fchar)
//
//  This routine determines and returns the modulo class of the passed 
//  fidel character.
//
//  fchar    -a single Unicode addressed character of the FCHAR datatype
//
//  The number of forms of letters, and character class may be determined 
//  by its address following:
//
//        0 <= address <= 175   :   8 forms
//      176 <= address <= 319   :  12 forms
//      320 <= address <= 368   :   7 forms
//      369 <= address <= 382   :     extensions
//      383 <= address <= 402   :     number range
//      403 <= address <= 411   :     ethiopic punctuation range
//      414 <= address <= 418   :     ethiopic-stylized punctuation range
//      419 <= address          :     private use range
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/
int
get_fmodulo (fchar)
  FCHAR fchar;
{

int mod, modfch;


  if ( fchar == '\0' || !isethiopic(fchar) )
    return ( _LET_FAIL );


  if ( isfidel(fchar) ) 
    {
      modfch = UniToMod[fchar-UNIFIDEL];
      if ( modfch < UniToMod[HAE-UNIFIDEL] 
           || (MAE <= fchar && fchar <= MAE + DIQALA) /* this is the interim fix */
           || (BAE <= fchar && fchar <= BAE + DIQALA) /* until the extended ethiopic */
           || (FAE <= fchar && fchar <= FAE + DIQALA) /* is fixed */
           || (PAE <= fchar && fchar <= PAE + DIQALA)
         )
        mod = 8;
      else if ( modfch < UniToMod[QYAE-UNIFIDEL] )
        mod = 12;
      else if ( modfch < UniToMod[MYA-UNIFIDEL] )
        mod = 7;
      else 
        mod = 3;

     /* `he / he correction */
      if ( UniToMod[HAE-UNIFIDEL] <= modfch && modfch <= UniToMod[(HAE+SABI)-UNIFIDEL] ) 
        mod = 7;
      else if ( (UniToMod[HZAE-UNIFIDEL] <= modfch && modfch <= UniToMod[(HZAE+SABI)-UNIFIDEL])
                 ||  (UniToMod[(HZAE+DIQALA_RABI)-UNIFIDEL] <= modfch && modfch <= UniToMod[(HZAE+DIQALA_SADS)-UNIFIDEL]) )
        mod = 12;
     /* we - wo correction //
      else if ( UniToMod[WAE-UNIFIDEL] <= modfch && modfch <= UniToMod[(WAE+SABI)-UNIFIDEL] ) 
        mod = 7; */
    }
  else if ( isfpunct(fchar) ) 
    mod = 15; 
  else if ( isfdigit(fchar) ) 
    mod = 10; 
  else if ( isprivate(fchar) )
    mod = 1; 
  else mod = NIL;

  return (mod);

}


 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  get_formNumber (fchar)
//
//  This routine determines and returns the syllabic order of the passed 
//  fidel character.  When a non-syllable is passed the form number is the
//  position of the fchar in its class list.
//
//  fchar    -a single Unicode addressed character of the FCHAR datatype
//
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/
/*
 *  get_formNumber returns DIQALA_RABI when I was expecting DIQALA,
 *  this is too strict, get_formNumber should be locale aware.
 *
 */
int
get_formNumber (fchar)
  FCHAR fchar;
{

int fmod, formNumber;


  fmod  = get_fmodulo (fchar);
  switch (fmod)
    {
      case  3:  /* mYa, rYa, fYa */
                formNumber = 1; 
                break;

      case  7:  /* traditional syllable */
                formNumber = (fchar % 8);        /* distance from left side */
                break;

      case  8:  /* traditional syllable */
                formNumber = (fchar % 8);        /* distance from left side */
                if ( formNumber == 7 )
                  formNumber = 10;
                break;

      case 10:  /* digit */
                formNumber = (fchar - ONE);      /*  ONE is 0 */
                break;

      case 12:  /* has labiovelar extensions */
                  

                formNumber = (fchar % 16);       /* distance from left side */

                /* me, ke and Ke are out of sync */
                if ( (MAE <= fchar && fchar <= MAE + ROW - 1)
                    || (KAE  <= fchar && fchar <= KAE  + ROW - 1)
                    || (KHAE <= fchar && fchar <= KHAE + ROW - 1)
                    || (WAE  <= fchar && fchar <= WAE  + ROW - 1)
                    || (GAE  <= fchar && fchar <= GAE  + ROW - 1)
                    || (GGAE <= fchar && fchar <= GGAE + ROW - 1) 
                    || (FAE  <= fchar && fchar <= FAE  + ROW - 1) )
                formNumber -= 8;

                /* kWe->kW' and KWe->KW'  are out of sync */
                if ( (KAE + ROW <= fchar && fchar <= KAE + ROW + ROW - 1)
                    || (KHAE + ROW <= fchar && fchar <= KHAE + ROW + ROW - 1)
                    || (GAE + ROW <= fchar && fchar <= GAE + ROW + ROW - 1)
                    || (GGAE + ROW <= fchar && fchar <= GGAE + ROW + ROW - 1) )
                formNumber += 8;

                if ( formNumber >= 7 && fchar < MYA )
                  {
                    switch (formNumber)
                      {
                        case  7:  /*  Wa of MWA, BWA, FWA, GWA, PWA */
                                  formNumber = 10;
                                  break;            /* this makes a problem */
                        case  8:  /*  We  */
                        case 10:  /*  Wi  */
                        case 11:  /*  Wa  */
                        case 12:  /*  WE  */
                                  formNumber -= 1;
                                  break;
                        case 13:  /*  W' -> Wu */
                                  formNumber -= 5;
                        default:
                                  break;
                      }
                  }
                else if ( fchar >= MWAE )
                  {
                    if ( fchar < MWAE+ROW || fchar == WWAE )                       /* We */
                      formNumber =  8;
                    else if ( fchar < MWAE + ROW + ROW || fchar == WWAE + 1 )      /* Wi */
                      formNumber = 10;
                    else if ( fchar == WWAE + 2 )
                      formNumber = 11;
                    else if ( fchar < MWAE + 2*(ROW + ROW) || fchar == WWAE + 3 )  /* WE */
                      formNumber = 12;
                    else if ( fchar < MWAE + 3*(ROW + ROW) || fchar == WWAE + 4 )  /* W' -> Wu */
                      formNumber =  9;
                  }
                                           /* extensions                 */
                break;

      case 15:  /* punctuation */
                if ( fchar <=  PARAGRAPH )
                  formNumber = fchar - SPACE; 
                else
                  formNumber = fchar - GEMINATION + 10; 
				break;

      default:  formNumber = NIL;
                break;
    }

    return ( formNumber );

}


 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  get_formOffset (fchar)
//
//  This routine determines and returns the syllabic order of the passed 
//  fidel character.  When a non-syllable is passed the form number is the
//  position of the fchar in its class list.
//
//  fchar    -a single Unicode addressed character of the FCHAR datatype
//
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/
int
get_formOffset (fchar)
  FCHAR fchar;
{

int fmod, formOffset = NIL;


  fmod  = get_fmodulo (fchar);
  switch (fmod)
    {
      case  3:  /* mYa, rYa, fYa */
                if (fchar == MYA)
                  formOffset = (MYA-MAE); 
                else if (fchar == RYA)
                  formOffset = (RYA-RAE); 
                else if (fchar == FYA)
                  formOffset = (FYA-FAE); 
                break;

      case  7:  /* traditional syllable */
      case  8:  /* traditional syllable */
                formOffset = (fchar % 8);        /* distance from left side */
                break;


      case 10:  /* digit */
                formOffset = (fchar - ONE);      /*  ONE is 0 */
                break;


      case 12:  /* has labiovelar extensions */
                if ( ( NAE < fchar && fchar < PAE )
                    || fchar <= SZAE             /* this catch MAE series */
                   )
                  fchar += 8;
                formOffset = (fchar % 16);       /* distance from left side */

                break;


      case 15:  /* punctuation */
                if ( fchar <=  PARAGRAPH )
                  formOffset = fchar - SPACE; 
                else
                  formOffset = fchar - GEMINATION + 10; 
				break;

      default:  break;
    }

    return ( formOffset );

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  set_formNumber (fchar, form)
//
//  This routine determines and returns the syllabic order of the passed 
//  fidel character.  When a non-syllable is passed the form number is the
//  position of the fchar in its class list.
//
//  fchar    -a single Unicode addressed character of the FCHAR datatype
//
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/
int
set_formNumber (fchar, newForm)
  FCHAR fchar;
  int newForm;
{

  fchar -= get_formOffset (fchar);
  fchar += newForm;

  return (fchar);

}


 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
// get_traditional
//
// is here becuase fidel.map does not have a TraditionalToUni
// ...maybe it should ?
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/
int 
get_traditional ( trad, uni )
  int trad; 
  FCHAR* uni;
{

int uniMap;


  uniMap = *uni = 0;
  while ( UniToTraditional[uniMap] != trad && uniMap < UNITOTAL ) 
    (uniMap)++;

  if ( uniMap == UNITOTAL ) /* nothing found */
    return ( NIL );

  *uni = uniMap + UNIFIDEL;

  if ( *uni >= EXTLAST )
    *uni = ( *uni - EXTLAST ) + PRIVATE_USE_END - NUM_SPECIAL;

  return ( uniMap ) ;

}



FCHAR
get_traditional_series ( trad, syllable )
  int trad, syllable;
{

int uniMap = GeezMaps[trad];
FCHAR uni, *uniP;


  if ( get_fmodulo (uniMap) < 12 )
    return ( (uniMap+syllable) );

  uniP =& uni;

  uniMap = get_traditional ( UniToTraditional[uniMap-UNIFIDEL]+syllable, uniP );

  return (uni);

}



FCHAR*
get_fidel_oli (item)
  int item;
{

register int i;
FCHAR *fitem, fnumber;
int base=41, places=0, coef=0;
int cycle=1, last=0;


  /*  Don't waste time with additional processing...
   *
   */
  if ( item < base )
    {
      fitem = (FCHAR *) malloc ( 2 * sizeof (FCHAR) );
      fitem[0] = (FCHAR)GeezMaps[item];
      fitem[1] = '\0';
      return (fitem);
    }


  while ( (cycle *= base) <= item )
    places++;
  places++;

  fitem = (FCHAR *) calloc ( (places + 1), sizeof (FCHAR) ); /* (places+1) +1 */
  fitem[places] = '\0';

  cycle = 1;
  for ( i = places-1; i >= 0; i-- )
    {
      if ( !i )
        coef = ( (item - last) / cycle ) % (base+1) - 1;
      else
        coef = ( (item - last) / cycle ) % base;
      fnumber = get_traditional_series (coef, GIZ);
      fitem[i] = fnumber;
      cycle *= base;
      last  += coef;
    }

  /* do mirror copy here */
  return (fitem);

}
