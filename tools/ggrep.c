/*
**  sera2any v0.26
**
**  Generalized code to convert SERA (The System for Ethiopic Representation
**  in ASCII) to an arbitrary second system.  The generalized transcription
**  is achieved here by requiring a mapping of the output system into the
**  "fidel" address table (see fidel.map).
** 
**  This is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation; either version 2, or (at your option)
**  any later version.  See the included "COPYING" file.
** 
**  --Daniel Yaqob, 1995-1997
** 
*/

#include <string.h>
#include <libeth/fidel.h>
#include <libeth/etstdlib.h>
#include <libeth/etstdio.h>
#include <libeth/etmath.h>
#include <libeth/html.h>
#include <libeth/rtf.h>
#include <libeth/maptypes.h>
#include "tables.h"
#include "common.h"

#define GFF_UTIL "sera2any"
#define GFF_UTIL_MAJOR_VERSION 0.2
#define GFF_UTIL_MINOR_VERSION 6
#define GFF_UTIL_EXPORT_DATE "Wed Dec 11 21:39:02 EET 1996"

char* xGFF_UTIL               = GFF_UTIL;
float xGFF_UTIL_MAJOR_VERSION = GFF_UTIL_MAJOR_VERSION;
int   xGFF_UTIL_MINOR_VERSION = GFF_UTIL_MINOR_VERSION;

extern char* ISO639_2Names[];   /* data found in etstdlib.c */
extern char* ISO639_3Names[];

#ifdef __STDC__
  int flag_reset ( int argc, char** argv, FILE** fp, char** iPath, StatsFlags** statsFlags, LibEthFlags** lethFlags );
  void printEnglishHelp  ( void );
  void printAmharicHelp  ( void );
  void printTigrignaHelp ( void );
#else
  int flag_reset(),
#endif   /* __STDC_ */

char* Enumber=NULL;
boolean closeStream = false;

/*-------------------------------------------------------------------------//
//                                                                         //
//  Main reads input switches, does file read-in, and sends output where   //
//  we want it.                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

void 
main ( argc, argv )
  int argc;
  char **argv;
{

FCHAR *uniString, *test, *uniFound;
FILE *inptr = stdin;
FILE* outptr = stdout;
LibEthFlags* lethFlags;
StatsFlags* statsFlags;    /* we need this around even w/o stats support */
#ifdef MAKESTATS
  StatsData Stats[UNITOTAL];
#else
  StatsData* Stats=NULL;
#endif /* MAKESTATS */
register int i; 
int setid=NIL, searchKey;
unsigned char* outString;
enum HTMLEscapes TagOn = Off;
boolean set0On = false, isTTF = false;
char* iPath;


  if (signal(SIGTERM, sig_term) == SIG_ERR)    /* catch kill commands */
    fprintf (stderr, "can't catch SIGTERM");
  if (signal(SIGINT, sig_term) == SIG_ERR)     /* catch Control-C     */
    fprintf (stderr, "can't catch SIGINT");

  searchKey = flag_reset (argc, argv, &inptr, &iPath, &statsFlags, &lethFlags);

#ifdef MAKESTATS
  if ( statsFlags->yes )
    for ( i = 0; i < UNITOTAL; i++ )
      {
        Stats[i].stat = 0;
        Stats[i].name = NULL;
      }
#endif /* MAKESTATS */

  isTTF = isFidelTrueType( lethFlags->out );

  if ( lethFlags->cstOut == rtf && isTTF )
    fout_rtf ( inptr, Stats, statsFlags, lethFlags );
  else do
   {
     test = uniString = fidel_fgets (NULL, WSIZE, inptr, lethFlags);

     uniNeedle = sget_fstring (argv[searchKey], lethFlags);
     uniFound = fidel_syllabic_strstr (uniString, uniNeedle, lethFlags->top->l, LETHC_PHONETIC);

     if (uniFound != NULL)
       if ( lethFlags->docIn == html && isTTF )
         {
           setid = fidel_HTML_sputs (uniString, &outString, setid, &TagOn, &set0On,  closeStream, lethFlags);
           printf ( "%s", outString );
           free ( outString );
         }
       else switch ( lethFlags->out )
         {

         /*  TeX and Java are not character codes schemes so we
          *  handle I/O at this level and not in the library.
          */

           case image:
             fout_image (uniString, iPath, outptr, lethFlags);
             break;

           case java:  
           case Java:  
             fout_java (uniString, outptr, lethFlags);
             break;

#ifdef  SUPPORT_TEX
           case muletex:  
             fout_tex (uniString, outptr, lethFlags);
             break;
#endif  /* SUPPORT_TEX */

           default:
             fidel_fputs (uniString, outptr, lethFlags);
             break;
	     }

     printf ("\n");
#ifdef MAKESTATS
     if (statsFlags->yes)
       {
         i = 0;
         while ( uniString[i] )
           {
             if ( isethiopic (uniString[i]) )
               if ( isprivate(uniString[i]) )
                 Stats[(UNITOTAL-1) + (uniString[i] - PRIVATE_USE_END)].stat ++;
               else
                 Stats[uniString[i]-UNIFIDEL].stat ++;
             i++;
           }
       }
#endif /* MAKESTATS */

     free ((FCHAR *)uniString); 
   }
 while (!feof(inptr) && test);

