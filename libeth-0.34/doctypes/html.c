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
#include "html.h"


int
fidel_HTML_sputs (fstring, htmlOut, lastSetid, TagOn, nestType, nestLevel, mylflags)
  FCHAR* fstring;
  unsigned char** htmlOut;
  int lastSetid;            /* These next three we need to pass each time */
  enum HTMLEscapes* TagOn;  /* to maintain state of the process           */
  unsigned char nestType;
  int* nestLevel;
  LibEthFlags* mylflags;
{
register int i=0;
int outTop=0, fidelStrlen, outEnd;
int setid=lastSetid, increment;
FCHAR fch;
unsigned char *outString=NULL, *holdCh=NULL, *setName=NULL, ansi;

  if ( fstring == NULL )
    return ( _LET_FAIL );
  mylflags = checkLibEthFlags ( mylflags );

  fidelStrlen = fidel_strlen (fstring);
  outEnd = fidelStrlen * 10;
  outString = (unsigned char *) calloc ( outEnd , sizeof(unsigned char) );

  while ( (fch = fstring[i++]) )
    if ( fch < ANSI )
      {
        if ( fch == '<' ) {  /* Don't drop font tags for HTML escapes */
          if ( !fidel_strncmp ( &fstring[i], "/sera>", 6 ) )
            {
              i += 6;
              if ( setid == NIL )
                fch = fstring[i++];
              else  /* close font to switch back to latin */
                {
                  outTop += closeFont (&outString, *nestLevel, outTop, &outEnd);
                  *nestLevel = 0;
                  setid = NIL;
                  *TagOn = BracketOn;
                  continue;
                }
            }
          else
            *TagOn = BracketOn;
        }

HERE:
	ansi = 0x0;
        if ( setid == NIL || fch <= ' ' || *TagOn || (fch != '&' && (ansi = isGoodANSI ( fch, mylflags ))) )
          {
          /*  No Font Change */
            if ( outEnd <= (outTop + 1) )
              outEnd = grow_string ( &outString, 2 );
            outString[outTop++] = (ansi) ? ansi : (unsigned char)fch;
            if ( (fch == '>' && *TagOn == BracketOn) )
              *TagOn = Off;
          }
        else /* close font to switch back to latin */
          {
            outTop += closeFont (&outString, *nestLevel, outTop, &outEnd);
            sprintf ( &outString[outTop++], "%c", (unsigned char) fch );
            *nestLevel = 0;
            setid = NIL;
          }

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
        else if ( holdCh == NULL && fch == EQUESTIONMARK )
          {
            fch = '?'; 
            goto HERE;
          }
        else if ( holdCh != NULL ) {
        if ( strstr (holdCh, "<" ) )
          insertString ( "<", "&lt;", &holdCh );
        else if ( strstr (holdCh, ">" ) )
          insertString ( ">", "&gt;", &holdCh );
        else if ( strstr (holdCh, "&" ) )
          insertString ( "&", "&amp;", &holdCh );

        if ( (setid = get_setid (fch, mylflags)) != lastSetid )
          {
            get_setName (setid, &setName, mylflags->csOut, mylflags->fontFaceOut);
            increment = strlen(setName) + strlen(holdCh) + 1 ;

            if ( *nestLevel == 0 )
             /* we are opening the font for the first time */
              {
                if ( outEnd <= (outTop + increment + 14) )
                  outEnd = grow_string ( &outString, increment+14 );
                sprintf ( &outString[outTop], "<font face=\"%s\">%s", setName, holdCh );
                *nestLevel = 1;
              }
            else if ( nestType & NESTONCE )
              /* In this case nest only once and only within the "Primary" font.     */
              /* So the nestLevel is never greater than two.                         */
              {
                if ( setid && *nestLevel == 1 && lastSetid == 0 )
                  {
                  /* we are nesting A->B, A->C                                       */
                     if ( outEnd <= (outTop + increment + 14) )
                       outEnd = grow_string ( &outString, increment+14 );
                     sprintf ( &outString[outTop], "<font face=\"%s\">%s", setName, holdCh );
                     *nestLevel = 2;
                  }
                else if ( setid == 0 && *nestLevel == 2 )
                  /* we are already nested and changing from font A->B->A            */
                  /* this is the most frequent case, the others are comparively rare */
                  {
                    if ( outEnd <= (outTop + increment + 7) )
                      outEnd = grow_string ( &outString, increment+7 );
                    sprintf ( &outString[outTop], "</font>%s", holdCh );
                    *nestLevel = 1;
                  }
                else /* ( setid && *nestLevel == 1,2 ) */
                  /* no nest leave change we are doing either A->B->C or B->C->B     */
                  /* or this is the first time we open font A, B->C->A               */
                  {
                    if ( outEnd <= (outTop + increment + 21) )
                      outEnd = grow_string ( &outString, increment+21 );
                    sprintf ( &outString[outTop], "</font><font face=\"%s\">%s", setName, holdCh );
                  }
              }
            else /* ( nestType & NONESTING ) */
              {
                if ( outEnd <= (outTop + increment + 21) )
                  outEnd = grow_string ( &outString, increment+21 );
                sprintf ( &outString[outTop], "</font><font face=\"%s\">%s", setName, holdCh );
                *nestLevel = 1;
              }
            free ( (char *)setName );
          }
        else  /* no font change */
          {
            increment = strlen(holdCh) + 1 ;
            if ( outEnd <=  (outTop + increment) )
              outEnd = grow_string (&outString, increment );
            sprintf (&outString[outTop], "%s", holdCh);
          }

          lastSetid = setid;
          outTop += strlen ( &outString[outTop] );
          free ( (unsigned char *)holdCh ); 
          holdCh = NULL;  /* free may not do this.. */
        }

      }

  outString[outTop] = '\0'; 

  if ( (nestType & CLOSESTRING) && *nestLevel )
    {
      outTop += closeFont (&outString, *nestLevel, outTop, &outEnd);
      *nestLevel = 0;
    }

  *htmlOut = (unsigned char *) malloc ( (outTop + 1) * sizeof(unsigned char) );

  strcpy (*htmlOut, outString);

  free ((unsigned char *) outString);

  return ( setid );

}



