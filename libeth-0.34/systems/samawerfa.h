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

#ifndef SAMAWERFA_H
#define SAMAWERFA_H  1

#ifndef SUPPORT_SAMAWERFA
#  define SUPPORT_SAMAWERFA 1
#endif /* SUPPORT_SAMAWERFA */

#define SAMAWERFA_EMAIL ""
#define SAMAWERFA_WWW   ""
#define SAMAWERFA_FTP   ""


#define SAM_ullu 0xfd
#define SAM_ulld 0xe7
#define SAM_ul   0xe6
#define SAM_ur   0xe5
#define SAM_urr  0xe8
#define SAM_irr  0xe9
#define SAM_ir   0xea
#define SAM_im   0xeb
#define SAM_il   0xec
#define SAM_ill  0xed
#define SAM_Err  0xee
#define SAM_Er   0xef
#define SAM_Em   0xf0
#define SAM_El   0xf1
#define SAM_Ell  0xf2
#define SAM_Wel  0xf9
#define SAM_Wer  0xf8
#define SAM_Wi   0xf7
#define SAM_W    0xf6
#define SAM_Wal  0xf5
#define SAM_Wam  0xf4
#define SAM_War  0xf3
#define SAM_WEl  0xfb
#define SAM_WEr  0xfc
#define SAM_B    0xfa
#define SAM_WS   0x3a

#define SSAM_ullu "\xfd"
#define SSAM_ulld "\xe7"
#define SSAM_ul   "\xe6"
#define SSAM_ur   "\xe5"
#define SSAM_urr  "\xe8"
#define SSAM_irr  "\xe9"
#define SSAM_ir   "\xea"
#define SSAM_im   "\xeb"
#define SSAM_il   "\xec"
#define SSAM_ill  "\xed"
#define SSAM_Err  "\xee"
#define SSAM_Er   "\xef"
#define SSAM_Em   "\xf0"
#define SSAM_El   "\xf1"
#define SSAM_Ell  "\xf2"
#define SSAM_Wel  "\xf9"
#define SSAM_Wer  "\xf8"
#define SSAM_Wi   "\xf7"
#define SSAM_W    "\xf6"
#define SSAM_Wal  "\xf5"
#define SSAM_Wam  "\xf4"
#define SSAM_War  "\xf3"
#define SSAM_WEl  "\xfb"
#define SSAM_WEr  "\xfc"
#define SSAM_B    "\xfa"
#define SSAM_WS   "\x3a"


#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR SamawerfaToUnicode (LibEthFlags* mylflags);
unsigned char* UnicodeToSamawerfaWP (FCHAR fch);
unsigned char* UnicodeToSamawerfa98 (FCHAR fch);
int Samawerfa_get_setid (FCHAR fch);
int Samawerfa_get_setName (int setid, int fontFace, unsigned char** setName);
char* Samawerfa_get_netInfo (char INFO);
int Samawerfa_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
unsigned char Samawerfa_isGoodANSI (FCHAR fch);

#define Samawerfa98ToUnicode() SamawerfaToUnicode( mylflags )
#define SamawerfaWPToUnicode() SamawerfaToUnicode( mylflags )

#endif  /* SAMAWERFA_H */
