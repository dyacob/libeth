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

%{
/*
**  Note, this is a char stream scanner for SERA developed for the libeth
**  project.  The routines here are neither robust nor thoroughly tested.
**  Reporting compilation and run problems to facilitators at Admas Concepts
**  will assist libeth development.  The routines in this module are only
**  those that would need to access f/lex specific entities.
**
*/

/*
**  Lex has a default option of 300 positions for a given state. Since this
**  filter handles 412 characters of Fidel, the Fidel ``state'' is broken into
**  two for transportability.
**
**  The original output default was to be Unicode, however since Fidel
**  extensions for Unicode have been postponed for the time being, the
**  default output is set for Junet which can handle the full set.  A 
**  Unicode mapping table is then required and found in ``fidel.map''.
**
**  Considerations for Flex:  Primarily LATIN, GREEK and other script states
**  could be made exclusive with %x declarations. FIDEL, could then be 
**  eliminated as it would be the default initial state.  Flex specific
**  code is found between #if(n)def FLEX_SCANNER .... #endif .
**
**  Lex does not read reliably between multiple open input streams reliably.
**  Flex solves this deficiency of Lex.  For portability and consistant
**  operation of the library functions on all platforms, we can not exceed
**  any of the Lex capabilities in Flex.
*/


#include "fidel.h"
#include "etstdlib.h"
#include "etstdio.h"
#include "etmath.h"
#include "lethutil.h"
#include "sysinfo.h"
#ifdef SUPPORT_GREEK
#  include "greek.h"
#endif /* SUPPORT_GREEK */

#define NEWSTATE FidelFlags->top->s

#define RESCAN 0xFFFF

/* these next three are required for using lex with strings instead of files */

#if __STDC__ || WIN32
  int my_yyinput ( char* buf,int max_size );
  void lexer_push ( int c );
  void lexer_reset ( LibEthFlags* lethFlags );
#else
  int my_yyinput ();
  void lexer_push ();
  void lexer_reset ();
#endif /* __STDC__ || WIN32 */


int lexer_pop ();
int change_state ();


#ifdef FLEX_SCANNER                 /* if we are using flex */
#  define YY_READ_BUF_SIZE 1        /* read one char at a time like lex */
#  undef YY_INPUT
#  define YY_INPUT(buf, result, max) (result = my_yyinput(buf, max))
#else                               /*    we are using lex */
#  undef input
#  undef unput
#endif  /* FLEX_SCANNER */

#ifdef NO_LIBL
#  undef yywrap
#endif /* NO_LIBL */


extern LibEthFlags* FidelFlags;   /* in etstdlib.c */

extern LS LnS[];

enum Languages newLang;

extern FILE* iofp;

static FCHAR tempCh = 0;
static unsigned long int top = 0;  /* top keeps track of the read-end of iostring */

/*
 * Legacy stuff to remove later after lex testing.
 *
   Punct [-!"#$%&'()*+,./:;<=>?\[\]^_`{|}]
   %e 3670
   %n 680
   %p 6500
   %a 2010
 */
%}


%s GREEK SERANUMBER ESCAPES FPUNCT LPUNCT GLYPHS DEFAULT LANG POP VERBATIM HTML_A HTML_B SERA_OFF

