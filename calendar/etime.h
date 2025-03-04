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

#ifndef ETIME_H
#define ETIME_H

#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef BUILDLIBETH
#  include "../include/libeth.h"
#  include "../include/config.h"
#elif USELIBETH
#  include <libeth/libeth.h>
#  include <libeth/config.h>
#elif !LIBETH_H


#ifndef __BCC__
#  include <ctype.h>
#  include <locale.h>
#endif /* __BCC__ */

#if __G_HAVE_BOOL || __GNUG__
  typedef bool boolean;
#else
# define __LETH_HAVE_BOOL 1
  typedef enum {false, true} boolean; 
#endif  /* __G_HAVE_BOOL || __GNUG__ */


#define LETLANGMAJOR  gez

#define NUMLANGS    98
#define NUMETHLANGS 91


enum Languages { aiz, aar, qim, zlb, amh, myo, anu, arv, agj, awn, bsw, myf, bst, bej, bcq, wti, byn, bxe, bwo, bji, dox, cra, dsh, dim, gdl, mdx, doz, gft, gmo, gza, gwd, drs, gez, gto, guk, guy, gru, zgu, hdy, amf, har, hoz, kcx, koe, kbr, ktb, kxh, zkn, zko, kxc, kqy, bza, xuf, kmq, zkw, liq, mpe, mdy, mym, mfx, mys, mur, muz, nrb, noz, nus, nnj, lgn, gax, hae, orm, oyd, rer, ssy, sze, sbf, moy, she, sid, som, suq, tig, tir, tsb, udu, woy, wbc, xan, jnj, zwa, zay, eng, lat, gre, gfx, uni, undef, useLC };
#define ISO639_3 { "aiz", "aar", "qim", "zlb", "amh", "myo", "anu", "arv", "agj", "awn", "bsw", "myf", "bst", "bej", "bcq", "wti", "byn", "bxe", "bwo", "bji", "dox", "cra", "dsh", "dim", "gdl", "mdx", "doz", "gft", "gmo", "gza", "gwd", "drs", "gez", "gto", "guk", "guy", "gru", "zgu", "hdy", "amf", "har", "hoz", "kcx", "koe", "kbr", "ktb", "kxh", "zkn", "zko", "kxc", "kqy", "bza", "xuf", "kmq", "zkw", "liq", "mpe", "mdy", "mym", "mfx", "mys", "mur", "muz", "nrb", "noz", "nus", "nnj", "lgn", "gax", "hae", "orm", "oyd", "rer", "ssy", "sze", "sbf", "moy", "she", "sid", "som", "suq", "tig", "tir", "tsb", "udu", "woy", "wbc", "xan", "jnj", "zwa", "zay", "eng", "lat", "gre" }
#define ISO639_2 { "ai", "aa", "qi", "zl", "am", "ym", "an", "av", "ag", "aw", "bs", "mf", "bt", "bj", "bc", "wt", "by", "bx", "bw", "bu", "dx", "cr", "ds", "di", "dl", "md", "do", "gf", "gm", "gx", "gw", "dr", "gz", "gt", "gk", "gy", "gr", "zg", "hd", "hb", "ad", "ho", "kc", "ke", "kb", "kt", "kh", "zn", "zk", "kx", "kq", "bz", "xu", "mq", "zw", "li", "mp", "dy", "mm", "mx", "ys", "mu", "mz", "nr", "nz", "nu", "nn", "lg", "gx", "ae", "om", "od", "re", "sy", "sz", "sb", "oy", "hs", "sx", "so", "uq", "ig", "ti", "tb", "ud", "wy", "wb", "xa", "jn", "zx", "zy", "la", "el" }

#endif /* LIBETH_H | USELIBETH */

/*  Start Ethiopic Definitions for Calendards  */
/*  First transcribed names for months...      */  

#define MESKEREM    1
#define TEKEMT      2
#define HEDAR       3
#define TAHSAS      4
#define TER         5
#define YEKATIT     6
#define MEGABIT     7
#define MIAZIA      8
#define GENBOT      9
#define SENE       10
#define HAMLE      11
#define NEHASSE    12
#define PAGUMEN    13
#define E_EPOCH  2796  /* the beginning of time as we know it    */

#define NOTIME   0     /* unspecified, the locale is queried     */


