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

#ifndef GEEZFONT_H
#define GEEZFONT_H  1

#ifndef SUPPORT_GEEZFONT
#  define SUPPORT_GEEZFONT 1
#endif /* SUPPORT_GEEZFONT */

#define GEEZFONT_EMAIL "geezfont@geezfont.com"
#define GEEZFONT_WWW   "www.geezfont.com"
#define GEEZFONT_FTP   "ftp.geezfont.com"  /* or ftp.netnation.com/... */

#define GF_uru   0x3d   /* u right, up */
#define GF_ul    0x3c 
#define GF_ur    0xfa 
#define GF_ir    0x5e 
#define GF_il    0x3e 
#define GF_Er    0xfd 
#define GF_El    0x5f 
#define GF_War   0xfc 
#define GF_Wal   0x4f 
#define GF_Wer   0xe1 
#define GF_Wel   0xe9 
#define GF_Wir   0xfb 
#define GF_Wil   0xec 
#define GF_W     0xee 
#define GF_WEr   0xb9 
#define GF_WEl   0xef 
#define GF_B     0xfe
#define GF_P     0xe6


#define SGF_uru   "\x3d"
#define SGF_ul    "\x3c"
#define SGF_ur    "\xfa"
#define SGF_ir    "\x5e"
#define SGF_il    "\x3e"
#define SGF_Er    "\xfd"
#define SGF_El    "\x5f"
#define SGF_We    "\xfe"
#define SGF_War   "\xfc"
#define SGF_Wal   "\x4f"
#define SGF_Wer   "\xe1"
#define SGF_Wel   "\xe9"
#define SGF_Wir   "\xfb"
#define SGF_Wil   "\xec"
#define SGF_W     "\xee"
#define SGF_WEr   "\xb9"
#define SGF_WEl   "\xef"
#define SGF_B     "\xfe"
#define SGF_P     "\xe6"

#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR GeezFontToUnicode (void);
unsigned char* UnicodeToGeezFont (FCHAR fch);
int GeezFont_get_setid (FCHAR fch);
int GeezFont_get_setName (int setid, int fontFace, unsigned char** setName);
char* GeezFont_get_netInfo (char INFO);
int GeezFont_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
unsigned char GeezFont_isGoodANSI (FCHAR fch);

#endif  /* GEEZFONT_H */
