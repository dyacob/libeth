#include <libeth/etstdio.h>
#include <libeth/sysinfo.h>
#include <libeth/html.h>
#include <libeth/rtf.h>
#include "common.h"

extern char* xGFF_UTIL;
extern float xGFF_UTIL_MAJOR_VERSION;
extern int   xGFF_UTIL_MINOR_VERSION;

extern unsigned char *TeXFidel[];


int
fout_image (fstring, iPath, fp, lethFlags)
  FCHAR* fstring;
  char* iPath;
  FILE* fp;
  LibEthFlags* lethFlags;
{

register int i=-1, count=0;
int uniAddr;
unsigned char* fidelName;


  if ( fp == NULL || feof(fp) || fstring == NULL || lethFlags == NULL )
    return ( _LET_FAIL );

  while ( (uniAddr = fstring[++i]) )
    if ( fstring[i] < ANSI )
      fprintf (fp, "%c", fstring[i]);
    else if ( isethiopic (uniAddr) )
        {
          count++;
          lethFlags->csOut = ( uniAddr > FYA ) ? muletex : sera ;

          fidelName = fidel_sputc ( uniAddr, lethFlags );

          if ( fidelName[0] == '`' )
            {
              fidelName[0] = fidelName[1];
              fidelName[1] = '2';
            }
          else if ( uniAddr > FYA )
            {
              fidelName[strlen(fidelName)-1] = '\0';  /* kill the 'G' */
            }

/*        Our images use Tigrigna names, so we need to switch names back
 *        if we used an Amharic file.
 */
          if ( !isfdigit(uniAddr) && lethFlags->out->l == amh )
            {
              if ( fidelName[0] == 'a' && fidelName[1] != '2' )
                fidelName[0] = 'e';
              else if ( fidelName[0] == 'A' )
                fidelName[0] = 'a';
            }


          fprintf ( fp, "<img src=%s/%s>", iPath, fidelName );
          free (fidelName);
        }
      else
        fprintf (fp, "%c", fstring[i]);

  lethFlags->csOut = image ;
  return ( count );
}


#ifdef SUPPORT_RTF

int
fout_rtf (fp, Stats, statsFlags, lethFlags)
  FILE* fp;
  StatsData* Stats;
  StatsFlags* statsFlags;
  LibEthFlags* lethFlags;
{

int setid;
FCHAR *uniString=NULL, *test;
char *rtfHead, *rtfOut;
boolean set0On = false;
int* idList;


  idList = get_RTF_header ( lethFlags->fontFaceIn, &rtfHead, lethFlags );
  fprintf ( stdout, "%s", rtfHead );
  free (rtfHead);

  do
    {
      test = uniString = fidel_fgets ( NULL, WSIZE, fp, lethFlags );
      setid = fidel_RTF_sputs (uniString, &rtfOut, setid, idList, &set0On, 1, lethFlags);

#ifdef MAKESTATS
      if (statsFlags && statsFlags->yes)
        {
          int i = 0;
          while ( uniString[i] )
            {
              if ( isethiopic (uniString[i]) ) {
                if ( isprivate(uniString[i]) )
                  Stats[(UNITOTAL-1) + (uniString[i] - PRIVATE_USE_END)].stat ++;
                else
                  Stats[uniString[i]-UNIFIDEL].stat ++;
              }
              i++;
            }
        }
#endif /* MAKESTATS */

      fprintf ( stdout, "%s", rtfOut );
      free ((char *)rtfOut); 
      free ((FCHAR *)uniString); 
    }  /* end while (!feof(inptr) && test) */
  while (!feof(fp) && test);


  /* close RTF file */

  fprintf ( stdout, "\\par }\n" );

  free ((int *)idList);
  return ( 1 );

}
#endif /* SUPPORT_RTF */


#ifdef  SUPPORT_TEX

/*
 *  Simple routine to write files with tex macros for Ethiopic.
 *  This escapes correspond to those in the "fidelmap.tex" file.
 *  La/TeX support is limited at this time, some formatting will
 *  suffer or need revision afterwards.
 */
int
fout_tex (fstring, fp, lethFlags)
  FCHAR* fstring;
  FILE* fp;
  LibEthFlags* lethFlags;
{

int i=-1, count=0;
FCHAR fch;


  if ( fp == NULL || feof(fp) || fstring == NULL || lethFlags == NULL )
    return ( _LET_FAIL );
  
  while ( (fch = fstring[++i]) )
    if ( fch < ANSI )
      fprintf (fp, "%c", fstring[i]);
    else if ( fch >= UNIFIDEL && fch < UNIFIDEL+UNITOTAL )
      {
        count++;
        fch -= UNIFIDEL;
        if ( fstring[i+1] == GEMINATION )
		  {
            fprintf ( fp, "\\geminateG{\\%s}", TeXFidel[fch] );
			i++;
		  }
        else
          fprintf ( fp, "{\\%s}", TeXFidel[fch] );
      }
    else if ( fch >= PRIVATE_USE_BEGIN && fch <= PRIVATE_USE_END )
      {
        count++;
        fch  = (UNITOTAL-1)  + (fch - PRIVATE_USE_END);
        fprintf ( fp, "{\\%s}", TeXFidel[fch] );
      }

  return ( count );

}

#endif  /* SUPPORT_TEX */
 
/*-------------------------------------------------------------------------//
//                                                                         //
//  sig_term catches the more violent break signals, presumably something  //
//  has gone awry...                                                       //
//                                                                         //
//-------------------------------------------------------------------------*/

