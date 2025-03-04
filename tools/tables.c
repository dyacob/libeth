#include <libeth/sysinfo.h>
#include <libeth/libeth.h>
#include <libeth/rtf.h>
#include "common.h"
#include "tables.h"

extern int UniToTraditional[];                 /* from fidel.map */


/*-------------------------------------------------------------------------//
//                                                                         //
//  Print Table of Character Occurances                                    //
//                                                                         //
//-------------------------------------------------------------------------*/


void 
Print_Text_Stats (fidelStats, statsFlags, lethFlags)
  StatsData  fidelStats[];
  StatsFlags* statsFlags;
  LibEthFlags* lethFlags;
{

register int i;
int trad, uniMap, charBase, mod, space=0, stop;
FCHAR uni=0, *uniP;
FILE* outTable;
StatsData* PStats[UNITOTAL];
int formsTotal[12], total=0, seraBytes = 0;


  uniP =& uni;
  lethFlags->csOut = statsFlags->csOut;

  /* get comprehensive totals */

  /* open table and document for unsorted statistics */
  
  outTable = fopen ( "stats.txt", "w" );
  fprintf ( outTable, "=====================================================================================\n\n" );

  lethFlags->csOut = sera;
  memset (formsTotal, 0, 12*sizeof(int));

  for (uni = UNIFIDEL; uni < MYA; uni++)
    if ( fidelStats[(uni-UNIFIDEL)].stat != 0 )
      {
        formsTotal[get_formNumber(uni)] += fidelStats[(uni-UNIFIDEL)].stat;
/*
 *      the below works fine but we loose a count for punctuations and numbers
 *
 *      fidelStats[uniMap].name = fidel_sputc ( uni, lethFlags );
 *      seraBytes += strlen (fidelStats[(uni-UNIFIDEL)].name);
 *      free (fidelStats[(uni-UNIFIDEL)].name);
 */   }
  for ( i = 0;  i < 12; i++ )
    total += formsTotal[i];
  fprintf ( outTable, "Total Chars in Document: %d\n", total );
  fprintf ( outTable, "\n----------------------------\n" );
  fprintf ( outTable, "\n--------------------------------------------------------------\n" );
  fprintf ( outTable, "Distribution of Syllables:\n" );
  fprintf ( outTable, "  e    u    i    a    E    I    o    We    W'   Wi    Wa    WE\n" );
  for ( i = 0;  i < 12; i++ )
    fprintf ( outTable, "%3d    ", formsTotal[i] );
  fprintf ( outTable, "\n--------------------------------------------------------------\n" );
  fprintf ( outTable, "Percentage Distribution of Syllables:\n" );
  fprintf ( outTable, "  e    u    i    a    E    I    o    We    W'   Wi    Wa    WE\n" );
  for ( i = 0;  i < 12; i++ )
    fprintf ( outTable, "%2.2f    ", ((float)formsTotal[i]/(float)total)*100.0 );
  fprintf ( outTable, "\n" );
  total=0;


  fprintf ( outTable, "=====================================================================================\n\n" );


  /* write text table */

  for (trad = 0; trad < UNITOTAL; trad += ROW) 
    {
      charBase = get_traditional ( trad, uniP );

      mod = get_fmodulo ( uni ); 

      if ( uni == SPACE || uni == MYA || uni == ONE )
        fprintf ( outTable, "-------------------------------------------------------------------------------------\n\n" );

      if ( uni == SPACE ) 
        space = 1;

      for (i=0; i<mod; i++) 
        {
          if ( (mod == 12 && i > 6) || (mod == 15) )
            uniMap = get_traditional (trad+i, uniP);
          else
            uniMap = charBase + i;
          fidelStats[uniMap].name = fidel_sputc ( uni, lethFlags );
          fprintf ( outTable, "%*s    ", 3+space, fidelStats[uniMap].name );
          uni++;
        }

     fprintf ( outTable, "\n" );

     if ( mod == 12 )                           /* start over, uniMap was trashed */
       uniMap = get_traditional ( trad, uniP );
     for (i=0; i<mod; i++) 
       {
         if ( mod == 12 && i > 6 )
           uniMap = get_traditional (trad+i, uniP);
         else
           uniMap = charBase + i;

         fprintf ( outTable, "%*d    ", 3+space, fidelStats[uniMap].stat );
         seraBytes += strlen (fidelStats[uniMap].name) * fidelStats[uniMap].stat;
         total += fidelStats[uniMap].stat;
       }

       fprintf ( outTable, "\n\n" );

      if (mod > 8)
        {
          if (mod == 12)
            trad += ROW;
          else if ( (uni-mod) == ONE )
            trad += 2;
          else if ( (uni-mod) == (TEN+1) )   /* (TEN+1) = TWENTY */
            trad += 2;
          else if ( isfpunct(uni) )
            trad = UNITOTAL;
        }

    }   /* end for */


  /* close table and document */

  fprintf ( outTable, "-------------------------------------------------------------------------------------\n" );
  fprintf ( outTable, "Total Ethiopic Chars: %d\n", total );
  fprintf ( outTable, "Total SERA    Bytes : %d\n", seraBytes );
  fprintf ( outTable, "Total Uniocde Bytes : %d  (%f)\n", total*2, ((float)seraBytes/((float)total*2.0))*100.0 );
  fprintf ( outTable, "Total UTF-8   Bytes : %d  (%f)\n", total*3, ((float)seraBytes/((float)total*3.0))*100.0 );
  fprintf ( outTable, "-------------------------------------------------------------------------------------" );
  fclose ( outTable );


 
  /* open table and document for sorted statistics */

  outTable = fopen ( "stats2.txt", "w" );
  fprintf ( outTable, "-------------------------------------------------------------------------------------\n\n" );


  /* sort the statistics */

  for ( i = 0; i < UNITOTAL; i++ )
    {
      PStats[i] =& fidelStats[i]; 
      // fprintf (stdout, "%i => %s\n", i, fidelStats[i].name); 
    }
  qsort ( PStats, UNITOTAL, sizeof(StatsData *), gt );
  space = stop = 0;


  /* write sorted text table */

  for (trad = 0; trad < UNITOTAL; trad += ROW) 
    {
      fprintf ( outTable, "\n" );

      for (i=0; i < 8; i++) 
        fprintf ( outTable, "%0*d    ", 3+space, trad+i );
      fprintf ( outTable, "\n" );
      stop = 0;


      for (i=0; stop != 8 && (trad+i) < UNITOTAL; i++) 
        if ( PStats[trad+i]->name != NULL )
          {
            fprintf ( outTable, "%*s    ", 3+space, PStats[trad+i]->name );
            stop++;
          }

      fprintf ( outTable, "\n" );
      stop = 0;


      for (i=0; stop != 8 && (trad+i) < UNITOTAL; i++) 
        if ( PStats[trad+i]->name != NULL )
          {
            fprintf ( outTable, "%*d    ", 3+space, PStats[trad+i]->stat );
            stop++;
          }
      fprintf ( outTable, "\n\n" );


      if (i > ROW)
        trad += (i-ROW);


    }  /* end for */


  /* close table and document */

  fprintf ( outTable, "-------------------------------------------------------------------------------------");
  fclose ( outTable );


  return;

}




