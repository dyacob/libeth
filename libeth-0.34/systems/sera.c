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
#include "sera.map"
#include "systems.h"
#include "etstdlib.h"
#include "etctype.h"


FCHAR
SERAToUnicode ( void )
{

int form = '\0', tick;
unsigned char mod = 0;
unsigned char gemination = '\0';
FCHAR base;
int holdState = 0;




rescan:
  base = ( (tick = lexer_pop()) == SERAHash[SERAALT - SERAHASHBASE] ) ? lexer_pop() : tick;


  if ( (FidelFlags->top->s == latin && tick != '\\') 
       || ( (FidelFlags->cstIn == html || FidelFlags->cstOut == html)
            && (FidelFlags->lexerState >= LEX_HTML_A) )
     )
    {
      if ( FidelFlags->lexerState == LEX_HTML_B && tick == ';' )
        FidelFlags->lexerState = false;
      if ( tick == SERAHash[SERAALT - SERAHASHBASE] )
        lexer_push ( base );            /* if we read 2 tokens return the 2nd */
      return ( tick );
    }
  else if ( base == SERASTOP )
    goto rescan;

  if ( tick == SERAHash[SERAALT - SERAHASHBASE] )
    {
      if ( isdigit ( base ) )
        {
          FidelFlags->lexerState = LEX_SERANUMBER;
          lexer_push ( base );
          return ( yylex() );  /* we need to make sure it starts in SERANUMBERS */
        }
      else if ( base == '!' )
        return ( TEMHERTESLAQ );
      else if ( base == '\'' )
        {
          if ( tick == '`' )
            return ( SOFTSADIS );
          else                       /* we know tick is either ` or ' */
            return ( GEMINATION );
        }
      else if ( base == '?' )
        {
          if ( !(FidelFlags->options & gQmark) )
             return ( SOSTNETEB );
           else
             return ( EQUESTIONMARK );
        }
      else if ( base == '|' )
        return ( SOSTNETEB );
      else if ( base == ':' )
        return ( WORDSPACE );
      else if ( (SERAALTHASHBASE <= base && base <= SERAALTHASHTOP) 
                && SERAAltHash[base - SERAALTHASHBASE] != NUL )
        base = SERAAltHash[base - SERAALTHASHBASE];
      else
        {
          lexer_push ( base );
          goto rescan;   /* we got a loose ` so trash it and start over */
        }

      if ( OAE <= base && base <= OAE + SABI )
        return ( base );

    }
  else if ( base == 0xab )
    return ( LEFTQUOTE );
  else if ( base == 0xbb )
    return ( RIGHTQUOTE );
  else if ( FidelFlags->lexerState == LEX_LPUNCT )
    {
      if ( ispunct ( base ) )
        return ( base );
      FidelFlags->lexerState = false;
      if ( (base < ' ') || (SERAHASHTOP < base) )  /* must be < ' ' */
        return ( base );
      base = SERAHash[base - SERAHASHBASE];
    }
  else if ( SERAHash[base - SERAHASHBASE] == SERAPUNCT )
    {
      holdState = FidelFlags->lexerState;
      FidelFlags->lexerState = LEX_FPUNCT;
      lexer_push ( base );
      base = yylex();
      FidelFlags->lexerState = ( holdState == LEX_VERBATIM )
                            ? holdState
                            : ( FidelFlags->lexerState >= LEX_HTML_A )
                              ? FidelFlags->lexerState
                              : false
                            ;
      
      if ( base == RESCAN )
        goto rescan;
      else
        return ( base );
    }
  else if ( isdigit( base ) && (FidelFlags->lexerState == LEX_SERANUMBER) )
    {
      lexer_push ( base );
      base = yylex();
      if ( base == RESCAN )
        goto rescan;
      else
        return ( base );
    }
  else if ( SERAHash[base - SERAHASHBASE] == SERAESCAPE )
    {
      if ( FidelFlags->lexerState == LEX_VERBATIM )
        {
          tick = '\0';
          if ( ((form = lexer_pop()) == '~' )
               && ((tick = lexer_pop()) == '!') )
            {
              if ( (form = lexer_pop()) != ' ' )
                lexer_push ( form );

              FidelFlags->lexerState = false;
              goto rescan;
            }
          else if ( tick )
            lexer_push ( tick );

          lexer_push ( form );
          return ( SERAESCAPE );
        }

      FidelFlags->lexerState = LEX_ESCAPES;
      base = yylex();

      if ( base == RESCAN )
        goto rescan;
      else
        return ( base );
    }
  else if ( base == '?' )
    {
      if (FidelFlags->options & gQmark)
        return ( SOSTNETEB );
      else
        return ( EQUESTIONMARK );
    }
  else if ( (SERAHASHTOP < base || base < ' ') 
            || SERAHash[base - SERAHASHBASE] == SAFEANSI 
            || isfpunct((base = SERAHash[base - SERAHASHBASE])) )
    return ( base );


  if ( FidelFlags->lexerState != LEX_VERBATIM )
    FidelFlags->lexerState = false;

  
  if ( tick == ' ' ) {
    if ( (form = lexer_pop()) == ':' )
      /* tick still holds unhashed base */
      {
        lexer_push (':');
        lexer_push (' ');
        holdState = FidelFlags->lexerState;
        FidelFlags->lexerState = LEX_FPUNCT;
        base = yylex();
        if ( base == RESCAN )
          base = (FCHAR)lexer_pop();   /* this will again be ' ' */
        FidelFlags->lexerState = ( holdState == LEX_VERBATIM ) ? holdState : false;
        return ( base );
      }
    else if ( (FidelFlags->options & gSpace)
              && !isdigit(form)
              && ( !ispunct(form)
                   || (form == '`' 
                        && ((SERAALTHASHBASE <= form && form <= SERAALTHASHTOP
                             && SERAAltHash[form - SERAALTHASHBASE] != NUL)
                             &&  form != '?' && form != '!' && form != ':')
                      )
                 )
            )
      {
         lexer_push (form);

         if ( FidelFlags->lastChar > SPACE
              || isspace ((char)FidelFlags->lastChar)
              || ( FidelFlags->lastChar < ANSI
                   && FidelFlags->lastPunct ) 
              || FidelFlags->lastChar == '\0'     /* at beginning of file */
            )
         return ' ';

         return WORDSPACE;
      }
    else
      {
        lexer_push (form);
        return (' ');
      }
  }

  if ( ( form = lexer_pop() ) == '\'' )
    {
      if ( (gemination = lexer_pop()) == '\'' )
        lexer_push ( form );
      lexer_push ( gemination );
    }

  if ( AE <= base && base <= AE + SABI )
    {
      if ( form == '2' )
        {
          if ( base == AE && tick == 'a' )
            base += RABI;
          return (base + (OAE-AE));
        }


      if ( base == AE )
        {
          if ( form == 'a' && tick == 'e' )  /* don't confuse ea = aa */
            return (AE + DIQALA);
          else if ( FidelFlags->top->l == tir && tick == 'a' )
            base += RABI;
        }

      if ( form != SERASADS )
        lexer_push ( form );

      return ( base );
    }
  else if ( form == '2' ) {
         if ( (SERAALTHASHBASE <= tick && tick <= SERAALTHASHTOP) 
              && SERAAltHash[tick - SERAALTHASHBASE] != NUL )
           {
             base = SERAAltHash[tick - SERAALTHASHBASE];
             form = lexer_pop();
           }
         else
           {
             lexer_push ( form );
             return ( base );
           }
       }

  switch ( form )
    {
      case SERAGIZ    :  break;
      case SERAKAIB   :  base += KAIB; break;
      case SERASALS   :  base += SALS; break;
      case SERARABI   :  base += RABI; break;
      case SERAHAMS   :  base += HAMS; break;
      case SERASABI   :  base += SABI; break;
      case SERAYA     :  if ( base != MAE && base != RAE && base != FAE )
                           {
                             lexer_push ( form );
                             break;
                           }
                         if ( (form = lexer_pop()) != 'a' )
                           {
                               lexer_push ('Y');
                               lexer_push ('a');
                               break;
                           }
                         base = ( base == MAE ) ? MYA  
                              : ( base == RAE ) ? RYA
                              :  FYA
                              ;
                         break;

      case SERADIQALA :  if ( base == HAE )
                           base = HZAE;
                         else if ( base == TSZAE)
                           base = TSAE;
                         if ( (mod = get_fmodulo(base)) == 8 )
                           {
                              if ( (form = lexer_pop()) != 'a' )
                                lexer_push ( form );
                              base += DIQALA;
                           }
                         else if ( mod == 12 )
                           switch ( (form = lexer_pop()) )
                            {
                              case 'e' : base = set_formNumber ( base, DIQALA_GIZ  ); break;
                              case 'i' : base = set_formNumber ( base, DIQALA_SALS ); break;
                              case 'a' : base = set_formNumber ( base, DIQALA_RABI ); break;
                              case 'E' : base = set_formNumber ( base, DIQALA_HAMS ); break;
                              case 'u' : 
                              case '\'': base = set_formNumber ( base, DIQALA_SADS ); break;
                              default  : base = set_formNumber ( base, DIQALA_SADS ); 
                                         lexer_push ( form );
                                         break;
                            }
                         else 
                           lexer_push ( form );
                         break;

      default  :  base += SADS;
                  if ( form != SERASADS )
                    lexer_push ( form );
                  break;
    }


  return ( base );

}



