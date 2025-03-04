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
#include "languages/languages.h"
#include "languages/languages.data"
#include <stdio.h>
#include <math.h>


unsigned char*
ectime ( time, in, out, LCInfo )
  time_t* time;
  enum Languages in, out;
  unsigned int LCInfo;
{
struct tm* tp = localtime (time);
int *date, *month = (int *)malloc(sizeof(int));
int *year;

 

  date  =& tp->tm_mday;
 *month =  tp->tm_mon + 1;   /* +1 because months start at 0 in the struct tm */
  year  =& tp->tm_year;
 *year += 1900L;

  GregorianToEthiopic ( date,  month,  (long int *)year ); 

  tp->tm_mon   = *month - 1;
  tp->tm_year -= 1900;

  return ( easctime ( tp, in, out, LCInfo) );

}


struct tm*
elocaltime ( time )
  const time_t* time;
{
struct tm* tp = localtime (time);
int *date, *month = (int *)malloc(sizeof(int));
int *year;

 

  date  =& tp->tm_mday;
 *month =  tp->tm_mon + 1;
  year  =& tp->tm_year;
 *year += 1900L;

  GregorianToEthiopic ( date,  month,  (long int *)year ); 

  tp->tm_mon   = *month - 1;
  tp->tm_year -= 1900;

  return ( tp );

}



struct tm*
egmtime ( time )
  const time_t* time;
{
struct tm* tp = gmtime (time);
int *date, *month = (int *)malloc(sizeof(int));
int *year;

 

  date  =& tp->tm_mday;
 *month =  tp->tm_mon + 1;
  year  =& tp->tm_year;
 *year += 1900L;

  GregorianToEthiopic ( date,  month,  (long int *)year ); 

  tp->tm_mon   = *month - 1;
  tp->tm_year -= 1900;

  return ( tp );

}




unsigned char*
easctime ( time, in, out, LCInfo )
  struct tm* time;
  enum Languages in, out;
  unsigned int LCInfo;
{
  return ( strfetime (time, in, out, LCInfo, true) );
}


time_t
emktime ( etime )
  struct tm* etime;
{
int *date, *month = (int *)malloc(sizeof(int));
int *year;
struct tm time;

  time.tm_mday  = etime->tm_mday;
  time.tm_mon   = etime->tm_mon ;
  time.tm_year  = etime->tm_year;
  time.tm_hour  = etime->tm_hour;
  time.tm_min   = etime->tm_min;
  time.tm_sec   = etime->tm_sec;
  time.tm_wday  = etime->tm_wday;
  time.tm_yday  = etime->tm_yday;
  time.tm_isdst = etime->tm_isdst;

  date  =& time.tm_mday;
 *month =  time.tm_mon + 1;
  year  =& time.tm_year;
 *year += 1900;

  EthiopicToGregorian ( date,  month,  (long int *)year ); 

  time.tm_mon   = *month - 1;
  time.tm_year -= 1900;

  return ( mktime ( &time ) );

}


void
getUTF8Year (Year)
  unsigned char Year[];
{
unsigned char* aNumber;
int iNumber, i=0, j=0, mapYear[20];

  if ( Year[0] == '-' )
    aNumber = strtok ( &Year[1], "`" );
  else
    aNumber = strtok ( Year, "`" );

  do
    {
      iNumber = atoi (aNumber);
      if ( iNumber < 20 )
        mapYear[i++] = iNumber - 1;
      else if ( iNumber <= 100 )
        mapYear[i++] = 8 + iNumber/10;
      else 
        mapYear[i++] = 19;

    }
  while ( ( aNumber = strtok(NULL, "`") ) );

  iNumber = i;
  i = ( Year[0] == '-' ) ? 1 : 0 ;
  for ( j=0; j < iNumber; j++ )
    {
      strcpy ( &Year[i], EthiopicUTF8Numerals[mapYear[j]] );
      i += 3;
    }

  return;

}


boolean
isEthiopicLanguage ( lang )
  enum Languages lang;
{
	return ( lang < eng ) ? true : false;
}


