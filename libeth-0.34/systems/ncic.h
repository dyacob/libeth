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

#ifndef NCIC_H
#define NCIC_H  1

#ifndef SUPPORT_NCIC
#  define SUPPORT_NCIC 1
#endif /* SUPPORT_NCIC */

#define NCIC_EMAIL "estc@telecom.net.et"
#define NCIC_WWW   ""
#define NCIC_FTP   ""

#define NCC_u   0xfa 
#define NCC_ir  0xfb 
#define NCC_il  0xfc 
#define NCC_Er  0xfd 
#define NCC_El  0xfe 
#define NCC_Wa  0xff 


#define SNCC_u   "\xfa"
#define SNCC_ir  "\xfb"
#define SNCC_il  "\xfc"
#define SNCC_Er  "\xfd"
#define SNCC_El  "\xfe"
#define SNCC_Wa  "\xff"


#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR ToUnicode (void);

FCHAR NCICToUnicode (void);
unsigned char* UnicodeToNCIC (FCHAR fch);
int NCIC_get_setid (FCHAR fch);
int NCIC_get_setName (int setid, int fontFace, unsigned char** setName);
char* NCIC_get_netInfo (char INFO);
int NCIC_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
unsigned char NCIC_isGoodANSI (FCHAR fch);

FCHAR NCIC_ETToUnicode (void);
int NCIC_ET_get_setid (FCHAR fch);
int NCIC_ET_get_setName (int setid, int fontFace, unsigned char** setName);
boolean NCIC_ET_isGoodANSI (FCHAR fch);

#endif  /* NCIC_H */