void 
Print_RTF_Stats (fidelStats, statsFlags, lethFlags)
  StatsData  fidelStats[];
  StatsFlags* statsFlags;
  LibEthFlags* lethFlags;
{

register int i;
int trad, uniMap, charBase, mod, space=0, stop;
FCHAR uni=0, *uniP;
char *rtfHead;
FILE* outTable;
StatsData* PStats[UNITOTAL];



  uniP =& uni;
  lethFlags->csOut = statsFlags->csOut;


  /* open table and document for unsorted statistics */
  
  outTable = fopen ( "stats.rtf", "w" );
  /*
   *  This header could be libeth's get_RTF_header
   *  
   */
  get_RTF_header ( lethFlags->fontFaceIn, &rtfHead, lethFlags );
  fprintf ( outTable, "%s", rtfHead );

  /*  
   *  Replace this in the future with an rtf line drawing code
   */
  fprintf ( outTable, "-------------------------------------------------------------------------------------\n\n" );


  /* write text table */

  for (trad = 0; trad < UNITOTAL; trad += ROW) 
    {
      charBase = get_traditional ( trad, uniP );

      mod = get_fmodulo ( uni ); 

      if ( uni == SPACE || uni == MYA || uni == ONE )
        fprintf ( outTable, "-------------------------------------------------------------------------------------\\\r\n" );

      if ( uni == SPACE ) 
        space = 1;

      for (i=0; i<mod; i++) 
        {
          if ( (mod == 12 && i > 6) || (mod == 15) )
            uniMap = get_traditional (trad+i, uniP);
          else
            uniMap = charBase + i;
          fidelStats[uniMap].name = fidel_sputc ( uni, lethFlags );
          fprintf ( outTable, "%*s    ", 3+space, fidelStats[uniMap].name );
          uni++;
        }

     fprintf ( outTable, "\\\r\n" );

     if ( mod == 12 )                           /* start over, uniMap was trashed */
       uniMap = get_traditional ( trad, uniP );
     for (i=0; i<mod; i++) 
       {
         if ( mod == 12 && i > 6 )
           uniMap = get_traditional (trad+i, uniP);
         else
           uniMap = charBase + i;

         fprintf ( outTable, "%*d    ", 3+space, fidelStats[uniMap].stat );
       }

      fprintf ( outTable, "\\\r\n\n" );

      if (mod > 8)
        {
          if (mod == 12)
            trad += ROW;
          else if ( (uni-mod) == ONE )
            trad += 2;
          else if ( (uni-mod) == (TEN+1) )   /* (TEN+1) = TWENTY */
            trad += 2;
          else if ( isfpunct(uni) )
            trad = UNITOTAL;
        }

    }   /* end for */


  /* close table and document */

  fprintf ( outTable, "-------------------------------------------------------------------------------------\\\r\n" );
  fprintf ( outTable, "\\par }\n" );  /* close this file and we're done! */
  fclose ( outTable );


 
  /* open table and document for sorted statistics */

  outTable = fopen ( "stats2.rtf", "w" );
  /*
   *  This header could be libeth's get_RTF_header
   *  
   */
  get_RTF_header ( lethFlags->fontFaceIn, &rtfHead, lethFlags );

  fprintf ( outTable, "-------------------------------------------------------------------------------------\\\r\n" );


  /* sort the statistics */

  for ( i = 0; i < UNITOTAL; i++ )
    PStats[i] =& fidelStats[i]; 
  qsort ( PStats, UNITOTAL, sizeof(StatsData *), gt );
  space = stop = 0;


  /* write text table */

  for (trad = 0; trad < UNITOTAL; trad += ROW) 
    {
      fprintf ( outTable, "\n" );

      for (i=0; i < 8; i++) 
        fprintf ( outTable, "%0*d    ", 3+space, trad+i );
      fprintf ( outTable, "\\\r\n" );
      stop = 0;


      for (i=0; stop != 8 && (trad+i) < UNITOTAL; i++) 
        if ( PStats[trad+i]->name != NULL )
          {
            fprintf ( outTable, "%*s    ", 3+space, PStats[trad+i]->name );
            stop++;
          }

      fprintf ( outTable, "\\\r\n" );
      stop = 0;


      for (i=0; stop != 8 && (trad+i) < UNITOTAL; i++) 
        if ( PStats[trad+i]->name != NULL )
          {
            fprintf ( outTable, "%*d    ", 3+space, PStats[trad+i]->stat );
            stop++;
          }
      fprintf ( outTable, "\\\r\n" );


      if (i > ROW)
        trad += (i-ROW);


    }  /* end for */


  /* close table and document */

  fprintf ( outTable, "-------------------------------------------------------------------------------------\\\r\n");
  fprintf ( outTable, "\\par }\n" );  /* close this file and we're done! */
  fclose ( outTable );


  return;

}


