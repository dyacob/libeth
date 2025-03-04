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

#ifndef WAZEMA_H
#define WAZEMA_H  1

#ifndef SUPPORT_WAZEMA
#  define SUPPORT_WAZEMA 1
#endif /* SUPPORT_WAZEMA */

#define WAZEMA_EMAIL "w4z5m4@aol.com"
#define WAZEMA_WWW   "http://members.aol.com/w4z5m4/wazema.html"
#define WAZEMA_FTP   ""  /* check this... */

#define WAZ_Ba   0x3e
#define WAZ_Bb   0x4d
#define WAZ_Bc   0x97
#define WAZ_Bd   0xee
#define WAZ_Be   0xf6
#define WAZ_P    0xf7
#define WAZ_WS   0x9f

#define SWAZ_Ba   "0x3e"
#define SWAZ_Bb   "0x4d"
#define SWAZ_Bc   "0x97"
#define SWAZ_Bd   "0xee"
#define SWAZ_Be   "0xf6"
#define SWAZ_P    "0xf7"

#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR WazemaA1ToUnicode (void);
FCHAR WazemaA2ToUnicode (void);
unsigned char* UnicodeToWazema (FCHAR fch);
int Wazema_get_setid (FCHAR fch);
int Wazema_get_setName (int setid, int fontFace, unsigned char** setName);
char* Wazema_get_netInfo (char INFO);
int Wazema_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
unsigned char WazemaA1_isGoodANSI (FCHAR fch);
unsigned char WazemaA2_isGoodANSI (FCHAR fch);

#endif  /* WAZEMA_H */
