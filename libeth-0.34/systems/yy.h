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

#ifndef YY_H
#define YY_H 1

#if __STDC__ || WIN32
  extern int yylex(void);
  extern void lexer_push ( int c );
#else
  extern int yylex();
  extern void lexer_push ();
#endif /* __STDC__ || WIN32 */

extern int  lexer_pop ();
extern void lexer_flush ();
extern LibEthFlags* FidelFlags;   /* in etstdlib.c */

extern FILE* iofp;
extern unsigned char* iostring;


#define LEX_GREEK 1
#define LEX_SERANUMBER 2
#define LEX_ESCAPES 3
#define LEX_FPUNCT 4
#define LEX_LPUNCT 5
#define LEX_GLYPHS 6
#define LEX_DEFAULT 7
#define LEX_LANG 8
#define LEX_POP 9
#define LEX_VERBATIM 10
#define LEX_HTML_A 11
#define LEX_HTML_B 12
#define LEX_SERA_OFF 13
#define RESCAN 0xFFFF

#endif /* YY_H */
