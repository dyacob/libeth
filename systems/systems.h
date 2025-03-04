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

#ifndef SYSTEMS_H
#define SYSTEMS_H 1

#include <stdlib.h>
#include <stdio.h>
#ifdef IS_TRANSLIT_SYS
#  include "yy.h"
#else
#  include "systemio.h"
#endif /* SERA_H || ETHIOP_H */

#define LETH_EMAIL 0
#define LETH_WWW   1
#define LETH_FTP   2

#endif /* SYSTEMS_H */
