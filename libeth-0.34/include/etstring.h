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

#ifndef ETSTRING_H
#define ETSTRING_H  1

#include <string.h>
#include "libeth.h"


/*
**  We use a bitmap to handle all of the comparison types for Ethiopic strings. 
**  LETHC = "LibEth Comparison"
*/
#define LETHC_EXACT    0    /* default, all bits same        */
#define LETHC_FAMILY   1    /* fold forms le = lu = li = ... */
#define LETHC_PHONETIC 2    /* `se = se, he = `he, etc       */
#define LETHC_HEHA     4    /* amharic fold he = ha          */
#define LETHC_EA       8    /* amharic fold  e = a           */
#define LETHC_QUKUGU  16    /* gWu = gu, kWu = ku, qWu = qu  */
#define LETHC_QOKOGO  32    /* gWe = go, kWe = ko, qWe = qo  */
#define LETHC_WAdown  64    /* fold Wa unto wa               */
#define LETHC_WAup   128    /* fold wa unto Wa               */
#define LETHC_NETEB  256    /* fold : onto ' '               */
#define LETHC_ALL    LETHC_FAMILY | LETHC_PHONETIC | LETHC_HEHA | LETHC_EA | LETHC_QUKUGU | LETHC_QOKOGO | LETHC_WAdown | LETHC_NETEB 
/*
**  Some southern languages (wellaitigna?) will also fold le = la
**  and perhaps be = ba
*/



#if __STDC__ || WIN32


/*
**  string manipulation
*/

int fidel_strcpy ( FCHAR* target, FCHAR* fstring );

int fidel_strncpy ( FCHAR* target, FCHAR* fstring, int n );

FCHAR* fidel_strcat ( FCHAR* target, FCHAR* fstring );

FCHAR* fidel_strncat ( FCHAR* target, FCHAR* fstring, int n );

size_t fidel_strlen ( FCHAR* fstring );

int fidel_fstrcmp ( FCHAR* string1, FCHAR* string2 );

int fidel_fstrncmp ( FCHAR* string1, FCHAR* string2, int n );

int fidel_strcmp ( FCHAR* string1, char* string2 );

int fidel_strncmp ( FCHAR* string1, char* string2, int n );



/*
**  string and character matching functions
*/

FCHAR* fidel_lcss ( FCHAR* haystack, FCHAR* needle );

FCHAR* fidel_strchr ( FCHAR* fstring, FCHAR fch );

FCHAR* fidel_strrchr ( FCHAR* fstring, FCHAR fch );

FCHAR* fidel_memchr ( FCHAR* fstring, FCHAR fch, int n );

FCHAR* fidel_strstr ( FCHAR* haystack, FCHAR* needle );

FCHAR* fidel_strtok ( FCHAR* fstring, FCHAR* fchars );

int fidel_strspn ( FCHAR* fstring, FCHAR* fchars );

FCHAR* fidel_strpbrk ( FCHAR* fstring, FCHAR* fchars );

int fidel_strcspn ( FCHAR* fstring, FCHAR* fchars );

FCHAR* fidel_syllabic_strchr ( FCHAR* fstring, FCHAR fch, enum Languages lang, unsigned int REQUEST ); 

FCHAR* fidel_syllabic_strrchr ( FCHAR* fstring, FCHAR fch, enum Languages lang, unsigned int REQUEST );

FCHAR* fidel_syllabic_memchr ( FCHAR* fstring, FCHAR fch, int n, enum Languages lang, unsigned int REQUEST );

int fidel_syllabic_fstrcmp ( FCHAR *fstring1, FCHAR *fstring2, enum Languages lang, unsigned int REQUEST );

FCHAR* fidel_syllabic_lcss  ( FCHAR *fstring1, FCHAR *fstring2, enum Languages lang, unsigned int REQUEST );

int fidel_syllabic_fstrncmp ( FCHAR* fstring1, FCHAR* fstring2, int n, enum Languages lang, unsigned int REQUEST );

FCHAR* fidel_syllabic_strstr ( FCHAR* haystack, FCHAR* needle, enum Languages lang, unsigned int REQUEST );

FCHAR* fidel_syllabic_strtok ( FCHAR* fstring, FCHAR* fchars, enum Languages lang, unsigned int REQUEST );

int fidel_syllabic_strspn ( FCHAR* fstring, FCHAR* fchars, enum Languages lang, unsigned int REQUEST );

FCHAR* fidel_syllabic_strpbrk ( FCHAR* fstring, FCHAR* fchars, enum Languages lang, unsigned int REQUEST );

int fidel_syllabic_strcspn ( FCHAR* fstring, FCHAR* fchars, enum Languages lang, unsigned int REQUEST );

FCHAR* fidel_syllabic_simplify ( FCHAR* fstringIn, enum Languages lang, unsigned int REQUEST, int** changeList );

#define fidel_simplify( fstring, lang, REQUEST ) fidel_syllabic_simplify( fstring, lang, REQUEST, NULL )

#else  /* we do not have ANSI C */


/*
**  string manipulation
*/

int fidel_strcpy  (); 

int fidel_strncpy ();

int fidel_strcat  ();

int fidel_strlen  ();

int fidel_strcmp  ();

int fidel_strcmp  ();

#endif /* __STDC__ || WIN32 */

#endif /* ifndef ETSTRING_H */