void 
Print_HTML_Stats (fidelStats, statsFlags, lethFlags)
  StatsData  fidelStats[];
  StatsFlags* statsFlags;
  LibEthFlags* lethFlags;
{

register int i;
int trad, uniMap, charBase, mod, space=0, stop;
FCHAR uni=0, *uniP;
FILE* outTable;
StatsData* PStats[UNITOTAL];


  uniP =& uni;
  lethFlags->csOut = statsFlags->csOut;

  /* open table and document for unsorted statistics */

  outTable = fopen ( "stats.html", "w" );
  fprintf ( outTable, "<html>\n<head>\n");
  fprintf ( outTable, "  <title>Unsorted Fidel Character Occurances</title>\n</head>\n<body bgcolor=\"#f0f0f0\">\n\n");
  fprintf ( outTable, "<a name=\"top\"><h2 align=\"center\"><hr size=4 width=80%%>Unsorted Fidel Character Occurances<hr size=2 width=60%%></h2>\n\n<p>\n\n");
  fprintf ( outTable, "<center>\n<table border>\n");


  /* write HTML table */

  for (trad = 0; trad < UNITOTAL; trad += ROW) 
    {
      fprintf ( outTable, "  <tr>" );

      charBase = get_traditional ( trad, uniP );

      mod = get_fmodulo ( uni ); 

      if ( uni == SPACE ) 
        space = 1;

      for (i=0; i<mod; i++) 
        {
          if ( (mod == 12 && i > 6) || (mod == 15) )
            uniMap = get_traditional (trad+i, uniP);
          else
            uniMap = charBase + i;

          fidelStats[uniMap].name = fidel_sputc ( uni, lethFlags );

          fprintf ( outTable, "<td>%s<br>%d</td>", fidelStats[uniMap].name, fidelStats[uniMap].stat );

          uni++;
        }

      for (i=mod; i<15; i++) 
        fprintf ( outTable, "<td>&nbsp;</td>" );


      fprintf ( outTable, "</tr>\n  <tr>" );

      if (mod > 8)
        {
          if (mod == 12)
            trad += ROW;
          else if ( (uni-mod) == ONE )
            trad += 2;
          else if ( (uni-mod) == (TEN+1) )   /* (TEN+1) = TWENTY */
            trad += 2;
          else if ( isfpunct(uni) )
            trad = UNITOTAL;
        }

    }   /* end for */


  /* close table and document */

  fprintf ( outTable, "<tr><td colspan=4><a href=\"#top\">Back To Top</a></td>");
  fprintf ( outTable, "<td colspan=5>&nbsp;</td><td colspan=6 align=right><strong><em><a href=\"stats2.html\">To Sorted Stats</a></em></strong></td></tr>\n");
  fprintf ( outTable, "</table>\n</center>\n\n");
  fprintf ( outTable, "\n\n<hr>\n\n</body>\n</html>\n");

  fclose ( outTable );
 

  /* open table and document for sorted statistics */

  outTable = fopen ( "stats2.html", "w" );
  fprintf ( outTable, "<html>\n<head>\n");
  fprintf ( outTable, "  <title>Sorted Fidel Character Occurances</title>\n</head>\n<body bgcolor=\"#f0f0f0\">\n\n");
  fprintf ( outTable, "<a name=\"top\"><h2 align=\"center\"><hr size=4 width=80%%>Sorted Fidel Character Occurances<hr size=2 width=60%%></h2>\n\n<p>\n\n");
  fprintf ( outTable, "<center>\n<table border>\n");

  /* sort the statistics */

  for ( i = 0; i < UNITOTAL; i++ )
    PStats[i] =& fidelStats[i]; 
  qsort ( PStats, UNITOTAL, sizeof(StatsData *), gt );


  /* write HTML table */

  space = stop = 0;
  for (trad = 0; trad < UNITOTAL; trad += ROW) 
    {
      fprintf ( outTable, "  <tr>" );

      for (i=0; stop != 8 && (trad+i) < UNITOTAL; i++) 
        if ( PStats[trad+i]->name != NULL )
          {
            fprintf ( outTable, "<td>%0*d<br>%s<br>%d</td>", 3+space, trad+i, PStats[trad+i]->name, PStats[trad+i]->stat );
            stop++;
          }

      fprintf ( outTable, "\n" );
      stop = 0;


      fprintf ( outTable, "</tr>\n  <tr>" );


      if (i > ROW)
        trad += (i-ROW);

    }  /* end for */


  /* close table and document */

  fprintf ( outTable, "<tr><td colspan=4><a href=\"#top\">Back To Top</a></td>");
  fprintf ( outTable, "<td colspan=4 align=right><strong><em><a href=\"stats.html\">To UnSorted Stats</a></em></strong></td></tr>\n");
  fprintf ( outTable, "</table>\n</center>\n\n");
  fprintf ( outTable, "\n\n<hr>\n\n</body>\n</html>\n");

  fclose ( outTable );


  return;

}