/*  print stat tables if requested  */

#ifdef MAKESTATS
  if ( statsFlags->yes )
    switch ( statsFlags->cstOut )
      {
        case plain :
          Print_Text_Stats (Stats, statsFlags, lethFlags);
          break;

        case rtf:
          Print_RTF_Stats (Stats, statsFlags, lethFlags);
          break;

        case ltx:
        case tex:
          Print_TeX_Stats (Stats, statsFlags, lethFlags);
          break;

        case html:
        default:
          Print_HTML_Stats (Stats, statsFlags, lethFlags);
          break;
      }
#endif /* MAKESTATS */

/*-------Lets Be A Good Citizen-----------------*/

  fclose (inptr);
  free ((LibEthFlags *)lethFlags);
  free ((StatsFlags *)statsFlags);
  exit (0);

}



/*-------------------------------------------------------------------------//
//                                                                         //
//  Simple routine to read input options and reset the default flags.      //
//  The flags for this version are -l if a file starts in Latin and        //
//  -s to use Ethiopic word separators in Ethiopic text zones.             //
//                                                                         //
//-------------------------------------------------------------------------*/


int 
flag_reset (argc, argv, fp, iPath, statsFlags, lethFlags)
  int argc;
  char **argv;
  FILE** fp;
  char** iPath;
  StatsFlags** statsFlags;
  LibEthFlags** lethFlags;
{

register int i,j,k;
char* lang2=NULL;


/*---------------- Define and Initialize Flag Values -------------------------*/


  *lethFlags          =  SetDefaultLibEthFlags (NIL, LETLANGMINOR, NIL);

  *statsFlags         =  (StatsFlags *) malloc ( sizeof(StatsFlags) );
  (*statsFlags)->yes  =  false;
  (*statsFlags)->cstOut  =  plain;
  (*statsFlags)->out  =  sera;



/*---------------- Who Am I? -------------------------------------------------*/

  if ( strstr( argv[0], "getEnum" ) )
    Enumber = argv[argc-1];

    
/*---------------- What do You Want From Me? ---------------------------------*/


  i = 0;
  while ( ++i < argc )
    {
      if ( argv[i][0] == '-' ) 
        {
          switch ( toupper(argv[i][1]) ) 
            {
              case 'C' :  (*lethFlags)->options |= gColon;
                          break;

              case 'D' :  (*lethFlags)->out = debug;
                          break;

              case 'F' :  if ( toupper(argv[i][2]) == 'N' )
                            (*lethFlags)->fontFace =  atoi(argv[++i]);
#ifdef SUPPORT_DOS
                          else
                            (*lethFlags)->dos =  1;
#else
                          else
                            {
                              fprintf (stderr, "\a -fromdos option not available\n");
                              fprintf (stderr, "\a See ``README.dosio'' to enable DOS support\n");
                              exit (0);
                            }
#endif
                          break;

              case 'H' :  if ( !strcmp ( &argv[i][1], "html") )
                            (*lethFlags)->docIn = html;
                          else
                            goto USAGE;
                          break;

              case 'I' :  i++;
                          (*lethFlags)->csIn = getInputSystem (argv[i]);
                          break;
                         
              case 'L' :  j=-1;
                          while( ++j < NUMLANGS 
                                  && ( strncmp(argv[i+1], ISO639_2Names[j], 2)
                                    && strncmp(argv[i+1], ISO639_3Names[j], 3) ) );
                          if ( j == NUMLANGS )
                            {
                              fprintf (stderr, "Language %s Not Supported\n",argv[i+1]);
                              exit (1);
                            }
                          k=-1;
                          if ( (lang2 = strstr(argv[i+1],"~")) )  /* Minor Lang is Passed */
                             while( ++k < NUMLANGS 
                                     && ( strncmp((lang2+1), ISO639_2Names[k], 2)
                                       && strncmp((lang2+1), ISO639_3Names[k], 3) ) );
                          if ( k == NUMLANGS )
                            {
                              fprintf (stderr, "Language %s Not Supported\n",argv[i+1]);
                              exit (1);
                            }

                          (*lethFlags)->top =& LnS[j];  

                          if ( lang2 != NULL )
                            (*lethFlags)->minor =& LnS[k];  
                          else if ( (*lethFlags)->top == (*lethFlags)->minor )
                            (*lethFlags)->minor = (*lethFlags)->major;  

                          (*lethFlags)->major = (*lethFlags)->top;  

                          i++;
                          break; 

              case 'O' :  i++;
                          if ( strstr ( argv[i], "-html" ) )
                            (*lethFlags)->cstOut = html;
                          if ( strstr ( argv[i], "-rtf" ) )
                            (*lethFlags)->cstOut = rtf;

                          (*lethFlags)->out = getOutputSystem (argv[i]);
                          if ( (*lethFlags)->out == none )
                            {
                              fprintf (stderr, "\aSorry!  Output option \"%s\" unknown.\n", argv[i]);
                              exit (1);
                            }

                          if ( (*lethFlags)->out ==  image )
                            {
                              if ( argv[++i][0] == '-' )
                                {
                                  fprintf ( stderr, "Image Path Unexpected: %s\n", argv[i] );
                                  exit (1);
                                }
                              *iPath = (char *)malloc ( strlen(argv[i]) * sizeof(char) );
                              strcpy ( *iPath, argv[i] );
                            }
                          else if ( (*lethFlags)->out == muletex )
#ifdef SUPPORT_TEX
                              (*lethFlags)->cstOut = tex;
#else
                            {
                              fprintf (stderr, "\a TeX Output Not Available By This Package \n");
                              exit (0);
                            }
#endif

                          else if ( (*lethFlags)->out ==  muletex )
#ifdef SUPPORT_TEX
                              (*lethFlags)->cstOut  =  ltx;
#else
                            {
                              fprintf (stderr, "\a LaTeX Output Not Available By This Package \n");
                              exit (0);
                            }
#endif
                          break;

              case 'Q' :  (*lethFlags)->options |= qMark;
                          break;

              case 'R' :  (*lethFlags)->cstOut = rtf;
                          break;

              case 'S' :  if ( toupper(argv[i][2]) == 'T' )
                            {
#ifdef MAKESTATS
                              (*statsFlags)->yes = true;            /* give character occurance statistics */
                              if ( argv[i+1] == '\0' || argv[i+1][0] == '-' )
                                break;
                              i++;

                              /*  hmmm... we need to work on making tex a
                               *  stats output option...
                               */
                              if ( strstr ( argv[i], "-html" ) )
                                (*statsFlags)->cstOut  = html;
                              else if ( strstr ( argv[i], "-rtf" ) )
                                (*statsFlags)->cstOut  = html;
                              else if ( strstr ( argv[i], "-tex" ) )
                                (*statsFlags)->cstOut  = tex;

                              (*statsFlags)->out = getOutputSystem (argv[i]);
#else
                              fprintf (stderr, "\a Statistics Support Not Available By This Package \n");
                              exit (0);
#endif /* MAKESTATS */


                          if ( (*lethFlags)->out == muletex )
#ifdef SUPPORT_TEX
                              (*lethFlags)->cstOut = tex;
#else
                            {
                              fprintf (stderr, "\a TeX Output Not Available By This Package \n");
                              exit (0);
                            }
#endif

                          else if ( (*lethFlags)->csOut ==  muletex )
#ifdef SUPPORT_TEX
                            (*lethFlags)->cstOut  =  ltx;
#else
                            {
                              fprintf (stderr, "\a LaTeX Output Not Available By This Package \n");
                              exit (0);
                            }
#endif
                            }
                          else
                            (*lethFlags)->options |= gSpace;  /* use Eth Word Sep. for " " */
                          break;

              case 'T' :  
#ifdef SUPPORT_DOS
                          (*lethFlags)->dos = 2;
#else
                            {
                              fprintf (stderr, "\a -todos option not available\n");
                              fprintf (stderr, "\a Recompile sera2any and libeth with ``make withdos'' \n");
                              exit (0);
                            }
#endif
                          break;

              case 'V' :  fprintf (stdout, "This is %s Version %0.1f%i", argv[0], GFF_UTIL_MAJOR_VERSION, GFF_UTIL_MINOR_VERSION);
                          fprintf (stdout, "  (%s)\n", GFF_UTIL_EXPORT_DATE);
                          exit (1);
                          break;

              case 'X' :  closeStream = true;
                          break;
USAGE:
              case '?' :  
              default  :  if ( i+1 < argc && argv[i+1][1] == 'u' )  /*  meaning:  -? -u     */
                            {
                              if ( (*lethFlags)->top->l == amh )
                                printAmharicHelp ();
                              else if ( (*lethFlags)->top->l == tir )
                                printTigrignaHelp ();
                              exit (0); 
                            }

                          printEnglishHelp ();
                          exit (0); 
                          break;
            }
        }
      else if (Enumber == NULL)
        {
          fclose (*fp);
          if ((*fp = fopen(argv[i], "r")) == NULL)
            {
              fprintf (stderr, "\n*** File Not Found \"%s\" ***\n",argv[i]);
              exit (1);
            }
        }
    }

  return (true);

    /* else ignore, and use defaults */
}


