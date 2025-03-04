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

#include <stdlib.h>
#include <string.h>
#ifdef WIN32
# include <direct.h>    /* use WIN32 getcwd */
#else
# include <unistd.h>    /* use UNIX getcwd  */
#endif /* WIN32 */
#include <errno.h>
#include "etstdio.h"
#include "etctype.h"
#include "lethutil.h"


#if __STDC__ || WIN32
  int openRedTags ( char* pathNfile );
  char* readToEndofLine ( FILE* inptr );
  boolean iskeyword(unsigned char *word);
  void addkeyword(unsigned char *word);
  void *safealloc( int qty, size_t size);
  void stripExtraWhiteSpace ( unsigned char** word );
#else
  int openRedTags ( );
  char* readToEndofLine ( );
  boolean iskeyword ( );
  void addkeyword ( );
  void *safealloc ( );
  void stripExtraWhiteSpace ( );
#endif /* __STDC__ || WIN32 */

unsigned char **keyword[257];  /* hash table of keyword names */



/* This macro computes a hash value for a word, which is used for looking
 * the word up in the keyword[] table.  The word is known to be at least
 * one character long and terminated with a '\0', so word[1] is guaranteed to
 * be valid and consistent.
 */
#define KWHASH(word)	(((word)[0] & 0x1f) ^ (((word)[1] & 0x03) << 5))

/* The below seem to be unduely cautious, but we maintain the macros
 * to keep our borrowed code in sync with the elvis source.
 */
#define CHARcpy(d,s)	((void)strcpy((char *)(d), (char *)(s)))
#define CHARlen(s)	strlen((char *)(s))
/* #define CHARcmp(s,t)	(strcmp((char *)(s), (char *)(t))) */
#define CHARcmp(s,t)	(strstr((char *)(s), (char *)(t)))



int
openRedTags ( pathNfile )
  char* pathNfile;
{
char *openFile=NULL, *word=NULL;
int RTLength = 12;  /* length of "RedTags.sera" */
int i;
FILE* inptr=NULL;


  if ( pathNfile != NULL )
    {
      openFile = (char *) malloc ( (strlen(pathNfile) + RTLength + 1) * sizeof(char) );
      sprintf ( openFile, "%s/RedTags.sera", pathNfile );
    }
  else  /* Check in CWD */
    {
      i = 0;
      do
        {
          errno = 0;  /* bad news ? */
          openFile = (char *) realloc ( openFile, (((++i)*180 + RTLength + 1) * sizeof(char)) );
          getcwd (openFile, 180*i );
        }
      while ( errno == ERANGE );

      strcat ( openFile, "/RedTags.sera" );


      if ( (inptr = fopen(openFile,"r")) == NULL )  /* Check in HOME */
        {
          openFile = (char *) realloc ( openFile, ((strlen(getenv("HOME")) + RTLength + 1) * sizeof(char)) );
          sprintf ( openFile, "%s/RedTags.sera", getenv("HOME") );

          if ( (inptr = fopen(openFile,"r")) == NULL ) /* Check in Install Dir */
            {
              openFile = (char *) realloc ( openFile, ((strlen(INSTALL_DIR) + RTLength + 1) * sizeof(char)) );
              sprintf ( openFile, "%s/RedTags.sera", INSTALL_DIR );
    
              if ( (inptr = fopen(openFile,"r")) == NULL )
                return ( 0 );  /* We Give Up! */
            }
        }

    }


  while ( ( word = readToEndofLine(inptr) ) != NULL )
    {
      if ( word[0] != '\0' )
        addkeyword (word);
      free (word);
    }

  keyword[256] = (unsigned char**) malloc ( 2 * sizeof (unsigned char *) );
/*
 *word = (unsigned char*) malloc( 2 * sizeof(unsigned char) );
 *strcpy(word, "X");
 *keyword[256][0] = word;
 */
  keyword[256][0] = (unsigned char*) malloc( 2 * sizeof(unsigned char) );
  strcpy(keyword[256][0], "X");

  fclose (inptr);
  return ( 1 );

}


char*
readToEndofLine (inptr)
  FILE* inptr;
{
unsigned char *word = (unsigned char *) malloc ( 120 * sizeof(unsigned char) );
char *returnWord, ch, *comment;
int i=0, j=1;


  if ( inptr == NULL || feof(inptr) )
    return (NULL);

  fgets (word, 120, inptr);

  if ( feof(inptr) )
    return (NULL);

  if ( word[0] == '#' || word[0] == '\n' )
    {
      word[0] = '\0';
      return (word);
    }
  else if ( (comment = strchr(word, '#')) != NULL )
    {
      while (isspace(*--comment) );
      comment[1] = '\n';
      comment[2] = '\0';
    }

  if ( word[strlen(word)-1] != '\n' )
    while ( (ch = fgetc(inptr)) != '\n' && ch != '#' )
      {
         word[i++] = ch;

         if ( i > 120 )
           {
             grow_string (&word, 120);  /* grow by increment of 120 */
             j++;
           }
      }
  word[strlen(word)-1] = '\0';  /* chop \n */

  returnWord = (char *) malloc ( (strlen(word) + 1) * sizeof(char) );
  strcpy (returnWord, word);

  free(word);
  return (returnWord);

}



