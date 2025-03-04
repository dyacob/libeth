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

extern unsigned char** EthiopicMonthDayNames[];
extern unsigned char** EthiopicPagumeDayNames[];
extern unsigned char** EthiopicYearNames[];
extern unsigned char** EthiopicHolidays[];
extern unsigned char** EthiopicSeasonNames[];

extern unsigned char* (*(*LanguageMonths[]));
extern unsigned char* (*(*LanguageDays[]));
extern unsigned char** LanguageDayNames[];

extern unsigned char* EnglishMonths[]; 
extern unsigned char* EnglishDays[];

extern unsigned char* ISO639_3Names[];
extern unsigned char* ISO639_2Names[];

extern const unsigned short int GregorianDaysPerMonth[];

extern unsigned char* EthiopicSpaces[];
extern unsigned char* AmetaMihret_WithDot[];
extern unsigned char* AmetaMihret_WithSlash[];
extern unsigned char* AmetaAlem_WithDot[];
extern unsigned char* AmetaAlem_WithSlash[];
