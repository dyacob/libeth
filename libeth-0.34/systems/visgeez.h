/* This is part of the LibEth library, an ANSI C library for Ethiopic
   text and information processing (http://libeth.netpedia.net).
   Copyright (C) 1995-2000 Daniel Yacob.

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

#ifndef VISGEEZ_H
#define VISGEEZ_H  1

#ifndef SUPPORT_VISUALGEEZ
#  define SUPPORT_VISUALGEEZ 1
#endif /* SUPPORT_VISUALGEEZ */

#define VISUALGEEZ_EMAIL ""
#define VISUALGEEZ_WWW   ""
#define VISUALGEEZ_FTP   ""

#define VG_ul  0x24
#define VG_ur  0x23
#define VG_il  0x45
#define VG_ir  0x21
#define VG_El  0x26
#define VG_Er  0x40
#define VG_We  0xd6
#define VG_Wi  0xa4
#define VG_Wa  0x2a
#define VG_W   0xba
#define VG_WEx 0xb7    /* this is the WE left foot */
#define VG_WEy 0xdc    /* this is the WE left foot */
#define VG_WS  0xdd


#define SVG_ul  "\x24"
#define SVG_ur  "\x23"
#define SVG_il  "\x45"
#define SVG_ir  "\x21"
#define SVG_El  "\x26"
#define SVG_Er  "\x40"
#define SVG_We  "\xd6"
#define SVG_Wi  "\xa4"
#define SVG_Wa  "\x2a"
#define SVG_W   "\xba"
#define SVG_WEx "\xb7"
#define SVG_WEy "\xdc"
#define SVG_WS  "\xdd"


#define VG2K_ur  0xf9
#define VG2K_ul  0xdc
#define VG2K_il  0x45
#define VG2K_ir  0xb7
#define VG2K_ir2 0xfe
#define VG2K_El  0xbd
#define VG2K_Er  0xa4
#define VG2K_We  0xd6
#define VG2K_Wa  0x26
#define VG2K_Wi  0x93
#define VG2K_W   0x2a
#define VG2K_WS  0x94

#define SVG2K_ur  "\xf9"
#define SVG2K_ul  "\xdc"
#define SVG2K_il  "\x45"
#define SVG2K_ir  "\xb7"
#define SVG2K_ir2 "\xfe"
#define SVG2K_El  "\xbd"
#define SVG2K_Er  "\xa4"
#define SVG2K_Wa  "\x2a"
#define SVG2K_We  "\xd6"
#define SVG2K_Wi  "\x93"
#define SVG2K_W   "\x26"
#define SVG2K_WS  "\x94"

#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR VisualGeezToUnicode (void);
unsigned char* UnicodeToVisualGeez (FCHAR fch);
int VisualGeez_get_setid (FCHAR fch);
int VisualGeez_get_setName (int setid, int fontFace, unsigned char** setName);
char* VisualGeez_get_netInfo (char INFO);
int VisualGeez_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
unsigned char VisualGeez_isGoodANSI (FCHAR fch);


FCHAR VisualGeez2000ToUnicode ( void );
unsigned char* UnicodeToVisualGeez2000 (FCHAR fch);
int VisualGeez2000_get_setid (FCHAR fch);
unsigned char VisualGeez2000_isGoodANSI (FCHAR fch);



#endif  /* VISGEEZ_H */
