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

#ifndef GREEK_H
#define GREEK_H  1

#define GREEKBASE 700     /* Greek base point used by lex */

#ifndef HAVE_UNI_GREEK
#  define HAVE_UNI_GREEK  1
/* #  define UNIGREEK 0x0370   ?? */
#  define UNIGREEK 0x0386
#  define UNIGREEK_END 0x03f5
#  define ALPHAOFF 0x0020
#endif  /* HAVE_UNI_GREEK */


#endif  /* GREEK_H */
