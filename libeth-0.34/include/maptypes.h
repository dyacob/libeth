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

#ifndef MAPTYPES_H
#define MAPTYPES_H 1

# define SET0  0x00
# define SET1  0x01
# define SET2  0x02
# define SET3  0x03
# define SET4  0x04
# define SET5  0x05
# define SET7  0x06
# define SET8  0x07
 
# define SETW  0x10   /* for two char libiovelars (KWa) = (K)(wa)     */
# define SETD  0x11   /* for extended diqala detection in 1 set fonts */
# define SETX  0x12   /* for substituted characters                   */
# define SETID 0x13   /* for end of sets                              */
# define NOCH  '\0'   /* for empty fields                             */
# define NUL   0x00

# define DIACRITIC 0x01
# define SAFEANSI  0x02

typedef struct {
  unsigned char* fidel; 
  unsigned char* vowel;  /* We can not easily combine the id and set fields   */
  unsigned char    set;  /* anymore after the discover of diacritic+multifont */
} LETCHAR;               /* encoded fonts.                                    */


#endif /* MAPTYPES_H */


