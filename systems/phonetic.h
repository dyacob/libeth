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

#ifndef PHONETIC_H
#define PHONETIC_H 1

#ifndef SUPPORT_PHONETIC
#  define SUPPORT_PHONETIC 1
#endif /* SUPPORT_PHONETIC */

#define PHONETIC_EMAIL "yrussom@geezsoft.com"
#define PHONETIC_WWW   "www.geezsoft.com"
#define PHONETIC_FTP   ""

#define GT_uru  0xe9
#define GT_ul   0xea
#define GT_uld  0xeb
#define GT_ull  0xec
#define GT_ulll 0xee
#define GT_ir   0xef
#define GT_im   0xf0
#define GT_il   0xf1
#define GT_Er   0xed   /* normal */
#define GT_Erf  0xf2   /* fat    */
#define GT_El   0xf3
#define GT_Ell  0xf4
#define GT_Elll 0xf5
#define GT_yo   0xf6
#define GT_Weu  0xf7
#define GT_Wed  0xf8
#define GT_Wi   0xf9
#define GT_War  0xfa
#define GT_Wam  0xfb
#define GT_Wal  0xfc
#define GT_WEr  0xfd
#define GT_WEl  0xfe
#define GT_Wu   0xe8
#define GT_Wd   0xff
#define GT_WS   0x3a
#define GT_S    0x6d
#define GT_B    0x7a
#define GT_P    0xc2


#define SGT_uru  "\xe9"
#define SGT_ul   "\xea"
#define SGT_uld  "\xeb"
#define SGT_ull  "\xec"
#define SGT_ulll "\xee"
#define SGT_ir   "\xef"
#define SGT_im   "\xf0"
#define SGT_il   "\xf1"
#define SGT_Er   "\xed"   /* normal */
#define SGT_Erf  "\xf2"   /* fat    */
#define SGT_El   "\xf3"
#define SGT_Ell  "\xf4"
#define SGT_Elll "\xf5"
#define SGT_yo   "\xf6"
#define SGT_Weu  "\xf7"
#define SGT_Wed  "\xf8"
#define SGT_Wi   "\xf9"
#define SGT_War  "\xfa"
#define SGT_Wam  "\xfb"
#define SGT_Wal  "\xfc"
#define SGT_WEr  "\xfd"
#define SGT_WEl  "\xfe"
#define SGT_Wu   "\xe8"
#define SGT_Wd   "\xff"
#define SGT_S    "\x6d"
#define SGT_B    "\x7a"
#define SGT_P    "\xc2"

#define GTN_TSZAE 0xc6
#define GTN_B2    0x68
#define GTN_B3    0x8d

#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR GeezTypeToUnicode (void);
unsigned char* UnicodeToGeezType (FCHAR fch);
int GeezType_get_setid (FCHAR fch);
int GeezType_get_setName (int setid, int fontFace, unsigned char** setName);
char* GeezType_get_netInfo (char INFO);
int GeezType_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
unsigned char GeezType_isGoodANSI (FCHAR fch);

FCHAR GeezTypeNetToUnicode (void);
unsigned char* UnicodeToGeezTypeNet (FCHAR fch);
int GeezTypeNet_get_setid (FCHAR fch);
int GeezTypeNet_get_setName (int setid, int fontFace, unsigned char** setName);
unsigned char GeezTypeNet_isGoodANSI (FCHAR fch);

FCHAR PhoneticToUnicode ( FCHAR fch, enum CharacterSet sys );

#endif  /* PHONETIC_H */
