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

#ifndef POWERGEEZ_H
#define POWERGEEZ_H  1

#ifndef SUPPORT_POWERGEEZ
#  define SUPPORT_POWERGEEZ 1
#endif /* SUPPORT_POWERGEEZ */

#define POWERGEEZ_EMAIL ""
#define POWERGEEZ_WWW   ""
#define POWERGEEZ_FTP   ""

#define PWRG_u    0x3c
#define PWRG_il   0x3e
#define PWRG_ir   0x3d
#define PWRG_iQ   0x2b
#define PWRG_El   0x40
#define PWRG_Er   0x3f
#define PWRG_EQ   0x2c
#define PWRG_We   0x41
#define PWRG_Wi   0x43
#define PWRG_Wal  0x45
#define PWRG_War  0x44
#define PWRG_WE   0x46
#define PWRG_W    0x42
#define PWRG_WS   0x3a


#define SPWRG_u    "\x3c"
#define SPWRG_il   "\x3e"
#define SPWRG_ir   "\x3d"
#define SPWRG_iQ   "\x2b"
#define SPWRG_El   "\x40"
#define SPWRG_Er   "\x3f"
#define SPWRG_EQ   "\x2c"
#define SPWRG_We   "\x41"
#define SPWRG_Wi   "\x43"
#define SPWRG_Wal  "\x45"
#define SPWRG_War  "\x44"
#define SPWRG_WE   "\x46"
#define SPWRG_W    "\x42"
#define SPWRG_WS   "\x3a"


#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR PowerGeezToUnicode (void);
unsigned char* UnicodeToPowerGeez (FCHAR fch);
int PowerGeez_get_setid (FCHAR fch);
int PowerGeez_get_setName (int setid, int fontFace, unsigned char** setName);
char* PowerGeez_get_netInfo (char INFO);
unsigned char PowerGeez_isGoodANSI ( FCHAR fch );
int PowerGeez_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
unsigned char PowerGeez_isGoodANSI (FCHAR fch);

#endif  /* POWERGEEZ_H */
