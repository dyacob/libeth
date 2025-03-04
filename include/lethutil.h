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

#ifndef LIBETHP_H

#include "libeth.h"

#if __STDC__ || WIN32

int grow_string ( unsigned char** inString, int incremnt );
int grow_fstring ( FCHAR** inString, int incremnt );
int insertString ( unsigned char* token, unsigned char* insertString, unsigned char** oldString );
int insertFString ( int offset, unsigned char* insertString, FCHAR** oldString );

int grow_array ( void** inString, int newSize, size_t size );
int grow_changeList ( int** inString, int increment );
int remapPosition ( int index, int* changeList );

#else

FCHAR check_fidel_ungetc ();
void QueUnList ();


#endif /* __STDC__ || WIN32 */

#endif /* LIBETHP_H */
