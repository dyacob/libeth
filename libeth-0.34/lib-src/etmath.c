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

#include <string.h>
#include "fidel.h"
#include "etmath.h"
#include "etstdlib.h"
#include "etstdio.h"
#include "etctype.h"
#include "lethutil.h"

#ifndef __USE_BSD
#  define bzero(addr, cnt) memset(addr, 0, cnt)
#endif /* __USE_BSD */


 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//
//  ftoi (fstring, mylflags)
//
//  Convert and return an integer value from a string of Ethiopic Numbers.
//  
//
//  fstring   -is a pointer to an FCHAR text string of any supported character
//             coding system.
//  mylflags -is a SERA Flag structure which MUST contain a valid input and
//            output type.
//
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/

int
ftoi (fstring)
  FCHAR* fstring;
{

FCHAR fdig;
register int i=0, n;
int numout, power=1;


  if ( fstring == NULL )
    return ( _LET_FAIL );

  if ( fstring[0] == '-' )
    i++;

  n = 0;
  while ( (fdig = fstring[n++]) )
    if ( !isfdigit (fdig) )
      return ( _LET_FAIL );
  n -= 2;

  i = numout = 0;

  if ( fstring[0] == '-')
    i++;

  /*
   *  Read right to left to get the orders of 10 right
   */
  while ( (n-i+1) )
    {
      fdig = fstring[n-i];  
      if ( fdig == HUNDRED || fdig == TENTHOUSAND )
	    {
		  i++;
          if ( !fstring[n-i] )  /* in case `100 or `10000 are on the far left */
            {
              if ( fdig == TENTHOUSAND )
                power *= 10;
              numout += power;
            }
          continue;
	    }

      if ( fdig >= TEN )
        fdig -= 9;

      fdig -= (ONE-1) ; 

      /* 
       *  Rather than link in libm just for one routine the ``power''
       *  variable below is used.
	   *
	   *  numout += fdig * pow ( (double) 10, (double) i++); 
	   */
      numout += fdig * power;
      power *= 10;
	  i++;
    }

  return ( fstring[0] == '-') ? -numout : numout ;


}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//
//  arabtof (number)
//
//  Convert a string of ASCII digits into Ethiopic Numbers under a supported
//  encoding system.  The string length of the converted text is returned.  
//
//  number   -is a pointer to an FCHAR text string of any supported character
//            coding system.
//  target   -is the address of an FCHAR pointer whom we will direct to the 
//            output fstring allocated from memory by this routine.
//
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR*
arabtof (number)
  char* number;
{

FCHAR *ethioNumString, *returnString;
register int i, j, m, n;
char asciiOne, asciiTen;
FCHAR gezOne, gezTen;
int place ;
/**
 *struct lconv* localeconv(void);
 *
 * At the moment this struct is giving me empty string for 
 * localeconv()->thousands_sep and localeconv()->mon_thousands_sep
 * so, guess we'll be using it later...
 *
 */


  if ( number == NULL )
    return ( _LET_FAIL );

  n = strlen ( number ) - 1;

	    
  for (i = 0; number[i] ; i++ )  
    if ( !(isdigit(number[i]) 
           || number[i] == '.'
	       || number[i] == ',') )
      return ( _LET_FAIL );

  ethioNumString = (FCHAR *) malloc ( (4*i+1) * sizeof (FCHAR) );  /* hopefully big enough... */

  m = 0;

  for ( place = 0; place <= n; place++ )
    {

      asciiTen = '0';
      gezOne = gezTen = 0x0;
      asciiOne = number[n-place]; 

      place++;

      if ( place <= n )
          asciiTen = number[n-place]; 

      if ( ( asciiOne == '0' && asciiTen == '0' ) && ( place < n ) )
        continue;

      /* We form a group if: 
       *   1) the tens place is non zero.
       *   2) the ones place is greater than one.
       *   3) we are working on the first position group.
       */
      if ( asciiTen != '0' || asciiOne > '1'  || place == 1 )
        {
          if ( asciiOne != '0' )
            gezOne = asciiOne + (ONE - '1');  /* map onto Ethiopic "ones" */

          if ( asciiTen != '0' )
            gezTen = asciiTen + (TEN - '1');  /* map onto Ethiopic "tens" */
	    
        }

      if ( place > 1 )
        {
            for ( j=0; j < (place/4); j++ )
              ethioNumString[m++] = TENTHOUSAND;

            if ( (place/2)%2 )
              ethioNumString[m++] = HUNDRED;
        }

      if ( gezOne )
        ethioNumString[m++] = gezOne;

      if ( gezTen )
        ethioNumString[m++] = gezTen;

    }

  returnString = ( FCHAR * ) malloc ( (m+1) * sizeof (FCHAR) );

  for (i=m; i>0; i--)
    returnString[i-1] = ethioNumString[m-i];

  returnString[m] = '\0';

  free ( ethioNumString );

  return ( returnString );

}


 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//
//  arabtoeth (number, target)
//
//  Convert a string of ASCII digits into Ethiopic Numbers under a supported
//  encoding system.  The string length of the converted text is returned.  
//
//  number   -is a pointer to an FCHAR text string of any supported character
//            coding system.
//  target   -is the address of an FCHAR pointer whom we will direct to the 
//            output fstring allocated from memory by this routine.
//
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


