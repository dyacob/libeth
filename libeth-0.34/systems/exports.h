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

#ifndef EXPORTS_H
#define EXPORTS_H 1

#ifndef MAPTYPES_H
#  include "maptypes.h"
#endif /* MAPTYPES_H */


#if    !(ABSHA_MAP || ABSHA_H)
  extern LETCHAR GeezEditFidel[]; 
  extern FCHAR GeezEditToUnicode (void);
  extern unsigned char* UnicodeToGeezEdit (FCHAR fch);
  extern int GeezEdit_get_setid (FCHAR fch);
  extern int GeezEdit_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* Absha_get_netInfo (char INFO);
  extern int GeezEdit_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
  extern unsigned char GeezEdit_isGoodANSI (FCHAR fch);
#endif /* ABSHA */


#if    !(ACIS_MAP || ACUWORK_H)
  extern LETCHAR ACISFidel[]; 
  extern FCHAR ACISToUnicode (void);
  extern unsigned char* UnicodeToACIS (FCHAR fch);
  extern int ACIS_get_setid (FCHAR fch);
  extern int ACIS_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* ACIS_get_netInfo (char INFO);
  extern int ACIS_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
  extern unsigned char ACIS_isGoodANSI (FCHAR fch);
#endif /* ACIS */


#if    !(ACUWORK_MAP || ACUWORK_H)
  extern LETCHAR ALXEtFidel[]; 
  extern FCHAR AcuworkToUnicode (void);
  extern unsigned char* UnicodeToAcuwork (FCHAR fch);
  extern int Acuwork_get_setid (FCHAR fch);
  extern int Acuwork_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* Acuwork_get_netInfo (char INFO);
  extern int Acuwork_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
  extern unsigned char Acuwork_isGoodANSI (FCHAR fch);
#endif /* ACUWORK */


#if    !(ADDISWORD_MAP || ADDISWORD_H)
  extern LETCHAR AddisWordFidel[]; 
  extern FCHAR AddisWordOneToUnicode (void);
  extern FCHAR AddisWordTwoToUnicode (void);
  extern unsigned char* UnicodeToAddisWord (FCHAR fch);
  extern int AddisWord_get_setid (FCHAR fch);
  extern int AddisWord_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* AddisWord_get_netInfo (char INFO);
  extern int AddisWord_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
  extern unsigned char AddisWord_isGoodANSI (FCHAR fch);
#endif /* ADDISWORD */


#if    !(ALPAS_MAP || ALPAS_H)
  extern LETCHAR AlpasFidel[]; 
  extern FCHAR AlpasToUnicode (void);
  extern unsigned char* UnicodeToAlpas (FCHAR fch);
  extern int Alpas_get_setid (FCHAR fch);
  extern int Alpas_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* Alpas_get_netInfo (char INFO);
  extern int Alpas_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
  extern unsigned char Alpas_isGoodANSI (FCHAR fch);
#endif /* ALPAS */


#if    !(BRANA_MAP || BRANA_H)
  extern LETCHAR BranaFidel[]; 
  extern FCHAR BranaIToUnicode (void);
  extern FCHAR BranaIIToUnicode (void);
  extern unsigned char* UnicodeToBrana (FCHAR fch);
  extern int Brana_get_setid (int fch);
  extern int Brana_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* Brana_get_netInfo (char INFO);
  extern int Brana_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
  extern unsigned char BranaI_isGoodANSI (FCHAR fch);
#endif /* BRANA */


#if    !(CBHALE_MAP || CBHALE_H)
  extern LETCHAR CBHaleFidel[]; 
  extern FCHAR CBHaleAToUnicode (void);
  extern FCHAR CBHaleBToUnicode (void);
  extern unsigned char* UnicodeToCBHale (FCHAR fch);
  extern int CBHale_get_setid (FCHAR fch);
  extern int CBHale_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* CBHale_get_netInfo (char INFO);
  extern int CBHale_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
  extern unsigned char CBHaleA_isGoodANSI (FCHAR fch);
#endif /* CBHALE */


