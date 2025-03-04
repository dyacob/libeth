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

#ifndef BRANA_H
#define BRANA_H  1

#ifndef SUPPORT_BRANA
#  define SUPPORT_BRANA 1
#endif /* SUPPORT_BRANA */

#define BRANA_EMAIL "brana@truman.cs.missouri.edu"
#define BRANA_WWW   "truman.cs.missouri.edu/~brana/"
#define BRANA_FTP   ""

#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR BranaIToUnicode (void);
FCHAR BranaIIToUnicode (void);
unsigned char* UnicodeToBrana (FCHAR fch);
int Brana_get_setid (FCHAR fch);
int Brana_get_setName (int setid, int fontFace, unsigned char** setName);
char* Brana_get_netInfo (char INFO);
int Brana_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
unsigned char BranaI_isGoodANSI (FCHAR fch);

#endif  /* BRANA_H*/
