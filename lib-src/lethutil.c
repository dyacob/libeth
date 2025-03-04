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

#include <stdio.h>
#include "etstdlib.h"
#include "etstring.h"
#include "lethutil.h"


int
grow_string ( inString, increment )
  unsigned char** inString;
  int increment;  /* contains the request for the '\0' terminator */
{

unsigned char* outString;
int newStrlen;


  newStrlen = increment + strlen (*inString);
  outString = (unsigned char *) calloc ( newStrlen, sizeof(unsigned char) );
  /* if ( !outString )
    fprintf (stderr, "\aCalloc failure in grow_string\n"); */
  strcpy ( outString, *inString );
  free ( (unsigned char *) *inString );
  *inString = outString;

  return (newStrlen);

}



int
grow_fstring ( inString, increment )
  FCHAR** inString;
  int increment;    /* contains the request for the '\0' terminator */
{

FCHAR* outString;
int newStrlen;


  newStrlen = increment + fidel_strlen ( *inString );
  outString = (FCHAR *) malloc ( newStrlen * sizeof(FCHAR) );
  fidel_strcpy ( outString, *inString );
  free ( (FCHAR *) *inString );
  *inString = outString;

  return (newStrlen);

}



int
grow_changeList (inString, increment)
  int** inString;
  int increment;     /* contains the request for the '\0' terminator */
{

int* outString;
int newStrlen=1;


  if ( *inString != NULL )
    newStrlen += abs((*inString)[0]);

  newStrlen += increment;

  outString = (int *) malloc ( newStrlen * sizeof(int) );

  if ( *inString != NULL )
    {
      memcpy ( outString, *inString, (abs((*inString)[0])+1) * sizeof(int) );
      free ( (int *) *inString );
    }
  *inString = outString;

  return (newStrlen);

}



int
grow_array (inString, newSize, size)
  void** inString;
  int newSize;       /* contains the request for the '\0' terminator */
  size_t size;       /* size of type */
{

void* outString =* inString;
int newLen = newSize * size;


  outString = (void *) malloc ((size_t)newLen );

  if ( *inString != NULL )
    {
      memcpy ( outString, *inString, (newLen) );
      if ( size == sizeof(char) )
        free ( *(char **)inString );
      else if ( size == sizeof(FCHAR) )
        free ( *(FCHAR **)inString );
      else if ( size == sizeof(int) )
        free ( *(int **)inString );
    }
  *inString = outString;

  return (newLen);

}



int
insertString ( token, insertString, oldString ) 
  unsigned char* token, *insertString;
  unsigned char** oldString;
{

unsigned char *newString=NULL, *mark=NULL, *insertPoint=NULL;


  insertPoint = (unsigned char *)strstr ( *oldString, token );

  newString = (unsigned char *) malloc ( (strlen(*oldString) + strlen(insertString) - strlen(token) + 1) * sizeof(unsigned char) );

  mark = *oldString;
  while ( mark < insertPoint )
    *newString = *mark++;
  strcpy ( newString+(mark-*oldString), insertString );
  strcat ( newString, mark+1 );
  free (*oldString);
  *oldString = newString;

  return (1);

}



int
insertFString ( offset, insertString, oldString ) 
  int            offset;
  unsigned char* insertString;
  FCHAR**        oldString;
{

FCHAR *newString=NULL, *mark=NULL, *insertPoint=NULL;
register int i=0;


  i  = fidel_strlen(*oldString);
  i += strlen(insertString) + 1;

  newString = (FCHAR *) malloc ( i * sizeof(FCHAR) );

  i = 0;
  mark = *oldString;
  insertPoint = *oldString + offset;

  while ( mark < insertPoint )
    *newString = *mark++;
  while ( insertString[i] )
    newString[mark-*oldString + i] = insertString[i++];

  fidel_strcat ( newString, mark+1 );
  free (*oldString);
  *oldString = newString;


  return (1);

}
