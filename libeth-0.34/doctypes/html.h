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

#ifndef HTML_H
#define HTML_H 1

enum HTMLEscapes {Off, BracketOn, AmpersandOn};

int fidel_HTML_sputs ( FCHAR* fstring, unsigned char** htmlOut, int lastSetid,  enum HTMLEscapes* TagOn, unsigned char nestType, int* nestLevel, LibEthFlags* mylflags );

int fidel_filter_HTML ( char** htmlString, enum HTMLEscapes TagOn );

int closeFont ( unsigned char** oldString, int nestLevel, int top, int* end );



/*  There appears to be a variety of ways to write HTML output for multifont
 *  systems:
 *
 *  No Nesting:   
 *
 *     <font face="A">he</font><font face="B">He</font>
 *
 *      ...good  for MonoType and ENHPFR fonts.
 *
 *  One Level of Nesting:
 *
 *     <font face="A">he<font face="B">He</font><font face="C">Xe</font></font>
 *
 *      ...good for the Hadish Alemayehu and other frequency based fonts.
 *
 *  N Levels of Nesting:
 *
 *     <font face="A">he<font face="B">He<font face="C">Xe</font></font></font>
 *
 *
 * Since browsers at the 4.0 level still aren't too smart about nested fonts,
 * we're going to implement only the first two options.
 *
 */
#define NONESTING   0x01  /* never nest                    */
#define NESTONCE    0x02  /* allow one level of nexting    */
#define CLOSESTRING 0x04  /* close all font levels at exit */

#endif /* HTML_H */
