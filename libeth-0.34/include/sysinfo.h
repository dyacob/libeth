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

#include "libeth.h"

/*
**  TrueType utilities
*/

#if __STDC__ || WIN32

unsigned char* fidel_sputc ( FCHAR fch, LibEthFlags* mylflags );

boolean isFidelTrueType ( enum CharacterSet system );

boolean isTransliteration ( enum CharacterSet system );

unsigned char isGoodANSI ( FCHAR fch, LibEthFlags* mylflags );

int get_setid ( FCHAR fch, LibEthFlags* mylflags );

int get_setName ( int setid, unsigned char** setName, enum CharacterSet system, int fontFace);

int get_setName ( int setid, unsigned char** setName, enum CharacterSet system, int fontFace);

int get_setRTFPrefix ( int setid, char** RTFPrefix, enum CharacterSet system, int fontFace );

#endif /* __STDC__ || WIN32 */


/*
**  Net Information
*/

#define LETH_EMAIL 0
#define LETH_WWW   1
#define LETH_FTP   2

#define get_vendorEmail ( vendor ) get_netInfo ( vendor, LETH_EMAIL );
#define get_vendorWWW  ( vendor ) get_netInfo ( vendor, LETH_WWW );
#define get_vendorFTP  ( vendor ) get_netInfo ( vendor, LETH_FTP );

#if __STDC__ || WIN32

char* get_netInfo ( enum CharacterSet vendor, char INFO );

#endif /* __STDC__ || WIN32 */


