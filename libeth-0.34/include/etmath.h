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

#ifndef ETMATH_H
#define ETMATH_H 1

#include <math.h>
#include "libeth.h"

#if __STDC__ || WIN32

/*
**  Numeric and Other utilities
*/

int ftoi ( FCHAR* fstring );

FCHAR* arabtof ( char* number );

char* arabtoeth ( long int number, int reduction );

FCHAR* itof ( int iNumber );

FCHAR* AddEthiopicEthiopic ( FCHAR *A, FCHAR *B );

FCHAR* SubtractEthiopicEthiopic ( FCHAR *A, FCHAR *B );

FCHAR* MultiplyEthiopicEthiopic ( FCHAR *A, FCHAR *B );

FCHAR* DivideEthiopicEthiopic ( FCHAR *A, FCHAR *B );

FCHAR* AddEthiopicInteger ( FCHAR *A, int B );

FCHAR* SubtractEthiopicInteger ( FCHAR *A, int B );

FCHAR* MultiplyEthiopicInteger ( FCHAR *A, int B );

FCHAR* DivideEthiopicInteger ( FCHAR *A, int B );

FCHAR* DivideIntegerEthiopic ( int A, FCHAR *B );

FCHAR* PowerEthiopicInteger ( FCHAR *A, int B );

FCHAR* PowerIntegerEthiopic ( int A, FCHAR *B );

#else  /* we do not have ANSI C */

/*
**  utilities
*/

int ftoi ();

FCHAR* arabtof ();

char* arabtoeth ();

FCHAR* itof ();

FCHAR* AddEthiopicEthiopic ();

FCHAR* SubtractEthiopicEthiopic ();

FCHAR* MultiplyEthiopicEthiopic ();

FCHAR* DivideEthiopicEthiopic ();

FCHAR* AddEthiopicInteger ();

FCHAR* SubtractEthiopicInteger ();

FCHAR* MultiplyEthiopicInteger ();

FCHAR* DivideEthiopicInteger ();

FCHAR* DivideIntegerEthiopic ();

FCHAR* PowerEthiopicInteger ();

FCHAR* PowerIntegerEthiopic ();

#endif /* __STDC__ || WIN32 */

#endif /* ETMATH_H */
