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

#ifndef JIS_H
#define JIS_H  1

#ifndef SUPPORT_JIS
#  define SUPPORT_JIS 1
#endif /* SUPPORT_JIS */

#define JIS_WWW   ""
#define JIS_FTP   ""
#define JIS_EMAIL ""

#define JISFIDEL       0x7a21
#define JISFIDELLAST   0x7e7e
#define JISFIDELSIZE   94*5 

#define JISGREEK       0x2621
#define JISGREEKLAST   0x2658

#define JISADJUST      0xa0

#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR JISToUnicode (void);
unsigned char* UnicodeToJIS (FCHAR fch);
char* JIS_get_netInfo (char INFO);

#endif  /* JIS_H */
