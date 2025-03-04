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

#ifndef ETSTDIO_H
#define ETSTDIO_H  1

#include <stdio.h>
#include "libeth.h"

#if __STDC__ || WIN32

/* 
**  get macros 
*/
#define fidel_getc(fp, mylflags) fidel_fgetc(fp, mylflags)
#define fidel_getchar(myflags) fidel_fgetc(stdin, myflags)
#define sget_fchar (tstring, mylflags) get_fchar (tstring, NULL, mylflags)

/*
**  put macros 
*/ 
#define fidel_puts(fstring, mylflags) fidel_fputs(fstring, stdout, mylflags)
#define fidel_putc(fchar, mylflags) fidel_fputc(fchar, stdout, mylflags)
#define fidel_putchar(fchar, mylflags) fidel_fputc(fchar, stdout, mylflags)


/*
**  get functions 
*/


FCHAR get_fchar ( FILE* fp, LibEthFlags* mylflags );

FCHAR* sget_fstring ( unsigned char* tstring, LibEthFlags* mylflags );

FCHAR fidel_fgetc ( FILE* fp, LibEthFlags* mylflags );

FCHAR* fidel_gets ( FCHAR* fillString, LibEthFlags* mylflags );

FCHAR* fidel_fgets ( FCHAR* fillString, int n, FILE* fp, LibEthFlags* mylflags );

FCHAR* fidel_sgets ( FCHAR* fillString, unsigned char* tstring, LibEthFlags* mylflags );

FCHAR* fidel_notfscanf ( FILE* fp, LibEthFlags* mylflags );

int fidel_ungetc ( FCHAR fch, FILE* fp, LibEthFlags* mylflags );

FCHAR fidel_flush ( FILE* fp, LibEthFlags* mylflags );


/*
**  put functions 
*/

int fidel_sputs ( FCHAR* fstring, unsigned char** target, LibEthFlags* mylflags );

int fidel_fputc ( FCHAR fch, FILE* fp, LibEthFlags* mylflags );

int fidel_fputs ( FCHAR* fstring, FILE* fp, LibEthFlags* mylflags );

FCHAR fidel_kbhit ( unsigned char** lastChar, LibEthFlags* mylflags );


#else  /* we do not have ANSI C */


/*
**  get functions 
*/

FCHAR get_fchar    ();

FCHAR sget_fchar   ();

int  sget_fstring  ();

FCHAR fidel_fgetc  ();

int fidel_gets     ();

int fidel_fgets    ();

FCHAR* fidel_notfscanf();

int fidel_ungetc   ();

FCHAR fidel_flush  ();

/*
**  put functions 
*/

int fidel_sputs  ();

int fidel_fputc  ();

int fidel_fputs  ();

FCHAR fidel_kbhit();


#endif /* __STDC__ || WIN32 */

#endif /* ifndef ETSTDIO_H */
