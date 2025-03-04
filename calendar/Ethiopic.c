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


boolean
isBogusEthiopicDate ( date, month, year )
  int date, month;
  int long year;
{

 if ( !( 1 <= date && date <= 30 )
      || !(  1 <= month && month <= 13 )
      || ( month ==  13 && date > 6 )
      || ( month ==  13 && date == 6 && !isEthiopicLeapYear(year) )
    )
   return true;


 return false;
}



int
GregorianToEthiopic ( date, month, year )
  int *date, *month;
  long int *year;
{
long int fixed;


  if ( isBogusGregorianDate ( *date, *month, *year ) )
    return (-1);

  fixed = GregorianToFixed ( *date, *month, *year );
  FixedToEthiopic ( fixed, date, month, year );

  return (1);

}



void
FixedToEthiopic ( fixed, date, month, year )
  long int fixed;
  int *date, *month;
  long int *year;
{

  *year  = quotient ( (4 * (fixed - E_EPOCH) + 1463), 1461 );
  *month = quotient ( (fixed - EthiopicToFixed(1, 1, *year)), 30 ) + 1;
  *date  = (int)( fixed +1L - EthiopicToFixed(1, *month, *year) );

}



long int
EthiopicToFixed ( date, month, year )
  int date, month;
  long int  year;
{


  if ( isBogusEthiopicDate ( date, month, year ) )
    return (-1);

  return ( E_EPOCH - 1
           + 365 * (year - 1L)
           + quotient ( year, 4 )
           + 30 * (month - 1)
           + date );
}



boolean
isEthiopicLeapYear( eYear )
  long int eYear;
{
  eYear += 1;
  return ( !(eYear%4) );
}



enum Languages
getEnvironmentLanguage (void)
{
char* envlang = (char *)getenv("LANG");
int i=0;
enum Languages lang = undef;

	if ( !envlang )
		return ( LETLANGMAJOR );

	while ( envlang[i] )
		  envlang[i] = tolower ( envlang[i++] );

	if ( strlen(envlang) > 3 )
	  {
		if ( !strcmp(envlang, "adari") )
			lang = har;
		else if ( !strcmp(envlang, "afar") )
			lang = aar;
		else if ( !strcmp(envlang, "agew") )
			lang = qim;
		else if ( !strcmp(envlang, "amharic") )
			lang = amh;
		else if ( !strcmp(envlang, "bilin") )
			lang = byn;
		else if ( !strcmp(envlang, "gedio") )
			lang = drs;
		else if ( !strcmp(envlang, "geez") )
			lang = gez;
		else if ( !strcmp(envlang, "oromo") )
			lang = orm;
		else if ( !strcmp(envlang, "qotu") )
			lang = hae;
		else if ( !strcmp(envlang, "seb") )
			lang = guy;
		else if ( !strcmp(envlang, "sidamo") )
			lang = sid;
		else if ( !strcmp(envlang, "siltie") )
			lang = zgu;
		else if ( !strcmp(envlang, "sodo") )
			lang = gru;
		else if ( !strcmp(envlang, "tigre") )
			lang = tig;
		else if ( !strcmp(envlang, "bedo") )
			lang = tig;
		else if ( !strcmp(envlang, "tigrigna") )
			lang = tir;
	  }
	else if ( strlen(envlang) == 3 )
	  {
		while ( !strcmp(ISO639_3Names[lang], envlang) && lang < NUMETHLANGS )
			lang++;		
	  }
	else if ( strlen(envlang) == 2 )
	  {
		while ( !strcmp(ISO639_3Names[lang], envlang) && lang < NUMETHLANGS )
			lang++;		
	  }
	if ( lang == NUMETHLANGS || lang == undef )
		lang = LETLANGMAJOR;

	return ( lang );
}



unsigned char*
getEthiopicDayTranslation ( lang, LCInfo )
  enum Languages lang;
  unsigned int LCInfo;
{
unsigned char *returnString, *returnP;
unsigned int sys;


  if ( lang == undef || lang == useLC )
	lang = getEnvironmentLanguage();

  sys = ( LCInfo & 0x0f00 ) >>  8;
  returnP = LanguageDayNames[lang][sys];

  returnString = (unsigned char*) malloc ( (strlen(returnP)+1) * sizeof (unsigned char));
  strcpy ( returnString, returnP );

  return ( returnString );

}



unsigned char*
getEthiopicDayOfWeek ( date, month, year, lang, LCInfo )
  int date, month;
  long int year;
  enum Languages lang;
  unsigned int LCInfo;
{
unsigned char *returnString, *returnP;
int day;
unsigned int lc, sys;
// unsigned char**** array;


  day = abs( EthiopicToFixed ( date, month, year ) ) % 7;

  if ( lang == undef || lang == useLC )
	lang = getEnvironmentLanguage();

  lc  = ( LCInfo & 0xf000 ) >> 12;
  sys = ( LCInfo & 0x0f00 ) >>  8;

  /*
  array = (unsigned char***)&LanguageDays[lang];
  returnP = array[lc][sys][day];
  */
  returnP = LanguageDays[lang][lc*3+sys][day];

  // returnP = (*LanguageDays)[lang][lc][sys][day];

  returnString = (unsigned char*) malloc ( (strlen(returnP)+1) * sizeof (unsigned char));
  strcpy ( returnString, returnP );

  return ( returnString );

}



