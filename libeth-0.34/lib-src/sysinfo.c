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

#include <stdio.h>
#include <string.h>
#include "fidel.h"
#include "etstdlib.h"
#include "etctype.h"
#include "lethutil.h"
#include "sysinfo.h"
#include "../systems/exports.h"


char* CharacterSetNames[ETHCHARSETS] = _CharacterSetNames;

FILE* iofp;


#define SUPPORT_ALL 1
#define SUPPORT_IES 0

 /*============================================================================/
/=============================================================================/
//  get_fchar (tstring, fp, mylflags)
//
//  Return address of next token from passed stream of SERA text. Either
//  the file or text string pointer must be NULL.
//  The address of the returned token is specified by the character coding
//  system passed in mylflags->out.
//
//  get_fchar is intended to be of very low level, such that users would not
//  be using it.
//
//  tstring  -is a character pointer to SERA text
//  fp       -is a file pointer to SERA text
//  mylflags -is a LEth Flag structure which MUST contain a valid input and
//            output type.
//
//=============================================================================/
/============================================================================*/


FCHAR 
get_fchar (fp, mylflags)
  FILE* fp;
  LibEthFlags* mylflags;
{

FCHAR fch = NIL;
extern LibEthFlags* FidelFlags;  /* in lib-src/etstdlib.c */


  /* these next two tests would actually happen within systemio.c so
   * we are safe if we don't do them, but lets check here just to save
   * a little travel
   */
  if ( mylflags->holdChars
       && isethiopic (mylflags->holdChars[ mylflags->holdChars[0] ]) )
    {
      fch = mylflags->holdChars[ mylflags->holdChars[0]++ ];
      if ( !mylflags->holdChars[ mylflags->holdChars[0] ] )
        {
          free ( mylflags->holdChars );
          mylflags->holdChars = NULL;
        }
      return ( fch );
    }
  else if ( mylflags->stringTop && !mylflags->stringTop[0] )
    return ( 0 );
  else
    /*  We need export this so getToken can access the holdChars list.
     */
    FidelFlags = mylflags = checkLibEthFlags ( mylflags );

  iofp = fp;

  switch (mylflags->csIn)
    {
#if SUPPORT_ACIS || SUPPORT_ALL 
      case acis :
           fch = ACISToUnicode ();
           break;
#endif /* SUPPORT_ACIS || SUPPORT_ALL */


#if SUPPORT_ACUWORK || SUPPORT_ALL 
      case acuwork :
           fch = AcuworkToUnicode ();
           break;
#endif /* SUPPORT_ACUWORK || SUPPORT_ALL */


#if SUPPORT_ADDISWORD || SUPPORT_ALL 
      case addisword1 : 
           fch = AddisWordOneToUnicode ();
           break;
      case addisword2 : 
           fch = AddisWordTwoToUnicode ();
           break;
#endif  /* SUPPORT_ADDISWORD || SUPPORT_ALL */


#if SUPPORT_ALPAS || SUPPORT_ALL 
      case alpas :
           fch = AlpasToUnicode ();
           break;
#endif /* SUPPORT_ALPAS || SUPPORT_ALL */


#if SUPPORT_BRANA || SUPPORT_ALL
      case branai :
           fch = BranaIToUnicode ();
           break;
      case branaii:
           fch = BranaIIToUnicode ();
           break;
#endif /* SUPPORT_BRANA || SUPPORT_ALL */


#if SUPPORT_CBHALE || SUPPORT_ALL
      case cbhalea:
           fch = CBHaleAToUnicode ();
           break;
      case cbhaleb:
           fch = CBHaleBToUnicode ();
           break;
#endif /* SUPPORT_CBHALE || SUPPORT_ALL */


#if SUPPORT_DEJENE || SUPPORT_ALL 
      case dejene1 : 
           fch = Dejene1ToUnicode ();
           break;
      case dejene2 : 
           fch = Dejene2ToUnicode ();
           break;
#endif  /* SUPPORT_DEJENE || SUPPORT_ALL */


#if SUPPORT_ECOLING || SUPPORT_ALL
/*    case ecoling :
           fch = EcoLingUnicode ();
           break;
*/
#endif /* SUPPORT_ECOLING || SUPPORT_ALL */


#if SUPPORT_ED || SUPPORT_ALL
      case ed  :
           fch = EdToUnicode ();
           break;
#endif /* SUPPORT_ED || SUPPORT_ALL */


#if SUPPORT_ETHIOME || SUPPORT_ALL
      case ethiome  :
           fch = EthioMEPrimaryToUnicode   ();
      case ethiomex :
           fch = EthioMESecondaryToUnicode ();
           break;
#endif /* SUPPORT_ME || SUPPORT_ALL */


#if SUPPORT_ETHIOP || SUPPORT_ALL
      case ethiop :
           fch = EthiopToUnicode ();
           break;
#endif /* SUPPORT_ETHIOP || SUPPORT_ALL */


#if SUPPORT_ETHIOPIC || SUPPORT_ALL 
      case ethiopic1 : 
           fch = Ethiopic1ToUnicode ();
           break;
      case ethiopic2 : 
           fch = Ethiopic2ToUnicode ();
           break;
#endif  /* SUPPORT_ETHIOPIC || SUPPORT_ALL */


#if SUPPORT_ETHCITA
      case ethcitau  : 
           fch = EthCITAUniPToUnicode ();
      case ethcitap  : 
           fch = EthCITABiPToUnicode  ();
           break;
      case ethcitas  : 
           fch = EthCITABiSToUnicode  ();
           break;
#endif  /* SUPPORT_ETHCITA || SUPPORT_ALL */


#if SUPPORT_ETHIOSYS || SUPPORT_ALL 
      case ethiosys  : 
           fch = EthioSysPrimaryToUnicode   ();
           break;
      case ethiosysx : 
           fch = EthioSysSecondaryToUnicode ();
           break;
#endif  /* SUPPORT_ETHIOSYS || SUPPORT_ALL */


#if SUPPORT_ETHIOWALIA || SUPPORT_ALL 
      case ethiowalia  : 
           fch = EthioWaliaToUnicode   ();
           break;
#endif  /* SUPPORT_ETHIOWALIA || SUPPORT_ALL */


#if SUPPORT_FIDELEXTRA || SUPPORT_ALL
      case fidelxtr1 :
           fch = FidelExtra1ToUnicode ();
           break;
      case fidelxtr2 :
           fch = FidelExtra2ToUnicode ();
           break;
#endif /* SUPPORT_FIDELEXTRA || SUPPORT_ALL */


#if SUPPORT_GEEZEDIT || SUPPORT_ALL 
      case gezedit :
           fch = GeezEditToUnicode ();
           break;
#endif  /* SUPPORT_GEEZEDIT || SUPPORT_ALL */


#if SUPPORT_GEEZFONT || SUPPORT_ALL 
      case gezfont :
           fch = GeezFontToUnicode ();
           break;
#endif /* SUPPORT_GEEZFONT || SUPPORT_ALL */


#if SUPPORT_GEEZFREE || SUPPORT_ALL
      case gezfree1  : 
           fch = EthioSysPrimaryToUnicode ();
           break;
      case gezfree2 : 
           fch = GeezFree2ToUnicode ();
           break;
#endif /* SUPPORT_GEEZFREE || SUPPORT_ALL */


#if SUPPORT_GEEZII || SUPPORT_ALL
      case gezi  :
           fch = GeezIToUnicode  ();
           break;
      case gezii :
           fch = GeezIIToUnicode ();
           break;
#endif /* SUPPORT_GEEZII || SUPPORT_ALL */


#if SUPPORT_GEEZIGNA || SUPPORT_ALL 
      case gezigna :
           fch = GeezignaToUnicode ();
           break;
#endif /* SUPPORT_GEEZIGNA || SUPPORT_ALL */


#if SUPPORT_GEEZNEWAB || SUPPORT_ALL
      case geznewa :
           fch = GeezNewAToUnicode ();
           break;
      case geznewb :
           fch = GeezNewBToUnicode ();
           break;
#endif /* SUPPORT_GEEZNEWAB || SUPPORT_ALL */


#if SUPPORT_LASERAMHARIC || SUPPORT_ALL
/*    case laser :
           fch = LaserAmharicToUnicode ();
           break;
*/
#endif /* SUPPORT_LASERAMHARIC || SUPPORT_ALL */


#if SUPPORT_MAINZ || SUPPORT_ALL
      case mainz  :
           /* fch = MainzToUnicode (); */
           break;
#endif /* SUPPORT_MAINZ || SUPPORT_ALL */


#if SUPPORT_MONOTYPE || SUPPORT_ALL
      case monotype1 :
           fch = MonoType1ToUnicode ();
           break;
      case monotype2 :
           fch = MonoType2ToUnicode ();
           break;
      case monotype3 :
           fch = MonoType3ToUnicode ();
           break;
      case monoalt :
           fch = MonoTypeAltToUnicode ();
           break;
/*    case mononum :
           fch = MonoTypeNumUnicode ();
           break;  */
#endif /* SUPPORT_MONOTYPE || SUPPORT_ALL */


#if SUPPORT_NCI || SUPPORT_ALL
      case nci :
           fch = NCIToUnicode ();
           break;
#endif /* SUPPORT_NCI || SUPPORT_ALL */


#if SUPPORT_NCIC || SUPPORT_ALL
      case ncic    :
           fch = NCICToUnicode ();
           break;
      case ncic_et :
           fch = NCIC_ETToUnicode ();
           break;
#endif /* SUPPORT_NCIC || SUPPORT_ALL */


#if SUPPORT_OMNITECH || SUPPORT_ALL
      case omnitech :
           fch = OmniTechToUnicode ();
           break;
#endif /* SUPPORT_OMNITECH || SUPPORT_ALL */


#if SUPPORT_PHONETICSYS || SUPPORT_ALL
      case geztype    :
           fch = GeezTypeToUnicode ();
           break;
      case geztypenet :
           fch = GeezTypeNetToUnicode ();
           break;
#endif /* SUPPORT_PHONETICSYS || SUPPORT_ALL */


#if SUPPORT_POWERGEEZ || SUPPORT_ALL
      case powergez :
           fch = PowerGeezToUnicode ();
           break;
      case powergeznum :
           fch = PowerGeezExtrasToUnicode ();
           break;
#endif /* SUPPORT_POWERGEEZ || SUPPORT_ALL */


#if SUPPORT_SAMAWERFA || SUPPORT_ALL
      case sam98:
           fch = Samawerfa98ToUnicode ();
           break;
      case samwp:
           fch = SamawerfaWPToUnicode ();
           break;
#endif /* SUPPORT_SAMAWERFA || SUPPORT_ALL */


#if SUPPORT_TFANUS || SUPPORT_ALL
      case ethiosoft:
      case gezbausi :
      case tfanus   :
      case tfanusnew:
           fch = TFanusToUnicode ( mylflags );
           break;
#endif /* SUPPORT_TFANUS || SUPPORT_ALL */


#if SUPPORT_VISUALGEEZ || SUPPORT_ALL
      case visualgez:
           fch = VisualGeezToUnicode ();
           break;
      case visualgez2k:
           fch = VisualGeez2000ToUnicode ();
           break;
#endif /* SUPPORT_VISUALGEEZ || SUPPORT_ALL */


#if SUPPORT_WAZEMA || SUPPORT_ALL 
      case wazema1  : 
           fch = WazemaA1ToUnicode ();
           break;
      case wazema2 : 
           fch = WazemaA2ToUnicode ();
           break;
#endif  /* SUPPORT_WAZEMA || SUPPORT_ALL */


#if SUPPORT_SERA || SUPPORT_ALL
      case sera:
           fch = SERAToUnicode ();
           break;
#endif /* SUPPORT_SERA || SUPPORT_ALL */



#if USE_TALIGENT && (SUPPORT_UTF8 || SUPPORT_ALL)
      case unicode:
           switch (mylflags->tvIn)
             {
               case utf8:
               default  :
                    fch = UTF8ToUnicode ();
                    break;
               case utf7:
                    fch = UTF7ToUnicode ();
                    break;
               case utf16:
                    fch = UTF16ToUnicode ();
                    break;
             }
           break;
#endif /* USE_TALIGENT  && (SUPPORT_UTF8 || SUPPORT_ALL) */


       default:  break;
  }


/*             tidy up....  */

  iofp       = NULL; 
  FidelFlags = NULL;  /* we need this to happen in all cases... */


  return ( mylflags->lastChar = fch );

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  fidel_sputc (fch, mylflags)
//
//  Convert a single address from a supported encoding system into character
//  types of  another.
//  The string length of the converted letter is returned.  
//
//  fch      -is the passed character address.
//  target   -is a character pointer whom we will direct to the output 
//            string allocated from memory by this routine.
//  mylflags -is a LEth Flag structure which MUST contain a valid input and
//            output type.
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


unsigned char*
fidel_sputc (fch, mylflags)
  FCHAR fch;
  LibEthFlags* mylflags;
{

unsigned char *returnCh = NULL, *newCh = NULL;
int i, j;
FCHAR uch = fch;


  mylflags = checkLibEthFlags ( mylflags );

  switch ( mylflags->csOut )
    {
#if SUPPORT_ACIS || SUPPORT_ALL
      case acis :
           returnCh = UnicodeToACIS ( fch );
           break;
#endif /* SUPPORT_ACIS || SUPPORT_ALL */


#if SUPPORT_ACUWORK || SUPPORT_ALL
      case acuwork :
           returnCh = UnicodeToAcuwork ( fch );
           break;
#endif /* SUPPORT_ACUWORK || SUPPORT_ALL */


#if SUPPORT_ADDISWORD || SUPPORT_ALL
      case addisword1 :
      case addisword2 :
           returnCh = UnicodeToAddisWord ( fch );
           break;
#endif /* SUPPORT_ADDISWORD || SUPPORT_ALL */


#if SUPPORT_ALPAS || SUPPORT_ALL
      case alpas :
           returnCh = UnicodeToAlpas ( fch );
           break;
#endif /* SUPPORT_ALPAS || SUPPORT_ALL */


#if SUPPORT_BRAILLE || SUPPORT_ALL
      case braille :
           switch ( mylflags->out->l )
             {
               case amh:
                    returnCh = UnicodeToBrailleAmharic ( fch );
                    break;
               case gez:
                    returnCh = UnicodeToBrailleGeez ( fch );
                    break;
               case tir:
               default :
                    returnCh = UnicodeToBrailleTigrigna ( fch );
                    break;
             }
           break;
#endif /* SUPPORT_BRAILLE || SUPPORT_ALL */


#if SUPPORT_BRANA || SUPPORT_ALL
      case branai :
      case branaii:
           returnCh = UnicodeToBrana ( fch );
           break;
#endif /* SUPPORT_BRANA || SUPPORT_ALL */


#if SUPPORT_CBHALE || SUPPORT_ALL
      case cbhalea:
      case cbhaleb:
           returnCh = UnicodeToCBHale ( fch );
           break;
#endif /* SUPPORT_CBHALE || SUPPORT_ALL */


#if SUPPORT_DEJENE || SUPPORT_ALL
      case dejene1: 
      case dejene2: 
           returnCh = UnicodeToDejene ( fch );
           break;
#endif /* SUPPORT_DEJENE || SUPPORT_ALL */


#if SUPPORT_ECOLING || SUPPORT_ALL
/*    case ecoling :
           returnCh = UnicodeToEcoLing ( fch );
           break;
*/
#endif /* SUPPORT_ECOLING || SUPPORT_ALL */


#if SUPPORT_ED || SUPPORT_ALL
      case dehai :
           returnCh = UnicodeToDehai ( fch, mylflags );
           break;
#endif /* SUPPORT_ED || SUPPORT_ALL */


#if SUPPORT_ED || SUPPORT_ALL
      case ed :
           returnCh = UnicodeToEd ( fch );
           break;
#endif /* SUPPORT_ED || SUPPORT_ALL */


#if SUPPORT_ENHPFR || SUPPORT_ALL
      case enhpfr :
           if ( fch < KHAE+DIQALA )
             returnCh = UnicodeToENHPFR_he ( fch );
           else
             returnCh = UnicodeToENHPFR_le ( fch );
           break;
#endif /* SUPPORT_ENHPFR || SUPPORT_ALL */


#if SUPPORT_ETHCITA
      case ethcitau  : 
           setid = UnicodeToEthCITAUni ( fch );
           break;
      case ethcitap  : 
      case ethcitas  : 
           setid = UnicodeToEthCITABi ( fch );
           break;
#endif  /* SUPPORT_ETHCITA || SUPPORT_ALL */


#if SUPPORT_ETHIOME || SUPPORT_ALL
      case ethiome :
           returnCh = UnicodeToEthioME ( fch );
           break;
#endif /* SUPPORT_ME || SUPPORT_ALL */


#if SUPPORT_ETHIOP || SUPPORT_ALL
      case ethiop :
           returnCh = UnicodeToEthiop ( fch );
           break;
#endif /* SUPPORT_ETHIOP || SUPPORT_ALL */


#if SUPPORT_ETHIOPIC || SUPPORT_ALL 
      case ethiopic1 :
      case ethiopic2 :
           returnCh = UnicodeToEthiopic ( fch );
           break;
#endif  /* SUPPORT_ETHIOPIC || SUPPORT_ALL */


#if SUPPORT_ETHIOSYS || SUPPORT_ALL
      case ethiosys  :
      case ethiosysx :
           returnCh = UnicodeToEthioSys ( fch );
           break;
#endif /* SUPPORT_ETHIOSYS || SUPPORT_ALL */


#if SUPPORT_ETHIOWALIA || SUPPORT_ALL 
      case ethiowalia  : 
           returnCh = UnicodeToEthioWalia ( fch );
           break;
#endif  /* SUPPORT_ETHIOWALIA || SUPPORT_ALL */


#if SUPPORT_FIDELEXTRA || SUPPORT_ALL
      case fidelxtr1 :
      case fidelxtr2 :
           returnCh = UnicodeToFidelExtra ( fch );
           break;
#endif /* SUPPORT_FIDELEXTRA || SUPPORT_ALL */


#if SUPPORT_GEEZEDIT || SUPPORT_ALL
      case gezedit :
           returnCh = UnicodeToGeezEdit ( fch );
           break;
#endif /* SUPPORT_GEEZEDIT || SUPPORT_ALL */


#if SUPPORT_GEEZFONT || SUPPORT_ALL
      case gezfont :
           returnCh = UnicodeToGeezFont ( fch );
           break;
#endif /* SUPPORT_GEEZFONT || SUPPORT_ALL */


#if SUPPORT_GEEZFREE || SUPPORT_ALL
      case gezfree1  : 
      case gezfree2 : 
           returnCh = UnicodeToGeezFree ( fch );
           break;
#endif /* SUPPORT_GEEZFREE || SUPPORT_ALL */


#if SUPPORT_GEEZIGNA || SUPPORT_ALL
      case gezigna :
           returnCh = UnicodeToGeezigna ( fch );
           break;
#endif /* SUPPORT_GEEZIGNA || SUPPORT_ALL */


#if SUPPORT_GEEZII || SUPPORT_ALL
      case gezi  :
      case gezii :
           returnCh = UnicodeToGeezII ( fch );
           break;
#endif /* SUPPORT_GEEZIGNA || SUPPORT_ALL */


#if SUPPORT_GEEZNEWAB || SUPPORT_ALL
      case geznewa :
      case geznewb :
           returnCh = UnicodeToGeezNewAB ( fch );
           break;
#endif /* SUPPORT_GEEZNEWAB || SUPPORT_ALL */


#if SUPPORT_IES
      case ies   :
           switch ( mylflags->out->l )
             {
               case amh:
                    returnCh = UnicodeToIESAmharic ( fch );
                    break;
               case gez:
                    returnCh = UnicodeToIESGeez ( fch );
                    break;
               case tir:
               default :
                    returnCh = UnicodeToIESTigrigna ( fch );
                    break;
             }

           break;
#endif  /* SUPPORT_IES || SUPPORT_ALL */


#if SUPPORT_ISO || SUPPORT_ALL
      case iso :
           returnCh = UnicodeToISOTC46SC2 ( fch, mylflags );
           break;
#endif /* SUPPORT_ISO || SUPPORT_ALL */


#if SUPPORT_JIS || SUPPORT_ALL
      case jis :
           returnCh = UnicodeToJIS ( fch );
           break;
#endif /* SUPPORT_JIS || SUPPORT_ALL */


#if SUPPORT_JUNET || SUPPORT_ALL
      case junet :
           returnCh = UnicodeToJUNET ( fch );
           break;
#endif /* SUPPORT_JUNET || SUPPORT_ALL */


#if SUPPORT_LASERAMHARIC || SUPPORT_ALL
/*    case laser :
           returnCh = UnicodeToLaserAmharic ( fch );
           break;
*/
#endif /* SUPPORT_LASERAMHARIC || SUPPORT_ALL */


#if SUPPORT_MAINZ || SUPPORT_ALL
      case mainz :
           returnCh = UnicodeToMainz ( fch, mylflags );
           break;
#endif /* SUPPORT_MAINZ || SUPPORT_ALL */


#if SUPPORT_MONOTYPE || SUPPORT_ALL
      case monotype1 :
      case monotype2 :
      case monotype3 :
           returnCh = UnicodeToMonoType ( fch );
           break;
      case monoalt :
      case mononum :
           returnCh = UnicodeToMonoTypeAlt ( fch );
           break;
#endif /* SUPPORT_MONOTYPE || SUPPORT_ALL */


#if SUPPORT_NCI || SUPPORT_ALL
      case nci :
           returnCh = UnicodeToNCI ( fch );
           break;
#endif /* SUPPORT_NCI || SUPPORT_ALL */


#if SUPPORT_NCIC || SUPPORT_ALL
      case ncic    :
      case ncic_et :
           returnCh = UnicodeToNCIC ( fch );
           break;
#endif /* SUPPORT_NCIC || SUPPORT_ALL */


#if SUPPORT_OMNITECH || SUPPORT_ALL
      case omnitech :
           returnCh = UnicodeToOmniTech ( fch );
           break;
#endif /* SUPPORT_OMNITECH || SUPPORT_ALL */


#if SUPPORT_PHONETICSYS || SUPPORT_ALL
      case geztype    :
           returnCh = UnicodeToGeezType ( fch );
           break;
      case geztypenet :
           returnCh = UnicodeToGeezTypeNet ( fch );
           break;
#endif /* SUPPORT_PHONETICSYS || SUPPORT_ALL */


#if SUPPORT_POWERGEEZ || SUPPORT_ALL
      case powergez    :
      case powergeznum :
           returnCh = UnicodeToPowerGeez ( fch );
           break;
#endif /* SUPPORT_POWERGEEZ || SUPPORT_ALL */


#if SUPPORT_QUBEE || SUPPORT_ALL
      case qubee :
           returnCh = UnicodeToQubee ( fch );
           break;
#endif /* SUPPORT_QUBEE || SUPPORT_ALL */


#if SUPPORT_SAMAWERFA || SUPPORT_ALL
      case sam98:
           returnCh = UnicodeToSamawerfa98 ( fch );
           break;
      case samwp:
           returnCh = UnicodeToSamawerfaWP ( fch );
           break;
#endif /* SUPPORT_SAMAWERFA || SUPPORT_ALL */


#if SUPPORT_SERA || SUPPORT_ALL
      case sera :
           returnCh = UnicodeToSERA ( fch );
           break;
#endif /* SUPPORT_SERA || SUPPORT_ALL */


#if SUPPORT_TEX || SUPPORT_ALL
      case muletex :
           returnCh = UnicodeToTeX ( fch );
           break;
#endif  /* SUPPORT_TEX || SUPPORT_ALL */


#if SUPPORT_TFANUS || SUPPORT_ALL
      case ethiosoft :
           returnCh = UnicodeToEthioSoft ( fch );
           break;
      case gezbausi  :
      case tfanus    :
      case tfanusnew :
           returnCh = UnicodeToTFanus ( fch );
           break;
#endif /* SUPPORT_TFANUS || SUPPORT_ALL */


#if SUPPORT_VISUALGEEZ || SUPPORT_ALL
      case visualgez:
           returnCh = UnicodeToVisualGeez ( fch );
           break;

      case visualgez2k:
           returnCh = UnicodeToVisualGeez2000 ( fch );
           break;

#endif /* SUPPORT_VISUALGEEZ || SUPPORT_ALL */


#if SUPPORT_VISUALGEEZ || SUPPORT_ALL
      case wazema1:
      case wazema2:
           returnCh = UnicodeToWazema ( fch );
           break;
#endif /* SUPPORT_VISUALGEEZ || SUPPORT_ALL */


      case unicode:
           break;


      default     : 
           if ( mylflags->csOut < ETHCHARSETS )
             fprintf (stderr, "Failing Out = %s\n", CharacterSetNames[mylflags->csOut]);
           else
             fprintf (stderr, "Failing Unknown Character System Value: '%i'\n", mylflags->csOut);
           break;

    }




  if ( (mylflags->tvOut != notv) )
    {
      /* This only works because uname is Ethiopic only right now... */
      i = ( returnCh ) ? strlen(returnCh) : ( mylflags->tvOut == uname ) ? 6 : 1 ;
      // newCh = (returnCh) ? returnCh : (unsigned char *) calloc ( ((i * 8) + 1), sizeof (unsigned char) );
      newCh = (unsigned char *) calloc ( ((i * 8) + 1), sizeof (unsigned char) );

      i = j = 0;
      while ( (fch = (returnCh) ? returnCh[i++] : fch) )
        {
          switch ( mylflags->tvOut )
            {
              case escd   :
              case decimal:
                   if ( 0x7f < fch )
                     {
                       if ( mylflags->tvOut == escd )
                         sprintf ( &newCh[j], "&#%i;", fch );
                       else
                         sprintf ( &newCh[j], "d%i", fch );
                       j = strlen ( newCh );
                     }
                   else
                     newCh[j++] = fch;
                   break;
#if SUPPORT_JAVA || SUPPORT_ALL
              case xml   :
                   if ( 0x7f < fch )
                     {
                   if ( mylflags->options & uppercase )
                     strcat ( newCh, UnicodeToJAVA ( fch ) );
                   else
                     strcat ( newCh, UnicodeTojava ( fch ) );

		   newCh[0] = '<';
		   newCh[1] = 'U';
		   strcat ( newCh, ">" );
                   while ( newCh[++j] );  /* increment j up to EOS */
                     }
                   else
                     newCh[j++] = fch;

                   break;

              case esch  : newCh[j++] = '&';
              case java  :
              case clike :
              case uplus :
              case zerox :
                   if ( mylflags->options & uppercase )
                     strcat ( newCh, UnicodeToJAVA ( fch ) );
                   else
                     strcat ( newCh, UnicodeTojava ( fch ) );

                   if ( 0x7f < fch )
                     {
                       if ( mylflags->tvOut == esch )
                         {
                           newCh[j] = '#';
                           newCh[j+1] = 'x';
                           strcat ( newCh, ";" );
                           // sprintf ( &newCh[j+2], "x%s;", &newCh[j+2] );
                         }
                       else if ( mylflags->tvOut == clike || mylflags->tvOut == zerox )
                         {
                           newCh[j+1] = 'x';
                           if ( mylflags->tvOut == zerox )
                             newCh[j] = '0';
                         }
                       else if ( mylflags->tvOut == uplus )
                         {
                           newCh[j]   = 'U';
                           newCh[j+1] = '+';
                         }
                       while ( newCh[++j] );  /* increment j up to EOS */
                     }
                   else
                     j++;

                   break;
#endif /* SUPPORT_JAVA || SUPPORT_ALL */


              case uname :
                   strcat ( newCh, UnicodeToName ( fch ) );
                   if ( !(mylflags->options & uppercase) )
                     while ( newCh[j] )
                       newCh[j] = tolower ( newCh[j++] );
                   break;


#if SUPPORT_UTF7 || SUPPORT_ALL
              case utf7 :
                   strcat ( newCh, UnicodeToUTF7 ( fch ) );
                   break;
#endif /* SUPPORT_UTF7 || SUPPORT_ALL */


#if SUPPORT_UTF8 || SUPPORT_ALL
              case utf8 :
                   strcat ( newCh, UnicodeToUTF8 ( fch ) );
                   break;
#endif /* SUPPORT_UTF8 || SUPPORT_ALL */


#if SUPPORT_UTF16 || SUPPORT_ALL
              case utf16:
                   strcat ( newCh, UnicodeToUTF16 ( fch ) );
                   break;
#endif /* SUPPORT_UTF16 || SUPPORT_ALL */
              default   :
                   break;
            }
          if ( !returnCh )  /* need this to exit the while loop */
            fch = 0;

        }

      if ( returnCh ) 
        free ( returnCh );
      returnCh = newCh;
    }


  if ( (mylflags->options & debug) && isethiopic(uch) )
    {
      newCh = (unsigned char *) malloc ( ( ( strlen (returnCh) + 3 ) * sizeof (unsigned char) ) );
      sprintf ( newCh, "(%s)", returnCh );

      free ( returnCh );
      returnCh = newCh;
    }




  return ( returnCh );

}


 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  get_setid (fch, mylflags)
//
//  Return address of next token from passed stream of SERA text. Either
//  the file or text string pointer must be NULL.
//  The address of the returned token is specified by the character coding
//  system passed in mylflags->out.
//
//  get_setid is intended to be of very low level, such that users would not
//  be using it.
//
//  tstring  -is a character pointer to SERA text
//  fp       -is a file pointer to SERA text
//  mylflags -is a LEth Flag structure which MUST contain a valid input and
//            output type.
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


int 
get_setid (fch, mylflags)
  FCHAR fch;
  LibEthFlags* mylflags;
{

int setid = NIL;


  mylflags = checkLibEthFlags ( mylflags );

  switch (mylflags->csOut)
    {
#if SUPPORT_ACIS || SUPPORT_ALL 
      case acis :
           setid = ACIS_get_setid ( fch );
           break;
#endif /* SUPPORT_ACIS || SUPPORT_ALL */


#if SUPPORT_ACUWORK || SUPPORT_ALL 
      case acuwork :
           setid = Acuwork_get_setid ( fch );
           break;
#endif /* SUPPORT_ACUWORK || SUPPORT_ALL */


#if SUPPORT_ADDISWORD || SUPPORT_ALL 
      case addisword1 : 
      case addisword2 : 
           setid = AddisWord_get_setid ( fch );
           break;
#endif  /* SUPPORT_ADDISWORD || SUPPORT_ALL */


#if SUPPORT_ALPAS || SUPPORT_ALL 
      case alpas :
           setid = Alpas_get_setid ( fch );
           break;
#endif /* SUPPORT_ALPAS || SUPPORT_ALL */


#if SUPPORT_BRAILLE || SUPPORT_ALL
/*
      case braille:
           setid = Braille_get_setid ( fch );
           break;
*/
#endif /* SUPPORT_BRAILLE || SUPPORT_ALL */


#if SUPPORT_BRANA || SUPPORT_ALL
      case branai :
      case branaii:
           setid = Brana_get_setid ( fch );
           break;
#endif /* SUPPORT_BRANA || SUPPORT_ALL */


#if SUPPORT_CBHALE || SUPPORT_ALL
      case cbhalea:
      case cbhaleb:
           setid = CBHale_get_setid ( fch );
           break;
#endif /* SUPPORT_CBHALE || SUPPORT_ALL */


#if SUPPORT_DEJENE || SUPPORT_ALL 
      case dejene1: 
      case dejene2: 
           setid = Dejene_get_setid ( fch );
           break;
#endif  /* SUPPORT_DEJENE || SUPPORT_ALL */


#if SUPPORT_ECOLING || SUPPORT_ALL
/*    case ecoling :
           setid = EcoLing_get_setid( fch );
           break;
*/
#endif /* SUPPORT_ECOLING || SUPPORT_ALL */


#if SUPPORT_ENHPFR || SUPPORT_ALL
      case enhpfr :
           setid = ENHPFR_get_setid( fch );
           break;
#endif /* SUPPORT_ENHPFR || SUPPORT_ALL */


#if SUPPORT_ETHCITA
      case ethcitau  : 
           setid = EthCITAUni_get_setid ( fch );
           break;
      case ethcitap  : 
      case ethcitas  : 
           setid = EthCITABi_get_setid ( fch );
           break;
#endif  /* SUPPORT_ETHCITA || SUPPORT_ALL */


#if SUPPORT_ETHIOPIC || SUPPORT_ALL 
      case ethiopic1 :
      case ethiopic2 :
           setid = Ethiopic_get_setid ( fch );
           break;
#endif  /* SUPPORT_ETHIOPIC || SUPPORT_ALL */


#if SUPPORT_ETHIOSYS || SUPPORT_ALL 
      case ethiosys  : 
      case ethiosysx : 
           setid = EthioSys_get_setid ( fch );
           break;
#endif  /* SUPPORT_ETHIOSYS || SUPPORT_ALL */


#if SUPPORT_ETHIOWALIA || SUPPORT_ALL 
      case ethiowalia  : 
           setid = EthioWalia_get_setid ( fch );
           break;
#endif  /* SUPPORT_ETHIOWALIA || SUPPORT_ALL */


#if SUPPORT_FIDELEXTRA || SUPPORT_ALL
      case fidelxtr1 :
      case fidelxtr2 :
           setid = FidelExtra_get_setid ( fch );
           break;
#endif /* SUPPORT_FIDELEXTRA || SUPPORT_ALL */


#if SUPPORT_GEEZEDIT || SUPPORT_ALL 
      case gezedit :
           setid = GeezEdit_get_setid ( fch );
           break;
#endif  /* SUPPORT_GEEZEDIT || SUPPORT_ALL */


#if SUPPORT_GEEZFONT || SUPPORT_ALL 
      case gezfont :
           setid = GeezFont_get_setid ( fch );
           break;
#endif /* SUPPORT_GEEZFONT || SUPPORT_ALL */


#if SUPPORT_GEEZFREE || SUPPORT_ALL
      case gezfree1  : 
      case gezfree2 : 
           setid = GeezFree_get_setid ( fch );
           break;
#endif /* SUPPORT_GEEZFREE || SUPPORT_ALL */


#if SUPPORT_GEEZII || SUPPORT_ALL
      case gezi  :
      case gezii :
           setid = GeezII_get_setid ( fch );
           break;
#endif /* SUPPORT_GEEZII || SUPPORT_ALL */


#if SUPPORT_GEEZIGNA || SUPPORT_ALL 
      case gezigna :
           setid = Geezigna_get_setid ( fch );
           break;
#endif /* SUPPORT_GEEZIGNA || SUPPORT_ALL */


#if SUPPORT_GEEZNEWAB || SUPPORT_ALL
      case geznewa :
      case geznewb :
           setid = GeezNewAB_get_setid ( fch );
           break;
#endif /* SUPPORT_GEEZNEWAB || SUPPORT_ALL */


#if SUPPORT_LASERAMHARIC || SUPPORT_ALL
/*    case laser :
           setid = LaserAmharic_get_setid ( fch );
           break;
*/
#endif /* SUPPORT_LASERAMHARIC || SUPPORT_ALL */


#if SUPPORT_MONOTYPE || SUPPORT_ALL
      case monotype1 :
      case monotype2 :
      case monotype3 :
           setid = MonoType_get_setid ( fch );
           break;
      case monoalt :
      case mononum :
           setid = MonoTypeAlt_get_setid ( fch );
           break;
#endif /* SUPPORT_MONOTYPE || SUPPORT_ALL */


#if SUPPORT_NCI || SUPPORT_ALL
      case nci :
           setid = NCI_get_setid ( fch );
           break;
#endif /* SUPPORT_NCI || SUPPORT_ALL */


#if SUPPORT_NCIC || SUPPORT_ALL
      case ncic   :
           setid = NCIC_get_setid ( fch );
           break;
      case ncic_et:
           setid = NCIC_ET_get_setid ( fch );
           break;
#endif /* SUPPORT_NCIC || SUPPORT_ALL */


#if SUPPORT_OMNITECH || SUPPORT_ALL
      case omnitech :
           setid = OmniTech_get_setid ( fch );
           break;
#endif /* SUPPORT_OMNITECH || SUPPORT_ALL */


#if SUPPORT_PHONETICSYS || SUPPORT_ALL
      case geztype    :
           setid = GeezType_get_setid ( fch );
           break;
      case geztypenet :
           setid = GeezType_get_setid ( fch );
           break;
#endif /* SUPPORT_PHONETICSYS || SUPPORT_ALL */


#if SUPPORT_POWERGEEZ || SUPPORT_ALL
      case powergez    :
      case powergeznum :
           setid = PowerGeez_get_setid ( fch );
           break;
#endif /* SUPPORT_POWERGEEZ || SUPPORT_ALL */


#if SUPPORT_SAMAWERFA || SUPPORT_ALL
      case sam98:
      case samwp:
           setid = Samawerfa_get_setid ( fch );
           break;
#endif /* SUPPORT_SAMAWERFA || SUPPORT_ALL */


#if SUPPORT_TFANUS || SUPPORT_ALL
      case ethiosoft:
      case gezbausi:
      case tfanus:
      case tfanusnew:
           setid = TFanus_get_setid ( fch );
           break;
#endif /* SUPPORT_TFANUS || SUPPORT_ALL */


#if SUPPORT_VISUALGEEZ || SUPPORT_ALL
      case visualgez:
           setid = VisualGeez_get_setid ( fch );
           break;
      case visualgez2k:
           setid = VisualGeez2000_get_setid ( fch );
           break;
#endif /* SUPPORT_VISUALGEEZ || SUPPORT_ALL */


#if SUPPORT_WAZEMA || SUPPORT_ALL
      case wazema1:
      case wazema2:
           setid = Wazema_get_setid ( fch );
           break;
#endif /* SUPPORT_WAZEMA || SUPPORT_ALL */

       default:  break;
  }


  return ( setid );

}


 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  isGoodANSI (fch, mylflags)
//
//  Return address of next token from passed stream of SERA text. Either
//  the file or text string pointer must be NULL.
//  The address of the returned token is specified by the character coding
//  system passed in mylflags->out.
//
//  get_setid is intended to be of very low level, such that users would not
//  be using it.
//
//  fch      -is a character pointer to SERA text
//  mylflags -is a LEth Flag structure which MUST contain a valid input and
//            output type.
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


unsigned char 
isGoodANSI (fch, mylflags)
  FCHAR fch;
  LibEthFlags* mylflags;
{

  mylflags = checkLibEthFlags ( mylflags );

  switch (mylflags->csOut)
    {
#if SUPPORT_ACIS || SUPPORT_ALL 
      case acis :
           return ( ACIS_isGoodANSI ( fch ) );
           break;
#endif /* SUPPORT_ACIS || SUPPORT_ALL */


#if SUPPORT_ACUWORK || SUPPORT_ALL 
      case acuwork :
           return ( Acuwork_isGoodANSI ( fch ) );
           break;
#endif /* SUPPORT_ACUWORK || SUPPORT_ALL */


#if SUPPORT_ADDISWORD || SUPPORT_ALL 
      case addisword1 : 
           return ( AddisWord_isGoodANSI ( fch ) );
           break;
      case addisword2 : 
           break;
#endif  /* SUPPORT_ADDISWORD || SUPPORT_ALL */


#if SUPPORT_ALPAS || SUPPORT_ALL 
      case alpas :
           return ( Alpas_isGoodANSI ( fch ) );
           break;
#endif /* SUPPORT_ALPAS || SUPPORT_ALL */


#if SUPPORT_BRAILLE || SUPPORT_ALL
/*
      case braille :
           return ( Braille_isGoodANSI ( fch ) );
           break;
*/
#endif /* SUPPORT_BRAILLE || SUPPORT_ALL */


#if SUPPORT_BRANA || SUPPORT_ALL
      case branai :
           return ( BranaI_isGoodANSI ( fch ) );
           break;
      case branaii:
           break;
#endif /* SUPPORT_BRANA || SUPPORT_ALL */


#if SUPPORT_CBHALE || SUPPORT_ALL
      case cbhalea:
           return ( CBHaleA_isGoodANSI ( fch ) );
           break;
      case cbhaleb:
           break;
#endif /* SUPPORT_CBHALE || SUPPORT_ALL */


#if SUPPORT_DEJENE || SUPPORT_ALL 
      case dejene1: 
           return ( Dejene_isGoodANSI ( fch ) );
           break;
      case dejene2: 
           break;
#endif  /* SUPPORT_DEJENE || SUPPORT_ALL */


#if SUPPORT_ECOLING || SUPPORT_ALL
/*    case ecoling :
           return ( EcoLing_isGoodANSI ( fch ) );
           break;
*/
#endif /* SUPPORT_ECOLING || SUPPORT_ALL */


#if SUPPORT_ENHPFR || SUPPORT_ALL
      case enhpfr  : 
           return ( ENHPFR_isGoodANSI (fch) );
           break;
#endif /* SUPPORT_ENHPFR || SUPPORT_ALL */


#if SUPPORT_ETHCITA
      case ethcitau  : 
           setid = EthCITAUni_isGoodANSI ( fch );
           break;
      case ethcitap  : 
      case ethcitas  : 
           setid = EthCITABi_isGoodANSI ( fch );
           break;
#endif  /* SUPPORT_ETHCITA || SUPPORT_ALL */


#if SUPPORT_ETHIOPIC || SUPPORT_ALL 
      case ethiopic1 : 
      case ethiopic2 : 
           return ( Ethiopic_isGoodANSI ( fch ) );
           break;
#endif  /* SUPPORT_ETHIOPIC || SUPPORT_ALL */


#if SUPPORT_ETHIOSYS || SUPPORT_ALL 
      case ethiosys  : 
           return ( EthioSys_isGoodANSI ( fch ) );
           break;
      case ethiosysx : 
           break;
#endif  /* SUPPORT_ETHIOSYS || SUPPORT_ALL */


#if SUPPORT_ETHIOWALIA || SUPPORT_ALL 
      case ethiowalia  : 
           return ( EthioWalia_isGoodANSI ( fch ) );
           break;
#endif  /* SUPPORT_ETHIOWALIA || SUPPORT_ALL */


#if SUPPORT_FIDELEXTRA || SUPPORT_ALL
      case fidelxtr1 :
      case fidelxtr2 :
           break;
#endif /* SUPPORT_FIDELEXTRA || SUPPORT_ALL */


#if SUPPORT_GEEZEDIT || SUPPORT_ALL 
      case gezedit :
           return ( GeezEdit_isGoodANSI ( fch ) );
           break;
#endif  /* SUPPORT_GEEZEDIT || SUPPORT_ALL */


#if SUPPORT_GEEZFONT || SUPPORT_ALL 
      case gezfont :
           return ( GeezFont_isGoodANSI ( fch ) );
           break;
#endif /* SUPPORT_GEEZFONT || SUPPORT_ALL */


#if SUPPORT_GEEZFREE || SUPPORT_ALL
      case gezfree1  : 
           return ( EthioSys_isGoodANSI ( fch ) );
           break;
      case gezfree2 : 
           break;
#endif /* SUPPORT_GEEZFREE || SUPPORT_ALL */


#if SUPPORT_GEEZII || SUPPORT_ALL
      case gezi  :
           return ( GeezI_isGoodANSI ( fch ) );
      case gezii :
           break;
#endif /* SUPPORT_GEEZII || SUPPORT_ALL */


#if SUPPORT_GEEZIGNA || SUPPORT_ALL 
      case gezigna :
           break;
#endif /* SUPPORT_GEEZIGNA || SUPPORT_ALL */


#if SUPPORT_GEEZNEWAB || SUPPORT_ALL
      case geznewa :
           return ( GeezNewA_isGoodANSI ( fch ) );
           break;
      case geznewb :
           break;
#endif /* SUPPORT_GEEZNEWAB || SUPPORT_ALL */


#if SUPPORT_LASERAMHARIC || SUPPORT_ALL
/*    case laser :
           return ( LaserAmharic_isGoodANSI ( fch ) );
           break;
*/
#endif /* SUPPORT_LASERAMHARIC || SUPPORT_ALL */


#if SUPPORT_MONOTYPE || SUPPORT_ALL
      case monotype1 :
      case monotype2 :
      case monotype3 :
           break;
      case monoalt :
      case mononum :
           break;
#endif /* SUPPORT_MONOTYPE || SUPPORT_ALL */


#if SUPPORT_NCI || SUPPORT_ALL
      case nci :
           return ( NCI_isGoodANSI ( fch ) );
           break;
#endif /* SUPPORT_NCI || SUPPORT_ALL */


#if SUPPORT_NCIC || SUPPORT_ALL
      case ncic   :
           return ( NCIC_isGoodANSI ( fch ) );
           break;
      case ncic_et:
           return ( NCIC_ET_isGoodANSI ( fch ) );
           break;
#endif /* SUPPORT_NCIC || SUPPORT_ALL */


#if SUPPORT_OMNITECH || SUPPORT_ALL
      case omnitech :
           return ( NCI_isGoodANSI ( fch ) );
           break;
#endif /* SUPPORT_OMNITECH || SUPPORT_ALL */


#if SUPPORT_PHONETICSYS || SUPPORT_ALL
      case geztype :
           return ( GeezType_isGoodANSI ( fch ) );
           break;
      case geztypenet :
           return ( GeezTypeNet_isGoodANSI ( fch ) );
           break;
#endif /* SUPPORT_PHONETICSYS || SUPPORT_ALL */


#if SUPPORT_POWERGEEZ || SUPPORT_ALL
      case powergez    :
           return ( PowerGeez_isGoodANSI ( fch ) );
           break;
      case powergeznum :
           return ( false );
           break;
#endif /* SUPPORT_POWERGEEZ || SUPPORT_ALL */


#if SUPPORT_SAMAWERFA || SUPPORT_ALL
      case sam98 :
      case samwp :
           return ( Samawerfa_isGoodANSI ( fch ) );
           break;
#endif /* SUPPORT_SAMAWERFA || SUPPORT_ALL */


#if SUPPORT_TFANUS || SUPPORT_ALL
      case ethiosoft:
           return ( EthioSoft_isGoodANSI ( fch ) );
           break;
      case gezbausi:
           return ( GeezBausi_isGoodANSI ( fch ) );
           break;
      case tfanus:
           return ( TFanus_isGoodANSI ( fch ) );
           break;
      case tfanusnew:
           return ( TFanusNew_isGoodANSI ( fch ) );
           break;
#endif /* SUPPORT_TFANUS || SUPPORT_ALL */


#if SUPPORT_VISUALGEEZ || SUPPORT_ALL
      case visualgez:
           return ( VisualGeez_isGoodANSI ( fch ) );
           break;
      case visualgez2k:
           return ( VisualGeez2000_isGoodANSI ( fch ) );
           break;
#endif /* SUPPORT_VISUALGEEZ || SUPPORT_ALL */


#if SUPPORT_WAZEMA || SUPPORT_ALL
      case wazema1:
           return ( WazemaA1_isGoodANSI ( fch ) );
           break;
      case wazema2:
           return ( WazemaA2_isGoodANSI ( fch ) );
           break;
#endif /* SUPPORT_WAZEMA || SUPPORT_ALL */


      default:  
           return (false);
           break;
    }

  return (false);

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  get_netInfo (setid, setName, mylflags)
//
//  Return address of next token from passed stream of SERA text. Either
//  the file or text string pointer must be NULL.
//  The address of the returned token is specified by the character coding
//  system passed in mylflags->out.
//
//  get_setid is intended to be of very low level, such that users would not
//  be using it.
//
//  tstring  -is a character pointer to SERA text
//  fp       -is a file pointer to SERA text
//  mylflags -is a LEth Flag structure which MUST contain a valid input and
//            output type.
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


char*
get_netInfo (vendor, INFO)
  enum CharacterSet vendor;
  char INFO;
{

char* netInfo=NULL;


  switch (vendor)
    {
#if SUPPORT_ACIS || SUPPORT_ALL 
      case acis :
           netInfo = ACIS_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_ACIS || SUPPORT_ALL */


#if SUPPORT_ACUWORK || SUPPORT_ALL 
      case acuwork :
           netInfo = Acuwork_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_ACUWORK || SUPPORT_ALL */


#if SUPPORT_ADDISWORD || SUPPORT_ALL 
      case addisword1 : 
      case addisword2 : 
           netInfo = AddisWord_get_netInfo ( INFO );
           break;
#endif  /* SUPPORT_ADDISWORD || SUPPORT_ALL */


#if SUPPORT_ALPAS || SUPPORT_ALL 
      case alpas :
           netInfo = Alpas_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_ALPAS || SUPPORT_ALL */


#if SUPPORT_BRAILLE || SUPPORT_ALL
      case braille:
           netInfo = Braille_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_BRAILLE || SUPPORT_ALL */


#if SUPPORT_BRANA || SUPPORT_ALL
      case branai :
      case branaii:
           netInfo = Brana_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_BRANA || SUPPORT_ALL */


#if SUPPORT_CBHALE || SUPPORT_ALL
      case cbhalea:
      case cbhaleb:
           netInfo = CBHale_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_CBHALE || SUPPORT_ALL */


#if SUPPORT_DEJENE || SUPPORT_ALL 
      case dejene1: 
      case dejene2: 
           netInfo = Dejene_get_netInfo ( INFO );
           break;
#endif  /* SUPPORT_DEJENE || SUPPORT_ALL */


#if SUPPORT_ECOLING || SUPPORT_ALL
/*    case ecoling :
           netInfo = EcoLing_get_netInfo ();
           break;
*/
#endif /* SUPPORT_ECOLING || SUPPORT_ALL */


#if SUPPORT_ED || SUPPORT_ALL
      case dehai :
           netInfo = Dehai_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_ED || SUPPORT_ALL */


#if SUPPORT_ED || SUPPORT_ALL
      case ed :
           netInfo = Ed_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_ED || SUPPORT_ALL */


#if SUPPORT_ENHPFR || SUPPORT_ALL
      case enhpfr :
           netInfo = ENHPFR_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_ENHPFR || SUPPORT_ALL */


#if SUPPORT_ETHCITA
      case ethcitau  : 
      case ethcitap  : 
      case ethcitas  : 
           setid = EthCITA_get_netInfo ( INFO );
           break;
#endif  /* SUPPORT_ETHCITA || SUPPORT_ALL */


#if SUPPORT_ETHIOP || SUPPORT_ALL
      case ethiop :
           netInfo = Ethiop_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_ETHIOP || SUPPORT_ALL */


#if SUPPORT_ETHIOPIC || SUPPORT_ALL 
      case ethiopic1 :
      case ethiopic2 :
           netInfo = Ethiopic_get_netInfo ( INFO );
           break;
#endif  /* SUPPORT_ETHIOPIC || SUPPORT_ALL */


#if SUPPORT_ETHIOSYS || SUPPORT_ALL 
      case ethiosys  : 
      case ethiosysx : 
           netInfo = EthioSys_get_netInfo ( INFO );
           break;
#endif  /* SUPPORT_ETHIOSYS || SUPPORT_ALL */


#if SUPPORT_ETHIOWALIA || SUPPORT_ALL 
      case ethiowalia  : 
           netInfo = EthioWalia_get_netInfo ( INFO );
           break;
#endif  /* SUPPORT_ETHIOWALIA || SUPPORT_ALL */


#if SUPPORT_FIDELEXTRA || SUPPORT_ALL
      case fidelxtr1 :
      case fidelxtr2 :
           netInfo = FidelExtra_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_FIDELEXTRA || SUPPORT_ALL */


#if SUPPORT_ABSHA || SUPPORT_ALL 
      case gezedit :
           netInfo = Absha_get_netInfo ( INFO );
           break;
#endif  /* SUPPORT_ABSHA || SUPPORT_ALL */


#if SUPPORT_GEEZFONT || SUPPORT_ALL 
      case gezfont :
           netInfo = GeezFont_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_GEEZFONT || SUPPORT_ALL */


#if SUPPORT_GEEZFREE || SUPPORT_ALL
      case gezfree1  : 
      case gezfree2 : 
           netInfo = GeezFree_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_GEEZFREE || SUPPORT_ALL */


#if SUPPORT_GEEZII || SUPPORT_ALL
      case gezi  :
      case gezii :
      case gezigna :
      case geznewa :
      case geznewb :
           netInfo = Feedel_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_GEEZNEWAB || SUPPORT_ALL */


#if SUPPORT_IES
      case ies :
           netInfo = IES_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_IES || SUPPORT_ALL */


#if SUPPORT_ISO || SUPPORT_ALL
      case iso :
           netInfo = ISO_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_ISO || SUPPORT_ALL */


#if SUPPORT_JAVA || SUPPORT_ALL
/*    case java :
           netInfo = Java_get_netInfo ( INFO );
           break; */
#endif /* SUPPORT_JAVA || SUPPORT_ALL */


#if SUPPORT_JIS || SUPPORT_ALL
      case jis :
           netInfo = JIS_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_JIS || SUPPORT_ALL */


#if SUPPORT_JUNET || SUPPORT_ALL
      case junet :
           netInfo = JUNET_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_JUNET || SUPPORT_ALL */


#if SUPPORT_LASERAMHARIC || SUPPORT_ALL
/*    case laser :
           netInfo = LaserAmharic_get_netInfo ( INFO );
           break;
*/
#endif /* SUPPORT_LASERAMHARIC || SUPPORT_ALL */


#if SUPPORT_MAINZ || SUPPORT_ALL
      case mainz :
           netInfo = Mainz_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_MAINZ || SUPPORT_ALL */


#if SUPPORT_MONOTYPE || SUPPORT_ALL
      case monotype1 :
      case monotype2 :
      case monotype3 :
      case monoalt :
      case mononum :
           netInfo = MonoType_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_MONOTYPE || SUPPORT_ALL */


#if SUPPORT_NCI || SUPPORT_ALL
      case nci :
           netInfo = NCI_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_NCI || SUPPORT_ALL */


#if SUPPORT_NCIC || SUPPORT_ALL
      case ncic    :
      case ncic_et :
           netInfo = NCIC_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_NCIC || SUPPORT_ALL */


#if SUPPORT_OMNITECH || SUPPORT_ALL
      case omnitech :
           netInfo = OmniTech_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_OMNITECH || SUPPORT_ALL */


#if SUPPORT_PHONETICSYS || SUPPORT_ALL
      case geztype    :
      case geztypenet :
           netInfo = GeezType_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_PHONETICSYS || SUPPORT_ALL */


#if SUPPORT_POWERGEEZ || SUPPORT_ALL
      case powergez    :
      case powergeznum :
           netInfo = PowerGeez_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_POWERGEEZ || SUPPORT_ALL */


#if SUPPORT_SAMAWERFA || SUPPORT_ALL
      case sam98 :
      case samwp :
           netInfo = Samawerfa_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_SAMAWERFA || SUPPORT_ALL */


#if SUPPORT_QUBEE || SUPPORT_ALL
      case qubee :
           netInfo = Qubee_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_QUBEE || SUPPORT_ALL */


#if SUPPORT_SERA || SUPPORT_ALL
      case sera  :
           netInfo = SERA_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_SERA || SUPPORT_ALL */


#if SUPPORT_TEX || SUPPORT_ALL
      case muletex :
           netInfo = TeX_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_TEX || SUPPORT_ALL */


#if SUPPORT_TFANUS || SUPPORT_ALL
      case ethiosoft :
           netInfo = EthioSoft_get_netInfo ( INFO );
           break;
      case gezbausi  :
      case tfanus    :
      case tfanusnew :
           netInfo = TFanus_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_TFANUS || SUPPORT_ALL */


#if SUPPORT_UTF7 || SUPPORT_UTF8 || SUPPORT_UTF16 || SUPPORT_ALL
      case unicode:
           netInfo = Unicode_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_UTF7 || SUPPORT_UTF8 || SUPPORT_UTF16 || SUPPORT_ALL */


#if SUPPORT_VISUALGEEZ || SUPPORT_ALL
      case visualgez:
      case visualgez2k:
           netInfo = VisualGeez_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_VISUALGEEZ || SUPPORT_ALL */


#if SUPPORT_WAZEMA || SUPPORT_ALL
      case wazema1:
      case wazema2:
           netInfo = Wazema_get_netInfo ( INFO );
           break;
#endif /* SUPPORT_WAZEMA || SUPPORT_ALL */

       default:  break;
  }


  return (netInfo);

}



 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  get_setName (setid, setName, mylflags)
//
//  Return address of next token from passed stream of SERA text. Either
//  the file or text string pointer must be NULL.
//  The address of the returned token is specified by the character coding
//  system passed in mylflags->out.
//
//  get_setid is intended to be of very low level, such that users would not
//  be using it.
//
//  tstring  -is a character pointer to SERA text
//  fp       -is a file pointer to SERA text
//  mylflags -is a LEth Flag structure which MUST contain a valid input and
//            output type.
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


int
get_setName (setid, setName, system, fontFace)
  int setid;
  unsigned char** setName;
  enum CharacterSet system;
  int fontFace;
{

int nextSetid = 0;


  switch ( system )
    {
#if SUPPORT_ACIS || SUPPORT_ALL 
      case acis :
           nextSetid = ACIS_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_ACIS || SUPPORT_ALL */


#if SUPPORT_ACUWORK || SUPPORT_ALL 
      case acuwork :
           nextSetid = Acuwork_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_ACUWORK || SUPPORT_ALL */


#if SUPPORT_ADDISWORD || SUPPORT_ALL 
      case addisword1 : 
      case addisword2 : 
           nextSetid = AddisWord_get_setName (setid, fontFace, setName);
           break;
#endif  /* SUPPORT_ADDISWORD || SUPPORT_ALL */


#if SUPPORT_ALPAS || SUPPORT_ALL 
      case alpas :
           nextSetid = Alpas_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_ALPAS || SUPPORT_ALL */


#if SUPPORT_BRAILLE || SUPPORT_ALL
/*
      case braille:
           nextSetid = Braille_get_setName (setid, fontFace, setName);
           break;
*/
#endif /* SUPPORT_BRAILLE || SUPPORT_ALL */


#if SUPPORT_BRANA || SUPPORT_ALL
      case branai :
      case branaii:
           nextSetid = Brana_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_BRANA || SUPPORT_ALL */


#if SUPPORT_CBHALE || SUPPORT_ALL
      case cbhalea:
      case cbhaleb:
           nextSetid = CBHale_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_CBHALE || SUPPORT_ALL */


#if SUPPORT_DEJENE || SUPPORT_ALL 
      case dejene1: 
      case dejene2: 
           nextSetid = Dejene_get_setName (setid, fontFace, setName);
           break;
#endif  /* SUPPORT_DEJENE || SUPPORT_ALL */


#if SUPPORT_ECOLING || SUPPORT_ALL
/*    case ecoling :
           nextSetid = EcoLingUnicode ();
           break;
*/
#endif /* SUPPORT_ECOLING || SUPPORT_ALL */


#if SUPPORT_ENHPFR || SUPPORT_ALL 
      case enhpfr  : 
           nextSetid = ENHPFR_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_ENHPFR || SUPPORT_ALL */


#if SUPPORT_ETHCITA
      case ethcitau  : 
           setid = EthCITAUni_get_setName ( fch );
           break;
      case ethcitap  : 
           setid = EthCITABiP_get_setName ( fch );
      case ethcitas  : 
           setid = EthCITABiS_get_setName ( fch );
           break;
#endif  /* SUPPORT_ETHCITA || SUPPORT_ALL */


#if SUPPORT_ETHIOPIC || SUPPORT_ALL 
      case ethiopic1 :
      case ethiopic2 :
           nextSetid = Ethiopic_get_setName (setid, fontFace, setName);
           break;
#endif  /* SUPPORT_ETHIOPIC || SUPPORT_ALL */


#if SUPPORT_ETHIOSYS || SUPPORT_ALL 
      case ethiosys  : 
      case ethiosysx : 
           nextSetid = EthioSys_get_setName (setid, fontFace, setName);
           break;
#endif  /* SUPPORT_ETHIOSYS || SUPPORT_ALL */


#if SUPPORT_ETHIOWALIA || SUPPORT_ALL 
      case ethiowalia  : 
           nextSetid = EthioWalia_get_setName (setid, fontFace, setName);
           break;
#endif  /* SUPPORT_ETHIOWALIA || SUPPORT_ALL */


#if SUPPORT_FIDELEXTRA || SUPPORT_ALL
      case fidelxtr1 :
      case fidelxtr2 :
           nextSetid = FidelExtra_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_FIDELEXTRA || SUPPORT_ALL */


#if SUPPORT_GEEZEDIT || SUPPORT_ALL 
      case gezedit :
           nextSetid = GeezEdit_get_setName (setid, fontFace, setName);
           break;
#endif  /* SUPPORT_GEEZEDIT || SUPPORT_ALL */


#if SUPPORT_GEEZFONT || SUPPORT_ALL 
      case gezfont :
           nextSetid = GeezFont_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_GEEZFONT || SUPPORT_ALL */


#if SUPPORT_GEEZFREE || SUPPORT_ALL
      case gezfree1  : 
      case gezfree2 : 
           nextSetid = GeezFree_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_GEEZFREE || SUPPORT_ALL */


#if SUPPORT_GEEZII || SUPPORT_ALL
      case gezi  :
      case gezii :
           nextSetid = GeezII_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_GEEZII || SUPPORT_ALL */


#if SUPPORT_GEEZIGNA || SUPPORT_ALL 
      case gezigna :
           nextSetid = Geezigna_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_GEEZIGNA || SUPPORT_ALL */


#if SUPPORT_GEEZNEWAB || SUPPORT_ALL
      case geznewa :
      case geznewb :
           nextSetid = GeezNewAB_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_GEEZNEWAB || SUPPORT_ALL */


#if SUPPORT_LASERAMHARIC || SUPPORT_ALL
/*    case laser :
           nextSetid = LaserAmharic_get_setName (setid, fontFace, setName);
           break;
*/
#endif /* SUPPORT_LASERAMHARIC || SUPPORT_ALL */


#if SUPPORT_MONOTYPE || SUPPORT_ALL
      case monotype1 :
      case monotype2 :
      case monotype3 :
           nextSetid = MonoType_get_setName (setid, fontFace, setName);
           break;
      case monoalt :
      case mononum :
           nextSetid = MonoTypeAlt_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_MONOTYPE || SUPPORT_ALL */


#if SUPPORT_NCI || SUPPORT_ALL
      case nci :
           nextSetid = NCI_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_NCI || SUPPORT_ALL */


#if SUPPORT_NCIC || SUPPORT_ALL
      case ncic    :
           nextSetid = NCIC_get_setName (setid, fontFace, setName);
           break;
      case ncic_et :
           nextSetid = NCIC_ET_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_NCIC || SUPPORT_ALL */


#if SUPPORT_OMNITECH || SUPPORT_ALL
      case omnitech :
           nextSetid = OmniTech_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_OMNITECH || SUPPORT_ALL */


#if SUPPORT_PHONETICSYS || SUPPORT_ALL
      case geztype    :
      case geztypenet :
           nextSetid = GeezType_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_PHONETICSYS || SUPPORT_ALL */


#if SUPPORT_POWERGEEZ || SUPPORT_ALL
      case powergez    :
      case powergeznum :
           nextSetid = PowerGeez_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_POWERGEEZ || SUPPORT_ALL */


#if SUPPORT_SAMAWERFA || SUPPORT_ALL
      case sam98:
      case samwp:
           nextSetid = Samawerfa_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_SAMAWERFA || SUPPORT_ALL */


#if SUPPORT_TFANUS || SUPPORT_ALL
      case ethiosoft:
           nextSetid = EthioSoft_get_setName (setid, fontFace, setName);
           break;
      case gezbausi:
           nextSetid = GeezBausi_get_setName (setid, fontFace, setName);
           break;
      case tfanus:
           nextSetid = TFanus_get_setName (setid, fontFace, setName);
           break;
      case tfanusnew:
           nextSetid = TFanusNew_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_TFANUS || SUPPORT_ALL */


#if SUPPORT_VISUALGEEZ || SUPPORT_ALL
      case visualgez:
           nextSetid = VisualGeez_get_setName (setid, fontFace, setName);
           break;
      case visualgez2k:
           nextSetid = VisualGeez_get_setName (setid, fontFace+3, setName);
           break;
#endif /* SUPPORT_VISUALGEEZ || SUPPORT_ALL */


#if SUPPORT_WAZEMA || SUPPORT_ALL
      case wazema1:
      case wazema2:
           nextSetid = Wazema_get_setName (setid, fontFace, setName);
           break;
#endif /* SUPPORT_WAZEMA || SUPPORT_ALL */

       default:  break;
  }


  return (nextSetid);

}


#ifdef SUPPORT_RTF
 /**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
//  get_setRTFPrefix (setid, RTFPrefix, mylflags)
//
//  Return address of next token from passed stream of SERA text. Either
//  the file or text string pointer must be NULL.
//  The address of the returned token is specified by the character coding
//  system passed in mylflags->out.
//
//  get_setid is intended to be of very low level, such that users would not
//  be using it.
//
//  tstring  -is a character pointer to SERA text
//  fp       -is a file pointer to SERA text
//  mylflags -is a LEth Flag structure which MUST contain a valid input and
//            output type.
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+/
/+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**/


int 
get_setRTFPrefix (setid, RTFPrefix, system, fontFace)
  int setid;
  char** RTFPrefix;
  enum CharacterSet system;
  int fontFace;
{

int nextSetid = 0;


  switch ( system )
    {
#if SUPPORT_ACIS || SUPPORT_ALL 
      case acis :
           nextSetid = ACIS_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif /* SUPPORT_ACIS || SUPPORT_ALL */


#if SUPPORT_ACUWORK || SUPPORT_ALL 
      case acuwork :
           nextSetid = Acuwork_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif /* SUPPORT_ACUWORK || SUPPORT_ALL */


#if SUPPORT_ADDISWORD || SUPPORT_ALL 
      case addisword1 : 
      case addisword2 : 
           nextSetid = AddisWord_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif  /* SUPPORT_ADDISWORD || SUPPORT_ALL */


#if SUPPORT_ALPAS || SUPPORT_ALL 
      case alpas :
           nextSetid = Alpas_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif /* SUPPORT_ALPAS || SUPPORT_ALL */

#if SUPPORT_BRAILLE || SUPPORT_ALL
/*
      case braille:
           nextSetid = Braille_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
*/
#endif /* SUPPORT_BRAILLE || SUPPORT_ALL */


#if SUPPORT_BRANA || SUPPORT_ALL
      case branai :
      case branaii:
           nextSetid = Brana_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif /* SUPPORT_BRANA || SUPPORT_ALL */


#if SUPPORT_CBHALE || SUPPORT_ALL
      case cbhalea:
      case cbhaleb:
           nextSetid = CBHale_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif /* SUPPORT_CBHALE || SUPPORT_ALL */


#if SUPPORT_DEJENE || SUPPORT_ALL 
      case dejene1: 
      case dejene2: 
           nextSetid = Dejene_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif  /* SUPPORT_DEJENE || SUPPORT_ALL */


#if SUPPORT_ECOLING || SUPPORT_ALL
/*    case ecoling :
           EcoLingUnicode ();
           break;
*/
#endif /* SUPPORT_ECOLING || SUPPORT_ALL */


#if SUPPORT_ETHIOPIC || SUPPORT_ALL 
      case ethiopic1 :
      case ethiopic2 :
           nextSetid = Ethiopic_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif  /* SUPPORT_ETHIOPIC || SUPPORT_ALL */


#if SUPPORT_ETHIOSYS || SUPPORT_ALL 
      case ethiosys  : 
      case ethiosysx : 
           nextSetid = EthioSys_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif  /* SUPPORT_ETHIOSYS || SUPPORT_ALL */


#if SUPPORT_ETHIOWALIA || SUPPORT_ALL 
      case ethiowalia  : 
           nextSetid = EthioWalia_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif  /* SUPPORT_ETHIOWALIA || SUPPORT_ALL */


#if SUPPORT_FIDELEXTRA || SUPPORT_ALL
      case fidelxtr1 :
      case fidelxtr2 :
           nextSetid = FidelExtra_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif /* SUPPORT_FIDELEXTRA || SUPPORT_ALL */


#if SUPPORT_GEEZEDIT || SUPPORT_ALL 
      case gezedit :
           nextSetid = GeezEdit_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif  /* SUPPORT_GEEZEDIT || SUPPORT_ALL */


#if SUPPORT_GEEZFONT || SUPPORT_ALL 
      case gezfont :
           nextSetid = GeezFont_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif /* SUPPORT_GEEZFONT || SUPPORT_ALL */


#if SUPPORT_GEEZFREE || SUPPORT_ALL
      case gezfree1  : 
      case gezfree2 : 
           nextSetid = GeezFree_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif /* SUPPORT_GEEZFREE || SUPPORT_ALL */


#if SUPPORT_FEEDEL || SUPPORT_ALL
      case gezi  :
      case gezii :
      case gezigna :
      case geznewa :
      case geznewb :
           nextSetid = Feedel_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif /* SUPPORT_GEEZNEWAB || SUPPORT_ALL */


#if SUPPORT_LASERAMHARIC || SUPPORT_ALL
/*    case laser :
           nextSetid = LaserAmharic_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
*/
#endif /* SUPPORT_LASERAMHARIC || SUPPORT_ALL */


#if SUPPORT_MONOTYPE || SUPPORT_ALL
      case monotype1 :
      case monotype2 :
      case monotype3 :
      case monoalt   :
      case mononum   :
           nextSetid = MonoType_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif /* SUPPORT_MONOTYPE || SUPPORT_ALL */


#if SUPPORT_NCI || SUPPORT_ALL
      case nci :
           nextSetid = NCI_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif /* SUPPORT_NCI || SUPPORT_ALL */


#if SUPPORT_NCIC || SUPPORT_ALL
      case ncic    :
      case ncic_et :
           nextSetid = NCIC_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif /* SUPPORT_NCIC || SUPPORT_ALL */


#if SUPPORT_OMNITECH || SUPPORT_ALL
      case omnitech :
           nextSetid = OmniTech_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif /* SUPPORT_OMNITECH || SUPPORT_ALL */


#if SUPPORT_PHONETICSYS || SUPPORT_ALL
      case geztype    :
      case geztypenet :
           nextSetid = GeezType_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif /* SUPPORT_PHONETICSYS || SUPPORT_ALL */


#if SUPPORT_POWERGEEZ || SUPPORT_ALL
      case powergez    :
      case powergeznum :
           nextSetid = PowerGeez_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif /* SUPPORT_POWERGEEZ || SUPPORT_ALL */


#if SUPPORT_SAMAWERFA || SUPPORT_ALL
      case sam98:
      case samwp:
           nextSetid = Samawerfa_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif /* SUPPORT_SAMAWERFA || SUPPORT_ALL */


#if SUPPORT_TFANUS || SUPPORT_ALL
      case ethiosoft:
      case gezbausi :
      case tfanus   :
      case tfanusnew:
           nextSetid = TFanus_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif /* SUPPORT_TFANUS || SUPPORT_ALL */


#if SUPPORT_VISUALGEEZ || SUPPORT_ALL
      case visualgez:
      case visualgez2k:
           nextSetid = VisualGeez_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif /* SUPPORT_VISUALGEEZ || SUPPORT_ALL */


#if SUPPORT_WAZEMA || SUPPORT_ALL
      case wazema1:
      case wazema2:
           nextSetid = Wazema_get_setRTFPrefix (setid, fontFace, RTFPrefix);
           break;
#endif /* SUPPORT_WAZEMA || SUPPORT_ALL */

       default:  break;
  }


  return (nextSetid);

}
#endif


boolean
isFidelTrueType ( system )
  enum CharacterSet system;
{

  switch ( system )
    {
      case acis:
      case acuwork:
      case addisword1:
      case addisword2:
      case alpas:
      case branai:
      case branaii:
      case cbhalea:
      case cbhaleb:
      case dejene1:
      case dejene2:
      case ecoling:
      case ethiopic1: 
      case ethiopic2: 
      case ethiosoft:
      case ethiosys:
      case ethiosysx:
      case enhpfr:
      case fidelxtr1:
      case fidelxtr2:
      case gezbausi:
      case gezedit:
      case gezfont:
      case gezfree1:
      case gezfree2:
      case gezigna:
      case gezi:
      case gezii:
      case geznewa:
      case geznewb:
      case geztype:
      case geztypenet:
      case laser:
      case monotype1:
      case monotype2:
      case monotype3:
      case monoalt:
      case mononum:
      case nci:
      case ncic:
      case ncic_et:
      case omnitech:
      case powergez:
      case powergeznum:
      case sam98:
      case samwp:
      case sil1:
      case sil2:
      case sil3:
      case tfanus:
      case tfanusnew:
      case visualgez:
      case visualgez2k:
      case wazema1:
      case wazema2:
           return (true);
           break;

      default:
           return (false);
           break;
    }

  return (false);

}


boolean
isTransliteration ( system )
  enum CharacterSet system;
{

  switch ( system )
    {
      case braille:
      case dehai:
      case ed:
      case ethiop:
      case ies:
      case iso:
      case mainz:
      case sera:
           return (true);
           break;

      default:
           return (false);
           break;
    }

  return (false);

}
