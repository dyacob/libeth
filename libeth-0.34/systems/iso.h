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

#ifndef ISO_H
#define ISO_H 1

#ifndef SUPPORT_ISO
#  define SUPPORT_ISO 1
#endif /* SUPPORT_ISO */

#define IS_TRANSLIT_SYS

#define ISO_EMAIL "Ethiopic@sesame.com"
#define ISO_WWW   "www.iso.org/x/y/"
#define ISO_FTP   ""

#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

unsigned char* UnicodeToISOTC46SC2 (FCHAR fch, LibEthFlags* mylflags);
extern unsigned char* _UnicodeToSERA (FCHAR fch, LibEthFlags* mylflags);
char* ISO_get_netInfo (char INFO);

#endif /* ISO_H */
