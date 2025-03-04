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

#ifndef TFANUS_H
#define TFANUS_H 1

#ifndef SUPPORT_TFANUS
#  define SUPPORT_TFANUS 1
#endif /* SUPPORT_TFANUS */

#define TFANUS_EMAIL ""
#define TFANUS_WWW   ""
#define TFANUS_FTP   ""

#define ETHIOSOFT_EMAIL "ethiosoft@ethiosoft.com"  /* check these */
#define ETHIOSOFT_WWW   "www.ethiosoft.com"
#define ETHIOSOFT_FTP   ""

#define TF_uu   0x23 
#define TF_ud   0xf1 
#define TF_il   0xda 
#define TF_ir   0xf2 
#define TF_El   0xdd 
#define TF_Er   0xf4 
#define TF_We   0xf8 
#define TF_Wal  0xf0 
#define TF_War  0xfb 
#define TF_WEl  0xf7 
#define TF_WEr  0xfc 
#define TF_W    0xfa 
#define TF_WS   0xb5
#define TF_QM   0xba
#define TF_B    0xbf 
#define TF_o    0xf6 
#define TF_x    0xf3  /* unknown */

#define TF_WNew 0xbb  /* in GeezTimesNew Only */
#define TF_WiES 0x27  /* in EthioSoft Only */

#define STF_uu   "\x23"
#define STF_ud   "\xf1"
#define STF_il   "\xda"
#define STF_ir   "\xf2"
#define STF_El   "\xdd"
#define STF_Er   "\xf4"
#define STF_We   "\xf8"
#define STF_Wal  "\xf0"
#define STF_War  "\xfb"
#define STF_WEl  "\xf7"
#define STF_WEr  "\xfc"
#define STF_W    "\xfa"
#define STF_B    "\xbf"
#define STF_o    "\xf6"
#define STF_x    "\xf3"
#define STF_WNew "\xbb"

#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR TFanusToUnicode (LibEthFlags* mylflags);
unsigned char* UnicodeToTFanus (FCHAR fch);
int TFanus_get_setid (FCHAR fch);
int TFanus_get_setName (int setid, int fontFace, unsigned char** setName);
char* TFanus_get_netInfo (char INFO);
int TFanus_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
unsigned char TFanus_isGoodANSI (FCHAR fch);

unsigned char TFanusNew_isGoodANSI (FCHAR fch);
int TFanusNew_get_setName (int setid, int fontFace, unsigned char** setName);

unsigned char GeezBausi_isGoodANSI (FCHAR fch);
int GeezBausi_get_setName (int setid, int fontFace, unsigned char** setName);

unsigned char* UnicodeToEthioSoft (FCHAR fch);
unsigned char EthioSoft_isGoodANSI (FCHAR fch);
int EthioSoft_get_setName (int setid, int fontFace, unsigned char** setName);
char* EthioSoft_get_netInfo (char INFO);
int EthioSoft_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);

#endif  /* TFANUS_H */
