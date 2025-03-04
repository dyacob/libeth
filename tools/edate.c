#include <libeth/etstdlib.h>
#include <libeth/etstdio.h>
#include <libeth/ettime.h>
#include <libeth/html.h>
#include "common.h"

#define GFF_UTIL "edate"
#define GFF_UTIL_MAJOR_VERSION 0.1
#define GFF_UTIL_MINOR_VERSION 0
#define GFF_UTIL_EXPORT_DATE "Wed Dec 11 21:39:02 EET 1996"

char* xGFF_UTIL               = GFF_UTIL;
float xGFF_UTIL_MAJOR_VERSION = GFF_UTIL_MAJOR_VERSION;
int   xGFF_UTIL_MINOR_VERSION = GFF_UTIL_MINOR_VERSION;

extern char* ISO639_2Names[];   /* data found in etstdlib.c */
extern char* ISO639_3Names[];

typedef struct  {
        unsigned int LCInfo;
        boolean AATime, Talbot, isHoliday;
        boolean isLeapYear, YearName, noTime;
        enum Languages calIn, calOut;
        int date, month, year;
      } MyFlags; 


#define GMT_FUDGE 1 /* because daniel's computer is wack and daniel is lazy...*/


#ifdef __STDC__
  boolean flag_reset ( int argc, char **argv, char** iPath, MyFlags** timeFlags, LibEthFlags** lethFlags );
  int fprintUniString ( FILE* fp, unsigned char* utf8String, char* iPath, LibEthFlags** lethFlags );
  void printEnglishHelp  ( void );
  void printAmharicHelp  ( void );
  void printTigrignaHelp ( void );
#else
  boolean flag_reset ();
  int fprintUniString ();
  void printEnglishHelp  ();
  void printAmharicHelp  ();
  void printTigrignaHelp ();
#endif /* __STDC__ */

boolean closeStream = false;

