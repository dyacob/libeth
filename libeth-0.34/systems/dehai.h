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

#ifndef DEHAI_H
#define DEHAI_H  1

#ifndef SUPPORT_DEHAI
#  define SUPPORT_DEHAI 1
#endif /* SUPPORT_DEHAI */

#define IS_TRANSLIT_SYS  1

#define DEHAI_EMAIL ""
#define DEHAI_WWW   "www.primenet.com/~ephrem"
#define DEHAI_FTP   ""

#define DEHAIALT     '`'
#define DEHAISTOP    '\''
#define DEHAIESCAPE  '^'
#define DEHAIGIZ     'e'
#define DEHAIKAIB    'u'
#define DEHAISALS    'i'
#define DEHAIRABI    'a'
#define DEHAIHAMS    'E'
#define DEHAISADS    SERAHash[SERASTOP]
#define DEHAISABI    'o'
#define DEHAIDIQALA  'W'
#define DEHAIYA      'Y'
#define DEHAIPUNCT   '-'

#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR DehaiToUnicode (void);
unsigned char* UnicodeToDehai (FCHAR fch, LibEthFlags* mylflags);
char* DEHAI_get_netInfo (char INFO);

#endif  /* DEHAI_H */
