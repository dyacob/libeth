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

#ifndef ETHCITA_H
#define ETHCITA_H  1

#ifndef SUPPORT_ETHCITA
#  define SUPPORT_ETHCITA  1
#endif /* SUPPORT_ETHCITA */

#define ETHCITA_EMAIL ""
#define ETHCITA_WWW   "www.ethiopians.com/EthCITA.htm"
#define ETHCITA_FTP   ""

/*  Begin UniFont  */
/*
22:34  is :
23:35  is Ur
25:37  is Ul
26:38  is Ir
30:42  is Il
31:43  is Er
32:44  is El
3a:58  is We
3b:59  is War
3c:60  is Wal
3d:61  is Wx
3e:62  is Wx2  (for qe)
40:64  is Wi
71:113 is butterfly
72:114 is Q
f0:240 is WEl  New (previously KWa)
ff:255 is WEr
*/


#define ECU_ur   0x23
#define ECU_ul   0x25
#define ECU_ir   0x26
#define ECU_il   0x30
#define ECU_Er   0x31
#define ECU_El   0xc2
#define ECU_We   0x3a
#define ECU_War  0x3b
#define ECU_Wal  0x3c
#define ECU_Wu   0x3d
#define ECU_Wd   0x3e
#define ECU_Wi   0x40
#define ECU_B    0x71
#define ECU_WS   0x22

/*  This is WE mark is the only difference from GeezNewA,
 *  it is used only for qWE and nothing else.
 */
#define ECU_WE_Q  0xf0
#define SECU_WE_Q "\xf0"


#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

extern int GeezNewAHashTable[];
extern LETCHAR GeezNewABFidel[];
extern unsigned char* UnicodeToGeezNewAB (FCHAR fch);
extern int GeezNewA_get_setid (FCHAR fch);
extern unsigned char GeezNewA_isGoodANSI (FCHAR fch);

FCHAR EthCITAUniToUnicode (void);
unsigned char* UnicodeToEthCITAUni (FCHAR fch);
int EthCITAUni_get_setid (FCHAR fch);
int EthCITAUni_get_setName (int setid, int fontFace, unsigned char** setName);
unsigned char EthCITAUni_isGoodANSI (FCHAR fch);
int EthCITAUni_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);


extern unsigned char* UnicodeToEthioSys (FCHAR fch);
extern FCHAR EthioSysPrimaryToUnicode (void);
extern FCHAR EthioSysSecondaryToUnicode (void);
extern int EthioSys_get_setid (FCHAR fch);
extern unsigned char EthioSys_isGoodANSI (FCHAR fch);

unsigned char* UnicodeToEthCITABi (FCHAR fch);
int EthCITABi_get_setid (FCHAR fch);
unsigned char EthCITABi_isGoodANSI (FCHAR fch);
char* EthCITA_get_netInfo (char INFO);

FCHAR EthCITABiPToUnicode (void);
int EthCITABiP_get_setName (int setid, int fontFace, unsigned char** setName);
int EthCITABiP_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);

FCHAR EthCITABiSToUnicode (void);
unsigned char* UnicodeToEthCITABi (FCHAR fch);
int EthCITABiS_get_setName (int setid, int fontFace, unsigned char** setName);
int EthCITABiS_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);

#endif  /* ETHCITA_H */