unsigned char*
strfetime ( time, in, out, LCInfo, getHour )
  struct tm* time;
  enum Languages in, out;
  unsigned int LCInfo;
  boolean getHour;
{

int hour, *date=(int *)malloc(sizeof(int)), *month=(int *)malloc(sizeof(int));
long int  *year=(long int *)malloc(sizeof(long int));
unsigned char *OutTime=(char *)malloc(120*sizeof(unsigned char));  /* a really big string */
unsigned char *ReturnTime, *shiftString;
unsigned char *Day, *Month, CommaSpace[5], Date[8], Year[20], Space[4], *Qen;
boolean ethTimeIn = false, ethTimeOut = false;
unsigned short sys;


  if ( isEthiopicLanguage ( in ) )
    ethTimeIn = true;
  if ( isEthiopicLanguage ( out ) )
    ethTimeOut = true;


  if ( !(in == eng || ethTimeIn || out == eng || ethTimeOut) )
    {
      /* error response */
      return (NULL);
    }

  *date  = time->tm_mday;
  *month = time->tm_mon + 1;
  *year  = time->tm_year + 1900;
   hour  = time->tm_hour;

  sys = (LCInfo & 0x0f00 ) >> 8;

  if ( !ethTimeIn )
    {
      if ( !ethTimeOut )
        {
          if ( getHour )
            return ( asctime ( time ) );

          strftime (OutTime, 120, "%A, %B %d, %Y", time);
          while ( ( shiftString = strstr (OutTime, " 0") ) != NULL )
            strcpy ( shiftString+1, shiftString+2 );
          return ( OutTime );
        }

      /* if we reach here out is amh or tir */
      GregorianToEthiopic ( date, month, year );
    }


  if ( !ethTimeOut ) /* if we enter here "in" was Ethiopic */
    {
      EthiopicToGregorian ( date, month, year );

      /* We do not have the address of structure time so when 
         we exit the routine time will not be modified        */

      time->tm_mday  =  *date;
      time->tm_mon   =  *month - 1;
      time->tm_year  =  *year - 1900;

      if ( !ethTimeOut )
        {
          if ( getHour )
            return ( asctime ( time ) );

          strftime (OutTime, 120, "%A, %B %d, %Y", time);
          while ( ( shiftString = strstr (OutTime, " 0") ) != NULL )
            strcpy ( shiftString+1, shiftString+2 );
          return ( OutTime );
        }

    }


  if ( ethTimeOut )
    {

     /* if out is unknown get from env */

      Day   = getEthiopicDayOfWeek (*date, *month, *year, out, LCInfo);
      Month = getEthiopicMonth (*month, out, LCInfo);
      if (LCInfo & WITHQEN)
        Qen = getEthiopicDayTranslation (out, LCInfo);

      if ( LCInfo & WITHNETEB )
        strcpy (Space, EthiopicSpaces[sys]);
	  else
        strcpy (Space, " ");

      if ( LCInfo & WITHETHHOUR ) 
        hour = (24+hour-6)%24;
	  
      if ( LCInfo & WITHHOUR12 ) 
        hour %= 12;

      if ( LCInfo & WITHETHDATE ) 
        // if (LCInfo & WITHUTF8)
        if ( sys == 1 || sys == 2 )
          strcpy (Date, arabtoeth (*date,2));
        else
          {
            strcpy (Date, arabtoeth (*date,0));
            getUTF8Year (Date);
          }
      else
        sprintf (Date, "%i", *date);

      if ( LCInfo & WITHETHYEAR ) 
        if ( sys == 1 || sys == 2 )
        // if (LCInfo & WITHUTF8)
          strcpy (Year, arabtoeth (*year,2));
        else
          {
            strcpy (Year, arabtoeth (*year,0));
            getUTF8Year (Year);
          }
      else
        sprintf (Year, "%li", *year);

      if ( LCInfo & WITHDAYCOMMA ) 
        {
            // if (LCInfo & WITHUTF8)
            if ( sys == 1 || sys == 2 )
              strcpy (CommaSpace, ", ");
            else
              if ( LCInfo & WITHNETEB )
                strcpy (CommaSpace, "፣");
              else
                strcpy (CommaSpace, "፣ ");
        }
        else
          strcpy (CommaSpace, Space);

      if ( getHour )
        {
          if ( LCInfo & WITHQEN )
            sprintf ( OutTime, "%s%s%s%s%s%s%s%s%02i:%02i:%02i%s%s",
                      Day,   CommaSpace,
                      Month, Space,
                      Date,  Space,
                      Qen,   Space,
                      hour,  time->tm_min, time->tm_sec, Space,
                      Year
                    );
          else
            sprintf ( OutTime, "%s%s%s%s%s%s%02i:%02i:%02i%s%s",
                      Day,   CommaSpace,
                      Month, Space,
                      Date,  Space,
                      hour,  time->tm_min, time->tm_sec, Space,
                      Year
                    );
        }
      else
        {
          if ( LCInfo & WITHQEN )
            sprintf ( OutTime, "%s%s%s%s%s%s%s%s%s",
                      Day,   CommaSpace,
                      Month, Space,
                      Date,  Space,
                      Qen,   Space,
                      Year
                    );
          else
            sprintf ( OutTime, "%s%s%s%s%s%s%s",
                      Day,   CommaSpace,
                      Month, Space,
                      Date,  Space,
                      Year
                    );
        }


      if ( (LCInfo & WITHAM) || *year < 0 )
        {
          strcat (OutTime, Space);
          if (*year > 0)
            {
              if (LCInfo & WITHSLASH)
                strcat (OutTime, AmetaMihret_WithSlash[sys]);
              else 
                strcat (OutTime, AmetaMihret_WithDot[sys]);
            }
          else
            {
              if (LCInfo & WITHSLASH)
                strcat (OutTime, AmetaAlem_WithSlash[sys]);
              else 
                strcat (OutTime, AmetaAlem_WithDot[sys]);
            }
        }
    }

  if ( getHour )
    strcat (OutTime, "\n");

  ReturnTime = (char *)malloc( (strlen(OutTime)+1)*sizeof(unsigned char) );
  strcpy (ReturnTime, OutTime);

  free (date);
  free (month);
  free (year);

  free (Day);
  free (Month);
  free (OutTime);

  return (ReturnTime);

}




#ifndef LIBETH_H

#ifndef __USE_BSD
#  define bzero(addr, cnt) memset(addr, 0, cnt)
#endif /* __USE_BSD */

 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//
//  arabtoeth (number, reduction)
//
//  Convert a string of ASCII digits into Ethiopic Numbers under a supported
//  encoding system.  The string length of the converted text is returned.  
//
//  number    -is a pointer to an FCHAR text string of any supported character
//             coding system.
//  reduction -is the address of an FCHAR pointer whom we will direct to the 
//             output fstring allocated from memory by this routine.
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
#endif /* LIBETH_H */



int
quotient ( x, y )
  double x;
  double y;
{
  return ( (int)floor(x/y) );
}


#ifdef NO_LIBM
double
floor (double x)
{
long int front, back;

  front = (int) x; 

  if (x > 0)
    return ( (double)front );

  /* else x is negative ... */


  back = 10*fabs(x) - 10*abs(front); 

 return  ( back < 5 ) ? (double)front : (double)(front-1);

}
#endif /* NO_LIBM */