#ifdef SUPPORT_TEX 


void 
Print_TeX_Stats (fidelStats, statsFlags, lethFlags)
  StatsData  fidelStats[];
  StatsFlags* statsFlags;
  LibEthFlags* lethFlags;
{

register int i;
int trad, uniMap, charBase, mod, space=0, stop;
FCHAR uni=0, *uniP;
FILE* outTable;
StatsData* PStats[UNITOTAL];


  uniP =& uni;
  lethFlags->csOut = statsFlags->csOut;

  /* open table and document for unsorted statistics */

  outTable = fopen ( "stats.tex", "w" );

  if (lethFlags->cstOut == ltx) 
    {
      fprintf ( outTable, "\\documentstyle{report} \n\\begin{document}\n\n" );
      fprintf ( outTable, "\\newfont{\\fidel}{%s%s%d.%dpk}\n", TEXFONTDIR, FONTPREFIX, TEXFONTSIZE, FONTDPI );
      fprintf ( outTable, "\\newfont{\\fidelx}{%s%sxx%d.%dpk}\n", TEXFONTDIR, FONTPREFIX, TEXFONTSIZE, FONTDPI );
      fprintf ( outTable, "\\include{fidelmap}\n\n" );
      fprintf ( outTable, "{\\Large\\textbf Character Occurance Statistics}\n\n" );
      fprintf ( outTable, "\\begin{tabular}{|c|c|c|c|c|c|c|c|} \\hline\\hline\n" );
    }
  else
    {
      fprintf ( outTable, "\\font\\fidel=%s%s%d.%dpk\n", TEXFONTDIR, FONTPREFIX, TEXFONTSIZE, FONTDPI );
      fprintf ( outTable, "\\font\\fidelx=%s%sxx%d.%dpk\n", TEXFONTDIR, FONTPREFIX, TEXFONTSIZE, FONTDPI );
      fprintf ( outTable, "\\input fidelmap.tex\n" );
      fprintf ( outTable, "{\\Large\\bf Character Occurance Statistics}\n\n" );
      /*
       * unfortunately I don't remember tables in TeX anymore, so the below
       * will have to modified later.
       */
      fprintf ( outTable, "\\begin{tabular}{|c|c|c|c|c|c|c|c|} \\hline\\hline\n" );
    }


  /* write LaTeX table */

  for (trad = 0; trad < UNITOTAL; trad += ROW) 
    {

      charBase = get_traditional ( trad, uniP );

      mod = get_fmodulo ( uni ); 

      if ( uni == SPACE ) 
        space = 1;

      for (i=0; i<mod; i++) 
        {
          if ( (mod == 12 && i > 6) || (mod == 15) )
            uniMap = get_traditional (trad+i, uniP);
          else
            uniMap = charBase + i;
          fidelStats[uniMap].name = fidel_sputc ( uni, lethFlags );
          fprintf ( outTable, "%*s &  ", 3+space, fidelStats[uniMap].name );
          uni++;
        }

     fprintf ( outTable, " \\\n" );

     if ( mod == 12 )                           /* start over, uniMap was trashed */
       uniMap = get_traditional ( trad, uniP );
     for (i=0; i<mod; i++) 
       {
         if ( mod == 12 && i > 6 )
           uniMap = get_traditional (trad+i, uniP);
         else
           uniMap = charBase + i;

         fprintf ( outTable, "%*d &  ", 3+space, fidelStats[uniMap].stat );
       }

      fprintf ( outTable, "\\\\ \\hline\n" );

      if (mod > 8)
        {
          if (mod == 12)
            trad += ROW;
          else if ( (uni-mod) == ONE )
            trad += 2;
          else if ( (uni-mod) == (TEN+1) )   /* (TEN+1) = TWENTY */
            trad += 2;
          else if ( isfpunct(uni) )
            trad = UNITOTAL;
        }

    }   /* end for */


  /* close table and document */

  fprintf ( outTable, "\\hline\\hline\n\\end{tabular}\n\n" );
  fprintf ( outTable, "\\newpage\n");

 


  /* open table and document for sorted statistics */

  if (lethFlags->cstOut == ltx) 
    {
      fprintf ( outTable, "{\\Large\\textbf Character Occurance Statistics}\n\n" );
      fprintf ( outTable, "\\begin{tabular}{|c|c|c|c|c|c|c|c|} \\hline\\hline\n" );
    }
  else
    {
      fprintf ( outTable, "{\\Large\\bf Character Occurance Statistics}\n\n" );
      /*
       * unfortunately I don't remember tables in TeX anymore, so the below
       * will have to modified later.
       */
      fprintf ( outTable, "\\begin{tabular}{|c|c|c|c|c|c|c|c|} \\hline\\hline\n" );
    }


  /* sort the statistics */

  for ( i = 0; i < UNITOTAL; i++ )
    PStats[i] =& fidelStats[i]; 
  qsort ( PStats, UNITOTAL, sizeof(StatsData *), gt );


  /* write LaTeX table */

  space = stop = 0;
  for (trad = 0; trad < UNITOTAL; trad += ROW) 
    {
      fprintf ( outTable, "\n" );

      for (i=0; i < 8; i++) 
        fprintf ( outTable, "%0*d &  ", 3+space, trad+i );
      fprintf ( outTable, "\\\n" );
      stop = 0;


      for (i=0; stop != 8 && (trad+i) < UNITOTAL; i++) 
        if ( PStats[trad+i]->name != NULL )
          {
            fprintf ( outTable, "%*s &  ", 3+space, PStats[trad+i]->name );
            stop++;
          }

      fprintf ( outTable, "\\\n" );
      stop = 0;


      for (i=0; stop != 8 && (trad+i) < UNITOTAL; i++) 
        if ( PStats[trad+i]->name != NULL )
          {
            fprintf ( outTable, "%*d &  ", 3+space, PStats[trad+i]->stat );
            stop++;
          }
      fprintf ( outTable, "\\\\ \\hline \n" );


      if (i > ROW)
        trad += (i-ROW);


    }  /* end for */


  /* close table and document */

  fprintf ( outTable, "\\hline\\hline\n\\end{tabular}\n\n" );
  if ( lethFlags->cstOut == ltx )               /*  it's latex */
    fprintf ( stdout, "\n\\end{document}\n" );
  else                                          /*  it's tex   */
    fprintf ( stdout, "\n\\bye\n" );

  fclose ( outTable );


  return;

}

#endif  /* SUPPORT_TEX */



int gt ( A, B )
  const void *A, *B;
{
  return ( (*(StatsData **)B)->stat - (*(StatsData **)A)->stat );
}