int
fidel_filter_HTML (htmlString, TagOn)
  char** htmlString;
  enum HTMLEscapes TagOn;
{
char *BracketLeft=NULL, *BracketRight=NULL,
     *Ampersand=NULL,   *Semicolon=NULL;


  BracketLeft  = strstr ( *htmlString, "<" );
  BracketRight = strstr ( *htmlString, ">" );
  Ampersand    = strstr ( *htmlString, "&" );
  Semicolon    = strstr ( *htmlString, ";" );

  if ( !TagOn ) {
    if ( BracketLeft != NULL
        && ( Ampersand == NULL
            || (BracketLeft < Ampersand) ) )
      {
        TagOn = BracketOn;
        *htmlString = BracketLeft;
      } 
    else if ( Ampersand != NULL )
      {
        TagOn = AmpersandOn;
        *htmlString = Ampersand;
      } 
  }
  if ( (TagOn == BracketOn && BracketRight != NULL)
      && ( Semicolon == NULL
          || (BracketRight < Semicolon) ) )
    {
      TagOn = Off;
      *htmlString = Ampersand;
    } 
  else if ( TagOn == AmpersandOn && Semicolon != NULL )
    {
      TagOn = Off;
      *htmlString = Semicolon;
    } 

  return (TagOn);

}


int
closeFont (oldString, nestLevel, top, end)
  unsigned char** oldString;
  int nestLevel;
  int  top;   /* top is the current strlen of oldString,   */
  int* end;   /* grow_string works with respect to strlen  */
{
int i;
int increment    = 7*nestLevel + 1;
int lengthNeeded = top + increment;


  if ( *end <= lengthNeeded )
   *end = grow_string ( oldString, increment );

  for (i=0; i<nestLevel; i++)
    strcat ( *oldString, "</font>" );

  return ( --increment );

}
