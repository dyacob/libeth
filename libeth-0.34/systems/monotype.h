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

#ifndef MONOTYPE_H
#define MONOTYPE_H 1

#ifndef SUPPORT_MONOTYPE
#  define SUPPORT_MONOTYPE 1
#endif /* SUPPORT_MONOTYPE */

#define MONOTYPE_WWW   "www.monotype.com"
#define MONOTYPE_FTP   "ftp.monotype.com"
#define MONOTYPE_EMAIL "info@monotype.com"

#define MTA_um  0xe5
#define MTA_ul  0xe6
#define MTA_ur  0xf3
#define MTA_ulc 0xf9
#define MTA_urc 0xfa
#define MTA_yor 0xe9
#define MTA_yol 0xf5
#define MTA_il  0xe3
#define MTA_ir  0xe4
#define MTA_ill 0xfe
#define MTA_irr 0xff
#define MTA_Em  0xe7
#define MTA_Er  0xfc
#define MTA_El  0xfd
#define MTA_Wel 0xe8
#define MTA_Wer 0xf4
#define MTA_Welld 0xf8
#define MTA_Wi  0xf6
#define MTA_Wal 0xea
#define MTA_War 0xfb
#define MTA_W   0xf7
#define MTA_WS  0xd1


#define SMTA_um  "\xe5"
#define SMTA_ul  "\xe6"
#define SMTA_ur  "\xf3"
#define SMTA_ulc "\xf9"
#define SMTA_urc "\xfa"
#define SMTA_yor "\xe9"
#define SMTA_yol "\xf5"
#define SMTA_il  "\xe3"
#define SMTA_ir  "\xe4"
#define SMTA_ill "\xfe"
#define SMTA_irr "\xff"
#define SMTA_Em  "\xe7"
#define SMTA_Er  "\xfc"
#define SMTA_El  "\xfd"
#define SMTA_Wel "\xe8"
#define SMTA_Wer "\xf4"
#define SMTA_Welld "\xf8"
#define SMTA_Wi  "\xf6"
#define SMTA_Wal "\xea"
#define SMTA_War "\xfb"
#define SMTA_W   "\xf7"


#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR MonoType1ToUnicode (void);
FCHAR MonoType2ToUnicode (void);
FCHAR MonoType3ToUnicode (void);
FCHAR MonoTypeNToUnicode (void);
FCHAR MonoTypeAltToUnicode (void);
unsigned char* UnicodeToMonoType (FCHAR fch);
unsigned char* UnicodeToMonoTypeAlt (FCHAR fch);
int MonoType_get_setid (FCHAR fch);
int MonoType_get_setName (int setid, int fontFace, unsigned char** setName);
int MonoTypeAlt_get_setid (FCHAR fch);
int MonoTypeAlt_get_setName (int setid, int fontFace, unsigned char** setName);
int MonoType_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
char* MonoType_get_netInfo (char INFO);


#endif  /* MONOTYPE_H */