#if    !(DEHAI_MAP || ED_H)
  extern FCHAR DehaiToUnicode (void);
  extern unsigned char* UnicodeToDehai (FCHAR fch, LibEthFlags* myflags);
  extern char* Dehai_get_netInfo (char INFO);
#endif /* DEHAI*/


#if    !(DEJENE_MAP || DEJENE_H)
  extern LETCHAR DejeneFidel[]; 
  extern FCHAR Dejene1ToUnicode (void);
  extern FCHAR Dejene2ToUnicode (void);
  extern unsigned char* UnicodeToDejene (FCHAR fch);
  extern int Dejene_get_setid (FCHAR fch);
  extern int Dejene_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* Dejene_get_netInfo (char INFO);
  extern int Dejene_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
  extern unsigned char Dejene_isGoodANSI (FCHAR fch);
#endif /* DEJENE */


#if    !(ED_MAP || ED_H)
  extern LETCHAR EdFidel[]; 
  extern FCHAR EdToUnicode (void);
  extern unsigned char* UnicodeToEd (FCHAR fch);
  extern char* Ed_get_netInfo (char INFO);
#endif /* ED */


#if    !(ENHPFR_MAP || ENHPFR_H)
  extern unsigned char* UnicodeToENHPFR_he (FCHAR fch);
  extern unsigned char* UnicodeToENHPFR_le (FCHAR fch);
  extern int ENHPFR_get_setid (FCHAR fch);
  extern int ENHPFR_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* ENHPFR_get_netInfo (char INFO);
  extern unsigned char ENHPFR_isGoodANSI (FCHAR fch);
#endif /* ENHPFR */


#if    !(ETHCITA_MAP || ETHCITA_H)
  extern FCHAR EthCITAUniToUnicode (void);
  extern unsigned char* UnicodeToEthCITAUni (FCHAR fch);
  extern int EthCITAUni_get_setid (FCHAR fch);
  extern int EthCITAUni_get_setName (int setid, int fontFace, unsigned char** setName);
  extern unsigned char EthCITAUni_isGoodANSI (FCHAR fch);
  extern int EthCITAUni_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);

  extern unsigned char* UnicodeToEthCITABi (FCHAR fch);
  extern int EthCITABi_get_setid (FCHAR fch);
  extern unsigned char EthCITABi_isGoodANSI (FCHAR fch);
  extern char* EthCITA_get_netInfo (char INFO);

  extern FCHAR EthCITABiPToUnicode (void);
  extern int EthCITABiP_get_setName (int setid, int fontFace, unsigned char** setName);
  extern int EthCITABiP_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);

  extern FCHAR EthCITABiSToUnicode (void);
  extern unsigned char* UnicodeToEthCITABi (FCHAR fch);
  extern int EthCITABiS_get_setName (int setid, int fontFace, unsigned char** setName);
  extern int EthCITABiS_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
#endif /* ETHCITA */


#if    !(ETHIOPIC_MAP || ETHIOPIC_H)
  extern LETCHAR EthiopicFidel[]; 
  extern FCHAR Ethiopic1ToUnicode (void);
  extern FCHAR Ethiopic2ToUnicode (void);
  extern unsigned char* UnicodeToEthiopic (FCHAR fch);
  extern int Ethiopic_get_setid (FCHAR fch);
  extern int Ethiopic_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* Ethiopic_get_netInfo (char INFO);
  extern int Ethiopic_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
  extern unsigned char Ethiopic_isGoodANSI (FCHAR fch);
#endif /* ETHIOPIC */


#if    !(ETHIOSYS_MAP || ETHIOSYS_H)
  extern LETCHAR EthioSysFidel[]; 
  extern FCHAR EthioSysPrimaryToUnicode (void);
  extern FCHAR EthioSysSecondaryToUnicode (void);
  extern unsigned char* UnicodeToEthioSys (FCHAR fch);
  extern int EthioSys_get_setid (FCHAR fch);
  extern int EthioSys_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* EthioSys_get_netInfo (char INFO);
  extern int EthioSys_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
  extern unsigned char EthioSys_isGoodANSI (FCHAR fch);
#endif /* ETHIOSYS */