punct [-!"#$%&'()*+,./:;<=>?\[\\\]^_`{|}~]
notpunct [^\-!"#$%&'()*+,./:;<=>?\[\\\]^_`{|}~]
white [ \n\t\r]
White [ \n\t\r\\]
NotWhite [^ \n\t\r\\]
langs   (am[h]?|ti[r]?|g[e]?z|la[t]?|en[g]?|gre|el)
defaults ((`[?|:])|-:)
glyphs (a|e|A|E|X)

%%
%{

   yyin = iofp;

   if (FidelFlags->lexerState)
     BEGIN (FidelFlags->lexerState);
   else
     BEGIN (change_state());  /* make a language specific change */

%}


%{ 
      /* Standard SERA Defined Escapes */
%}

<POP,HTML_B,SERA_OFF>.|\n       { return ( 0x00ff & yytext[0] ); }

<ESCAPES>(<|{notpunct})  { 
              FidelFlags->lexerState = false;
              if ( FidelFlags->top == FidelFlags->minor )
                FidelFlags->top = FidelFlags->major;
              else   /* 
                     ** we are returning from a \~lang escape 
                     ** and switches are one cycle out of phase
                     */
                FidelFlags->top = FidelFlags->minor;

              if ( yytext[0] != ' ' )  /* preserve returns and tabs   */
                yyless(yyleng-1);

              return RESCAN;
            }
<ESCAPES>~#-?([0-9]+){White}?  {
                     yyless ( yyleng-1 );
                     FidelFlags->holdChars = arabtof ( &yytext[2] );
                     tempCh = FidelFlags->holdChars[0];
                     if ( !FidelFlags->holdChars[1] )
                       {
                         free ( FidelFlags->holdChars );
                         FidelFlags->holdChars = NULL;
                       }

                     FidelFlags->holdChars[0] = 1;
                     return tempCh;
                   }
<ESCAPES>~!{White}? {
              FidelFlags->lexerState = VERBATIM;

              if ( yytext[yyleng-1] != ' ' )  /* preserve returns and tabs  */
                yyless(yyleng-1);
              return RESCAN;
            }

%{ 
      /* SERA Special Escapes */
%}

<ESCAPES>~{glyphs}{White}? {
              yyless(1); 
              BEGIN GLYPHS; 
            }
<ESCAPES>~{defaults}{White}? { 
                        yyless(1); 
                        BEGIN DEFAULT; 
                      }
<ESCAPES>~{langs}(~{langs})?{White}? { 
                                 FidelFlags->top = NULL;
                                 FidelFlags->lexerState = LANG;
                                 yyless(1);
                                 BEGIN LANG;
                               }
<ESCAPES>~{White}  { return RESCAN; }
%{ 
      /* Application Defined Escapes */
%}

<GLYPHS>X{White}?  {
                     if ( FidelFlags->top->s != fidel )
                       REJECT;
                     if ( yytext[yyleng-1] != ' ' )  /* preserve returns and tabs */
                       yyless(yyleng-1);
                     return ORNAMENT;
                   }
<GLYPHS>e{White}?  {
                     if ( FidelFlags->top->s != fidel )
                       REJECT;
                     if ( yytext[yyleng-1] != ' ' )  /* preserve returns and tabs */
                       yyless(yyleng-1);
                     return FIDELLAND;
                   }
<GLYPHS>E{White}?  {
                     if ( FidelFlags->top->s != fidel )
                       REJECT;
                     if ( yytext[yyleng-1] != ' ' )  /* preserve returns and tabs */
                     yyless(yyleng-1);
                     return INVFIDELLAND;
                   }
<GLYPHS>a{White}?  {
                     if ( FidelFlags->top->s != fidel )
                       REJECT;
                     if ( yytext[yyleng-1] != ' ' )  /* preserve returns and tabs */
                       yyless(yyleng-1);
                     return AFRICA;
                   }
<GLYPHS>A{White}?  {
                     if ( FidelFlags->top->s != fidel )
                       REJECT;
                     if ( yytext[yyleng-1] != ' ' )  /* preserve returns and tabs */
                       yyless(yyleng-1);
                     return INVAFRICA;
                   }

%{ 
      /* Special SERA Defined Default Escapes */
      /* Check the performance on this, it is probably not useful to have a
          state with a single cycle... */
%}



<DEFAULT>`:{White}?   { 
                  if ( yytext[yyleng-1] != ' ' )  /* preserve returns */
                    yyless(yyleng-1);
                  FidelFlags->options &= ~gColon; 
                  return RESCAN;
                }
<DEFAULT>-:{White}?   { 
                  if ( yytext[yyleng-1] != ' ' )  /* preserve returns */
                    yyless(yyleng-1);
                  FidelFlags->options |= gColon; 
                  return RESCAN;
                }
<DEFAULT>`"?"{White}?  { 
                  if ( yytext[yyleng-1] != ' ' )  /* preserve returns */
                    yyless(yyleng-1);
                  FidelFlags->options &= ~gQmark; 
                  return RESCAN;
                }
<DEFAULT>`"|"{White}? { 
                  if ( yytext[yyleng-1] != ' ' )  /* preserve returns */
                    yyless(yyleng-1);
                  FidelFlags->options |= gQmark; 
                  return RESCAN;
                }

%{ 
      /* Special SERA Defined Language Escapes */
%}

<LANG>am[h]?(~|{White})?   { newLang = amh; REJECT; }
<LANG>ti[r]?(~|{White})?   { newLang = tir; REJECT; }
<LANG>la[t]?(~|{White})?   { newLang = lat; REJECT; }
<LANG>en[g]?(~|{White})?   { newLang = eng; REJECT; }
<LANG>g[e]?z(~|{White})?   { newLang = gez; REJECT; }
<LANG>(gre|el)(~|{White})? { newLang = gre; REJECT; }
<LANG>{langs}(~|{White})?  { 
              if ( isspace(yytext[yyleng-1]) && yytext[yyleng-1] != ' ' )
                yyless(yyleng-1);          /* eat spaces, keep returns */

              if (FidelFlags->top == NULL)
			    {
                  FidelFlags->top =& LnS[newLang];
                  if ( yytext[yyleng-1] == '~' )
                    {
                      FidelFlags->minor = NULL;
                      BEGIN LANG;
                    }
                  else
                    {
                      FidelFlags->lexerState = false;
                      return RESCAN;
                    }
			    }
              else if (FidelFlags->minor == NULL)  /* our 2nd time through */
                {                                 /* from a ~lang~lang    */
                  FidelFlags->major =  FidelFlags->top;
                  FidelFlags->minor =& LnS[newLang];
                  FidelFlags->lexerState = false;
                  return RESCAN;
			    }
            }
<LANG>.|\n  { 
              yyless(0); 
              FidelFlags->lexerState = false;
              return RESCAN;
            }
%{
            /* Unknown escape request follows \~ .  Treat accordingly. */
%}

<ESCAPES>~({NotWhite}*){white}?  { 
							/* ignore, we don't know what it is */ 
                            if ( yytext[yyleng-1] == '\n' 
							     || yytext[yyleng-1] == '\t'
								 || yytext[yyleng-1] == '\r')
                              yyless(yyleng-1);
                             
		                  }

%{
            /* Punctuation Toggle Cotrols */
%}

<ESCAPES>{punct} {
            if ( NEWSTATE != fidel || (FidelFlags->cstIn == html && yytext[1] == '<') )
               REJECT;
            yyless(0);
            FidelFlags->lastPunct  = true;
            FidelFlags->lexerState = LPUNCT;
           
            BEGIN FidelFlags->lexerState;
          }

<LPUNCT,FPUNCT>{notpunct}  {
                             yyless(0);
                             FidelFlags->lexerState = false;
                             FidelFlags->lastPunct  = false;
                             return RESCAN;
                           }

%{
		/* Fidel Punctuation */
%}

<FPUNCT>:-     {return PREFACECOLON;}
<FPUNCT>-:     {return COLON;}
<FPUNCT>::     {return FULLSTOP;}

<FPUNCT>[ ]?:[^\-|:0-9] {  /* Escaping hyphen makes SGU Lex 1.4 happy... */
                         if ( !(FidelFlags->options & gColon) )
                           {
                             if ( yytext[0] != ' '
                                  && ( '0' < FidelFlags->lastChar 
                                      && FidelFlags->lastChar < '9' ) )
                               {
                                 yyless(yyleng-1);
                                 return ':';
                               }

                             if ( !( yytext[yyleng-1] == ' ' && yytext[yyleng-2] != ' ') )
                               yyless(yyleng-1);

                             return WORDSPACE;
                           }
                         else
                           {
                             if (yyleng == 1)
                               return COLON;
  
                             if (yyleng == 2) {
                               if (yytext[1] == ':')
                                 {
                                   yyless(1);
                                   return ' ';
                                 }
                               else
                                 {
                                   yyless(1);
                                   return COLON;
                                 }
                             }

                             if (yyleng == 3)
                               {
                                 yyless(1);
                                 return ' ';
                               }
                           }
                       }

<FPUNCT>:"|":  {return PARAGRAPH;}
<FPUNCT><<     {return LEFTQUOTE;}
<FPUNCT>>>     {return RIGHTQUOTE;}


%{
		/* Ethiopic Numbers, Also Universal */
%}


<SERANUMBER>1?(0000)+       { if (yytext[0] == '1')
                                yyless(5);
                              else
                                yyless(4);
                              return (TENTHOUSAND);
                            }
<SERANUMBER>[1-9]0(00)*     { if (yyleng > 2)
                                yyless(2); 
                              return (TEN + yytext[0]-'1');
                            }
<SERANUMBER>[2-9](00)*      {yyless(1); return (ONE + yytext[0]-'1');}
<SERANUMBER>1?(00)*         {
                              if (yyleng == 1)
                                return (ONE);
                              else 
                                {
                                  if (yytext[0] == '1')
                                    yyless(3);
                                  else
                                    yyless(2);
                                  return (HUNDRED);
                                }
                            }


<SERANUMBER>[^0-9]     { fprintf (stderr, "\nPutting Back %s\n", yytext);
                         yyless(0); 
                         FidelFlags->lexerState = false;
                         return RESCAN;
                       }


%{
		/* Greek Simple Mapping */
%}

<GREEK>[a-zA-Z] {
#ifdef SUPPORT_GREEK
                  FidelFlags->lastPunct = false;
                  return (yytext[0] + GREEKBASE);
#endif /* SUPPORT_GREEK */
                }


%{
		/* Simple HTML Control -ignore everything between < > & and ; */
%}

"<"[/]?[Hh][Tt][Mm][Ll]  {
                       FidelFlags->cstIn = (yyleng == 6) ? plain : html; 
                       FidelFlags->lexerState = SERA_OFF;
                       yyless (1);
                       return '<';
                     }

<HTML_A>[^>]  {return ( 0x00ff & yytext[0] );}
<HTML_A>>  {
             FidelFlags->lexerState = false;
             return '>';
           }

"<"        {
             if (FidelFlags->cstIn == html)
               FidelFlags->lexerState = HTML_A;

               return '<';
           }

%{ /*
<HTML_B>[^;]  {return ( 0x00ff & yytext[0] );}
<HTML_B>;  {
             FidelFlags->lexerState = false;
             return ';';
           }
  */
%}
&          {
             if (FidelFlags->cstIn == html)
               FidelFlags->lexerState = HTML_B;

             return '&';
           }

"<"[/]?[Ss][Ee][Rr][Aa]">"  {
                          if (FidelFlags->cstIn == html) 
                            {
                              if (yyleng == 7)
                                {
                                  FidelFlags->lexerState = SERA_OFF;
                                  if ( isFidelTrueType ( FidelFlags->csOut ) )
                                    {
                                     /* this is done for doctypes/html.c
                                      * which is looking for </sera>
                                      * we could return here </font> but
                                      * it would still be necessary for
                                      * doctypes/html.c to catch the </font>
                                      * and adjust the nestlevel count
                                      */
                                      yyless (1);
                                      return '<';
                                    }
                                  else
                                    BEGIN SERA_OFF;
                                }
                              else
                                {
                                  FidelFlags->lexerState = false;
                                  FidelFlags->top = FidelFlags->major;
                                  BEGIN INITIAL;
                                }
                            }
                           else
                            {
                              yyless (1);
                              return '<';
                            }
                        }

%{
		/* Anything Else... ...Just Kick It Out */
%}

{punct}   {
            FidelFlags->lastPunct = true;
            return ( 0x00ff & yytext[0] );
          }
%{
        /* To Enable DOS support replace / and * below with % and } */
/*

"\r"      {
            if ( FidelFlags->xferIn != TextDOS ) 
              return ( 0x00ff & yytext[0] );
          }
\n        {
            if ( FidelFlags->xferOut == TextDOS ) 
              {
                yyless(0);
                FidelFlags->xferOut =-  TextDOS ;
                return  '\r';
              }
            if ( FidelFlags->xferOut == -TextDOS ) 
              FidelFlags->xferOut = TextDOS ;
            return ( 0x00ff & yytext[0] );
          }
*/
          /* For DOS support, replace * and / above with % and { */
%}

.|\n      {
            FidelFlags->lastPunct = false;
            return ( 0x00ff & yytext[0] );
          }

%%



/*
**  Simple state changer code required at yylex entry. 
**  Lex may provide a better facility for accomplishing 
**  the same.
*/


int 
change_state()
{

  switch (NEWSTATE)
    {
      case latin:   fprintf (stderr, "LEXER ERROR:  State \"LATIN\" no longer supported in change_state()\n");
                    break;
#ifdef SUPPORT_GREEK
      case greek:  return GREEK;
#endif /* SUPPORT_GREEK */

/*   the code should never below this point.
 *   but lets make lint happy and add these cases anyway...
 */
      case fidel:  
      case special: 
      default:      fprintf (stderr, "LEXER ERROR:  State \"FIDEL\" no longer supported in change_state()\n");
                    break;
    }


/* we shouldn't get here either... */

  return POP;

}


/*
**  input and unput are required to get lex working with strings instead  
**  of files.  These code segments are from ``lex & yacc'' by John Levine,
**  et al pages 40 - 41.
*/



#ifdef FLEX_SCANNER
int
my_yyinput (buf, max_size)
  char* buf;
  int max_size;
{

unsigned long int n;


  if (FidelFlags->stringTop != NULL) /*  we are working with a string 
                                      *  DO NOT try : if (yyin == NULL)
                                      *  Flex defaults yyin to stdin when NULL
                                      */
    {
      if ( !FidelFlags->stringTop[top] )
        return (YY_NULL);

      n = strlen(FidelFlags->stringTop); 
      if ( (n-top) >= YY_BUF_SIZE)
        n = YY_BUF_SIZE;
      else if ( n >= YY_BUF_SIZE )
        n -= top;
                              /*  These above five lines may be less elegant
                               *  than what is commented out.  But, it seems
                               *  to accomplish the same and doesn't bone up
                               *  YY_READ_BUF_SIZE is set to 1.  It will 
                               *  crash for strings of size > YY_BUF_SIZE
                               *  with out the size check.
                               *
                               *  For now use this, and figure it out later.
                               */
      if (n > 0)
        {
          memcpy (buf, &FidelFlags->stringTop[top], n);
          top += n;
        }
      else
        top = 0;
   
      return ( (top) ? n : YY_NULL ); 
    }
  else              /* we are working with a file, use original Flex YY_INPUT */
    {
      if ( yy_current_buffer
           && yy_current_buffer->yy_is_interactive )       /* if yyin = stdin */
        { 
          int c = '*'; 
          for ( n = 0; n < max_size
                && (c = getc( yyin )) != EOF && c != '\n'; ++n ) 
            buf[n] = (char) c; 
          if ( c == '\n' ) 
            buf[n++] = (char) c; 
          if ( c == EOF && ferror( yyin ) ) 
            YY_FATAL_ERROR( "input in flex scanner failed" ); 
        } 
      else if ( ((n = fread( buf, 1, max_size, yyin )) == 0) 
                && ferror( yyin ) ) 
             YY_FATAL_ERROR( "input in flex scanner failed" );
      return n; 
    }
}

#ifdef NO_LIBL
int
yywrap()
{
  return ( 1 );
}
#endif  /* NO_LIBL */

#else  /* LEX SCANNER */

int
input()
{


  if (FidelFlags->stringTop != NULL)      /* we are working with a string */
    {
      if (FidelFlags->stringTop[top] == '\0') { 
         top = 0;
         return(0);  /* EOF */
      }
      return (FidelFlags->stringTop[top++]);
    }
  else   /* we are working with a file, use original Lex input */
    return (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar);

}


void
unput (ch)
  int ch;
{


  if (yyin == NULL)     /* we are working with a string */
    {
      if (ch == 0)
        return;
      if (top) 
        {
          top--;
          return;
        }
    }
  else                  /* we are working with a file, use original Lex unput */
    {
      yytchar = (ch);
      if (yytchar == '\n')
        yylineno--;
      *yysptr++ = yytchar;
    }

  return;

}
#endif  /* FLEX_SCANNER */


#ifndef FLEX_SCANNER
/*
 *  I don't know what this is anymore...
 *
 */
FCHAR
fidel_flush (fp, mylflags)
  FILE* fp;
  LibEthFlags* mylflags;
{

char* pch=NULL;
int i,j;
FCHAR fch;

  if ( fp == NULL )                        /* bail if pointing nowhere */
    return ( _LET_FAIL );
  mylflags = checkLibEthFlags ( mylflags );

  if ( *yysptr == NULL )
    return 0;

  pch = yysptr;

  while ( *pch++ )
    i++;

  pch = (char *) malloc ( (i+1) * sizeof (char) );

  while ( *yysptr++ )
    pch[i-j] = *yysptr;

  pch[i] = '\0';

  fch = get_fchar (fp, mylflags);

  return ( fch );

}

yywrap()
{

  while ( *yysptr++ );

  return ( EOF );

}
#endif  /* !FLEX_SCANNER */



/*  The following are interfaces to f/lex to grab or return an untokenized
 *  char without breaking anything.  lexer_pop in particular is slower than
 *  optimal but works with both lex and flex nuetrally.  To increase 
 *  performance here would mean accessing flex internals which may not be
 *  portable across versions.
 */
int
lexer_pop ()
{
int lastState = FidelFlags->lexerState;
int c;


  FidelFlags->lexerState  =  ( FidelFlags->lexerState >= HTML_A )
                          ?  FidelFlags->lexerState
                          :  POP
                          ;
  c = yylex();
  FidelFlags->lexerState  =  ( FidelFlags->lexerState >= HTML_A )
                          ?  FidelFlags->lexerState
                          :  ( lastState >= HTML_A )
                             ?  false
                             :  lastState
                          ;
  return ( c );
}


void
lexer_push (c)
  int c;
{
  unput(c);
}


void
lexer_reset ( LibEthFlags* mylflags )
{

  if ( top )
    {
      yy_delete_buffer ( YY_CURRENT_BUFFER );
      yy_start = mylflags->lexerState = INITIAL;
      yy_init = 1;
      top = 0;
    }
}
