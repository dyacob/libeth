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

#ifndef ABSHA_H
#define ABSHA_H  1

#ifndef SUPPORT_ABSHA
#  define SUPPORT_ABSHA 1
#endif /* SUPPORT_ABSHA */

#define ABSHA_EMAIL "ethiopian@aol.com"
#define ABSHA_WWW   "www.ethiopic.com"
#define ABSHA_FTP   ""

#define GE_urr  0x90
#define GE_ull  0x9e
#define GE_ur   0xb2    /* angled up */
#define GE_ul   0xc0    /* angled up */
#define GE_ir   0x8e
#define GE_il   0xa3
#define GE_Er   0x81
#define GE_El   0xb8
#define GE_War  0x92
#define GE_Wal  0x9d
#define GE_Walw 0xb6    /* wide */
#define GE_Wer  0xb1
#define GE_Wel  0xdf
#define GE_Wir  0xa4
#define GE_Wil  0xbf
#define GE_W    0x8d
#define GE_yo   0xfb
#define GE_P    0xd6
#define GE_S    0xba
#define GE_BW   0x8f        /* like for r(W)a, x(W)a   */
#define GE_Bj   0xcf        /* (j)oins like for xe     */
#define GE_B    0xdc        /* usual with double cusps */
#define GE_WEx  0x80
         
                           /* 0x88 is africa (filled) */


#define SGE_urr  "\x90"
#define SGE_ull  "\x9e"
#define SGE_ur   "\xb2"
#define SGE_ul   "\xc0"
#define SGE_ir   "\x8e"
#define SGE_il   "\xa3"
#define SGE_Er   "\x81"
#define SGE_El   "\xb8"
#define SGE_War  "\x92"
#define SGE_Wal  "\x9d"
#define SGE_Walw "\xb6"
#define SGE_Wer  "\xb1"
#define SGE_Wel  "\xdf"
#define SGE_Wir  "\xa4"
#define SGE_Wil  "\xbf"
#define SGE_W    "\x8d"
#define SGE_yo   "\xfb"
#define SGE_BW   "\x8f"    /* like for r(W)a, x(W)a   */
#define SGE_Bj   "\xcf"    /* (j)oins like for xe     */
#define SGE_B    "\xdc"    /* usual with double cusps */
#define SGE_S    "\xba"
#define SGE_P    "\xd6"
#define SGE_WEx  "\x80"


#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR GeezEditToUnicode (void);
unsigned char* UnicodeToGeezEdit (FCHAR fch);
int GeezEdit_get_setid (FCHAR fch);
int GeezEdit_get_setName (int setid, int fontFace, unsigned char** setName);
char* Absha_get_netInfo (char INFO);
int GeezEdit_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
unsigned char GeezEdit_isGoodANSI (FCHAR fch);

#endif /* ABSHA_H */