#if    !(ETHIOWALIA_MAP || ETHIOWALIA_H)
  extern LETCHAR EthioWaliaFidel[]; 
  extern FCHAR EthioWaliaToUnicode (void);
  extern unsigned char* UnicodeToEthioWalia (FCHAR fch);
  extern int EthioWalia_get_setid (FCHAR fch);
  extern int EthioWalia_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* EthioWalia_get_netInfo (char INFO);
  extern int EthioWalia_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
  extern unsigned char EthioWalia_isGoodANSI (FCHAR fch);
#endif /* ETHIOWALIA */


#if    !(ETHIOME_MAP || ETHIOME_H)
  extern FCHAR EthioMEPrimaryToUnicode (void);
  extern FCHAR EthioMESecondaryToUnicode (void);
  extern LETCHAR EthioMEFidel[]; 
  extern unsigned char* UnicodeToEthioME (FCHAR fch);
#endif /* ETHIOME */


#if    !(ETHIOP_MAP || ETHIOP_H)
  extern LETCHAR EthiopFidel[]; 
  extern FCHAR EthiopToUnicode (void);
  extern unsigned char* UnicodeToEthiop (FCHAR fch);
  extern char* Ethiop_get_netInfo (char INFO);
#endif /* ETHIOP */


#if    !(FIDELEXTRA_MAP || FIDELEXTRA_H)
  extern LETCHAR FidelExtraFidel[]; 
  extern FCHAR FidelExtra1ToUnicode (void);
  extern FCHAR FidelExtra2ToUnicode (void);
  extern unsigned char* UnicodeToFidelExtra (FCHAR fch);
  extern int FidelExtra_get_setid (FCHAR fch);
  extern int FidelExtra_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* FidelExtra_get_netInfo (char INFO);
  extern int FidelExtra_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
#endif /* FIDELEXTRA */


#if    !(FEEDEL_MAP || FEEDEL_H)
  extern LETCHAR GeezignaFidel[]; 
  extern FCHAR GeezignaToUnicode (void);
  extern unsigned char* UnicodeToGeezigna (FCHAR fch);
  extern int Geezigna_get_setid (FCHAR fch);
  extern int Geezigna_get_setName (int setid, int fontFace, unsigned char** setName);

  extern LETCHAR GeezIIFidel[]; 
  extern FCHAR GeezIToUnicode (void);
  extern FCHAR GeezIIToUnicode (void);
  extern unsigned char* UnicodeToGeezII (FCHAR fch);
  extern int GeezII_get_setid (FCHAR fch);
  extern int GeezII_get_setName (int setid, int fontFace, unsigned char** setName);
  extern unsigned char GeezI_isGoodANSI (FCHAR fch);

  extern LETCHAR GeezNewABFidel[]; 
  extern FCHAR GeezNewAToUnicode (void);
  extern FCHAR GeezNewBToUnicode (void);
  extern unsigned char* UnicodeToGeezNewAB (FCHAR fch);
  extern unsigned char GeezNewAB_isGoodANSI (FCHAR fch);
  extern int GeezNewAB_get_setid (FCHAR fch);
  extern int GeezNewAB_get_setName (int setid, int fontFace, unsigned char** setName);
  extern unsigned char GeezNewA_isGoodANSI (FCHAR fch);
  extern char* Feedel_get_netInfo (char INFO);
  extern int Feedel_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
#endif /* FEEDEL */


#if    !(GEEZFONT_MAP || GEEZFONT_H)
  extern LETCHAR GeezFontFidel[]; 
  extern FCHAR GeezFontToUnicode (void);
  extern unsigned char* UnicodeToGeezFont (FCHAR fch);
  extern int GeezFont_get_setid (FCHAR fch);
  extern int GeezFont_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* GeezFont_get_netInfo (char INFO);
  extern int GeezFont_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
  extern unsigned char GeezFont_isGoodANSI (FCHAR fch);
#endif /* GEEZFONT */


#if    !(GEEZFREE_MAP || GEEZFREE_H)
  extern LETCHAR GeezFreeFidel[]; 
  extern FCHAR GeezFree2ToUnicode (void);
  extern unsigned char* UnicodeToGeezFree (FCHAR fch);
  extern int GeezFree_get_setid (FCHAR fch);
  extern int GeezFree_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* GeezFree_get_netInfo (char INFO);
  extern int GeezFree_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
