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

#include <stdlib.h>
#include <stdio.h>
#include "etstring.h"
#include "unicode.h"
#include "systemio.h"

extern LibEthFlags* FidelFlags;  /* in lib-src/etstdlib.c */

/*
 *  Ok, here's the situation.  The OtherInput and OtherUnput are added for
 *  the tokenizing of the ``other'' allowable input systems (washra, feedel, 
 *  etc) that do not call the lexer.  But the basic needs remain, grab a char
 *  and release a char from either a string or file input source.  So we
 *  reuse the global resources we've got already (iofp, iostring, top).
 *  I think this is the easiest way out....
 */


unsigned char
getOneChar( void )
{
int ch;

/*
 * Since UTF7,8,16 do not use unget, we need not check here
 * but lets keep the code around just in case.
 *
  if ( FidelFlags->holdChars )
    {
      unsigned char c = (unsigned char)FidelFlags->holdChars[ FidelFlags->holdChars[0]++ ];
      if ( !FidelFlags->holdChars[ FidelFlags->holdChars[0] ] )
        flush_stream ( FidelFlags );
      return c;
    }
 */
  if (FidelFlags->stringTop)      /* we are working with a string */
    return (  FidelFlags->stringTop[0] ? *FidelFlags->stringTop++ : 0 );
  else   /* we are working with a file, use getc and cross fingers... */
    {
	  if ( feof(iofp) )
        return ( 0 );
	  else
        return ( (unsigned char)(((ch=fgetc(iofp))==EOF)?0:ch) ); 
    }

}



void
ungetOneChar ( ch )
  int ch;
{

  if (iofp == NULL)    /* we are working with a string */
    {
      if (ch == 0)
        return;
      if (FidelFlags->stringTop) 
        {
          FidelFlags->stringTop--;
	  if ( *FidelFlags->stringTop != (unsigned char)ch )
	    *FidelFlags->stringTop = (unsigned char)ch;
          return;
        }
    }
  else                 /* we are working with a file, use ungetc and cross fingers... */
    {
      ungetc (ch, iofp);
    }

  return;

}



/* Read an 8 bit character from a stream, encoded in one of 4 ways
 *
 *
 */
unsigned char
getToken ( void )
{

  if ( FidelFlags->holdChars )
    /* check if we have a previously read and variant decoded character */
    {
      unsigned char c = (unsigned char)FidelFlags->holdChars[ FidelFlags->holdChars[0]++ ];
      if ( !FidelFlags->holdChars[ FidelFlags->holdChars[0] ] )
        flush_stream ( FidelFlags );
      return c;
    }
  else switch ( FidelFlags->tvIn )
    {
      default   :
           return getOneChar();
           break;

      case utf8 :
           return UTF8ToUnicode();
           break;

      case utf7 :
           return UTF7ToUnicode();
           break;

      case utf16:
           return UTF16ToUnicode();
           break;
    }

}



void
ungetToken ( ch )
  int ch;
{
FCHAR* tempChars;


  switch ( FidelFlags->tvIn )
    {
      case notv :
      case dos  :
           ungetOneChar (ch);
           break;
           
      default:
           if ( !FidelFlags->holdChars )
             {
               FidelFlags->holdChars = (FCHAR *) calloc (3, sizeof(FCHAR));
               FidelFlags->holdChars[1] = ch;
               FidelFlags->holdChars[0] = 1;
             }
           else
             {
               tempChars = FidelFlags->holdChars;
               FidelFlags->holdChars = (FCHAR *) 
                 malloc ((fidel_strlen(FidelFlags->holdChars) + 1) * sizeof(FCHAR));
               FidelFlags->holdChars[1] = ch;
               FidelFlags->holdChars[0] = 1;
               fidel_strcpy (&FidelFlags->holdChars[2], tempChars);
               free ( tempChars );
             }

           break;
    }

}



void
flush_stream ( LibEthFlags* mylflags )
{
  if ( mylflags->holdChars )
    free ( mylflags->holdChars );

  mylflags->holdChars = NULL;
}