unsigned char*
_UnicodeToSERA ( fch, mylflags )
  FCHAR fch;
  LibEthFlags* mylflags;
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



/* We are clear of bad characters, return then requested SERA mapping */

  holdCh = (unsigned char *) malloc ( (6 + 1) * sizeof(unsigned char) );


  form = uch % 8;
  base = uch - form;

  if ( HAE <= base && base < MYA )                /*  Basic Range Syllables  */
    {
      if ( base == AE )
        {
          if ( uch == AE && mylflags->out->l == amh )
            strcpy ( holdCh, "a" );
          else if ( uch == AE+RABI && mylflags->out->l == amh )
            strcpy ( holdCh, "A" );
          else if (form == DIQALA)
            strcpy ( holdCh, "ea" );
          else
            strcpy ( holdCh, SERAVowelHash[(int)form] );
        }
      else if ( base == OAE )
        sprintf ( holdCh, "`%s", SERAVowelHash[(int)form] );
      else if ( form != SADS )
        sprintf ( holdCh, "%s%s", SERAFidelHash[(fch/8)], SERAVowelHash[(int)form] );
      else
        strcpy ( holdCh, SERAFidelHash[(fch/8)] );
    }
  else if ( SPACE <= uch && uch <  ONE )                    /*  Punctuation  */
    sprintf ( holdCh, "%s", SERAPunctHash[(int)(uch%16)] );
  else if ( ONE <= uch && uch <= TENTHOUSAND )              /*  Numerals     */
    {
      if ( uch < TEN )
        sprintf ( holdCh, "`%i", (uch - (ONE - 1)) );
      else if ( uch < HUNDRED )
        sprintf ( holdCh, "`%i0", (uch - (TEN - 1)) );
      else if ( uch == HUNDRED )
        strcpy ( holdCh, "`100" );
      else
        strcpy ( holdCh, "`10000" );
    }
  else switch ( uch )
    {
    	case MYA: strcpy ( holdCh, "mYa" );
    	          break;
    	case RYA: strcpy ( holdCh, "rYa" );
    	          break;
    	case FYA: strcpy ( holdCh, "fYa" );
    	          break;
        default : if ( ORNAMENT <= uch && uch <= PRIVATE_USE_END )
                    strcpy ( holdCh, SERAExtHash[(uch-ORNAMENT+NUM_EXTENDED)] );
                  else if ( QYAE <= uch && uch <= (QYAE+NUM_EXTENDED) )
                    strcpy ( holdCh, SERAExtHash[uch-QYAE] );
                  else
                    fprintf (stderr, "SERA: No Unicode mapping found.\n");
    	          break;
    }

  returnCh = (unsigned char*) malloc ( (strlen (holdCh) + 1) * sizeof(holdCh) );
  strcpy ( returnCh, holdCh );
  free ( (unsigned char*) holdCh );

  return ( returnCh );

}


unsigned char
SERA_isGoodANSI ( fch )
  FCHAR fch;
{


  if ( fch >= ANSI )
    return ( false );

  if ( fch <= 0x20 )
    return ( (unsigned char)fch );

  switch ( fch )
    {
      case ':' :
      case ',' :
      case ';' :
      case '\'':
      case '`' :
      case '\\' :
        return ( false );
        break;

      default:
        return ( (unsigned char)fch );
    }


  return ( false );

}


char*
SERA_get_netInfo (INFO)
  char INFO;
{

  switch (INFO)
    {
      case LETH_EMAIL:
        return (SERA_EMAIL);
        break;
      case LETH_WWW:
        return (SERA_WWW);
        break;
      case LETH_FTP:
        return (SERA_FTP);
        break;
      default:
        break;
    }

  return (NULL);

}