#endif /* GEEZFREE */


#if    !(GEEZTYPE_MAP || GEEZTYPE_H)
  extern LETCHAR GeezTypeFidel[]; 
  extern FCHAR GeezTypeToUnicode (void);
  extern unsigned char* UnicodeToGeezType (FCHAR fch);
  extern int GeezType_get_setid (FCHAR fch);
  extern int GeezType_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* GeezType_get_netInfo (char INFO);
  extern int GeezType_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
  extern unsigned char GeezType_isGoodANSI (FCHAR fch);

  extern LETCHAR GeezTypeNetFidel[]; 
  extern FCHAR GeezTypeNetToUnicode (void);
  extern unsigned char* UnicodeToGeezTypeNet (FCHAR fch);
  extern int GeezTypeNet_get_setid (FCHAR fch);
  extern int GeezTypeNet_get_setName (int setid, int fontFace, unsigned char** setName);
  extern unsigned char GeezTypeNet_isGoodANSI (FCHAR fch);
#endif /* GEEZTYPE */


#if    !(IES_MAP || IES_H)
/*extern phonset IESGeez[];
  extern phonset IESTigrigna[];
  extern phonset IESAmharic[];
*/extern unsigned char* UnicodeToIESAmharic (FCHAR fch);
  extern unsigned char* UnicodeToIESGeez (FCHAR fch);
  extern unsigned char* UnicodeToIESTigrigna (FCHAR fch);
  extern char* IES_get_netInfo (char INFO);
#endif /* IES */


#if    !(ISO_MAP || ISO_H)
  extern unsigned char* ISOTC46SC2Fidel[];
  extern unsigned char* UnicodeToISOTC46SC2 (FCHAR fch, LibEthFlags* mylflags);
  extern char* ISO_get_netInfo (char INFO);
#endif /* ISO */


#ifndef JAVA_H
  extern unsigned char* UnicodeToJava (FCHAR fch, boolean lower);
# define UnicodeTojava(fch)  UnicodeToJava(fch, true)
# define UnicodeToJAVA(fch)  UnicodeToJava(fch, false)
  extern char* Java_get_netInfo (char INFO);
#endif /* JAVA */


#if    !(JIS_MAP || JIS_H)
  extern unsigned char* UnicodeToJIS (FCHAR fch);
  extern char* JIS_get_netInfo (char INFO);
#endif /* JIS */


#if    !(JUNET_MAP || JUNET_H)
  extern unsigned char* UnicodeToJUNET (FCHAR fch);
  extern char* JUNET_get_netInfo (char INFO);
#endif /* JUENT */


#if    !(MAINZ_MAP || MAINZ_H)
  extern FCHAR MainzToUnicode (void);
  extern unsigned char* UnicodeToMainz (FCHAR fch, LibEthFlags* mylflags);
  extern char* Mainz_get_netInfo (char INFO);
#endif /* MAINZ */


#if    !(MONOTYPE_MAP || MONOTYPE_H)
  extern LETCHAR MonoTypeFidel[]; 
  extern LETCHAR MonoTypeAltFidel[]; 
  extern FCHAR MonoType1ToUnicode (void);
  extern FCHAR MonoType2ToUnicode (void);
  extern FCHAR MonoType3ToUnicode (void);
  extern FCHAR MonoTypeNToUnicode (void);
  extern FCHAR MonoTypeAltToUnicode (void);
  extern unsigned char* UnicodeToMonoType (FCHAR fch);
  extern unsigned char* UnicodeToMonoTypeAlt (FCHAR fch);
  extern int MonoType_get_setid (FCHAR fch);
  extern int MonoType_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* MonoType_get_netInfo (char INFO);
  extern int MonoTypeAlt_get_setid (FCHAR fch);
  extern int MonoTypeAlt_get_setName (int setid, int fontFace, unsigned char** setName);
  extern int MonoType_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
#endif /* MONOTYPE */


