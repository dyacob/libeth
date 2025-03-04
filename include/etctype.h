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

#ifndef ETCTYPE_H
#define ETCTYPE_H  1

#include "libeth.h"

#if __STDC__ || WIN32


/*
**  ctype functions
*/

boolean isfidel ( FCHAR fchar );

boolean isfdigit ( FCHAR fchar );

boolean isflnum ( FCHAR fchar );

boolean isethiopic ( FCHAR fchar );

boolean isethiopicdefined ( FCHAR fchar );

boolean isfamily ( FCHAR fchar1, FCHAR fchar2 );

boolean isEquiv ( FCHAR A, FCHAR B, enum Languages lang );

boolean isfpunct ( FCHAR fchar );

boolean isfspace ( FCHAR fchar );

boolean isfprint ( FCHAR fchar );

boolean isfcntrl ( FCHAR fchar );

boolean isfgraph ( FCHAR fchar );

boolean isprivate ( FCHAR fchar );

boolean isRedTerm ( FCHAR* fstring, LibEthFlags* mylflags );

/*
**  other token id, setting and sorting utils
*/

int get_fmodulo ( FCHAR fchar );

int get_formNumber ( FCHAR fchar );

int set_formNumber ( FCHAR fchar, int newForm );

int get_formOffset ( FCHAR fchar );

int get_traditional ( int trad, FCHAR* uni );

FCHAR get_traditional_series ( int trad, int syllable ); 

FCHAR* get_fidel_oli ( int item );




#else  /* we do not have ANSI C */


/*
**  ctype functions
*/

boolean isfidel  ();

boolean isfdigit ();

boolean isflnum  ();

boolean isethiopic ();

boolean isethiopicdefined ();

boolean isfamily ();

boolean isfpunct ();

boolean isfspace ();

boolean isfprint ();

boolean isfcntrl ();

boolean isfgraph ();

boolean isprivate();

#endif /* __STDC__ || WIN32 */

#endif /* ifndef ETCTYPE_H */