/* A bitmap is used for setting formatted output. If all bits      */
/* (fields) are off the default output appears as:                 */
/*                                                                 */
/*                            Ihu Ter 15 19:37:50 EET 1990         */

#define WITHETHHOUR     1  /* Ihu Ter 15 13:37:50 EET 1990         */
#define WITHETHDATE     2  /* Ihu Ter `10`5 13:37:50 EET 1990      */
#define WITHQEN         4  /* Ihu Ter 15 qen 17:37:50 EET 1990     */
#define WITHETHYEAR     8  /* Ihu Ter 15:13:37:50 EET `10`9`100`90 */
#define WITHNETEB      16  /* Ihu:Ter:15:13:37:50:EET:1990         */
#define WITHAM         32  /* Ihu Ter 15 13:37:50 EET 1990 `a.m    */
                           /*       use `ameta mhret, `ameta `alem */
#define WITHSLASH      64  /* Ihu Ter 15 13:37:50 EET 1990 `a/m    */
#define WITHDAYCOMMA  128  /* Ihu, Ter 15 13:37:50 EET 1990 `a/m   */
#define WITHHOUR12    256  /* Ihu, Ter 15  1:37:50 EET 1990 `a/m   */
#define WITHUTF8      512

/* A 16 bit wide data type is assumed.  The first 12 bits are reserved
 * for combinable attributes.  The last 4 bits are should be read as
 * per their decimal value to indicate language specific locale choices
 */
/*                            removed comment to apply
#define WITHONEPREFIX 256  // `100 becomes `1`100                  */
/* #define WITHSERA     1024  // Return SERA Transliterated Names     */
/* #define WITHTRANSCRIPTION      0x2000 */


char* arabtoeth ( long int number, int reduction );

boolean isBogusEthiopicDate ( int date, int month, long int year );
boolean isEthiopicLeapYear ( long int year );
unsigned char* isEthiopianHoliday ( int date, int month, long int year, unsigned int LCINFO );

enum Languages getEnvironmentLanguage (void);

unsigned char* getEthiopicMonth ( int month, enum Languages lang, unsigned int LCInfo );
unsigned char* getEthiopicDayTranslation ( enum Languages lang, unsigned int LCInfo );

int EthiopicToGregorian ( int *date, int *month, long int *year );
void FixedToEthiopic ( long int fixed, int *date, int *month, long int *year );
long int EthiopicToFixed ( int date, int month, long int year );

int EthiopicLastDayOfMonth ( int month, long int year );

unsigned char* getEthiopicDayOfWeek ( int date, int month, long int year, enum Languages lang, unsigned int LCInfo );

unsigned char* getEthiopicDayName ( int date, int month, unsigned int LCInfo );
unsigned char* getEthiopicYearName ( long int eyear, unsigned int LCInfo );

/*  Start Gregorian Definitions for Calendards  */
/*  First transcribed names for months...       */ 

#define JANUARY    1
#define FEBRUARY   2
#define MARCH      3
#define APRIL      4
#define MAY        5
#define JUNE       6
#define JULY       7
#define AUGUST     8
#define SEPTEMBER  9
#define OCTOBER   10
#define NOVEMBER  11
#define DECEMBER  12
#define G_EPOCH    1

boolean isBogusGregorianDate ( int date, int month, long int year );
boolean isLeapYear ( long int year );

int GregorianToEthiopic ( int *date, int *month, long int *year );
void FixedToGregorian ( long int fixed, int *date, int *month, long int *year );
long int GregorianToFixed ( int date, int month, long int year );

int lastDayOfMonth ( int month, long int year );
unsigned char* getMonthName ( int month );


unsigned char* easctime ( struct tm* time, enum Languages in, enum Languages out, unsigned int LCInfo );
unsigned char* strfetime ( struct tm* time, enum Languages in, enum Languages out, unsigned int LCInfo, boolean getHour );
unsigned char* ectime ( time_t* time, enum Languages in, enum Languages out, unsigned int LCInfo );

time_t emktime ( struct tm* time );
struct tm* egmtime ( const time_t* time );
struct tm* elocaltime ( const time_t* time );

int quotient ( double x, double y );
void getUTF8Year ( unsigned char Year[] );

#ifdef NO_LIBM
double floor ( double x );
#endif /* NO_LIBM */

#endif /* ETIME_H */
