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

#ifndef ACIS_H
#define ACIS_H  1

#ifndef SUPPORT_ACIS
#  define SUPPORT_ACIS 1
#endif /* SUPPORT_ACIS */

#define ACIS_EMAIL "acis@telecom.net.et"
#define ACIS_WWW   "www.acisconsulting.com"
#define ACIS_FTP   ""

#define ACIS_ur   0x2e
#define ACIS_ul   0xd7
#define ACIS_ir   0x3e
#define ACIS_il   0x5e
#define ACIS_Er   0x3f
#define ACIS_El   0xe4
#define ACIS_We   0xfa
#define ACIS_War  0x5f
#define ACIS_Wal  0xf4
#define ACIS_W    0xab
#define ACIS_Wi   0xaa
#define ACIS_Br   0x23
#define ACIS_Bm   0xba
#define ACIS_Bl   0xf5
#define ACIS_WS   0xee    /* "wordspace", needed to catch fullstops */
#define ACIS_WEx  0xbe 


#define SACIS_ur   "\x2e"
#define SACIS_ul   "\xd7"
#define SACIS_ir   "\x3e"
#define SACIS_il   "\x5e"
#define SACIS_Er   "\x3f"
#define SACIS_El   "\xe4"
#define SACIS_We   "\xfa"
#define SACIS_War  "\x5f"
#define SACIS_Wal  "\xf4"
#define SACIS_W    "\xab"
#define SACIS_Wi   "\xaa"
#define SACIS_Br   "\x23"
#define SACIS_Bm   "\xba"
#define SACIS_Bl   "\xf5"
#define SACIS_WS   "\xee"
#define SACIS_WEx  "\xbe"


#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR ACISToUnicode (void);
unsigned char* UnicodeToACIS (FCHAR fch);
int ACIS_get_setid (FCHAR fch);
int ACIS_get_setName (int setid, int fontFace, unsigned char** setName);
char* ACIS_get_netInfo (char INFO);
int ACIS_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
unsigned char ACIS_isGoodANSI (FCHAR fch);

#endif  /* ACIS_H */
