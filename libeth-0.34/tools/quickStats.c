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

#define ADMAS_UTIL "quickStats"
#define ADMAS_UTIL_MAJOR_VERSION 0.0
#define ADMAS_UTIL_MINOR_VERSION 1
#define ADMAS_UTIL_EXPORT_DATE "Wed Dec 11 21:39:02 EET 1996"

#include <signal.h>
#include <syslog.h>
#include <stdio.h>
#include "gezxfer.h"

/* #define MYDEFMAJOR  amh */
/* #define MYDEFMAJOR  gez */
#define MYDEFMAJOR  tir 

extern char *TeXFidel[];
extern int UniToTraditional[];
extern LS LnS[];

#ifdef __STDC__
  int flag_reset ( int argc, char** argv, FILE** fp, StatsFlags** statsFlags, LEthFlags** lethFlags );
#else
  int flag_reset (),
#endif   /* __STDC_ */

FIDELStats fidelStats[UNITOTAL];

/*-------------------------------------------------------------------------//
//                                                                         //
//  Main reads input switches, does file read-in, and sends output where   //
//  we want it.                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

void 
main (argc,argv)
  int argc;
  char **argv;
{

FCHAR* uniString;
FILE *inptr = stdin;
FILE* outptr = stdout;
LEthFlags* lethFlags;
StatsFlags* statsFlags;
int i, test = true;


  flag_reset (argc, argv, &inptr, &statsFlags, &lethFlags);

  while (!feof(inptr) && test)
   {
     test = fidel_fgets (&uniString, WSIZE, inptr, lethFlags);
     if (statsFlags->yes)
       {
         i = 0;
         while ( uniString[i] )
           {
             if ( isethiopic (uniString[i]) && !isfcntrl(uniString[i]) )
               if ( isprivate(uniString[i]) )
                 fidelStats[(UNITOTAL-1) + (uniString[i] - PRIVATE_USE_END)].stat ++;
               else
                 fidelStats[uniString[i]-UNIFIDEL].stat ++;
             i++;
           }
       }
     free ((FCHAR *)uniString); 
   }


/*  print stat tables if requested  */

  if ( statsFlags->yes )
    switch ( statsFlags->cstOut )
      {
        case plain :
          Print_Text_Stats (fidelStats, statsFlags, lethFlags);
          break;

//      case rtf:
//        Print_RTF_Stats (Fout, fi, Roman, fidelStats, statsFlags, lethFlags);
//        break;

#ifdef SUPPORT_TEX
        case ltx:
        case tex:
          Print_TeX_Stats (fidelStats, statsFlags, lethFlags);
          break;
#endif /* SUPPORT_TEX */

        case html:
        default:
          Print_HTML_Stats (fidelStats, statsFlags, lethFlags);
          break;
      }