unsigned char* 
getEthiopicMonth ( month, lang, LCInfo )
  int month;
  enum Languages lang;
  unsigned int LCInfo;
{
unsigned char *returnString, *returnP;
unsigned int lc, sys;
// unsigned char**** array;


  if ( lang == undef || lang == useLC )
	lang = getEnvironmentLanguage();

  lc  = ( LCInfo & 0xf000 ) >> 12;
  sys = ( LCInfo & 0x0f00 ) >>  8;

  /*
  array = (unsigned char***)&LanguageMonths[lang];
  returnP = array[lc][sys][month];
  */
  returnP = LanguageMonths[lang][lc*3+sys][month - 1];

  // returnP = (*LanguageMonths)[lang][lc][sys][month - 1];

  returnString = (unsigned char*) malloc ( (strlen(returnP)+1) * sizeof (unsigned char));
  strcpy ( returnString, returnP );

  return ( returnString );

}



int
getEthiopicHour ( hour )
  int hour;
{
 return ( (24+hour-6) % 24 );
}


unsigned char*
getEthiopicDayName ( date, month, LCInfo )
  int date, month;
  unsigned int LCInfo;
{
unsigned char *returnString, *returnP;
unsigned int sys;


  sys = ( LCInfo & 0x0f00 ) >>  8;

  if ( month < 13 )
    returnP = EthiopicMonthDayNames[sys][date - 1];
  else  
    returnP = EthiopicPagumeDayNames[sys][date - 1];

  returnString = (unsigned char*) malloc ( (strlen(returnP)+1) * sizeof (unsigned char));
  strcpy ( returnString, returnP );

  return ( returnString );

}



unsigned char*
getEthiopicYearName ( eyear, LCInfo )
  long int eyear;
  unsigned int LCInfo;
{
unsigned char *returnString, *returnP;
unsigned int sys;


  sys = ( LCInfo & 0x0f00 ) >>  8;
  returnP = EthiopicYearNames[sys][abs(eyear%4)];

  returnString = (unsigned char*) malloc ( (strlen(returnP)+1) * sizeof (unsigned char));
  strcpy ( returnString, returnP );

  return ( returnString );

}



int 
EthiopicLastDayOfMonth ( month, year )
  int month;
  long int year;
{
  switch (month)
    {
      case 13:
        if ( isEthiopicLeapYear(year) )
          return 6;
        else
          return 5;
        break;

      default:
        return 30;
        break;
    }
}


unsigned char*
isEthiopianHoliday ( date, month, year, LCInfo )
  int date, month;
  long int year;
  unsigned int LCInfo;
{
unsigned char** EthHolidays;
int *gDate, *gMonth;
long int *gYear;
unsigned char *returnString = NULL, *returnP = NULL;
unsigned int sys;


  sys = ( LCInfo & 0x0f00 ) >>  8;
  EthHolidays = EthiopicHolidays[sys];


  switch ( month )
    {
      case MESKEREM:
         if ( date == 1 )              /* New Years */
           returnP = EthHolidays[0];
         else if ( date == 17 )
           returnP =  EthHolidays[1];  /* Meskel    */
         break;
         
      case TAHSAS:
         if ( date == 29 )             /* Gena      */
           returnP = EthHolidays[2];
         break;

      case TER:
         if ( date == 11 )             /* Temqet    */
           returnP = EthHolidays[3];
         break;

      case YEKATIT:            
         if ( date == 23 )             /* Adwa V-Day   */
           returnP = EthHolidays[4];
         break;

      case MIAZIA:                    

         /* we need to check for easter here... */

         if ( date == 27 )            /* Patriots Day */
           returnP = EthHolidays[8];
         break;

      case GENBOT:                   
         if ( date == 20 )            /* Fall of Dergue */
           returnP = EthHolidays[9];
         break;

      default:
        gDate   = (int *) malloc ( sizeof(int) );
        gMonth  = (int *) malloc ( sizeof(int) );
        gYear   = (long int *) malloc ( sizeof(long int) );

        *gDate  = date;
        *gMonth = month;
        *gYear  = year;

        EthiopicToGregorian ( gDate, gMonth, gYear );
        if ( *gDate == 1 && *gMonth == 5 )  /* May Day/Labour Day */
          {
            free (gDate);
            free (gMonth);
            free (gYear);
            return ( EthHolidays[7] );  
          }

        return ( NULL );
        break;
    }


  if ( returnP )
    {
      returnString = (unsigned char*) malloc ( (strlen(returnP)+1) * sizeof (unsigned char));
      strcpy ( returnString, returnP );
    }

  return ( returnString );

}



unsigned char*
getEthiopicSeason ( date, month, LCInfo )
  int date, month;
  unsigned int LCInfo;
{
unsigned char *returnString, *returnP;
char season = 0;  // MESKEREM 25 - TAHSAS 24 //
unsigned int sys;


if (SENE <= month && date >= 25) 
  season = 3;
else if (MEGABIT <= month && date >= 25) 
  season = 2;
else if (TAHSAS <= month && date >= 25) 
  season = 1;


  sys = ( LCInfo & 0x0f00 ) >>  8;
  returnP = EthiopicSeasonNames[sys][(int)season];


  returnString = (unsigned char*) malloc ( (strlen(returnP)+1) * sizeof (unsigned char));
  strcpy ( returnString, returnP );

  return ( returnString );

}
