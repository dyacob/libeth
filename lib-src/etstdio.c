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

#include "fidel.h"
#include "etstdlib.h"
#include "etstdio.h"
#include "etstring.h"
#include "etctype.h"
#include "lethutil.h"

#ifdef SUPPORT_HTML
# include "../doctypes/html.h"
#else
# include "html.h"
#endif /* SUPPORT_HTML */

extern char* ISO639_3Names[];     /* in etstdlib.c */
extern unsigned char* fidel_sputc ( FCHAR fch, LibEthFlags* mylflags );


#ifdef SUPPORT_MULTISTREAM_UNGET
/*
 *  This section is private to the etstdio module.  It is optionally
 *  compiled since the check for unbegotten characters impacts performance
 *  and the author has never used ungetting so...
 */
typedef struct UGList {
   FCHAR fch;
   FILE* fp;
   struct UGList* next;
}  UnGetList;

static UnGetList *ulist = NULL;
static FCHAR check_fidel_ungetc ( FILE* fp );
static void QueUnList ( UnGetList** q, FCHAR fch, FILE* fp );

#endif /* SUPPORT_MULTISTREAM_UNGET */


 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_fgetc (fp, mylflags)
//
//  This routine is the simple analog of fgetc for the FCHAR data type.
//  Return address of next token from a file of SERA text.
//  The address of the returned token is specified by the character coding
//  system passed in mylflags->out.
//
//  fp       -is a file pointer to SERA text
//  mylflags -is a SERA Flag structure which MUST contain a valid input and
//            output type.
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR
fidel_fgetc (fp, mylflags)
  FILE* fp;
  LibEthFlags* mylflags;
{

  if ( fp == NULL || feof(fp) )                   /* bail if pointing nowhere */
    return ( _LET_FAIL );
  mylflags = checkLibEthFlags ( mylflags );


#ifdef SUPPORT_MULTISTREAM_UNGET
FCHAR start = 0;
  if ( (start = check_fidel_ungetc ( fp )) )      /* reget ungot char, if any */
    return ( start );                  /* return address if we were given one */
#endif /* SUPPORT_MULTISTREAM_UNGET */


  return ( get_fchar(fp, mylflags) );     /* get and return next token  */

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_gets (target, mylflags)
//
//  This routine is the simple analog of gets for the FCHAR data type.
//  This routine scans a single string from stdin.  The string length of
//  the target string is the return value.
//
//  target   -is an FCHAR pointer whom we will direct to an FCHAR output 
//            string allocated from memory by this routine.
//  mylflags -is a SERA Flag structure which MUST contain a valid input and
//            output type.
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR*
fidel_gets (fillString, mylflags)
  FCHAR* fillString;
  LibEthFlags* mylflags;
{

FCHAR start = 0;
FCHAR *holdText, *returnP;
register unsigned long int i = 1;
unsigned char *text = (char *) malloc (WSIZE*sizeof(unsigned char));
int end;


  if ( fgets ( text, WSIZE, stdin ) == NULL )  /* get next string from stream */
    return NULL;                
  mylflags = checkLibEthFlags ( mylflags );

  while ( text[end=(strlen(text)-1)] != '\n' && !feof(stdin) )
    {                                          /* keep grabbing text until \n */
      grow_string ( &text, WSIZE );
      fgets ( &text[(i++)*WSIZE-1], WSIZE, stdin );
    }
  text[end] = '\0';
  holdText = (FCHAR *) malloc ( (end+2) * sizeof (FCHAR) );


#ifdef SUPPORT_MULTISTREAM_UNGET
  start = check_fidel_ungetc ( stdin );           /* reget ungot char, if any */
  if ( start )                     /* if token returned, add to start of list */
    {
      holdText[0] = start;
      start = 1;
    }
#endif /* SUPPORT_MULTISTREAM_UNGET */


  i = start;
  mylflags->stringTop = text;
  while ( (holdText[i++] = get_fchar ( NULL, mylflags)) );
  i--;

  holdText[i] = '\0';

  if ( fillString == NULL )
    fillString = (FCHAR *) malloc ( (i+1) * sizeof(FCHAR) );

  fidel_strcpy (fillString, holdText);

  returnP = fillString;

  free ((FCHAR *)holdText);

  return ( returnP );

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_fgets (target, n, fp, mylflags)
//
//  This routine is the simple analog of fgets for the FCHAR data type.
//  This routine scans a single string of length ``n'' from the file pointed 
//  to by ``fp''.  ``n'' is also the return value.
//
//  target   -is the address of an FCHAR pointer whom we will direct to an FCHAR
//            output string allocated from memory by this routine.
//  n        -is the number of fchars to copy.
//  fp       -is a file pointer to SERA text
//  mylflags -is a SERA Flag structure which MUST contain a valid input and
//            output type.
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR*
fidel_fgets (fillString, n, fp, mylflags)
  FCHAR* fillString;
  int n;
  FILE* fp;
  LibEthFlags* mylflags;
{

FCHAR start = 0;
FCHAR fch = 0, *holdText, *returnP;
register unsigned long int i;
int newStrlen = n;
#ifdef SUPPORT_HTML
enum HTMLEscapes TagOn = Off;
#endif /* SUPPORT_HTML */


  if ( ferror(fp) || feof(fp) || fp == NULL || n < 1 )
    return ( NULL );
  mylflags = checkLibEthFlags ( mylflags );

  holdText = ( FCHAR * ) malloc ( (n+1) * sizeof (FCHAR) );


#ifdef SUPPORT_MULTISTREAM_UNGET
  start = check_fidel_ungetc ( fp );              /* reget ungot char, if any */
  if ( start )                     /* if token returned, add to start of list */
    {
      holdText[0] = start;
      start = 1;
    }
#endif /* SUPPORT_MULTISTREAM_UNGET */


#ifdef SUPPORT_HTML
  if ( mylflags->cstIn != html ) {
    for (i = start; i < n && (fch = get_fchar(fp, mylflags)); i++)
      holdText[i] = fch; 
    }
  else
    {
      for (i = start; i < n && (fch = get_fchar(fp, mylflags)); i++)
        {
          holdText[i] = fch; 
          if ( fch == '<' && TagOn == Off )
            TagOn = BracketOn;
          if ( fch == '&' && TagOn == Off )
            TagOn = AmpersandOn;
          if ( fch == '>' && TagOn == BracketOn )
            TagOn = Off;
          if ( fch == ';' && TagOn == AmpersandOn )
            TagOn = Off;
        }
      if ( TagOn != Off )
        {
          grow_fstring ( &holdText, WSIZE );
          newStrlen += WSIZE;               
        }                                   
      if ( TagOn == BracketOn )
        {
          while ( (holdText[i++] = get_fchar (fp, mylflags)) != '>' )
            if ( i > newStrlen )
              {
                grow_fstring ( &holdText, WSIZE );
                newStrlen += WSIZE;
              }
        }
      if ( TagOn == AmpersandOn )
         while ( (holdText[i++] = get_fchar (fp, mylflags)) != ';' 
                 && (i < newStrlen)
               );   /* No Escape should be this long, if so bail... */

        TagOn = Off;
    }
#else
  for (i = start; i < n && (fch = get_fchar(fp, mylflags)); i++)
    holdText[i] = fch; 
#endif /* SUPPORT_HTML */

  holdText[i] = '\0';

  if ( fillString == NULL )
    fillString = (FCHAR *) malloc ( (i+1) * sizeof(FCHAR) );

  fidel_strcpy (fillString, holdText);

  returnP = fillString;

  free ((FCHAR *)holdText);

  return ( returnP );

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_sgets (target, n, fp, mylflags)
//
//  This routine is the simple analog of fgets for the FCHAR data type.
//  This routine scans a single string of length ``n'' from the file pointed 
//  to by ``fp''.  ``n'' is also the return value.
//
//  target   -is the address of an FCHAR pointer whom we will direct to an FCHAR
//            output string allocated from memory by this routine.
//  mylflags -is a SERA Flag structure which MUST contain a valid input and
//            output type.
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR*
fidel_sgets (fillString, tstring, mylflags)
  FCHAR* fillString;
  unsigned char* tstring;
  LibEthFlags* mylflags;
{

FCHAR* returnP;


  returnP = sget_fstring (tstring, mylflags);

  if ( fillString == NULL )
    fillString = (FCHAR *) malloc ( fidel_strlen(returnP) * sizeof(FCHAR) );

  fidel_strcpy (fillString, returnP);

  free (returnP);

  returnP = fillString;

  return ( returnP );

}



#ifdef SUPPORT_MULTISTREAM_UNGET
 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_ungetc (fch, fp, mylflags)
//
//  This routine is the simple analog of ungetc for the FCHAR data type.
//  The specified character ``fp'' is ungot from the file stream ``fp''.
//  As with ANSI C the file pointer fp is NOT decremented by one char.
//  The ungot character, fch, is stored in a linked list and associated 
//  with the fp file pointer.  The next ungot character for stream fp then 
//  replaces the last stored value.
//
//  fp       -is a file pointer to SERA text
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


int
fidel_ungetc ( fch, fp, mylflags )
  FCHAR fch;
  FILE* fp;
  LibEthFlags* mylflags;  /* ignored in the multistream version */
{

UnGetList* startOfList;


  if ( fp == NULL || feof(fp) )                         /* bail if pointing nowhere */
    return ( _LET_FAIL );

  startOfList = ulist;

  while ( ulist->fp != fp && ulist->next != NULL )     /* check list for existing definition */
    ulist = ulist->next;

  if ( ulist->fp == fp )                               /* copy over old, as per ungetc */
    {
      ulist->fch = fch;
      ulist = startOfList;
      return ( _LET_SUCCESS );
    }

  QueUnList ( &ulist, fch, fp );                         /* add file and char entry to existing list */
  ulist = startOfList;
  return ( _LET_SUCCESS );

}



FCHAR
check_fidel_ungetc ( fp )
  FILE* fp;
{

UnGetList *startOfList, *utemp;
FCHAR fch;


  if ( ulist == NULL )
    return ( 0 );

  startOfList = utemp = ulist;

  while ( ulist->fp != fp && ulist->next != NULL )     /* check list for existing definition */
    ulist = ulist->next;

  if ( ulist->fp == fp )                               /* copy over old, as per ungetc */
    {
      fch = ulist->fch;
      while ( utemp->next != ulist )
        utemp = utemp->next;

      utemp->next = ulist->next;                       /* deletion of node */
      free ( ulist );
      ulist = startOfList;

      return ( fch );
   }

  ulist = startOfList;
  return ( 0 );                                        /* no chars stored */

}


static void
QueUnList ( q, fch, fp )
  UnGetList** q;
  FCHAR fch;
  FILE* fp;
{

  (*q)->next = ( UnGetList * ) malloc ( sizeof (UnGetList) );
  *q = (*q)->next ;

  (*q)->fch  = fch ;
  (*q)->fp   = fp;
  (*q)->next = NULL ;

  return;

}

#else  /* stream is tied to mylflags */

int
fidel_ungetc ( fch, fp, mylflags )
  FCHAR fch;
  FILE* fp;               /* ignored in the multistream version */
  LibEthFlags* mylflags;
{
FCHAR* tempChars;


  if ( !mylflags->holdChars )
    {
      mylflags->holdChars = (FCHAR *) calloc (3, sizeof(FCHAR));
      mylflags->holdChars[1] = fch;
      mylflags->holdChars[0] = 1;
    }
  else
    {
      tempChars = mylflags->holdChars;
      mylflags->holdChars = (FCHAR *) 
        malloc ((fidel_strlen(mylflags->holdChars) + 1) * sizeof(FCHAR));
      mylflags->holdChars[1] = fch;
      mylflags->holdChars[0] = 1;
      fidel_strcpy (&mylflags->holdChars[2], tempChars);
      free ( tempChars );
    }


  return ( _LET_SUCCESS );

}

#endif /* SUPPORT_MULTISTREAM_UNGET */



/*
 *
 *  Following Will be Primarily The "Put" Analogs for Ethiopic
 *
 */



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_sputs (fstring, target, mylflags)
//
//  Convert a string of FCHAR addresses from a supported encoding system into 
//  another.  The string length of the converted text is returned.  
//
//  fstring  -is a pointer to an FCHAR text string from whom tokens are 
//            scanned. 
//  target   -is the address of a character pointer whom we will direct to the 
//            output string allocated from memory by this routine.
//  mylflags -is a SERA Flag structure which MUST contain a valid input and
//            output type.
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/

extern boolean SERA_isGoodANSI ( FCHAR fch );

int
fidel_sputs (fstring, target, mylflags)
  FCHAR* fstring;
  unsigned char** target;
  LibEthFlags* mylflags;
{

unsigned char *hold, *holdCh;
int n, fudgeLength=24;           /* a large value that we will never exceed */
register unsigned long int i;    /* 24 = uname + debug                      */
enum Languages ethLang, notEthLang, lastLang;


  if ( fstring == NULL )                        /* bail if pointing nowhere */
    return ( _LET_FAIL );
  mylflags = checkLibEthFlags ( mylflags );

  n = fidel_strlen (fstring); 
  hold = (unsigned char *) calloc ( (fudgeLength*n+1) , sizeof(unsigned char) );

  if ( mylflags->csOut == sera )
    {
      if ( mylflags->out->l == amh 
           || mylflags->out->l == tir 
           || mylflags->out->l == gez )
        {
          ethLang = lastLang = mylflags->out->l;

          if ( mylflags->major->l == ethLang )
            notEthLang = mylflags->minor->l;
          else 
            notEthLang = mylflags->major->l;
        }
      else
        {
          notEthLang = lastLang = mylflags->out->l;
  
          if ( mylflags->major->l == notEthLang )
            ethLang = mylflags->minor->l;
          else 
            ethLang = mylflags->major->l;
        }

      for ( i = 0; i < n; i++ )
        {
          if ( (holdCh = fidel_sputc (fstring[i], mylflags)) != NULL )
            {
              /* This section of code for SERA unfortunately slows things
                 down for all systems.  We can not do the lastchar check in
                 the SERA module because it is not known at that level.
                 Making a new libeth flag to store it ( ->lastCharOut )
                 could be a solution.
               */
              if ( isethiopic(fstring[i]) )
                {
                  /*  This is the right idea but poorly implemented.        */
                  if ( (lastLang != amh && lastLang != tir && lastLang != gez) )
                    {
                      strcat (hold, "\\~");
                      strcat ((char *)hold, (char *)ISO639_3Names[ethLang]);
                      strcat (hold, " ");
                      lastLang = ethLang;
                    }
                  else if ( i && (AE <= fstring[i] && fstring[i] <= AE+DIQALA) && get_formNumber(fstring[i-1]) == SADS )
                    strcat (hold, "'");

                  strcat (hold, holdCh);
                }
              else if ( !SERA_isGoodANSI (fstring[i]) 
                        && (lastLang == amh || lastLang == tir || lastLang == gez) )
                {
                  strcat (hold, "\\");
                  strcat (hold, holdCh);
                  strcat (hold, " ");
                }
              else if ( isalpha (fstring[i])
                        && (lastLang == amh || lastLang == tir || lastLang == gez) )
                {
                  strcat (hold, "\\~");
                  strcat ((char *)hold, (char *)ISO639_3Names[notEthLang]);
                  strcat (hold, " ");
                  strcat (hold, holdCh);
                  lastLang = notEthLang;
                }
              else
                strcat (hold, holdCh);

              free (holdCh);
            }
        }
    }
  else  /* not sera */
    {
      for ( i = 0; i < n; i++ )
        {
          if ( (holdCh = fidel_sputc (fstring[i], mylflags)) != NULL )
            {
              strcat (hold, holdCh);
              free (holdCh);
            }
        }
    }


  *target  = ( unsigned char * ) malloc ( ((n=strlen(hold))+1) * sizeof(unsigned char) );
  strcpy ( *target, hold );
  free ( hold );

  return ( n );

}


int
fidel_fputc (fch, fp, mylflags)
  FCHAR fch;
  FILE* fp;
  LibEthFlags* mylflags;
{

  mylflags = checkLibEthFlags ( mylflags );

  if (fch == '\0' || fp == NULL || feof(fp))
      return ( fputc (fch, fp) );

  
  return ( fprintf (fp, "%s", fidel_sputc (fch, mylflags) ) );

}


int
fidel_fputs (fstring, fp, mylflags)
  FCHAR* fstring;
  FILE* fp;
  LibEthFlags* mylflags;
{

unsigned char* pstring;
int result;


  if ( fp == NULL || feof(fp) || fstring == NULL )
    return ( _LET_FAIL );
  mylflags = checkLibEthFlags ( mylflags );
  
  fidel_sputs (fstring, &pstring, mylflags);
  
  result = fputs (pstring, fp);

  free (pstring);

  return ( result );

}


 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//
//  fidel_kbhit (mylflags, lastChar)
//
//  Read next key strike and return new fidel char.
//
//  lastChar -is the last ASCII char read from the keyboard.  It may be NULL.
//  mylflags -is a SERA Flag structure which MUST contain a valid input and
//            output type.
//
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR
fidel_kbhit (lastChar, mylflags)
  unsigned char** lastChar;
  LibEthFlags* mylflags;
{

unsigned char temp[3];
FCHAR* fch;


  mylflags = checkLibEthFlags ( mylflags );

  if ( **lastChar == '\0' )
    {
      temp[0] = getchar ();
      temp[1] = '\0';
    }
  else
    {
      temp[0] = **lastChar; 
      temp[1] = getchar ();
      temp[2] = '\0';
    }

  fch = sget_fstring (temp, mylflags);
 
  **lastChar = temp[1]; 

  return ( fch[0] );

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  sget_fstring (tstring, mylflags)
//
//  Convert a string of SERA text into the requested output character coding 
//  system.  The addresses of the returned token list is specified by the 
//  character coding system passed in mylflags->out.  The string length of the 
//  converted letter is returned.  
//
//  target   -is an address of a FCHAR pointer whom we will direct to the 
//            the transcribed output.
//  tstring  -is a character pointer to SERA text
//  mylflags -is a LEth Flag structure which MUST contain a valid input and
//            output type.
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR*
sget_fstring (tstring, mylflags)
  unsigned char* tstring;
  LibEthFlags* mylflags;
{

FCHAR *holdText=NULL, *returnString=NULL;
register unsigned long int i;


  if ( tstring == NULL )                   /* bail if pointing nowhere */
    return ( NULL );
  mylflags = checkLibEthFlags ( mylflags );

  holdText = (FCHAR *) malloc ( (strlen(tstring) + 1) * sizeof (FCHAR) );

  i = 0;
  mylflags->stringTop = tstring;
  while ( (holdText[i++] = get_fchar (NULL, mylflags)) );
  i--;

  holdText[i] = '\0';

  if ( (returnString = (FCHAR *) malloc ( (i+1) * sizeof (FCHAR) )) )
    fidel_strcpy ( returnString, holdText );

  free ((FCHAR *)holdText);

  return (returnString);

}


 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_notfscanf (fp, mylflags)
//
//  This routine scans a single string from the file pointed to by ``fp''.
//  notfscanf is more like fgets sans the requirement for the number of
//  tokens to be scanned or much like fscanf(fp, "%s", target).
//
//  fp       -is a file pointer to SERA text
//  mylflags -is a LibEthFlag structure which MUST contain a valid input and
//            output type.
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


FCHAR*
fidel_notfscanf (fp, mylflags)
  FILE* fp;
  LibEthFlags* mylflags;
{

FCHAR start=0, fch, *holdText=NULL, *returnString=NULL;
register unsigned long int i;


  if ( fp == NULL || feof(fp) )            /* bail if pointing nowhere */
    return ( _LET_FAIL );
  mylflags = checkLibEthFlags ( mylflags );

  holdText = (FCHAR *) calloc ( WSIZE, sizeof (FCHAR) );

#ifdef SUPPORT_MULTISTREAM_UNGET
  start = check_fidel_ungetc ( fp );              /* reget ungot char, if any */
  if ( start )                     /* if token returned, add to start of list */
    {
      holdText[0] = start;
      start = 1;
    }
#endif /* SUPPORT_MULTISTREAM_UNGET */


  i = start;
  while ( (fch = get_fchar(fp, mylflags) )
          &&  fch != ' '
   /*     &&  fch != WORDSPACE     ...later, make an sscanf like this */
          &&  fch != '\n'
          &&  fch != '\t')  
   {
     holdText[i++] = fch;
     if ( !(i%WSIZE) )
       grow_fstring ( &holdText, WSIZE );
   }

  holdText[i] = '\0';

  if ( !i ) 
    {
      free ( holdText );
      return ( NULL );
    }

  fidel_ungetc ( fch, fp, mylflags );

  returnString = ( FCHAR * ) malloc ( (i+1) * sizeof (FCHAR) );

  fidel_strcpy ( returnString, holdText );

  free ( holdText );

  return ( returnString );

}
