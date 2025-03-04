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

#ifndef ACUWORK_H
#define ACUWORK_H  1

#ifndef SUPPORT_ACUWORK
#  define SUPPORT_ACUWORK 1
#endif /* SUPPORT_ACUWORK */

#define ACUWORK_EMAIL "AlexAK@aol.com"
#define ACUWORK_WWW   "www.acuwork.com"
#define ACUWORK_FTP   ""

#define ALX_ur  0x26
#define ALX_uru 0x83
#define ALX_urc 0x3e
#define ALX_ulc 0x2a
#define ALX_ul  0x84
#define ALX_il  0x40
#define ALX_im  0x23
#define ALX_ir  0x5e
#define ALX_Er  0x5f
#define ALX_Em  0x85
#define ALX_El  0x86
#define ALX_War 0xa1
#define ALX_Wam 0xa2
#define ALX_Wal 0xa3
#define ALX_WS  0xa5




#define SALX_ur  "\x26"
#define SALX_uru "\x83"
#define SALX_urc "\x3e"
#define SALX_ulc "\x2a"
#define SALX_ul  "\x84"
#define SALX_ir  "\x5e"
#define SALX_im  "\x23"
#define SALX_il  "\x40"
#define SALX_El  "\x86"
#define SALX_Em  "\x85"
#define SALX_Er  "\x5f"
#define SALX_Wal "\xa3"
#define SALX_Wam "\xa2"
#define SALX_War "\xa1"


#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR AcuworkToUnicode (void);
unsigned char* UnicodeToAcuwork (FCHAR fch);
int Acuwork_get_setid (FCHAR fch);
int Acuwork_get_setName (int setid, int fontFace, unsigned char** setName);
char* Acuwork_get_netInfo (char INFO);
int Acuwork_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
unsigned char Acuwork_isGoodANSI (FCHAR fch);

#endif /* ACUWORK_H */