int
main (argc,argv)
  int argc;
  char **argv;
{

time_t TimeNow;
struct tm* Time;
LibEthFlags *lethFlags = NULL;
char TimeZone[20];
MyFlags *timeFlags = NULL;
unsigned char *ethioString = NULL, *euroString = NULL;
char* iPath = NULL;
int *date, *month;
long int  *year;


  flag_reset ( argc, argv, &iPath, &timeFlags, &lethFlags );


  if ( !timeFlags->noTime 
       || ( timeFlags->date == NIL 
         && ( timeFlags->Talbot || timeFlags->isHoliday 
           || timeFlags->isLeapYear || timeFlags->YearName ) 
          )
     )
    {
      time ( &TimeNow );

      if ( timeFlags->AATime )
        {
          Time     = gmtime (&TimeNow);
          TimeNow  = mktime (Time);
          TimeNow += (3 + GMT_FUDGE)*3600; /* + 3 hours for AA Time ? */
          Time     = gmtime(&TimeNow);     /* I think this works...   */
        }
      else
        Time = localtime (&TimeNow);

    }


  if ( !timeFlags->noTime )
    {
      if ( timeFlags->date != NIL )        /* We are converting a date here   */
        {                                  /* so we do not want hours:min:sec */ 
          Time->tm_mday = timeFlags->date;
          Time->tm_mon  = timeFlags->month;
          Time->tm_year = timeFlags->year;

          if ( timeFlags->calIn == eng )  /* Gregorian -> Ethiopic */
            {
              euroString  = strfetime ( Time, eng, eng, timeFlags->LCInfo, false );
              ethioString = strfetime ( Time, eng, timeFlags->calOut,
                                          timeFlags->LCInfo, false );


              fprintUTF8String ( stdout, euroString, iPath, lethFlags );
              fprintf (stdout, " is " );
              fprintUTF8String ( stdout, ethioString, iPath, lethFlags );
            }
          else                             /* Ethiopic -> Gregorian */
            {           
              ethioString = strfetime ( Time, timeFlags->calIn, 
                                          timeFlags->calIn, 
                                          timeFlags->LCInfo, false );

              euroString  = strfetime ( Time, timeFlags->calIn, eng,
                                          timeFlags->LCInfo, false );


              fprintUTF8String ( stdout, ethioString, iPath, lethFlags );
              fprintf (stdout, " " );
              fprintUTF8String ( stdout, euroString, iPath, lethFlags );
              if ( timeFlags->LCInfo & WITHUTF8 )
                if ( timeFlags->calOut == tir )
                  fprintf (stdout, " እዩ።" );
                else
                  fprintf (stdout, " ነው።" );
              else
                fprintf (stdout, " new::" );
            }

          fprintf (stdout, "\n" );
          free (euroString);
          free (ethioString);

        }
      else /* we want current time with hours:minutes:seconds */
        {
          ethioString = easctime ( Time, timeFlags->calIn, 
                                     timeFlags->calOut, timeFlags->LCInfo );
          fprintUTF8String ( stdout, ethioString, iPath, lethFlags );
          free (ethioString);
        }
    }


  if ( timeFlags->isHoliday || timeFlags->Talbot || timeFlags->YearName 
       || timeFlags->isLeapYear )
    {

      /* in these four cases we need to set up values for date, 
         month and year. So we need to define the variable as per
         the source of time we are working with                   */

      date  = (int *) malloc (sizeof(int)); 
      month = (int *) malloc (sizeof(int));
      year  = (long int *) malloc (sizeof(long int));

      if ( timeFlags->date == NIL ) 
        {
          *date  = Time->tm_mday;
          *month = Time->tm_mon + 1;
          *year  = Time->tm_year + 1900;
        }
      else
        {
          *date  = timeFlags->date;
          *month = timeFlags->month;
          *year  = timeFlags->year;
        }

      if ( timeFlags->calIn == eng ) 
        GregorianToEthiopic ( date, month, year );


      if ( timeFlags->Talbot )
        {
          ethioString = getEthiopicDayName ( *date, *month, timeFlags->LCInfo );
          fprintUTF8String ( stdout, ethioString, iPath, lethFlags );
          fprintf (stdout, "\n" );
          free (ethioString);
        }
      if ( timeFlags->isHoliday )
        {
          ethioString = isEthiopianHoliday ( *date, *month, *year, timeFlags->LCInfo );
          if ( ethioString != NULL )
            {
              fprintUTF8String ( stdout, ethioString, iPath, lethFlags );
              fprintf (stdout, "\n" );
              free (ethioString);
            }
        }
      if ( timeFlags->YearName )
        {
          ethioString = getEthiopicYearName ( *year, timeFlags->LCInfo );
          fprintUTF8String ( stdout, ethioString, iPath, lethFlags );
          fprintf (stdout, "\n" );
          free (ethioString);
        }
      if ( timeFlags->isLeapYear )
        fprintf ( stdout, "%i\n", isEthiopicLeapYear(*year) );

      free ( date );
      free ( month );
      free ( year );

    }



  exit (0);

}




int
fprintUTF8String ( fp, utf8String, iPath, lethFlags )
  FILE* fp;
  unsigned char* utf8String;
  char* iPath;
  LibEthFlags* lethFlags;
{

enum HTMLEscapes TagOn = Off;
boolean set0On = false;
int setid=NIL;
FCHAR* uniString = NULL;
unsigned char* outString = NULL;


  uniString = sget_fstring ( utf8String, lethFlags );

  switch ( lethFlags->csOut )
    {

    /*  Image, TeX and Java are not character codes schemes so we
     *  handle I/O at this level and not in the library.
     */

     case image:
       fout_image (uniString, iPath, fp, lethFlags);
       break;

     case java:  
     case Java:  
       fout_java (uniString, fp, lethFlags);
       break;

#ifdef  SUPPORT_TEX
     case muletex:  
       fout_tex (uniString, fp, lethFlags);
       break;
#endif  /* SUPPORT_TEX */

     default:
       if ( lethFlags->docIn == html && isFidelTrueType( lethFlags->csOut ) )
         {
           setid = fidel_HTML_sputs (uniString, &outString, setid, &TagOn, &set0On,  closeStream, lethFlags);
           fprintf ( fp, "%s", outString );
           free ( outString );
         }
       else
         fidel_puts (uniString, lethFlags);

       break;

    }


  if (uniString != NULL)
    free (uniString);


  return (1);

}




