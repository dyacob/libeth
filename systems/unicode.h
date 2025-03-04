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

#ifndef UNICODE_H
#define UNICODE_H  1

#ifndef SUPPORT_UNICODE
#  define SUPPORT_UNICODE 1
#endif /* SUPPORT_UNICODE */

#define UNICODE_EMAIL "unicode@unicode.org"
#define UNICODE_WWW   "www.unicode.org"
#define UNICODE_FTP   ""

#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR UTF7ToUnicode (void);
FCHAR UTF8ToUnicode (void);
FCHAR UTF16ToUnicode (void);
unsigned char* UnicodeToUTF7 (FCHAR fch);
unsigned char* UnicodeToUTF8 (FCHAR fch);
unsigned char* UnicodeToUTF16 (FCHAR fch);
unsigned char* UnicodeToName (FCHAR fch);
char* Unicode_get_netInfo (char INFO);

extern char bytesFromUTF8[];

#ifndef IO_H
  extern unsigned char getToken ();
#endif /* IO_H */

#endif  /* UNICODE_H */