void
printEnglishHelp()
{

  fprintf (stderr, "\n\tUseage:  sera2any option[s] file\n");
  fprintf (stderr, "\tTo substitute Latin spaces with Ge'ez wordspace:\n");
  fprintf (stderr, "\t   -s\n");
  fprintf (stderr, "\tTo substitute Latin colon with Ge'ez colon:\n");
  fprintf (stderr, "\t(instead of wordspace):\n");
  fprintf (stderr, "\t   -c\n");
  fprintf (stderr, "\tTo switch the mappings for ?  and `? :\n");
  fprintf (stderr, "\t   -q\n");
  fprintf (stderr, "\tTo print tables of statistics in fidel.out and fidel2.out\n");
  fprintf (stderr, "\t   -stats [encoding]\n");
  fprintf (stderr, "\t           Encoding is one of: jun, jis, uni, utf8 (default is sera)\n");
  fprintf (stderr, "\tTo specify output encoding:\n");
  fprintf (stderr, "\t   -o encoding-name \n");
  fprintf (stderr, "\t      agafari = Agafari ANSI Mapping \n");
  fprintf (stderr, "\t      alxet = ALXEthiopian ANSI Mapping \n");
  fprintf (stderr, "\t      feedel = Feedel ANSI Mapping \n");
  fprintf (stderr, "\t      gezfree = Ge'ezFree (Ethiopian ASCII)\n");
  fprintf (stderr, "\t      java = Java  (lowercase hexidecimal)\n");
  fprintf (stderr, "\t      Java = Java  (UPPERCASE HEXIDECIMAL)\n");
  fprintf (stderr, "\t      jis  = JIS \n");
  fprintf (stderr, "\t      jun  = JUNET \n");
#ifdef SUPPORT_TEX
  fprintf (stderr, "\t      latex = LaTeX \n");
  fprintf (stderr, "\t      tex = TeX \n");
#endif
  fprintf (stderr, "\t      uni = Unicode \n");
  fprintf (stderr, "\t      utf8 = Unicode-UTF8 \n");
  fprintf (stderr, "\t      washra = Washra (Ethiopian ASCII)\n");
  fprintf (stderr, "\tTo set starting language:\n");
  fprintf (stderr, "\t   -l iso639-name \n");
  fprintf (stderr, "\t      am = amh = Amharic \n");
  fprintf (stderr, "\t      gz = gez = Ge'ez   \n");
  fprintf (stderr, "\t      la = lat = Latin   \n");
  fprintf (stderr, "\t      ti = tir = Tigrigna\n");
  fprintf (stderr, "\tTo force HTML conversion:\n");
  fprintf (stderr, "\t   -html\n");
  fprintf (stderr, "\t   or append -html to encoding name as in:\n");
  fprintf (stderr, "\t      -o jis-html\n");
#ifdef SUPPORT_DOS
  fprintf (stderr, "\tTo strip out DOS ^M end of line characters from input:\n");
  fprintf (stderr, "\t   -fromdos\n");
  fprintf (stderr, "\tTo insert DOS ^M end of line characters in output:\n");
  fprintf (stderr, "\t   -todos\n");
#endif
  fprintf (stderr, "\tEcho version number and quit:\n");
  fprintf (stderr, "\t   -v\n");
  fprintf (stderr, "\n\tTo contact the maintainers:\n");
  fprintf (stderr, "\t   fisseha@cig.mot.com / yacob@padis.gn.apc.org\n\n");

}


void
printAmharicHelp()
{

  fprintf (stdout, "\aSorry!  Amharic Help is not yet Available...\n\n");
  printEnglishHelp();

}


void
printTigrignaHelp()
{

  fprintf (stdout, "\aSorry!  Tigrigna Help is not yet Available...\n\n");
  printEnglishHelp();

}