#if    !(NCI_MAP || NCI_H)
  extern LETCHAR NCIFidel[]; 
  extern FCHAR NCIToUnicode (void);
  extern unsigned char* UnicodeToNCI (FCHAR fch);
  extern int NCI_get_setid (FCHAR fch);
  extern int NCI_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* NCI_get_netInfo (char INFO);
  extern int NCI_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
  extern unsigned char NCI_isGoodANSI (FCHAR fch);
#endif /* NCI */


#if    !(NCIC_MAP || NCIC_H)
  extern LETCHAR NCICFidel[]; 
  extern FCHAR NCICToUnicode (void);
  extern unsigned char* UnicodeToNCIC (FCHAR fch);
  extern int NCIC_get_setid (FCHAR fch);
  extern int NCIC_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* NCIC_get_netInfo (char INFO);
  extern int NCIC_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
  extern unsigned char NCIC_isGoodANSI (FCHAR fch);

  extern FCHAR NCIC_ETToUnicode (void);
  extern int NCIC_ET_get_setid (FCHAR fch);
  extern int NCIC_ET_get_setName (int setid, int fontFace, unsigned char** setName);
  extern unsigned char NCIC_ET_isGoodANSI (FCHAR fch);
#endif /* NCIC */


#if    !(OMNITECH_MAP || OMNITECH_H)
  extern LETCHAR OmniTechFidel[]; 
  extern FCHAR OmniTechToUnicode (void);
  extern unsigned char* UnicodeToOmniTech (FCHAR fch);
  extern int OmniTech_get_setid (FCHAR fch);
  extern int OmniTech_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* OmniTech_get_netInfo (char INFO);
  extern int OmniTech_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
#endif /* OMNITECH */


#if    !(POWERGEEZ_MAP || POWERGEEZ_H)
  extern LETCHAR PowerGeezFidel[]; 
  extern FCHAR PowerGeezToUnicode (void);
  extern FCHAR PowerGeezExtrasToUnicode (void);
  extern unsigned char* UnicodeToPowerGeez (FCHAR fch);
  extern int PowerGeez_get_setid (FCHAR fch);
  extern int PowerGeez_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* PowerGeez_get_netInfo (char INFO);
  extern unsigned char PowerGeez_isGoodANSI ( FCHAR fch );
  extern int PowerGeez_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
#endif /* POWERGEEZ */


#if    !(QUBEE_MAP || QUBEE_H)
  extern FCHAR QubeeToUnicode (void);
  extern unsigned char* UnicodeToQubee (FCHAR fch);
  extern char* Qubee_get_netInfo (char INFO);
#endif /* QUBEE */


#if    !(SAMAWERFA_MAP || SAMAWERFAT_H)
  extern LETCHAR SamawerfaFidel[]; 
  extern FCHAR SamawerfaToUnicode (LibEthFlags* mylflags);
  extern unsigned char* UnicodeToSamawerfa98 (FCHAR fch);
  extern unsigned char* UnicodeToSamawerfaWP (FCHAR fch);
  extern int Samawerfa_get_setid (FCHAR fch);
  extern int Samawerfa_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* Samawerfa_get_netInfo (char INFO);
  extern int Samawerfa_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
  extern unsigned char Samawerfa_isGoodANSI (FCHAR fch);

# define Samawerfa98ToUnicode() SamawerfaToUnicode( mylflags )
# define SamawerfaWPToUnicode() SamawerfaToUnicode( mylflags )

#endif /* SAMAWERFA */


#if    !(SERA_MAP || SERA_H)
#ifdef _LET_USE_SERA_FIDEL
  extern unsigned char* SERAFidel[]; 
#endif /* _LET_USE_SERA_FIDEL */
  extern FCHAR SERAToUnicode (void);
  extern unsigned char* _UnicodeToSERA (FCHAR fch, LibEthFlags* mylflags);
  extern char* SERA_get_netInfo (char INFO);
  extern unsigned char SERA_isGoodANSI (FCHAR fch);
  extern void lexer_reset ( LibEthFlags* lethFlags );
# define UnicodeToSERA(fch) _UnicodeToSERA(fch, mylflags)
#endif /* SERA */


