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

#ifndef FEEDEL_H
#define FEEDEL_H  1

#ifndef SUPPORT_FEEDEL
#  define SUPPORT_FEEDEL  1
#endif /* SUPPORT_FEEDEL */

#define FEEDEL_EMAIL "feedel@aol.com"
#define FEEDEL_WWW   "www.aol.com/members/Feedel/Feedel.htm"
#define FEEDEL_FTP   "ftp.aol.com/members/Feedel/"

/*  Begin Geezigna  */

#define FDL_ur   0x2e    /* . */
#define FDL_ul   0xb3    /* ³ */
#define FDL_ir   0x3e    /* > */
#define FDL_il   0xf9    /* ù */
#define FDL_Er   0x3f    /* ? */
#define FDL_El   0xc0    /* À */
#define FDL_We   0xd6    /* Ö */
#define FDL_War  0x5f    /* _ */
#define FDL_Wal  0xd0    /* Ð */
#define FDL_Wr   0x23    /* # */
#define FDL_Wl   0x8b
#define FDL_Wi   0x8a
#define FDL_Br   0x99
#define FDL_Bm   0x9b
#define FDL_Bl   0xd1    /* Ñ */
#define FDL_WS   0xca    /* Ê */ /* "wordspace", needed to catch fullstops */
#define FDL_WEx  0x9d 


#define SFDL_ur   "\x2e"
#define SFDL_ul   "\xb3"
#define SFDL_ir   "\x3e"
#define SFDL_il   "\xf9"
#define SFDL_Er   "\x3f"
#define SFDL_El   "\xc0"
#define SFDL_We   "\xd6"
#define SFDL_War  "\x5f"
#define SFDL_Wal  "\xd0"
#define SFDL_Wr   "\x23"
#define SFDL_Wl   "\x8b"
#define SFDL_Wi   "\x8a"
#define SFDL_S    "\x9d"  /* sads mark as in "b"                    */
#define SFDL_Br   "\x99"
#define SFDL_Bm   "\x9b"
#define SFDL_Bl   "\xd1" 
#define SFDL_WS   "\xca"  /* "wordspace", needed to catch fullstops */




/*  Begin Geez,II  */


#define FDLG_ul  0xb3
#define FDLG_ur  0x90
#define FDLG_il  0xf9
#define FDLG_ir  0x3e
#define FDLG_El  0xc0
#define FDLG_Er  0x3f
#define FDLG_We  0xd6
#define FDLG_Wal 0xd0
#define FDLG_War 0x5f
#define FDLG_Wi  0x8a
#define FDLG_Wd  0xca
#define FDLG_Wu  0x8b
#define FDLG_B   0x99
#define FDLG_P   0xea
#define FDLG_WEx 0x9d
#define FDLG_WS  0x23


#define SFDLG_ul  "\xb3"
#define SFDLG_ur  "\x90"
#define SFDLG_il  "\xf9"
#define SFDLG_ir  "\x3e"
#define SFDLG_El  "\xc0"
#define SFDLG_Er  "\x3f"
#define SFDLG_We  "\xd6"
#define SFDLG_Wal "\xd0"
#define SFDLG_War "\x5f"
#define SFDLG_Wi  "\x8a"
#define SFDLG_Wd  "\xca"
#define SFDLG_Wu  "\x8b"
#define SFDLG_B   "\x99"
#define SFDLG_P   "\xea"
#define SFDLG_WEx "\x9d"
#define SFDLG_WS  "\x23"




/*  Begin GeezNewA,B */


#define FDLN_ur  0x23    /* # */
#define FDLN_ul  0x25    /* % */
#define FDLN_ir  0x26    /* & */
#define FDLN_il  0x2a    /* * */
#define FDLN_Er  0x2b    /* + */
#define FDLN_El  0x2c    /* , */
#define FDLN_We  0x3a    /* : */
#define FDLN_Wi  0x40    /* @ */
#define FDLN_War 0x3b    /* ; */
#define FDLN_Wal 0x3c    /* < */
#define FDLN_Wu  0x3d    /* = */
#define FDLN_Wd  0x3e    /* > */
#define FDLN_WS  0x22    /* " */
#define FDLN_B   0x71    /* q */
#define FDLN_P   0xc9    /* È */
#define FDLN_Ex  0xff    /* ÿ */


#define SFDLN_ur  "\x23"
#define SFDLN_ul  "\x25"
#define SFDLN_ir  "\x26"
#define SFDLN_il  "\x2a"
#define SFDLN_Er  "\x2b"
#define SFDLN_El  "\x2c"
#define SFDLN_We  "\x3a"
#define SFDLN_Wi  "\x40"
#define SFDLN_War "\x3b"
#define SFDLN_Wal "\x3c"
#define SFDLN_Wu  "\x3d"
#define SFDLN_Wd  "\x3e"
#define SFDLN_B   "\x71"
#define SFDLN_P   "\xc9"
#define SFDLN_Ex  "\xff"


#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR GeezignaToUnicode (void);
unsigned char* UnicodeToGeezigna (FCHAR fch);
int Geezigna_get_setid (FCHAR fch);
int Geezigna_get_setName (int setid, int fontFace, unsigned char** setName);
FCHAR GeezNewAToUnicode (void);
FCHAR GeezNewBToUnicode (void);
int GeezNewAB_get_setid (FCHAR fch);
int GeezNewAB_get_setName (int setid, int fontFace, unsigned char** setName);
unsigned char* UnicodeToGeezNewAB (FCHAR fch);
unsigned char GeezNewAB_isGoodANSI (FCHAR fch);
FCHAR GeezIToUnicode (void);
FCHAR GeezIIToUnicode (void);
unsigned char* UnicodeToGeezII (FCHAR fch);
int GeezII_get_setid (FCHAR fch);
int GeezII_get_setName (int setid, int fontFace, unsigned char** setName);
char* Feedel_get_netInfo (char INFO);
int Feedel_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);

#endif  /* FEEDEL_H */