/*-------Lets Be A Good Citizen-----------------*/

  fclose (inptr);
  free ((LEthFlags *)lethFlags);
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
flag_reset (argc, argv, fp, statsFlags, lethFlags)
  int argc;
  char **argv;
  FILE** fp;
  StatsFlags** statsFlags;
  LEthFlags** lethFlags;
{

LS* default_lang =& LnS[MYDEFMAJOR];
char* Lnames2[NUMLANGS] = ISO639_2;
char* Lnames3[NUMLANGS] = ISO639_3;
register int i,j;


/*---------------- Define and Initialize Flag Values -------------------------*/


  *lethFlags          =  set_defaultLEthFlags (MYDEFMAJOR, DEFMINOR, DEFMAJOR);

  *statsFlags         =  (StatsFlags *) malloc ( sizeof(StatsFlags) );
  (*statsFlags)->yes  =  false;
  (*statsFlags)->cstOut  =  plain;
  (*statsFlags)->csOut  =  sera;


  i = 0;

/* Who Am I? */

  if ( strncmp( &argv[strlen(argv[0])-8], "sera2any", 8) )
    if ( strstr(argv[0], "sera2jis") ) 
      (*lethFlags)->csOut  =  jis;
    else if ( strstr(argv[0], "sera2jun") || strstr(argv[0], "sera2ps") ) 
      (*lethFlags)->csOut  =  jun;
    else if ( strstr(argv[0], "sera2java") ) 
      (*lethFlags)->csOut  =  java;
    else if ( strstr(argv[0], "sera2Java") ) 
      (*lethFlags)->csOut  =  Java;
    else if ( strstr(argv[0], "sera2uni") ) 
      (*lethFlags)->csOut  =  uni;
    else if ( strstr(argv[0], "sera2utf8") ) 
      (*lethFlags)->csOut  =  utf8;
    else if ( strstr(argv[0], "sera2agafari") ) 
      (*lethFlags)->csOut  =  agafari;
    else if ( strstr(argv[0], "sera2feedel") ) 
      (*lethFlags)->csOut  =  feedel;
    else if ( strstr(argv[0], "sera2gf") ) 
      (*lethFlags)->csOut  =  gezfree1;
    else if ( strstr(argv[0], "sera2alxet") ) 
      (*lethFlags)->csOut  =  alxet;
    else if ( strstr(argv[0], "sera2washra") ) 
      (*lethFlags)->csOut  =  washra;
    else if ( strstr(argv[0], "sera2tex") ) 
#ifdef SUPPORT_TEX
      (*lethFlags)->csOut  =  tex;
#else
      {
        fprintf (stderr, "\a TeX Output Not Available By This Package \n");
        exit(0);
      }
#endif
    


/* What Do You Want From Me? */

  while ( ++i < argc )
    {
      if ( argv[i][0] == '-' ) 
        {
          switch ( toupper(argv[i][1]) ) 
            {
              case 'C' :  (*lethFlags)->options |= gColon;
                          break;
              case 'D' :  (*lethFlags)->csOut = debug;
                          break;

              case 'F' :  
#ifdef SUPPORT_DOS
                          (*lethFlags)->dos =  1;
#else
                            {
                              fprintf (stderr, "\a -fromdos option not available\n");
                              fprintf (stderr, "\a See ``README.dosio'' to enable DOS support\n");
                              exit(0);
                            }
#endif
                          break;

              case 'H' :  if ( !strcmp ( &argv[i][1], "html") )
                            (*lethFlags)->cstOut = html;
                          else
                            goto USAGE;
                          break;

              case 'I' :  i++;
                          if ( !strncmp (argv[i], "feedel", 6) )
                            (*lethFlags)->csIn  =  feedel;
                          else if ( !strncmp (argv[i], "alxet", 5) )
                            (*lethFlags)->csIn  =  alxet;
                          else if ( !strncmp (argv[i], "agafari", 7) )
                            (*lethFlags)->csIn  =  agafari;
                          break;
                         
              case 'L' :  j=-1;
                          while( ++j < NUMLANGS && (strcmp(argv[i+1],Lnames2[j]) && strcmp(argv[i+1],Lnames3[j])) );
                          if (j < NUMLANGS ) 
                            (*lethFlags)->minor =& LnS[j];  
                          (*lethFlags)->top     =& LnS[j];  
                          if (j == lat)
                            (*lethFlags)->major = default_lang;
                          i++;
                          if (j == NUMLANGS) 
                            {
                              fprintf (stderr, "Language %s Not Supported\n",argv[i]);
                              exit(1);
                            }
                          break; 

              case 'O' :  i++;
                          if ( strstr ( argv[i], "-html" ) )
                            (*lethFlags)->cstOut = html;
                          if ( strstr ( argv[i], "-rtf" ) )
                            (*lethFlags)->cstOut = rtf;
                          if ( !strncmp (argv[i], "jun", 3) )
                            (*lethFlags)->csOut  =  jun;
                          else if ( !strncmp (argv[i], "jis", 3) )
                            (*lethFlags)->csOut  =  jis;
                          else if ( !strncmp (argv[i], "jav", 3) )
                            (*lethFlags)->csOut  =  java;
                          else if ( !strncmp (argv[i], "Jav", 3) )
                            (*lethFlags)->csOut  =  Java;
                          else if ( !strncmp (argv[i], "uni", 3) )
                            (*lethFlags)->csOut  =  uni;
                          else if ( !strncmp (argv[i], "utf8", 4) )
                            (*lethFlags)->csOut  =  utf8;
                          else if ( !strncmp (argv[i], "agafari", 7) )
                            (*lethFlags)->csOut  =  agafari;
                          else if ( !strncmp (argv[i], "feedel", 6) )
                            (*lethFlags)->csOut  =  feedel;
                          else if ( !strncmp (argv[i], "gezfree", 7) )
                            (*lethFlags)->csOut  =  gezfree1;
                          else if ( !strncmp (argv[i], "alxet", 5) )
                            (*lethFlags)->csOut  =  alxet;
                          else if ( !strncmp (argv[i], "washra", 6) )
                            (*lethFlags)->csOut  =  washra;
                          else if ( !strcmp (argv[i], "debug") )
                            (*lethFlags)->csOut = debug;
                          else if ( !strcmp (argv[i], "tex") )
#ifdef SUPPORT_TEX
                            (*lethFlags)->csOut  =  tex;
#else
                            {
                              fprintf (stderr, "\a TeX Output Not Available By This Package \n");
                              exit(0);
                            }
#endif

                          else if ( !strcmp (argv[i], "latex") )
#ifdef SUPPORT_TEX
                            (*lethFlags)->csOut  =  latex;
#else
                            {
                              fprintf (stderr, "\a LaTeX Output Not Available By This Package \n");
                              exit(0);
                            }
#endif
                          else if ( !strncmp (argv[i], "sera") )
                            (*lethFlags)->csOut  =  sera;

                          break;

              case 'Q' :  (*lethFlags)->qMark = true;
                          break;
              case 'R' :  (*lethFlags)->cstOut = rtf;
                          break;
              case 'S' :  if ( toupper(argv[i][2]) == 'T' )
                            {
                              (*statsFlags)->yes = true;            /* give character occurance statistics */
                              for ( j = 0; j < UNITOTAL; j++ )
                                fidelStats[j].stat = 0;
                              if ( argv[i+1] == '\0' || argv[i+1][0] == '-' )
                                break;
                              i++;

                              /*  hmmm... we need to work on making tex a
                               *  stats output option...
                               */
                              if ( strstr ( argv[i], "-html" ) )
                                (*statsFlags)->cstOut  = html;
                              if ( !strncmp (argv[i], "jun", 3) )
                                (*statsFlags)->csOut  =  jun;
                              else if ( !strncmp (argv[i], "jis", 3) )
                                (*statsFlags)->csOut  =  jis;
                              else if ( !strncmp (argv[i], "uni", 3) )
                                (*statsFlags)->csOut  =  uni;
                              else if ( !strncmp (argv[i], "utf8", 4) )
                                (*statsFlags)->csOut  =  utf8;
                              else if ( !strncmp (argv[i], "jav", 3) )
                                (*statsFlags)->csOut  =  java;
                              else if ( !strncmp (argv[i], "Jav", 3) )
                                (*statsFlags)->csOut  =  Java;
                              else if ( !strncmp (argv[i], "sera", 4) )
                                (*statsFlags)->csOut  = sera;
                              else if ( !strncmp (argv[i], "agafari", 7) )
                                (*statsFlags)->csOut  =  agafari;
                              else if ( !strncmp (argv[i], "feedel", 6) )
                                (*statsFlags)->csOut  =  feedel;
                              else if ( !strncmp (argv[i], "gezfree", 7) )
                                (*lethFlags)->csOut  =  gezfree1;
                              else if ( !strncmp (argv[i], "alxet", 5) )
                                (*statsFlags)->csOut  =  alxet;
                              else if ( !strncmp (argv[i], "washra", 6) )
                                (*statsFlags)->csOut  =  washra;
                              else
                                i--;  /* no alternative option given, stick with default */
                            }
                          else
                            (*lethFlags)->options |= gSpace;  /* use Eth Word Sep. for " " */
                          break;

              case 'T' :  
#ifdef SUPPORT_DOS
                          (*lethFlags)->dos =  2;
#else
                            {
                              fprintf (stderr, "\a -todos option not available\n");
                              fprintf (stderr, "\a Recompile sera2any and libeth with ``make withdos'' \n");
                              exit(0);
                            }
#endif
                          break;

              case 'V' :  fprintf (stdout, "This is %s Version %0.1f%i\n", ADMAS_UTIL, ADMAS_UTIL_MAJOR_VERSION, ADMAS_UTIL_MINOR_VERSION);
                          fprintf (stdout, "  Export Date:  %s\n", ADMAS_UTIL_EXPORT_DATE);
                          exit(1);
                          break;
USAGE:
              case '?' :
              default  :
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

                          exit(1);
                          break;
             
               }
           }  
         else 
           {
             fclose (*fp);
             if ((*fp = fopen(argv[i], "r")) == NULL)
               {
                 fprintf (stderr, "\n*** File Not Found \"%s\" ***\n",argv[i]);
                 exit(1);
               }
           }
  }

  return(true);

    /* else ignore, and use defaults */
}

