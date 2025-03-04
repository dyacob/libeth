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

#ifndef NCI_H
#define NCI_H  1

#ifndef SUPPORT_NCI
#  define SUPPORT_NCI 1
#endif /* SUPPORT_NCI */

#define NCI_EMAIL ""
#define NCI_WWW   ""
#define NCI_FTP   ""

#define NCI_u    0x22
#define NCI_il   0x25
#define NCI_ir   0x23
#define NCI_El   0x27
#define NCI_Er   0x26
#define NCI_We   0x2c
#define NCI_Wi   0x3b
#define NCI_Wal  0x3e
#define NCI_War  0x3c
#define NCI_WE   0x40
#define NCI_W    0x3a
#define NCI_WS   0xbd


#define SNCI_u    "\x22"
#define SNCI_il   "\x25"
#define SNCI_ir   "\x23"
#define SNCI_El   "\x27"
#define SNCI_Er   "\x26"
#define SNCI_We   "\x2c"
#define SNCI_Wi   "\x3b"
#define SNCI_Wal  "\x3e"
#define SNCI_War  "\x3c"
#define SNCI_WE   "\x40"
#define SNCI_W    "\x3a"
#define SNCI_WS   "\xbd"

#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR NCIToUnicode (void);
unsigned char* UnicodeToNCI (FCHAR fch);
int NCI_get_setid (FCHAR fch);
int NCI_get_setName (int setid, int fontFace, unsigned char** setName);
char* NCI_get_netInfo (char INFO);
int NCI_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
unsigned char NCI_isGoodANSI (FCHAR fch);

#endif  /* NCI_H */
