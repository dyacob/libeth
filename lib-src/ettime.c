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

#include "etstdlib.h"
#include "etstdio.h"
#include "ettime.h"
#include "lethutil.h"


FCHAR*
fidel_easctime ( time, in, out, LCInfo, mylflags )
  struct tm* time;
  enum Languages in, out;
  unsigned char LCInfo;
  LibEthFlags* mylflags;
{

char* myTime;
FCHAR* outString;
enum CharacterSet csIn;
enum TransferVariant tvIn;


  mylflags = checkLibEthFlags ( mylflags );

  myTime = easctime ( time, in, out, LCInfo | WITHUTF8 );

  csIn = mylflags->csIn;
  tvIn = mylflags->tvIn;
  mylflags->csIn = unicode;
  mylflags->tvIn = utf8;
  outString = sget_fstring ( myTime, mylflags );
  mylflags->csIn = csIn;
  mylflags->tvIn = tvIn;

  return ( outString );

}



FCHAR*
fidel_ectime ( time, in, out, LCInfo, mylflags )
  time_t* time;
  enum Languages in, out;
  unsigned char LCInfo;
  LibEthFlags* mylflags;
{

char* myTime;
FCHAR* outString;
enum CharacterSet csIn;
enum TransferVariant tvIn;


  mylflags = checkLibEthFlags ( mylflags );

  myTime = ectime ( time, in, out, LCInfo | WITHUTF8 );
  
  csIn = mylflags->csIn;
  tvIn = mylflags->tvIn;
  mylflags->csIn = unicode;
  mylflags->tvIn = utf8;
  outString = sget_fstring ( myTime, mylflags );
  mylflags->csIn = csIn;
  mylflags->tvIn = tvIn;

  return ( outString );

}