#if    !(TEX_MAP || TEX_H)
  extern unsigned char* TeXFidel[]; 
  extern unsigned char* UnicodeToTeX (FCHAR fch);
  extern char* TeX_get_netInfo (char INFO);
#endif /* TEX */


#if    !(TFANUS_MAP || TFANUS_H)
  extern LETCHAR TFanusFidel[]; 
  extern FCHAR TFanusToUnicode (LibEthFlags* mylflags);
  extern unsigned char* UnicodeToTFanus (FCHAR fch);
  extern unsigned char* UnicodeToEthioSoft (FCHAR fch);
  extern int TFanus_get_setid (FCHAR fch);
  extern int TFanus_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* TFanus_get_netInfo (char INFO);
  extern char* EthioSoft_get_netInfo (char INFO);
  extern int TFanus_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
  extern unsigned char TFanus_isGoodANSI (FCHAR fch);

  extern int TFanusNew_get_setName (int setid, int fontFace, unsigned char** setName);
  extern unsigned char TFanusNew_isGoodANSI (FCHAR fch);

  extern int GeezBausi_get_setName (int setid, int fontFace, unsigned char** setName);
  extern unsigned char GeezBausi_isGoodANSI (FCHAR fch);

  extern unsigned char* UnicodeToEthioSoft (FCHAR fch);
  extern int EthioSoft_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* EthioSoft_get_netInfo (char INFO);
  extern int EthioSoft_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
  extern unsigned char EthioSoft_isGoodANSI (FCHAR fch);
#endif /* TFANUS */


#if    !(VISGEEZ_MAP || VISGEEZ_H)
  extern LETCHAR VisualGeezFidel[]; 
  extern FCHAR VisualGeezToUnicode (void);
  extern unsigned char* UnicodeToVisualGeez (FCHAR fch);
  extern int VisualGeez_get_setid (FCHAR fch);
  extern int VisualGeez_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* VisualGeez_get_netInfo (char INFO);
  extern int VisualGeez_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
  extern unsigned char VisualGeez_isGoodANSI (FCHAR fch);

  extern LETCHAR VisualGeez2000Fidel[]; 
  extern FCHAR VisualGeez2000ToUnicode (void);
  extern unsigned char* UnicodeToVisualGeez2000 (FCHAR fch);
  extern int VisualGeez2000_get_setid (FCHAR fch);
  extern unsigned char VisualGeez2000_isGoodANSI (FCHAR fch);
#endif /* VISGEEZ */


#if    !(WAZEMA_MAP || WAZEMA_H)
  extern LETCHAR WazemaFidel[]; 
  extern FCHAR WazemaA1ToUnicode (void);
  extern FCHAR WazemaA2ToUnicode (void);
  extern unsigned char* UnicodeToWazema (FCHAR fch);
  extern int Wazema_get_setid (FCHAR fch);
  extern int Wazema_get_setName (int setid, int fontFace, unsigned char** setName);
  extern char* Wazema_get_netInfo (char INFO);
  extern int Wazema_get_setRTFPrefix (int setid, int fontFace, char** RTFPrefix);
  extern unsigned char WazemaA1_isGoodANSI (FCHAR fch);
  extern unsigned char WazemaA2_isGoodANSI (FCHAR fch);
#endif /* WAZEMA */


extern FCHAR UTF7ToUnicode (void);
extern FCHAR UTF8ToUnicode (void);
extern FCHAR UTF16ToUnicode (void);
extern unsigned char* UnicodeToUTF7 (FCHAR fch);
extern unsigned char* UnicodeToUTF8 (FCHAR fch);
extern unsigned char* UnicodeToUTF16 (FCHAR fch);
extern unsigned char* UnicodeToName (FCHAR fch);
extern char* Unicode_get_netInfo (char INFO);

extern unsigned char* RTFMAP[];


#ifndef FIDEL_MAP
  extern int UniToTraditional[];
  extern int UniToMod[];
  extern int GeezMaps[];
#endif /* FIDEL_MAP */


#ifndef LNS
  extern LS LnS[];
#endif /* LNS */


/* filters */
FCHAR* ayn2zero ( FCHAR* fstring );
FCHAR* jis_remap_space ( FCHAR* fstring );


#endif /* EXPORTS_H */
