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
#include "ed.map"
#include "systems.h"

#include <string.h>


FCHAR
EdToUnicode ( void )
{
#ifdef COMPILE
FCHAR fch = NIL;
unsigned char base, form; 
char formNumber;


  base = getToken();           /* read first char                            */
       
  if ( isspace(base)           /* don't wast time processing spaces...       */
       || base <= 0x20         /* or lesser chars that vendors don't use     */
       || (fch = (int) EdHashTable[base-0x20]) == 0             /* ...rouges */
     )
    {
      return ( (FCHAR) base );
    }

  switch (fch) 
    {
      case DIACRITIC :              /* convert diacritic back into vowel */
        switch (base)
          {
            case ED_e :  fch = AE +  GIZ;  break;
            case ED_u :  fch = AE + KAIB;  break;
            case ED_i :  fch = AE + SALS;  break;
            case ED_a :  fch = AE + RABI;  break;
            case ED_E :  fch = AE + HAMS;  break;
            case ED_o :  fch = AE + SABI;  break;
            default   :  break;              /* shouldn't happen... */
          }
        break;

      case '\\' :
        if ( ( form = getToken() ) ==  'p' )
          fch = '\n';
        else
          ungetToken (form);
        break;

      case '<' : if ( (form = getToken()) == '<' )
                   fch = LEFTQUOTE;
                 else
                   ungetToken (form);
                 break;
          
      case '>' : if ( (form = getToken()) == '>' )
                   fch = RIGHTQUOTE;
                 else
                   ungetToken (form);
                 break;

      case '^' :
        form = getToken();
        switch (form)
          {
            case 's':  fch = SZAE + SADS;   break;
            case 'h':  fch = HZAE + SADS;   break;
            case 'H':  fch = KHAE + SADS;   break;
            case 'S':  fch = TSAE + SADS;   break;
            case 't':  fch = TSZAE + SADS;  break;
            default :  break;
          }

        if ( fch == '^' ) 
          {
            ungetToken (form);
            break;
          }
        /* else  fall through to the default and continue */

             
      default:
        if ( fch <= WORDSPACE )     /* get diacritic mark */
          {
           if ( (EdHashTable[(form = getToken())-0x20]) == DIACRITIC )
             {
               formNumber = fch%8;  /* what is my vowel ? */
               fch -= formNumber;   /* normalize to ge'ez form to simplify following switch */   
               switch (form)
                 {
                   case ED_e  :  break;

                   case ED_u  :  if (fch == WAE)
                                    fch += SADS;
                                  else
                                    fch += KAIB;  break;

                   case ED_i  :  fch += SALS;  break;

                   case ED_a  :  fch += RABI;  break;

                   case ED_E  :  fch += HAMS;  break;

                   case ED_o  :  fch += SABI;  break;

                   case ED_W  :  
                     form = getToken();
                     switch (form)
                       {
                         case ED_e:  fch += DIQALA_GIZ;    break;
                         case ED_i:  fch += DIQALA_SALS;   break;
                         case ED_a:  if ( EdFidel[fch-UNIFIDEL+7].set == SETD )
                                       fch += DIQALA_RABI;
                                     else 
                                       fch += DIQALA;
                                     break;
                         case ED_E:  fch += DIQALA_HAMS;   break;
                         default  :  fch += DIQALA_SADS; 
                                     ungetToken (form);
                                     break;
                       }
                     break;
          
                   default:  
                     ungetToken (form);
                     fch += formNumber;   /* no diacritic mark, restore value */   
                     if ( EdFidel[fch-UNIFIDEL].vowel != NOCH ) 
                          /*  I don't have a diacritic mark 
                           *  in the stream, but I do in the table.
                           *  this shouldn't happen with the hash buckets,
                           *  but if it does echo a warning 
                           */
                       {
                         fprintf (stderr, "ID Failure for ED for char 0x%02x with form 0x%02x (%c)\n", fch, form, form);
                       }
                     break;
                 }
             }
           else
             ungetToken (form);
         }
           break;
    }  /* end switch */


  return (fch);
#else
  return (1);
#endif /* COMPILE */
}




unsigned char*
UnicodeToEd ( fch )
  FCHAR fch;
{

unsigned char *returnCh = NULL, *holdCh = NULL;
FCHAR uch = fch;
int base;
char form;


/* Detect Errors Here */

  if ( UNIFIDEL <= fch && fch <= EXTLAST )
    fch -= UNIFIDEL;
  else if ( PRIVATE_USE_BEGIN <= fch && fch <= PRIVATE_USE_END )
    fch  = (UNITOTAL - 1) + (fch - PRIVATE_USE_END);
  else if ( fch > 0xff )  /* bail, we shouldn't be here */
    {
      returnCh = (unsigned char *) malloc ( 3 * sizeof(unsigned char) );
      returnCh[0] = (fch >> 8);
      returnCh[1] = (fch & 255);
      returnCh[2] = '\0';
      return ( returnCh );
    }
  else  /* no more than 8 bits */
    {
      returnCh = (unsigned char *) malloc ( 2 * sizeof(unsigned char) );
      returnCh[0] = (unsigned char) fch;
      returnCh[1] = '\0';
      return ( returnCh );
    }



/* We are clear of bad characters, return then requested Ed mapping */

  holdCh = (unsigned char *) malloc ( (6 + 1) * sizeof(unsigned char) );


  form = uch % 8;
  base = uch - form;

  if ( HAE <= base && base < MYA )                /*  Basic Range Syllables  */
    {
      if ( base == AE && (form == SADS || form == DIQALA) )
        strcpy ( holdCh, EdVowelHash[(fch/8)] );
      else if ( form != SADS )
        sprintf ( holdCh, "%s%s", EdFidelHash[(fch/8)], EdVowelHash[(int)form] );
      else
        strcpy ( holdCh, EdFidelHash[(fch/8)] );
    }
  else if ( WORDSPACE <= uch && uch <  ONE )                /*  Punctuation  */
    sprintf ( holdCh, "%s", EdPunctHash[(int)(uch%16)-1] );
  else if ( ONE <= uch && uch <= TENTHOUSAND )              /*  Numerals     */
    {
      if ( uch < TEN )
        sprintf ( holdCh, "%i", (uch - (ONE - 1)) );
      else if ( uch < HUNDRED )
        sprintf ( holdCh, "%i0",(HUNDRED - uch)  );
      else if ( uch == HUNDRED )
        strcpy ( holdCh, "100" );
      else
        strcpy ( holdCh, "100100" );
    }
  else switch ( uch )
    {
    	case MYA: strcpy ( holdCh, "mya" );
    	          break;
    	case RYA: strcpy ( holdCh, "rya" );
    	          break;
    	case FYA: strcpy ( holdCh, "fya" );
    	          break;
        default : /* if ( ORNAMENT <= uch && uch <= PRIVATE_USE_END )
                    strcpy ( holdCh, EdExtHash[uch-ORNAMENT+NUM_EXTENDED] );
                  else if ( QYAE <= uch && uch <= (QYAE+NUM_EXTENDED) )
                    strcpy ( holdCh, EdExtHash[uch-QYAE] );
                  else */
                    fprintf (stderr, "Ed: No Unicode mapping found.\n");
    	          break;
    }

  returnCh = (unsigned char*) malloc ( (strlen (holdCh) + 1) * sizeof(holdCh) );
  strcpy ( returnCh, holdCh );
  free ( (unsigned char*) holdCh );

  return ( returnCh );

}


char*
Ed_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (ED_EMAIL);
        break;
      case LETH_WWW:
        return (ED_WWW);
        break;
      case LETH_FTP:
        return (ED_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