void
sig_term ( int signo )
{

  if ( signo == SIGTERM || signo == SIGINT )
    {
      /* ...personal toying with unix...
       *
	   * openlog ("sera2", LOG_PID, LOG_USER);
	   * syslog (LOG_DEBUG, "failed on %s", filename);
	   * closelog ();
	   */ 
      fprintf (stderr, "\nIndE??  You seem to have found a bug with %s version %0.1f%i\n", xGFF_UTIL, xGFF_UTIL_MAJOR_VERSION, xGFF_UTIL_MINOR_VERSION);
   	  fprintf (stderr, "Please email your input file to the maintainer\n");
	  fprintf (stderr, "Daniel Yacob:-  Yacob@EthiopiaOnline.Net\n");
	  fprintf (stderr, "                                              Thank You!\n\n");
	  exit (0);
    }

}


enum CharacterSet
getOutputSystem ( system )
  char* system;
{

enum CharacterSet getSys;


  if ( !strncmp (system, "enhpfr", 6) )
    return (  enhpfr );
  if ( ( getSys = getInputSystem ( system ) ) != nocs )
    return ( getSys );
  else if ( !strncmp (system, "jun", 3) )
    return ( junet );
  else if ( !strncmp (system, "jis", 3) )
    return ( jis );
  else if ( !strncmp (system, "image", 5) )
    return ( image );
  else if ( !strcmp (system, "tex") )
#ifdef SUPPORT_TEX
      return ( muletex );
#else
    {
      fprintf (stderr, "\a TeX Output Not Available By This Package \n");
      exit(0);
    }
#endif

  else if ( !strcmp (system, "latex") )
#ifdef SUPPORT_TEX
      return ( muletex );
#else
    {
      fprintf (stderr, "\a LaTeX Output Not Available By This Package \n");
      exit(0);
    }
#endif
  else if ( !strcmp (system, "sera") )
    return ( sera );
  else return ( nocs );


}


enum CharacterSet
getInputSystem ( system )
  char* system;
{

  if ( !strncmp (system, "uni", 3) )
    return ( unicode );
  else if ( !strncmp (system, "sera", 4) )
    return ( sera );
  else if ( !strncmp (system, "ncic_et", 7) )
    return ( ncic_et );
  else if ( !strncmp (system, "ncic", 4) )
    return ( ncic );
  else if ( !strncmp (system, "nci", 3) )
    return ( nci );
  else if ( !strncmp (system, "brana", 5) )
    return ( branai );
  else if ( !strncmp (system, "cbhale", 6) )
    return ( cbhalea );
  else if ( !strncmp (system, "geezigna", 8) )
    return ( gezigna );
  else if ( !strncmp (system, "geezab", 6) )
    return ( geznewa );
  else if ( !strncmp (system, "geezbausi", 9) )
    return ( gezbausi );
  else if ( !strncmp (system, "geezfont", 8) )
    return ( gezfont );
  else if ( !strncmp (system, "geezfree", 8) )
    return ( gezfree1 );
  else if ( !strncmp (system, "geezedit", 8) )
    return ( gezedit );
  else if ( !strncmp (system, "geeztypenet", 11) )
    return ( geztypenet );
  else if ( !strncmp (system, "geez", 4) )
    return ( gezi );
  else if ( !strncmp (system, "acuwork", 7) )
    return ( acuwork );
  else if ( !strncmp (system, "addisword", 9) )
    return ( addisword1 );
  else if ( !strncmp (system, "alpas", 5) )
    return ( alpas );
  else if ( !strncmp (system, "acis", 4) )
    return ( acis );
  else if ( !strncmp (system, "dejene", 6) )
    return ( dejene1 );
  else if ( !strncmp (system, "ethiopic", 8) )
    return ( ethiopic1 );
  else if ( !strncmp (system, "ethiosys", 8) )
    return ( ethiosys );
  else if ( !strncmp (system, "ethiosoft", 9) )
    return ( ethiosoft );
  else if ( !strncmp (system, "ethiowalia", 10) )
    return ( ethiowalia );
  else if ( !strncmp (system, "omnitech", 8) )
    return ( omnitech );
  else if ( !strncmp (system, "powergeez", 9) )
    return ( powergez );
  else if ( !strncmp (system, "tfanus", 6) )
    return ( tfanus );
  else if ( !strncmp (system, "tfanusnew", 9) )
    return ( tfanus );
  else if ( !strncmp (system, "monoalt", 7) )
    return ( monoalt );
  else if ( !strncmp (system, "mono", 4) )
    return ( monotype1 );
  else if ( !strncmp (system, "phonetic", 8) )
    return ( geztype );
  else if ( !strncmp (system, "visgeez2k", 9) )
    return ( visualgez2k );
  else if ( !strncmp (system, "visgeez", 7) )
    return ( visualgez );
  else if ( !strncmp (system, "wazema", 6) )
    return ( wazema1 );
  else if ( !strncmp (system, "addis98", 7) )
    return ( sam98 );
  else if ( !strncmp (system, "addiswp", 7) )
    return ( samwp );
  else if ( !strncmp (system, "fidel", 5) )
    return ( fidelxtr1 );
  else if ( !strncmp (system, "mainz", 5) )
    return ( mainz );
  else if ( !strncmp (system, "ies", 3) )
    return ( ies );
  else if ( !strncmp (system, "iso", 3) )
    return ( iso );
  else if ( !strncmp (system, "dehai", 5) )
    return ( dehai );
  else if ( !strncmp (system, "ed", 2) )
    return ( ed );
  else if ( !strncmp (system, "ethiome", 7) )
    return ( ethiome );
  else if ( !strncmp (system, "ethiop", 6) )
    return ( ethiop );
  else if ( !strncmp (system, "qubee", 5) )
    return ( qubee );
  else return ( nocs );


}
