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

#ifndef ETHIOWALIA_H
#define ETHIOWALIA_H  1

#ifndef SUPPORT_ETHIOWALIA
#  define SUPPORT_ETHIOWALIA 1
#endif /* SUPPORT_ETHIOWALIA */

#define ETHIOWALIA_EMAIL "webmaster@ethiowalia.com"
#define ETHIOWALIA_WWW   "www.ethiowalia.com/"
#define ETHIOWALIA_FTP   ""


#define ETWAL_Urd  'A'
#define ETWAL_Uru  'B'
#define ETWAL_Urux 'Y'
#define ETWAL_Ul   'X'
#define ETWAL_Il   'Z'
#define ETWAL_Ir   'C'
#define ETWAL_El   'M'
#define ETWAL_Er   'N'
#define ETWAL_Wel  'F'
#define ETWAL_Wer  'V'
#define ETWAL_Wal  'D'
#define ETWAL_War  'L'
#define ETWAL_Wi   'G'
#define ETWAL_WEr  'E'
#define ETWAL_WEl  'I'
#define ETWAL_Wr   'H'
#define ETWAL_Wrd  'O'
#define ETWAL_Wl   'K'
#define ETWAL_Bl   'R'
#define ETWAL_Bm   'S'
#define ETWAL_Br   'T'
#define ETWAL_Bx   'U'
#define ETWAL_P    'J'

#define SETWAL_Urd  "A"
#define SETWAL_Uru  "B"
#define SETWAL_Urux "Y"
#define SETWAL_Ul   "X"
#define SETWAL_Il   "Z"
#define SETWAL_Ir   "C"
#define SETWAL_El   "M"
#define SETWAL_Er   "N"
#define SETWAL_Wel  "F"
#define SETWAL_Wer  "V"
#define SETWAL_Wal  "D"
#define SETWAL_War  "L"
#define SETWAL_Wi   "G"
#define SETWAL_WEr  "E"
#define SETWAL_WEl  "I"
#define SETWAL_Wr   "H"
#define SETWAL_Wrd  "O"
#define SETWAL_Wl   "K"
#define SETWAL_Bl   "R"
#define SETWAL_Bm   "S"
#define SETWAL_Br   "T"
#define SETWAL_Bx   "U"
#define SETWAL_P    "J"


#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR EthioWaliaToUnicode (void);
unsigned char* UnicodeToEthioWalia (FCHAR fch);
int EthioWalia_get_setid (FCHAR fch);
int EthioWalia_get_setName (int setid, int fontFace, unsigned char** setName);
char* EthioWalia_get_netInfo (char INFO);
unsigned char EthioWalia_isGoodANSI ( FCHAR fch );
int EthioWalia_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
unsigned char EthioWalia_isGoodANSI (FCHAR fch);

#endif  /* ETHIOWALIA_H */
