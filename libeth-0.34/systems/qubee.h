/* This is part of the LibEth library, an ANSI C library for Qubeeic
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

#ifndef QUBEE_H
#define QUBEE_H 1

#ifndef SUPPORT_QUBEE
#  define SUPPORT_QUBEE 1
#endif /* SUPPORT_QUBEE */

#define QUBEE_EMAIL "SagalOromo@Aol.Com"
#define QUBEE_WWW   "www.oromosoft.com"
#define QUBEE_FTP   "ftp.oromosoft.com"

#ifndef LIBETH_H
#  include "libeth.h"
#endif /* LIBETH_H */

FCHAR QubeeToUnicode (void);
unsigned char* UnicodeToQubee (FCHAR fch);
char* Qubee_get_netInfo (char INFO);

#endif /* QUBEE_H */
