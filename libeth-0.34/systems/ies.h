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

/*
**   These are phonetic mapping for Ethiopic script devised by Steven Wright 
**   and adapted by the Institute of Ethiopian Studies and Kennedy Library
**   for library cataloging.
**
**   Wright, Stephen, "The Transliteration of Amharic", Journal of Ethiopian
**   Studies, Vol. II No. 1, Addis Ababa, January 1964.
*/

#ifndef IES_H
#define IES_H 1

#ifndef SUPPORT_IES
#  define SUPPORT_IES 1
#endif /* SUPORT_IES */

#define IES_EMAIL "ies@padis.gn.apc.org"
#define IES_WWW   "www.cs.indiana.edu/hyplan/dmulholl/ethiopia/aau/ies.html"
#define IES_FTP   ""

#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

unsigned char* UnicodeToIESAmharic (FCHAR fch);
unsigned char* UnicodeToIESGeez (FCHAR fch);
unsigned char* UnicodeToIESTigrigna (FCHAR fch);
char* IES_get_netInfo (char INFO);

#endif  /* IES_H */
