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

#include "doctypes.h"
#include "sysinfo.h"
#include "lethutil.h"
#include "maptypes.h"
#include "rtf.h"
#include "rtf.map"

#ifndef __USE_BSD
#  define bzero(addr, cnt) memset(addr, 0, cnt)
#endif /* __USE_BSD */


int
fidel_RTF_sputs (fstring, rtfOut, lastSetid, idList, set0On, latinId, mylflags)
  FCHAR* fstring;
  char** rtfOut;
  int lastSetid;            /* These next three we need to pass each time */
  int* idList;              /* to maintain state of the process           */
  boolean* set0On;
  int latinId;
  LibEthFlags* mylflags;
{
register int i=0,j;
int outTop=0, outEnd;
int setid=lastSetid, increment;
FCHAR fch;
unsigned char *outString=NULL, *holdCh=NULL;
char* rtfSwitch=NULL;


  if ( fstring == NULL )
    return ( _LET_FAIL );
  mylflags = checkLibEthFlags ( mylflags );

  outEnd = fidel_strlen(fstring) * 10;
  outString = (char *) calloc ( outEnd , sizeof(char) );

  while ( (fch = fstring[i++]) )
    if ( fch < ANSI )
      {

HERE:
        increment = strlen(RTFMAP[fch]);

        if ( setid == NIL || fch <= ' ' ||  isGoodANSI ( fch, mylflags ) )
          {
          /*  No Font Change */
            if ( outEnd <=  outTop + increment )
              outEnd = grow_string ( &outString, increment );
            sprintf ( &outString[outTop], "%s", RTFMAP[fch] );
          }
        else /* switch back to latin */
          {
            get_rtfSwitch (&rtfSwitch, 100+latinId, idList);
            increment += strlen(rtfSwitch);
            if ( outEnd <=  increment )
              outEnd = grow_string ( &outString, increment );
            sprintf ( &outString[outTop], "%s%s", rtfSwitch, RTFMAP[fch] );
            setid = NIL;
            free (rtfSwitch);
          }

        outTop += increment;  /* the position of \0 */
        lastSetid = setid;
      }
    else /* ethiopic */
      {
        holdCh = fidel_sputc (fch, mylflags); 

        /* check for and escape HTML meta characters */

        if ( holdCh == NULL && fch == NETEB )
          {
            fch = '.'; 
            goto HERE;
          }
        else if ( holdCh == NULL && fch == COMMA )
          {
            fch = ','; 
            goto HERE;
          }
        else if (holdCh != NULL)
          {
            if ( (setid = get_setid (fch, mylflags)) != lastSetid )
              {
                get_rtfSwitch (&rtfSwitch, setid, idList);
                increment = strlen(rtfSwitch);
                j = 0;
                while (holdCh[j])
                  increment += strlen( RTFMAP[holdCh[j++]] );

                if ( outEnd <= outTop + increment )
                  outEnd = grow_string ( &outString, increment );

                sprintf ( &outString[outTop], "%s ", rtfSwitch );
                j = 0;
                while (holdCh[j])
                  strcat ( outString, RTFMAP[holdCh[j++]] );

                free ( (char *)rtfSwitch );
                if ( !*set0On && setid == SET0 )
                  *set0On = true;
              }
            else /* no font change */
              {
                increment = 0;
                j = 0;
                while (holdCh[j])
                  increment += strlen( RTFMAP[holdCh[j++]] );

                if ( outEnd <=  outTop + increment )
                  outEnd = grow_string ( &outString, increment );
                j = 0;
                while (holdCh[j])
                  strcat ( outString, RTFMAP[holdCh[j++]] );
              }

          lastSetid = setid;
          outTop += strlen ( &outString[outTop] );
          free ( (unsigned char *)holdCh ); 
          holdCh = NULL;  /* free may not do this.. */
        }
      }


  outString[outTop] = '\0';
  *rtfOut = (char *) malloc ( (strlen(outString) +1) * sizeof(char) );
  strcpy (*rtfOut, outString);
  free ((char *) outString);


  return ( setid );

}



int*
get_RTF_header ( setid, rtfHead, mylflags )
  int setid;
  char** rtfHead;
  LibEthFlags*  mylflags;
{
register int i=0;
char* RTFPrefix;
unsigned char* setName;
char* outString = (char *) malloc ( 512 * sizeof(char) );
char fontString[120];
int tempFaceList[10], *returnFaceList;


  sprintf ( outString, "{\\rtf1\\ansi\\deff0\\deftab720{\\fonttbl{\\f0\\fnil MS Sans Serif;}{\\f1\\fnil\\fcharset2 Symbol;}{\\f2\\fswiss\\fprq2 System;}{\\f3\\fnil Times New Roman;}" );


  bzero (tempFaceList, 10*sizeof(int) );
  for (i=0; i<4; i++)
    tempFaceList[i] = 100 + i;
  i=0;

  while ( setid != NIL )
    {
      get_setRTFPrefix ( setid, &RTFPrefix, mylflags->csOut, mylflags->fontFaceOut );
      tempFaceList[4+i] = setid;
      setid = get_setName ( setid, &setName, mylflags->csOut, mylflags->fontFaceOut );
      sprintf ( fontString, "{\\f%i%s %s;}", 4+i++, RTFPrefix, setName );
      strcat ( outString, fontString );
    }
  strcat ( outString, "}\r\n{\\colortbl\\red0\\green0\\blue0;}\r\n" );
  strcat ( outString, "\\deflang1033\\pard\\plain\\f4\\fs20 " );

  *rtfHead = (char *) malloc ( (strlen(outString) + 1) * sizeof (char) );
  strcpy ( *rtfHead, outString );
  free ( outString );

  tempFaceList[4+i] = NIL;
  returnFaceList = (int *) calloc ( (4+i+1) , sizeof(int) );
  memcpy ( returnFaceList, tempFaceList, (4+i+1)*sizeof(int) );
  return ( returnFaceList );

}



boolean
get_rtfSwitch (rtfSwitch, setid, idList)
  char** rtfSwitch;
  int setid;
  int* idList;
{
register int i=0;


  while ( idList[i] != setid && idList[i] != NIL)
    i++;

  if ( idList[i] == NIL)
    return (false);

  *rtfSwitch = (char *) malloc ( sizeof(char)*5 );  /* good up to 99 fonts */
  sprintf ( *rtfSwitch, "\\f%i", i );

  return (true);

}
