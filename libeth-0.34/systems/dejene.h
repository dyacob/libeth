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

#ifndef DEJENE_H
#define DEJENE_H  1

#ifndef SUPPORT_DEJENE
#  define SUPPORT_DEJENE 1
#endif /* SUPPORT_DEJENE */

#define DEJENE_EMAIL ""
#define DEJENE_WWW   ""
#define DEJENE_FTP   ""


#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR Dejene1ToUnicode (void);
FCHAR Dejene2ToUnicode (void);
unsigned char* UnicodeToDejene (FCHAR fch);
int Dejene_get_setid (FCHAR fch);
int Dejene_get_setName (int setid, int fontFace, unsigned char** setName);
char* Dejene_get_netInfo (char INFO);
int Dejene_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
unsigned char Dejene_isGoodANSI (FCHAR fch);

#endif  /* DEJENE_H */
