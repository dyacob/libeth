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

#ifndef SERA_H
#define SERA_H  1

#ifndef SUPPORT_SERA
#  define SUPPORT_SERA 1
#endif /* SUPPORT_SERA */

#define IS_TRANSLIT_SYS  1

#define SERA_EMAIL "yacob@geez.org"
#define SERA_WWW   "www.abyssiniagateway.net/fidel/sera-faq.html"
#define SERA_FTP   "ftp.geez.org/pub/sera/"

#define SERAALT     '`'
#define SERASTOP    '\''
#define SERAESCAPE  '\\'
#define SERAGIZ     'e'
#define SERAKAIB    'u'
#define SERASALS    'i'
#define SERARABI    'a'
#define SERAHAMS    'E'
#define SERASADS    SERAHash[SERASTOP - SERAHASHBASE]
#define SERASABI    'o'
#define SERADIQALA  'W'
#define SERAYA      'Y'
#define SERAPUNCT   '-'

#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR SERAToUnicode (void);
unsigned char* _UnicodeToSERA (FCHAR fch, LibEthFlags* mylflags);

#define UnicodeToSERA(fch) _UnicodeToSERA(fch, mylflags)

unsigned char SERA_isGoodANSI (FCHAR fch);
char* SERA_get_netInfo (char INFO);

#endif  /* SERA_H */
