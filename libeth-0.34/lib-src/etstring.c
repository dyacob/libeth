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
#include "fidel.h"
#include "etstring.h"
#include "etctype.h"
#include "lethutil.h"

#include <string.h>


 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_strcpy (target, fstring)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


int
fidel_strcpy (target, fstring) 
  FCHAR* target;
  FCHAR* fstring;
{

  if ( fstring == NULL )
    return (_LET_FAIL);

  
  memcpy ( target, fstring, ((fidel_strlen (fstring) + 1) * sizeof (FCHAR)) );

  return ( 1 );

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_strncpy (target, fstring, n)
//
//  This routine is the simple analog of strncpy for the FCHAR data type.
//  ``n'' is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//  n        -is the number of fchars to copy.
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


int
fidel_strncpy (target, fstring, n)
  FCHAR* target;
  FCHAR* fstring;
  int n;
{

  if ( fstring == NULL )
    return (_LET_FAIL);

  
  memcpy ( target, fstring, (n * sizeof (FCHAR)) );

  return ( n );

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_strcat (target, fstring)
//
//  This routine is the simple analog of strncat for the FCHAR data type.
//  The new string length of the target string is the return value.
//
//  target   -is the address of a pointer to an FCHAR text string whom text is 
//            appended onto. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR*
fidel_strcat (target, fstring)
  FCHAR* target;
  FCHAR* fstring;
{

  if ( fstring == NULL || target == NULL )
    return (NULL);

  memcpy ( &target[fidel_strlen(target)], fstring, (fidel_strlen(fstring) * sizeof (FCHAR)) );
  

  return ( target );

}




 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_strncat (target, fstring, n)
//
//  This routine is the simple analog of strncat for the FCHAR data type.
//  The new string length of the target string is the return value.
//
//  target   -is the address of a pointer to an FCHAR text string whom text is 
//            appended onto. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR*
fidel_strncat (target, fstring, n)
  FCHAR* target;
  FCHAR* fstring;
  int n;
{

  if ( fstring == NULL || target == NULL )
    return (NULL);

  memcpy ( &target[fidel_strlen(target)], fstring, (n * sizeof (FCHAR)) );


  return ( target );

}




 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_strlen (fstring)
//
//  This routine is the simple analog of strlen for the FCHAR data type.
//  The number of charcters up to but NOT including the first NULL (or '\0') is 
//  returned.
//
//  fstring  -is an FCHAR pointer. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


size_t
fidel_strlen (fstring)
  FCHAR* fstring;
{

register int i=0;
 

  if ( fstring == NULL )
    return ( 0 );

  while ( fstring[i] ) 
    i++ ;

  return ( i ) ;   

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_fstrcmp (string1, string2)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


int
fidel_fstrcmp (fstring1, fstring2) 
  FCHAR* fstring1;
  FCHAR* fstring2;
{

int n;

  if ( (n=fidel_strlen(fstring1)) != fidel_strlen(fstring2) )
    return (NIL);

  return ( memcmp ( fstring1, fstring2, n*sizeof(FCHAR) ) );

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_fstrncmp (string1, string2, n)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


int
fidel_fstrncmp (fstring1, fstring2, n) 
  FCHAR* fstring1;
  FCHAR* fstring2;
  int n;
{

  if ( fidel_strlen(fstring1) < n
       || fidel_strlen(fstring2) < n)
    return (NIL);


  return ( memcmp ( fstring1, fstring2, n*sizeof(FCHAR) ) );

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_strcmp (string1, string2)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


int
fidel_strcmp (string1, string2) 
  FCHAR* string1;
  char* string2;
{

register int i=-1;


  if ( fidel_strlen(string1) != strlen(string2) )
    return (NIL);

  
  while ( string1[++i] && string2[i] )
    if (string1[i] != string2[i])
      return ( string1[i] - string2[i] );
   
  return ( 0 );

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_fstrncmp (string1, string2, n)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


int
fidel_strncmp (string1, string2, n) 
  FCHAR* string1;
  char* string2;
  int n;
{

register int i=-1;


  if ( fidel_strlen(string1) < n
       || strlen(string2) < n)
    return (NIL);

  while ( ++i < n )
    if (string1[i] != string2[i])
      return ( string1[i] - string2[i] );

  return ( 0 );

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//
//  Finds the longest common substring between to strings.
//  If two or more substrings of equal length are found only
//  the first will  be returned.  Substrings of unitary length
//  are not returned.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR*
fidel_lcss ( a, b )
    FCHAR *a, *b;
{

register int i,j,k;
int xi, length;
int maxXi = 0, maxLength = 0;
FCHAR* returnString;
int m = fidel_strlen ( a );
int n = fidel_strlen ( b );
FCHAR *x, *y;


  x = a;
  y = b;


  if ( m > n )  /* To minimize the test cycles we want x to be the smaller string */
    {
      x = b;
      y = a;
      i = m;
      m = n;
      n = i;
    }



  for ( k = 0; k < n; k++ )
    {
      /*  Break if we found a substring longer than our remaining string length  */
      if ( maxLength >= (m - k) )
        break;

      /*  Initialize this cycle  */
      j  = k;
      xi = 0;
      length = 0;


      for ( i = 0; i < m; i++ )
        if ( x[i] == y[j] )
          {
            if ( length == 0 )  /* save value of start of match */
              xi = i;
            length++;
            j++;
          }
        else if ( length )
          break;

      if ( length > maxLength )
        {
          maxLength = length;
          maxXi = xi;
          j = k;
        }
    }


  if ( maxLength > 1 )
    {
      returnString = (FCHAR *) malloc ( (maxLength + 1) * sizeof(FCHAR) );
      fidel_strncpy ( returnString, &x[maxXi], maxLength );
      return ( returnString );
    }


  return ( NULL );

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_syllabic_fstrcmp (string1, string2, REQUEST, lang)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


int
fidel_syllabic_fstrcmp (fstring1, fstring2, lang, REQUEST)
  FCHAR *fstring1, *fstring2;
  enum Languages lang;
  unsigned int REQUEST;
{

int comparison;
FCHAR *simpleFString1, *simpleFString2;


  if ( fidel_strlen(fstring1) != fidel_strlen(fstring2) )
    return (NIL);

  simpleFString1 = fidel_simplify (fstring1, lang, REQUEST);
  simpleFString2 = fidel_simplify (fstring2, lang, REQUEST);

  comparison = fidel_fstrcmp ( simpleFString1, simpleFString2 );

  free (simpleFString1);
  free (simpleFString2);

  return (comparison);

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_syllable_fstrncmp (string1, string2, n)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


int
fidel_syllabic_fstrncmp (fstring1, fstring2, n, lang, REQUEST)
  FCHAR* fstring1;
  FCHAR* fstring2;
  int n;
  enum Languages lang;
  unsigned int REQUEST;
{

int comparison;
FCHAR *simpleFString1, *simpleFString2;


  if ( fidel_strlen(fstring1) < n
       || fidel_strlen(fstring2) < n)
    return (NIL);

  simpleFString1 = fidel_simplify (fstring1, lang, REQUEST);
  simpleFString2 = fidel_simplify (fstring2, lang, REQUEST);

  comparison = fidel_fstrncmp ( simpleFString1,simpleFString2, n );

  free (simpleFString1);
  free (simpleFString2);

  return (comparison);

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//
//  Finds the longest common substring between to strings.
//  If two or more substrings of equal length are found only
//  the first will  be returned.  Substrings of unitary length
//  are not returned.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR*
fidel_syllabic_lcss (fstring1, fstring2, lang, REQUEST)
  FCHAR *fstring1, *fstring2;
  enum Languages lang;
  unsigned int REQUEST;
{

FCHAR *simpleFString1, *simpleFString2, *returnFString;


  simpleFString1 = fidel_simplify (fstring1, lang, REQUEST);
  simpleFString2 = fidel_simplify (fstring2, lang, REQUEST);

  returnFString  = fidel_lcss ( simpleFString1, simpleFString2 );

  free (simpleFString1);
  free (simpleFString2);

  return (returnFString);

}


 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_strchr (fstring, fch)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR*
fidel_strchr (fstring, fch)
  FCHAR* fstring;
  FCHAR fch;
{

register int i = -1;


  while ( fstring[++i] && fch != fstring[i] );

  if ( fstring[i] )
    return ( &fstring[i] );
  else
    return ( NULL );

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_strrchr (fstring, fch)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR*
fidel_strrchr (fstring, fch)
  FCHAR* fstring;
  FCHAR fch;
{

register int i=fidel_strlen(fstring);


  while ( fch != fstring[--i] && i );

  if ( fstring[i] )
    return ( &fstring[i] );
  else
    return ( NULL );

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_strchr (fstring, fch)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR*
fidel_memchr (fstring, fch, n)
  FCHAR* fstring;
  FCHAR fch;
  int n;
{

register int i=-1;


  while ( ++i < n && fch != fstring[i] );

  if ( i < n )
    return ( &fstring[i] );
  else
    return ( NULL );

}


 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_strcspn (fstring, fch)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


int
fidel_strcspn (fstring, fchars)
  FCHAR* fstring;
  FCHAR* fchars;
{

register int i, j, k;
int m;


  for ( i=j=k=0; fstring[i] && (fchars[j] != fstring[i]); k++, j=(k)%m, i=k/m );

  return ( i );

}




 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_strpbrk (fstring, fch)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR*
fidel_strpbrk (fstring, fchars)
  FCHAR* fstring;
  FCHAR* fchars;
{

int i;


  if ( (i = fidel_strcspn(fstring, fchars) ) != fidel_strlen(fstring) )
    return ( &fstring[i] );
  else
    return ( NULL );

}




 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_strspn (fstring, fch)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


int
fidel_strspn (fstring, fchars)
  FCHAR* fstring;
  FCHAR* fchars;
{

register int i=-1, j=0;
int m;


  m = fidel_strlen (fchars);
  
  while ( j != m && fstring[++i] )
    for ( j=0; j < m && ( fchars[j] != fstring[i] ); j++ );
   
  if ( i < fidel_strlen(fstring) )
    return ( i );
  else
    return ( 0 );

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_strtok (fstring, fch)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/

static FCHAR *lastFind=NULL;

FCHAR*
fidel_strtok (fstring, fchars)
  FCHAR* fstring;
  FCHAR* fchars;
{

int i;
FCHAR* nextFind;


  lastFind = (fstring == NULL) ? lastFind : fstring;

  if ( lastFind == NULL )
    return (NULL);

  i = fidel_strcspn (lastFind, fchars);

  nextFind = (FCHAR *) malloc ( (i+1) * sizeof(FCHAR) );
  fidel_strncpy (nextFind, lastFind, i);
  nextFind[i] = '\0';
  lastFind = ( i == fidel_strlen(lastFind) )
           ?  NULL 
           :  &lastFind[i+1] 
           ;

  return ( nextFind );

}




 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_syllabic_fstrstr (string1, string2)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR*
fidel_strstr (haystack, needle)
  FCHAR *haystack, *needle;
{

register int i=0;
int m, n;


  if ( (m=fidel_strlen(needle)) > (n=fidel_strlen(haystack)) )
    return (NULL);

  while ( i < (n-m) && haystack[i]
          && (memcmp ( &haystack[i], needle, m*sizeof(FCHAR) )) )
    i++;
   
  if ( i < (n-m) )
    return ( &haystack[i] );
  else
    return ( NULL );

}





 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_syllabic_strchr (fstring, fch)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR*
fidel_syllabic_strchr (fstring, fch, lang, REQUEST)
  FCHAR* fstring;
  FCHAR fch;
  enum Languages lang;
  unsigned int REQUEST;
{

register int i=-1;
FCHAR *simpleFString, *simpleFch, FchString[2];
int *changeList=NULL;


  FchString[0] =  fch;
  FchString[1] = '\0';

  simpleFString = fidel_syllabic_simplify (fstring, lang, REQUEST, &changeList);
  simpleFch     = fidel_simplify (FchString, lang, REQUEST);

  while ( simpleFch[0] != simpleFString[++i] && simpleFString[i] );

  free (simpleFString);
  free (simpleFch);

  if ( changeList != NULL )
    {
      i = remapPosition (i, changeList);
      free ((int *)changeList);
    }

  if ( fstring[i] )
    return ( &fstring[i] );
  else
    return ( NULL );

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_syllabic_strrchr (fstring, fch)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR*
fidel_syllabic_strrchr (fstring, fch, lang, REQUEST)
  FCHAR* fstring;
  FCHAR fch;
  enum Languages lang;
  unsigned int REQUEST;
{

register int i;
FCHAR *simpleFString, *simpleFch, FchString[2];
int* changeList=NULL;

  FchString[0] =  fch;
  FchString[1] = '\0';

  simpleFString = fidel_syllabic_simplify (fstring, lang, REQUEST, &changeList);
  simpleFch     = fidel_simplify (FchString, lang, REQUEST);
  i = fidel_strlen (simpleFString);

  while ( --i >= 0 && (simpleFch[0] != simpleFString[i]) );

  free (simpleFString);
  free (simpleFch);

  if ( changeList != NULL )
    {
      i = remapPosition (i, changeList);
      free ((int *)changeList);
    }

  if ( fstring[i] )
    return ( &fstring[i] );
  else
    return ( NULL );

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_syllabic_memchar (fstring, fch)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR*
fidel_syllabic_memchr (fstring, fch, n, lang, REQUEST)
  FCHAR* fstring;
  FCHAR fch;
  int n;
  enum Languages lang;
  unsigned int REQUEST;
{

register int i=-1;
FCHAR *simpleFString, *simpleFch, FchString[2];
int* changeList=NULL;

  FchString[0] =  fch;
  FchString[1] = '\0';

  simpleFString = fidel_syllabic_simplify (fstring, lang, REQUEST, &changeList);
  simpleFch     = fidel_simplify (FchString, lang, REQUEST);

  while ( ++i < n && simpleFch[0] != simpleFString[i] );

  if ( changeList != NULL )
    {
      i = remapPosition (i, changeList);
      free ((int *)changeList);
    }

  free (simpleFString);
  free (simpleFch);

  if ( i < n )
    return ( &fstring[i] );
  else
    return ( NULL );

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_syllabic_strcspn (fstring, fch)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


int
fidel_syllabic_strcspn (fstring, fchars, lang, REQUEST)
  FCHAR* fstring;
  FCHAR* fchars;
  enum Languages lang;
  unsigned int REQUEST;
{

register int i, j, k;
FCHAR *simpleFString, *simpleFchars;
int *changeList=NULL, m;


  simpleFString = fidel_syllabic_simplify (fstring, lang, REQUEST, &changeList);
  simpleFchars  = fidel_simplify (fchars, lang, REQUEST);

  m = fidel_strlen (simpleFchars);
  for ( i=j=k=0; simpleFString[i] && (simpleFchars[j] != simpleFString[i]); k++, j=(k)%m, i=k/m );
     

  free (simpleFString);
  free (simpleFchars);

  if ( changeList != NULL )
    {
      i = remapPosition (i, changeList);
      free ((int *)changeList);
    }

  return ( i );

}




 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_syllabic_strpbrk (fstring, fch)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR*
fidel_syllabic_strpbrk (fstring, fchars, lang, REQUEST)
  FCHAR* fstring;
  FCHAR* fchars;
  enum Languages lang;
  unsigned int REQUEST;
{

int i;


  if ( (i = fidel_syllabic_strcspn(fstring, fchars, lang, REQUEST)) 
       != fidel_strlen(fstring) )
    return ( &fstring[i] );
  else
    return ( NULL );

}




 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_syllabic_strspn (fstring, fch)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


int
fidel_syllabic_strspn (fstring, fchars, lang, REQUEST)
  FCHAR* fstring;
  FCHAR* fchars;
  enum Languages lang;
  unsigned int REQUEST;
{

register int i=-1, j=0;
FCHAR *simpleFString, *simpleFchars;
int *changeList=NULL, m;


  simpleFString = fidel_syllabic_simplify (fstring, lang, REQUEST, &changeList);
  simpleFchars  = fidel_simplify (fchars, lang, REQUEST);

  m = fidel_strlen (simpleFchars);
  
  while ( j != m && simpleFString[++i] )
    for ( j=0; j < m && ( simpleFchars[j] != simpleFString[i] ); j++ );
   
  free (simpleFString);
  free (simpleFchars);

  if ( changeList != NULL )
    {
      i = remapPosition (i, changeList);
      free ((int *)changeList);
    }

  if ( i < fidel_strlen(fstring) )
    return ( i );
  else
    return ( 0 );

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_syllabic_strtok (fstring, fch)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/

static FCHAR *syLastFind=NULL;

FCHAR*
fidel_syllabic_strtok (fstring, fchars, lang, REQUEST)
  FCHAR* fstring;
  FCHAR* fchars;
  enum Languages lang;
  unsigned int REQUEST;
{

int i;
FCHAR *nextFind=NULL;


  syLastFind = (fstring == NULL) ? syLastFind : fstring;

  if ( syLastFind == NULL )
    return (NULL);

  i = fidel_syllabic_strcspn (syLastFind, fchars, lang, REQUEST);

  nextFind = (FCHAR *) malloc ( (i+1) * sizeof(FCHAR) );
  fidel_strncpy (nextFind, syLastFind, i);
  nextFind[i] = '\0';
  syLastFind = ( i == fidel_strlen(syLastFind) )
           ?  NULL 
           :  &syLastFind[i+1] 
           ;

  return ( nextFind );

}




 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_syllabic_fstrstr (string1, string2, REQUEST, lang)
//
//  This routine is the simple analog of strcpy for the FCHAR data type.
//  The number of charcters up to and including the first NULL (or '\0') is 
//  copied, this number is also the return value.
//
//  target   -is a pointer to an FCHAR text string whom text is copied to. 
//  fstring  -is a pointer to an FCHAR text string from whom text is copied. 
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR*
fidel_syllabic_strstr (haystack, needle, lang, REQUEST)
  FCHAR *haystack, *needle;
  enum Languages lang;
  unsigned int REQUEST;
{

register int i=0;
FCHAR *simpleHaystack, *simpleNeedle;
int *changeList=NULL, m, n;


  if ( (m=fidel_strlen(needle)) > (n=fidel_strlen(haystack)) )
    return (NULL);

  simpleHaystack = fidel_syllabic_simplify (haystack, lang, REQUEST, &changeList);
  simpleNeedle   = fidel_simplify (needle, lang, REQUEST);

  if ( changeList != NULL )
    {
      n = fidel_strlen(simpleHaystack);
      m = fidel_strlen(simpleNeedle);
    }
/* oddly, this fails
*
* if ( changeList == NULL )
*   // fast way //
*   find = (FCHAR *) strstr ( (char *)simpleHaystack, (char *)simpleNeedle );
* else
*/
    /* slow way */
  while ( i < (n-m) && simpleHaystack[i]
          && (memcmp ( &simpleHaystack[i], simpleNeedle, m*sizeof(FCHAR) )) )
    i++;
   

  free (simpleHaystack);
  free (simpleNeedle);

  if ( changeList != NULL )
    {
      i = remapPosition (i, changeList);
      free ((int *)changeList);
    }
  if ( i < (n-m) )
    return ( &haystack[i] );
  else
    return ( NULL );


}



FCHAR*
fidel_syllabic_simplify (fstringIn, lang, REQUEST, changeList)
  FCHAR* fstringIn;
  enum Languages lang;
  unsigned int REQUEST;
  int** changeList;
{

register int i;
int EOS = fidel_strlen(fstringIn), mod, listEnd=0;
FCHAR *fstringOut, *returnString;
int *thisChangeList = NULL;


  if (REQUEST == LETHC_EXACT) 
    {
      returnString = (FCHAR *) malloc ((EOS+1) * sizeof(FCHAR));
      fidel_strcpy (returnString, fstringIn);
      return (returnString);
    }

  fstringOut = (FCHAR *) malloc ((EOS*2+1) * sizeof(FCHAR));
  fidel_strcpy (fstringOut, fstringIn);


  if (REQUEST & LETHC_WAdown)      /* fold Wa unto wa               */
    {
      i = 0;
      while ( fstringOut[i] )
        {
          if ( get_formNumber(fstringOut[i]) == 10 ) 
            {
              fstringOut[i] = set_formNumber (fstringOut[i], SADS); 
              fstringOut[++i] = WAE+RABI;
              if ( i < EOS )
                fidel_strcpy (&fstringOut[i+1], &fstringIn[i]);
              else
                fstringOut[i] = '\0';
              if ( changeList != NULL )
                {
                  grow_changeList (&thisChangeList, 1);
                  listEnd += 1;
                  thisChangeList[0] = -listEnd; 
                  thisChangeList[listEnd] = i; 
                }
            }
          i++;
        }
    }
  if (REQUEST & LETHC_WAup         /* fold wa unto Wa               */
      && !(REQUEST & LETHC_WAdown))
    {
      i = 0;
      while ( fstringOut[i] )
        {
          if ( i && fstringOut[i] == WAE+RABI  
               && get_formNumber(fstringOut[i-1]) == SADS 
               && (mod = get_fmodulo (fstringOut[i-1])) > DIQALA )
            {
              if ( mod == 8 
                   || fstringOut[i-1] == MAE  + SADS
                   || fstringOut[i-1] == BAE  + SADS
                   || fstringOut[i-1] == FAE  + SADS
                   || fstringOut[i-1] == PAE  + SADS
                   || fstringOut[i-1] == GGAE + SADS
                 )
                fstringOut[i-1] = set_formNumber (fstringOut[i-1], DIQALA); 
              else
                fstringOut[i-1] = set_formNumber (fstringOut[i-1], DIQALA_RABI);

              fidel_strcpy (&fstringOut[i], &fstringOut[i+1]);
              if ( changeList != NULL )
                {
                  grow_changeList (changeList, 1);
                  listEnd += 1;
                  (*changeList)[0] = listEnd; 
                  (*changeList)[listEnd] = i+1;
                }
            }
          i++;
        }
    }
  if (REQUEST & LETHC_FAMILY)    /* fold forms le = lu = li = ... */
    {
      i = 0;
      while ( fstringOut[i] )
        fstringOut[i++] = set_formNumber (fstringOut[i], SADS); 
    }
  if (REQUEST & LETHC_PHONETIC)  /* `se = se, he = `he, etc       */
    { 
      i = 0;
      while ( fstringOut[i] )
        {
          if ( isfamily(SZAE, fstringOut[i]) && isEquiv(SZAE, set_formNumber(SZAE, GIZ), lang) )
            fstringOut[i] += ROW*2;
          else if ( lang == amh && isfamily(HHAE, fstringOut[i]) && isEquiv(HHAE, set_formNumber (fstringOut[i], GIZ), lang) )
            {
              if ( fstringOut[i] == HHAE + DIQALA )
                fstringOut[i] = HZAE + DIQALA_RABI;
              else
                fstringOut[i] -= ROW*2;
            }
          else if ( isfamily(HZAE, fstringOut[i]) && isEquiv(HZAE, set_formNumber (fstringOut[i], GIZ), lang) && get_formNumber(fstringOut[i]) < DIQALA)
            fstringOut[i] -= ROW*16;
          else if ( lang == amh && isfamily(OAE, fstringOut[i]) && isEquiv(OAE, set_formNumber (fstringOut[i], GIZ), lang) )
            fstringOut[i] -= ROW*6;
          else if ( isfamily(TSZAE, fstringOut[i]) && isEquiv(TSZAE, set_formNumber (fstringOut[i], GIZ), lang) )
            fstringOut[i] -= ROW;
          i++;
        }
    }
  if (REQUEST & LETHC_HEHA)      /* amharic fold he = ha          */
    {
      i = 0;
      while ( fstringOut[i] )
        {
          if ( (fstringOut[i] == HAE + RABI) 
               || (lang == amh && fstringOut[i] == HHAE + RABI)
               || (fstringOut[i] == HZAE + RABI) )
            fstringOut[i] -= RABI;
          i++;
        }
    }
  if (REQUEST & LETHC_EA)        /* amharic fold  e = a           */
    {
      i = 0;
      while ( fstringOut[i] )
        {
          if ( (fstringOut[i] == AE + RABI) 
               || (lang == amh && fstringOut[i] == OAE + RABI) )
            fstringOut[i] -= RABI;
          i++;
        }
    }
  if (REQUEST & LETHC_QUKUGU)    /* gWu = gu, kWu = ku, qWu = qu  */
    {
      i = 0;
      while ( fstringOut[i] )
        {
          if ( (fstringOut[i] == QAE + DIQALA_SADS) 
               || (fstringOut[i] == KAE + DIQALA_SADS)
               || (fstringOut[i] == GAE + DIQALA_SADS) )
            fstringOut[i] -= (DIQALA_SADS-KAIB);
          i++;
        }
    }
  if (REQUEST & LETHC_QOKOGO)    /* gWe = go, kWe = ko, qWe = qo  */
    {
      i = 0;
      while ( fstringOut[i] )
        {
          if ( (fstringOut[i] == QAE + DIQALA_GIZ) 
               || (fstringOut[i] == KAE + DIQALA_GIZ)
               || (fstringOut[i] == GAE + DIQALA_GIZ) )
            fstringOut[i] -= (DIQALA_GIZ-SABI);
          i++;
        }
    }
  if (REQUEST & LETHC_NETEB)    /* fold forms le = lu = li = ... */
    {
      i = 0;
      while ( fstringOut[i] )
        if ( fstringOut[i] == NETEB )
          fstringOut[i++] = ' '; 
    }


  returnString = (FCHAR *) malloc ((fidel_strlen(fstringOut) + 1) * sizeof(FCHAR));
  fidel_strcpy (returnString, fstringOut);
  free (fstringOut);

  if ( changeList != NULL && thisChangeList != NULL )
    *changeList = thisChangeList;
  return (returnString);

}



boolean
isEquiv (A, B, lang) 
  FCHAR A, B;
  enum Languages lang;
{


  switch ( A )
    {
      case SAE:
      case SZAE: if ( !(B == SAE || B == SZAE) )
                   return ( false );
                 break;

      case HAE:
      case HZAE: if ( !(B == HAE || B == HZAE)
                     && !(lang == amh && (B == HZAE || B == KHAE)) )
                   return ( false );
                 break;

      case HHAE: if ( B != HHAE
                     && !(lang == amh && (B == HAE || B == HZAE || B == KHAE)) )
                   return ( false );
                 break;

      case AE:
      case OAE: if ( !(B == AE || B == OAE) )
                  return ( false );
                break;

      case KHAE: if ( B != KHAE
                     && !(lang == amh && (B == HAE || B == HZAE || B == HHAE)) )
                   return ( false );
                 break;

      case TSAE:
      case TSZAE: if ( !(B == TSAE || B == TSZAE) )
                    return ( false );
                  break;

      default:
        return ( true );
        break;
    }


  return ( true );


}



int
remapPosition (index, changeList)
  int index;
  int* changeList;
{

register int i;
int end = abs(changeList[0]) + 1;


  if ( changeList == NULL || changeList[1] > index )
    return (index);

  for (i=1; i < end; i++)
    if (index >= changeList[i])
      index += (changeList[0] > 0) ? 1 : -1;


  return (index);

}



#ifdef  NO_STRDUP
char *
strdup ( char * source )
{
char * target;

  target = (char *)safemalloc ( sizeof(char) * ( strlen(source) + 1 ) );

  strcpy ( target, source );

  return ( target );
}
#endif /* NO_STRDUP */