/*-------------------------------------------------------------------------//
//                                                                         //
//  Simple routine to read input options and reset the default flags.      //
//                                                                         //
//-------------------------------------------------------------------------*/


boolean 
flag_reset (argc, argv, iPath, timeFlags, lethFlags)
  int argc;
  char** argv;
  char** iPath;
  MyFlags** timeFlags;
  LibEthFlags** lethFlags;
{

register int i=0,k;


/*---------------- Define and Initialize Flag Values -------------------------*/


  *lethFlags              = SetDefaultLibEthFlags (NIL, LETLANGMINOR, NIL);
  (*lethFlags)->csIn      = utf8;

  *timeFlags              = (MyFlags *) malloc ( sizeof(MyFlags) );
  (*timeFlags)->LCInfo    = 0;
  (*timeFlags)->AATime    = false;
  (*timeFlags)->Talbot    = false;
  (*timeFlags)->isHoliday = false;
  (*timeFlags)->isLeapYear= false;
  (*timeFlags)->YearName  = false;
  (*timeFlags)->noTime    = false;
  (*timeFlags)->calIn     = eng;    /* meaning Gregorian */
  (*timeFlags)->calOut    = (*lethFlags)->top->l;
  (*timeFlags)->date      = NIL;
  (*timeFlags)->month     = NIL;
  (*timeFlags)->year      = NIL;


/* We go ahead and reset the calOut variable now to make life easier later
   since other command like flags will depend on this info                 */

  while ( ++i < argc && strcmp ( argv[i], "-l" ) && strcmp ( argv[i], "-lang" ) );

  if ( ++i < argc )  /* we found a -l or -lang request */
    {
      if ( !strcmp(argv[i], ISO639_3Names[amh]) 
            || !strcmp(argv[i], ISO639_2Names[amh]) )
        (*timeFlags)->calOut = amh;
      else if ( !strcmp(argv[i], ISO639_3Names[tir]) 
            || !strcmp(argv[i], ISO639_2Names[tir]) )
        (*timeFlags)->calOut = tir;
      else
        {
          fprintf (stderr, "Language %s Not Supported\n",argv[i]);
          exit (1);
        }
    }

    
/*---------------- What do You Want From Me? ---------------------------------*/

  i = 0;
  while ( ++i < argc )
    {
      if ( argv[i][0] == '-' ) 
        {
          switch ( toupper(argv[i][1]) ) 
            {
              case '1' :  (*timeFlags)->LCInfo |= WITHONEPREFIX;
                          break;

              case 'A' :  if ( toupper(argv[i][2]) == 'A' )
                            (*timeFlags)->AATime = true;
                          else if ( toupper(argv[i][2]) == 'M' )
                            (*timeFlags)->LCInfo |= WITHAM;
                          else 
                            goto USAGE;
                          break;

              case 'B' :  /*  -b as in 'be`al'         */
                          (*timeFlags)->isHoliday = true;
                          break;

              case ',' :
              case 'C' :  (*timeFlags)->LCInfo |= WITHDAYCOMMA;
                          break;

              case 'D' :  (*lethFlags)->csOut = debug;
                          break;

              case 'E' :  if ( toupper(argv[i][2]) == 'H' )
                            (*timeFlags)->LCInfo |= WITHETHHOUR;
                          else if ( toupper(argv[i][2]) == 'D' )
                            (*timeFlags)->LCInfo |= WITHETHDATE;
                          else if ( toupper(argv[i][2]) == 'Y' )
                            (*timeFlags)->LCInfo |= WITHETHYEAR;
                          else 
                            (*timeFlags)->calIn = (*timeFlags)->calOut;
                          break;

              case 'F' :  if ( toupper(argv[i][2]) == 'N' )
                            (*lethFlags)->fontFace =  atoi(argv[++i]);
                          else 
                            goto USAGE;
                          break;

              case 'H' :  if ( !strcmp ( &argv[i][1], "html") )
                            (*lethFlags)->docIn = html;
                          else
                            goto USAGE;
                          break;
                         
              case 'L' :  if ( toupper(argv[i][2]) == 'Y' )
                            {
                              (*timeFlags)->isLeapYear = true;
                              break;
                            }
                          i++; /* increment because we are back to -lang and
                                  need to skip over the lang request          */


                          break; 

              case ':' :
              case 'N' :  (*timeFlags)->LCInfo |= WITHNETEB;
                          break;

              case 'O' :  i++;
                          (*timeFlags)->LCInfo |= WITHUTF8;
                          if ( strstr ( argv[i], "-html" ) )
                            (*lethFlags)->cstOut = html;

                          (*lethFlags)->csOut = getOutputSystem (argv[i]);

                          if ( (*lethFlags)->csOut ==  image )
                            {
                              (*lethFlags)->csOut  =  image;
                              if ( argv[++i][0] == '-' )
                                {
                                  fprintf ( stderr, "Image Path Has Unexpected '-': %s\n", argv[i] );
                                  exit (1);
                                }
                              *iPath = (char *)malloc ( strlen(argv[i]) * sizeof(char) );
                              strcpy ( *iPath, argv[i] );
                            }
                          else if ( !strcmp (argv[i], "tex") )
#ifdef SUPPORT_TEX
                            {
                              (*lethFlags)->csOut   =  muletex;
                              (*lethFlags)->cstOut  =  tex;
                            }
#else
                            {
                              fprintf (stderr, "\a TeX Output Not Available By This Package \n");
                              exit (1);
                            }
#endif
                          else if ( !strcmp (argv[i], "latex") )
#ifdef SUPPORT_TEX
                            {
                              (*lethFlags)->csOut   =  muletex;
                              (*lethFlags)->cstOut  =  ltx;
                            }
#else
                            {
                              fprintf (stderr, "\a LaTeX Output Not Available By This Package \n");
                              exit (1);
                            }
#endif
                          else if ( !strcmp (argv[i], "sera") )
                            (*lethFlags)->csOut  =  sera;

                          break;

              case 'Q' :  (*timeFlags)->LCInfo |= WITHQEN;
                          break;

              case 'S' :  (*timeFlags)->noTime = true;
                          break;

              case 'T' :  (*timeFlags)->Talbot = true;
                          break;

              case 'U' :  (*timeFlags)->LCInfo |= WITHUTF8;
                          break;

              case 'V' :  fprintf (stdout, "This is %s Version %0.1f%i", argv[0], GFF_UTIL_MAJOR_VERSION, GFF_UTIL_MINOR_VERSION);
                          fprintf (stdout, "  (%s)\n", GFF_UTIL_EXPORT_DATE);
                          exit (1);
                          break;

              case 'X' :  closeStream = true;
                          break;

              case 'Y' : (*timeFlags)->YearName = true;
                          break;

              case '/' :  (*timeFlags)->LCInfo |= WITHSLASH;
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
      else
        {
          if ( argc - i < 3 
               || !isdigit(argv[i+1][0])  
               || !(isdigit(argv[i+2][0]) || (argv[i+2][0] == '-' && isdigit(argv[i+2][1])) ) 
             )
            {
              printf ("Date Arguments must be in the form DAY MONTH YEAR\n");
              exit (1);
            }
          (*timeFlags)->date   = atoi(argv[i++]);
          (*timeFlags)->month  = atoi(argv[i++]) - 1;
          (*timeFlags)->year   = atoi(argv[i++]) - 1900;
        }
    }

  return (true);


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
