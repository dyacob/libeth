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

#ifndef ALPAS_H
#define ALPAS_H  1

#ifndef SUPPORT_ALPAS
#  define SUPPORT_ALPAS 1
#endif /* SUPPORT_ALPAS */

#define ALPAS_EMAIL "alpas@usa.net"
#define ALPAS_WWW   "www.webscape.co.uk/ethiopia/pc_house/"
#define ALPAS_FTP   ""

#define ALP_ull  0xf2
#define ALP_ul   0xef
#define ALP_ur   0xf0
#define ALP_urr  0xf1
#define ALP_il   0xf5
#define ALP_im   0xf3
#define ALP_ir   0xf4
#define ALP_El   0xf8
#define ALP_Em   0xf7
#define ALP_Er   0xf6
#define ALP_We   0xf9
#define ALP_Wi   0xfb
#define ALP_Wal  0xfe
#define ALP_Wam  0xfd
#define ALP_War  0xfc
#define ALP_WE   0xff
#define ALP_W    0xfa
#define ALP_WS   0x3a


#define SALP_ull  "\xf2"
#define SALP_ul   "\xef"
#define SALP_ur   "\xf0"
#define SALP_urr  "\xf1"
#define SALP_il   "\xf5"
#define SALP_im   "\xf3"
#define SALP_ir   "\xf4"
#define SALP_El   "\xf8"
#define SALP_Em   "\xf7"
#define SALP_Er   "\xf6"
#define SALP_We   "\xf9"
#define SALP_Wi   "\xfb"
#define SALP_Wal  "\xfe"
#define SALP_Wam  "\xfd"
#define SALP_War  "\xfc"
#define SALP_WE   "\xff"
#define SALP_W    "\xfa"
#define SALP_WS   "\x3a"


#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR AlpasToUnicode (void);
unsigned char* UnicodeToAlpas (FCHAR fch);
int Alpas_get_setid (FCHAR fch);
int Alpas_get_setName (int setid, int fontFace, unsigned char** setName);
char* Alpas_get_netInfo (char INFO);
int Alpas_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
unsigned char Alpas_isGoodANSI (FCHAR fch);

#endif  /* ALPAS_H */
