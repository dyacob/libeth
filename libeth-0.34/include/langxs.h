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

#ifndef LANGXS_H
#define LANGXS_H 1

#include "libeth.h"

unsigned char* ArabToEthiopic ( char* Enumber, int system, int xfer, int font, char* iPath );

unsigned char* ConvertEthiopicString ( char* string, int sysIn, int xferIn, int sysOut, int xferOut, int fontOut, enum Languages langOut, char* iPath, unsigned int options, int closing );

unsigned char* ConvertEthiopicFileToString ( FILE* fileP, int sysIn, int xferIn, int sysOut, int xferOut, int fontOut, enum Languages langOut, char* iPath, unsigned int options );

void ConvertEthiopicFile ( FILE* fileIn, FILE* fileOut, int sysIn, int xferIn, int sysOut, int xferOut, int fontOut, enum Languages langOut, char* iPath, unsigned int options );


#endif /* LANGXS_H */
