/* This is part of the LibEth library, an ANSI C library for Ethiopic
   text and information processing (http://libeth.netpedia.net).
   Copyright (C) 1995-2000 Daniel Yacob.

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

#include "etime.h"
#include "etimeex.h"

static long int yearFromFixed ( long int fixed );


boolean
isBogusGregorianDate ( date, month, year )
  int date, month;
  long int year;
{

  if ( !(    1 <= month && month <= 12 )
       || !( 1 <= date  && date  <= GregorianDaysPerMonth[month-1] )
       || ( date == 29  && month == 2 && !isLeapYear(year) )
     )
    return true;

  return false;
}



int
EthiopicToGregorian ( date, month, year )
  int *date, *month;
  long int *year;
{
long int fixed;


  if ( isBogusEthiopicDate ( *date, *month, *year ) )
    return (-1);


  fixed = EthiopicToFixed ( *date, *month, *year );
  FixedToGregorian ( fixed, date, month, year );

  return (1);

}



void
FixedToGregorian ( fixed, date, month, year )
  long int fixed;
  int *date, *month;
  long int *year;
{
char correction;
int priorDays;

  *year  = yearFromFixed( fixed );

  /*
   * this is a problem since we are not checking for the -1 returned
   * by GregorianToFixed if the date is bogus
   * we should check it and return the value (an exception) if returned
   */
  priorDays = (int)( fixed - GregorianToFixed( 1, 1, *year ) );

  correction = ( fixed < GregorianToFixed( 1, 3, *year ) )
             ? 0
             : ( isLeapYear(*year) ? 1 : 2 )
             ;

  *month = quotient ((12 * (priorDays + correction) + 373), 367);
  *date = (int)(fixed - GregorianToFixed( 1, *month, *year ) + 1L);

}



long int 
GregorianToFixed (date, month, year)
  int date, month; 
  long int  year;
{


  if ( isBogusGregorianDate ( date, month, year ) )
    return (-1);


  return ( 365 * (year - 1L)
           + quotient((year - 1L) , 4) 
           - quotient((year - 1L) , 100) 
           + quotient((year - 1L) , 400) 
           + quotient((367 * month - 362) , 12) 
           + (month <= 2 ? 0 : (isLeapYear(year) ? -1 : -2))
           + date );

}



boolean 
isLeapYear ( year )
  long int year;
{
  return ( !(year%4) && ( (year%100) || !(year%400) ) );
}



int 
lastDayOfMonth ( month, year )
  int month;
  long int year;
{
  switch (month)
    {
      case 2:
        if ( isLeapYear(year) )
          return 29;
        else
          return 28;
        break;

      case 4:
      case 6:
      case 9:
      case 11:
        return 30;
        break;

      default:
        return 31;
        break;
    }
}



static long int
yearFromFixed ( fixed )
  long int fixed;
{
long int d0 = fixed - 1L;           /* 1 is the Gregorian EPOCH */
long int n400 = quotient(d0, 146097);
int        d1 = d0 % 146097;
int      n100 = quotient(d1, 36524);
int        d2 = d1 % 36524;
int        n4 = quotient(d2 , 1461);
int        d3 = d2 % 1461;
int        n1 = quotient(d3, 365);
/* int        d4 = d3 % 365 + 1; */
long int year = 400 * n400 + 100 * n100 + 4 * n4 + n1;


  return ( (n100 == 4 || n1 == 4) ? year : year + 1 );
}
