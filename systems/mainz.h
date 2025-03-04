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

#ifndef MAINZ_H
#define MAINZ_H  1

#ifndef SUPPORT_MAINZ
#  define SUPPORT_MAINZ 1
#endif /* SUPPORT_MAINZ */

#define IS_TRANSLIT_SYS  1

#define MAINZ_EMAIL "kropp@mzdmza.zdv.uni-mainz.de"
#define MAINZ_WWW   "www.uni-mainz.de/~kropp/"
#define MAINZ_FTP   ""

#define MAINZGIZ     'a'
#define MAINZKAIB    'u'
#define MAINZSALS    'i'
#define MAINZRABI    'A'
#define MAINZHAMS    'e'
#define MAINZSADS    'j'
#define MAINZSABI    'o'
#define MAINZDIQALA  'W'
#define MAINZPUNCT   ':'

#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

unsigned char* UnicodeToMainz (FCHAR fch, LibEthFlags* mylflags);
char* Mainz_get_netInfo (char INFO);
extern unsigned char* _UnicodeToSERA (FCHAR fch, LibEthFlags* mylflags);
FCHAR MainzToUnicode (LibEthFlags* mylflags);


#endif  /* MAINZ_H */