boolean
isRedTerm ( fstring, mylflags )
  FCHAR* fstring;
  LibEthFlags* mylflags;
{
unsigned char* testWord=NULL;
boolean test = false;
enum CharacterSet holdSys;


  if ( fstring == NULL )
    return ( false );

  if ( keyword[256] == NULL )
    openRedTags (NULL);

  holdSys = mylflags->csOut;
  mylflags->csOut = sera;

  fidel_sputs ( fstring, &testWord, mylflags );

  mylflags->csOut = holdSys;

  stripExtraWhiteSpace (&testWord);
  test = iskeyword (testWord);

  free (testWord);
  return (test);

}


/* This function returns a pointer to the hashed keyword description if the
 * given word is in fact a keyword.  Otherwise it returns NULL.
 */
boolean
iskeyword (word)
  unsigned char *word;  /* pointer to word */
{
int	hash;
register int i;

  /* compute a hash value for this word */
  hash = KWHASH(word);

  /* if no keywords have that hash value, then return False right away */
  if (!keyword[hash])
    return false;

  /* case sensitive assumed */
  for (i = 0; keyword[hash][i]; i++)
    /* true if one is a substring of the other */
/*  if ( fidel_syllabic_strstr (keyword[hash][i], word, LETHC_ALL)
         || fidel_syllabic_strstr (word, keyword[hash][i], LETHC_ALL) )
*/
    if ( CHARcmp(keyword[hash][i], word) != NULL
         || CHARcmp(word, keyword[hash][i]) != NULL )
      return true;

  /* we didn't find it in the keyword list */
  return false;
}



void 
addkeyword (word)
  unsigned char *word;              /* a keyword */
{
  int  hash;                        /* hash value of word */
  unsigned char	*newKeyword = NULL; /* entry describing the current keyword */
  unsigned char	**hashed = NULL;    /* new list for a hash table slot */
  register int	i;


/* see if the keyword is already in the list */
  if ( !iskeyword(word) )
    {
      /* no, we need to add it... */
      hash = KWHASH(word);
      if (keyword[hash])
        {
          /* allocate a new, larger copy of the hash array */
          for (i = 0; keyword[hash][i]; i++)
            hashed = safealloc(i + 2, sizeof(unsigned char *));
          for (i = 0; keyword[hash][i]; i++)
            hashed[i] = keyword[hash][i];

          free(keyword[hash]);
          keyword[hash] = hashed;
        }
      else
        {
          /* create the first hash list */
          keyword[hash] = safealloc(2, sizeof(unsigned char *));
          i = 0;
        }

        /* append the new keyword to the list */
        newKeyword = safealloc(CHARlen(word) + 1, sizeof(unsigned char));
        CHARcpy(newKeyword, word);                  /* defined in elvis.h */
        stripExtraWhiteSpace(&newKeyword);
        keyword[hash][i] = newKeyword;
        keyword[hash][i + 1] = NULL;
    }

}



void
*safealloc(qty, size)
	int	qty;	/* number of items to allocate */
	size_t	size;	/* size of each item */
{
	void	*newp;

	newp = (void *)calloc((size_t)qty, size);
	if (!newp)
	{
		fprintf (stderr, "No Memory\n");
	}
	return newp;
}



void
stripExtraWhiteSpace ( word )
  unsigned char** word;
{
register int i=0, j=0;
boolean lastSpace = false;
char *wordOut = (unsigned char *) malloc ( strlen(*word)*sizeof(unsigned char) );


  /*   We assume "word" does NOT contain \n -maybe we should check this... 
   *   isspace() is then assumed to check only for ' ' and \t
   */

  while ( (*word)[i] )
    {

      if ( isalnum((*word)[i]) )  /* [a-zA-Z0-9] */
        lastSpace = false;
      else if ( !lastSpace && isspace((*word)[i]) )
        {
          /* for  "word[ \t]word" sequences */
          (*word)[i] = ' ';
          lastSpace = true;
        }
      else if ( !lastSpace && (*word)[i] == ':' && !ispunct((*word)[i+1]) && (i && !ispunct((*word)[i-1])) )
        {
          /* for  "word:word" sequences we convert to ' ' */
          (*word)[i] = ' ';
          lastSpace = true;
        }
      else if ( lastSpace 
                && ( isspace((*word)[i]) || ((*word)[i] == ':' && !ispunct((*word)[i+1])) ) )
        {
          /* for  "word [ \t]*(:)?word" sequences that we skip */
          i++;
          continue;
        }

      wordOut[j++] = (*word)[i++];

    }  /* while */

  wordOut[j] = '\0';
  free (*word);

  *word = (unsigned char *) malloc ( strlen(wordOut)*sizeof(unsigned char) );
  strcpy (*word, wordOut);
  free (wordOut);

}