char*
arabtoeth (number, reduction)
  long int number;
  int reduction;
{

register int i, j;
int One, Ten, end;
char OneChar[10], TenChar[10], ThisGroup[40];
int place;
char Number[80];
char *NumString, *FinalNumString;
int odd;


  if ( number == 0 )
    {
      FinalNumString = (char *) malloc ( 2 * sizeof(char) );
      strcpy ( FinalNumString, "0" );
      return ( FinalNumString );
    }

  i = j = 0;
  sprintf (Number, "%i", abs(number));

  end = strlen (Number);
  odd = end%2;
  if ( end == 1 )
    place = 0;
  else
    place = (end-2)/2 + odd;

  NumString = (char *) calloc ( (16*end+1) , sizeof (char) );  /* hopefully big enough... */

  while ( i < end )
    {
      bzero (OneChar, 10);
      bzero (TenChar, 10);
      bzero (ThisGroup, 40);
      One = Ten = 0;

      if (!odd || (odd && i))         /* read only one digit the first time */
        Ten  = Number[i++] - '0';     /* for odd years                      */
      One  = Number[i++] - '0';
      
      if ( One > 1 || (One && (!place || Ten)) )/* One > 1 unless first cycle */
        {
          sprintf ( OneChar, "`%i", One );
          strcat ( ThisGroup, OneChar );
        }
      if ( Ten )
        {
          sprintf ( TenChar, "`%i0%s", Ten, ThisGroup );
          strcpy ( ThisGroup, TenChar );
        }
      if ( place && (Ten || One) )
        {
          if (place%2)
           strcat ( ThisGroup, "`100" );
          for ( j=0; j<place/2; j++ )
           strcat ( ThisGroup, "`10000" );
        }


      strcat (NumString, ThisGroup);
      place--;
    }


  if ( reduction )
    {
      end = strlen(NumString)-1;
      for (i=2,j=2; i<=end; i++)
        if ( NumString[i] != '`' )
          NumString[j++] = NumString[i];

      NumString[j] = '\0';
    }
  if ( reduction == 2 )
    {
      end = j-1;
      for (i=2,j=2; i<=end; i++)
        if ( NumString[i] != '1' || i == end )
          NumString[j++] = NumString[i];

      NumString[j] = '\0';
    }

  if (number < 0)
    {
      FinalNumString = (char *) malloc ( (strlen(NumString)+2) * sizeof(char) );
      sprintf (FinalNumString, "-%s", NumString);
    }
  else
    {
      FinalNumString = (char *) malloc ( (strlen(NumString)+1) * sizeof(char) );
      strcpy (FinalNumString, NumString);
    }

  free (NumString);

  return ( FinalNumString );

}



FCHAR*
itof ( iNumber )
  int iNumber;
{

char aNumber[12];  /* 2^32 is 10 digits */


  sprintf ( aNumber, "%i", iNumber );
  return ( arabtof(aNumber) );

}



FCHAR*
AddEthiopicEthiopic ( A, B )
  FCHAR *A, *B;
{

  return ( itof(ftoi(A) + ftoi(B)) );

}



FCHAR*
SubtractEthiopicEthiopic ( A, B )
  FCHAR *A, *B;
{

  return ( itof(ftoi(A) - ftoi(B)) );

}



FCHAR*
MultiplyEthiopicEthiopic ( A, B )
  FCHAR *A, *B;
{

  return ( itof(ftoi(A) * ftoi(B)) );

}



FCHAR*
DivideEthiopicEthiopic ( A, B )
  FCHAR *A, *B;
{

int a = ftoi(A);
int b = ftoi(B);


  return ( a > b ) ? itof((int)(a/b)) : itof(0) ;

}


FCHAR*
PowerEthiopicEthiopic ( A, B )
  FCHAR *A, *B;
{

  return ( itof( pow(ftoi(A),ftoi(B)) ) );

}



FCHAR*
AddEthiopicInteger ( A, B )
  FCHAR *A;
  int    B;
{

  return ( itof(ftoi(A) + B) );

}



FCHAR*
SubtractEthiopicInteger ( A, B )
  FCHAR *A;
  int    B;
{

  return ( itof(ftoi(A) - B) );

}



FCHAR*
MultiplyEthiopicInteger ( A, B )
  FCHAR *A;
  int    B;
{

  return ( itof(ftoi(A) * B) );

}



FCHAR*
DivideEthiopicInteger ( A, B )
  FCHAR *A;
  int    B;
{

int a = ftoi(A);
int b = B;

  return ( a > b ) ? itof((int)(a/b)) : itof(0) ;

}



FCHAR*
DivideIntegerEthiopic ( A, B )
  int    A;
  FCHAR *B;
{

int a = A;
int b = ftoi(B);

  return ( a > b ) ? itof((int)(a/b)) : itof(0) ;

}



FCHAR*
PowerEthiopicInteger ( A, B )
  FCHAR *A;
  int    B;
{

  return ( itof(pow(ftoi(A),B) ) );

}



FCHAR*
PowerIntegerEthiopic ( A, B )
  int    A;
  FCHAR *B;
{

  return ( itof( pow(A,ftoi(B)) ) );

}
