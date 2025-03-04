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

#ifndef OMNITECH_H
#define OMNITECH_H 1

#ifndef SUPPORT_OMNTIECH
#  define SUPPORT_OMNTIECH 1
#endif /* SUPPORT_OMNITECH */

#define OMNITECH_EMAIL "omnitech@telecom.net.et"
#define OMNITECH_WWW   "OmniTech.EthiopiaOnline.Net"
#define OMNITECH_FTP   ""

#define OMNI_u    0x22
#define OMNI_il   0x25
#define OMNI_ir   0x23
#define OMNI_El   0x27
#define OMNI_Er   0x26
#define OMNI_We   0x2c
#define OMNI_Wi   0x3b
#define OMNI_Wal  0x3e
#define OMNI_War  0x3c
#define OMNI_WE   0x40  /* the _WE glyph is identical to _Er which is a      */
#define OMNI_W    0x3a  /* discrepancy from NCI encoding that we will ignore */
#define OMNI_WS   0xbd  /* untill we get further info...                     */

#define SOMNI_u    "\x22"
#define SOMNI_il   "\x25"
#define SOMNI_ir   "\x23"
#define SOMNI_El   "\x27"
#define SOMNI_Er   "\x26"
#define SOMNI_We   "\x2c"
#define SOMNI_Wi   "\x3b"
#define SOMNI_Wal  "\x3e"
#define SOMNI_War  "\x3c"
#define SOMNI_WE   "\x40"
#define SOMNI_W    "\x3a"
#define SOMNI_WS   "\xbd"


#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR OmniTechToUnicode (void);
unsigned char* UnicodeToOmniTech (FCHAR fch);
int OmniTech_get_setid (FCHAR fch);
int OmniTech_get_setName (int setid, int fontFace, unsigned char** setName);
char* OmniTech_get_netInfo (char INFO);
int OmniTech_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);

#endif  /* OMNITECH_H */
