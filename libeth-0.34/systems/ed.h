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

#ifndef ED_H
#define ED_H  1

#ifndef SUPPORT_ED
#  define SUPPORT_ED 1
#endif /* SUPPORT_ED */

#define ED_WWW "www.sil.org"
#define ED_FTP "www.sil.org"
#define ED_EMAIL "jaars@sil.org"

#define ED_e   'v'
#define ED_u   'u'
#define ED_i   'i'
#define ED_a   'a'
#define ED_E   'e'
#define ED_o   'o'
#define ED_W   'W'


#define SED_e   "v"
#define SED_u   "u"
#define SED_i   "i"
#define SED_a   "a"
#define SED_E   "e"
#define SED_o   "o"
#define SED_We  "Wv"
#define SED_Wi  "Wi"
#define SED_Wa  "Wa"
#define SED_WE  "We"
#define SED_W   "W"

#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR EdToUnicode (void);
unsigned char* UnicodeToEd (FCHAR fch);
char* Ed_get_netInfo (char INFO);

#endif  /* ED_H */
