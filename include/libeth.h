/* This is part of the LibEth library, an ANSI C library for Ethiopic
   text and information processing (http://libeth.sourceforge.net).
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

#ifndef LIBETH_H
#define LIBETH_H  1

#include "config.h"

#ifndef __BCC__
#  include <ctype.h>
#  include <locale.h>
#endif /* __BCC__ */

#if __G_HAVE_BOOL || __GNUG__
  typedef bool boolean;
#else
# define __LETH_HAVE_BOOL 1
  typedef enum {false, true} boolean; 
#endif  /* __G_HAVE_BOOL || __GNUG__ */

#ifndef NIL
#  define NIL      -1
#endif  /* NIL */
#define WSIZE     120

#define LIBETH_VERSION_MAJOR 0.3
#define LIBETH_VERSION_MINOR 0.04
#define LIBETH_VERSION_NAME "ወልዲያ"
#define LIBETH_EXPORT_DATE "Sat Nov 27 11:27:27 EST 1999"
/*
**  We need a way to work with languages and scripts independently.
**  "special" may be used for symbols and glyphs.
**  "gfx" is a hypothetical graphical language, currently not used.
  #define NUMLANGS 7
*/
#define NUMLANGS    98
#define NUMETHLANGS 91

enum Scripts   { arabic, fidel, greek, latin, special };
// enum Languages { adr, aar, agw, amh, bil, ged, gez, orm, qot, seb, sid, sil, sod, tig, tir, eng, lat, gre, gfx, uni, undef, useLC };
enum Languages { aiz, aar, qim, zlb, amh, myo, anu, arv, agj, awn, bsw, myf, bst, bej, bcq, wti, byn, bxe, bwo, bji, dox, cra, dsh, dim, gdl, mdx, doz, gft, gmo, gza, gwd, drs, gez, gto, guk, guy, gru, zgu, hdy, amf, har, hoz, kcx, koe, kbr, ktb, kxh, zkn, zko, kxc, kqy, bza, xuf, kmq, zkw, liq, mpe, mdy, mym, mfx, mys, mur, muz, nrb, noz, nus, nnj, lgn, gax, hae, orm, oyd, rer, ssy, sze, sbf, moy, she, sid, som, suq, tig, tir, tsb, udu, woy, wbc, xan, jnj, zwa, zay, eng, lat, gre, gfx, uni, undef, useLC };

typedef struct {
   enum Languages l; 
   enum Scripts   s;
}  LS;


/*
**  LSDEFS associates language and scipts (as defaults)
**  ISO639_[23] are ISO-639 2 and 3 character language names
*/

#define LSDEFS { {aiz, fidel}, {aar, fidel}, {qim, fidel}, {zlb, fidel}, {amh, fidel}, {myo, fidel}, {anu, fidel}, {arv, fidel}, {agj, fidel}, {awn, fidel}, {bsw, fidel}, {myf, fidel}, {bst, fidel}, {bej, fidel}, {bcq, fidel}, {wti, fidel}, {byn, fidel}, {bxe, fidel}, {bwo, fidel}, {bji, fidel}, {dox, fidel}, {cra, fidel}, {dsh, fidel}, {dim, fidel}, {gdl, fidel}, {mdx, fidel}, {doz, fidel}, {gft, fidel}, {gmo, fidel}, {gza, fidel}, {gwd, fidel}, {drs, fidel}, {gez, fidel}, {gto, fidel}, {guk, fidel}, {guy, fidel}, {gru, fidel}, {zgu, fidel}, {hdy, fidel}, {amf, fidel}, {har, fidel}, {hoz, fidel}, {kcx, fidel}, {koe, fidel}, {kbr, fidel}, {ktb, fidel}, {kxh, fidel}, {zkn, fidel}, {zko, fidel}, {kxc, fidel}, {kqy, fidel}, {bza, fidel}, {xuf, fidel}, {kmq, fidel}, {zkw, fidel}, {liq, fidel}, {mpe, fidel}, {mdy, fidel}, {mym, fidel}, {mfx, fidel}, {mys, fidel}, {mur, fidel}, {muz, fidel}, {nrb, fidel}, {noz, fidel}, {nus, fidel}, {nnj, fidel}, {lgn, fidel}, {gax, fidel}, {hae, fidel}, {orm, fidel}, {oyd, fidel}, {rer, fidel}, {ssy, fidel}, {sze, fidel}, {sbf, fidel}, {moy, fidel}, {she, fidel}, {sid, fidel}, {som, fidel}, {suq, fidel}, {tig, fidel}, {tir, fidel}, {tsb, fidel}, {udu, fidel}, {woy, fidel}, {wbc, fidel}, {xan, fidel}, {jnj, fidel}, {zwa, fidel}, {zay, fidel}, {eng, latin}, {lat, latin}, {gre, greek}, {gfx, special} }

#define ISO639_3 { "aiz", "aar", "qim", "zlb", "amh", "myo", "anu", "arv", "agj", "awn", "bsw", "myf", "bst", "bej", "bcq", "wti", "byn", "bxe", "bwo", "bji", "dox", "cra", "dsh", "dim", "gdl", "mdx", "doz", "gft", "gmo", "gza", "gwd", "drs", "gez", "gto", "guk", "guy", "gru", "zgu", "hdy", "amf", "har", "hoz", "kcx", "koe", "kbr", "ktb", "kxh", "zkn", "zko", "kxc", "kqy", "bza", "xuf", "kmq", "zkw", "liq", "mpe", "mdy", "mym", "mfx", "mys", "mur", "muz", "nrb", "noz", "nus", "nnj", "lgn", "gax", "hae", "orm", "oyd", "rer", "ssy", "sze", "sbf", "moy", "she", "sid", "som", "suq", "tig", "tir", "tsb", "udu", "woy", "wbc", "xan", "jnj", "zwa", "zay", "eng", "lat", "gre" }
 
#define ISO639_2 { "ai", "aa", "qi", "zl", "am", "ym", "an", "av", "ag", "aw", "bs", "mf", "bt", "bj", "bc", "wt", "by", "bx", "bw", "bu", "dx", "cr", "ds", "di", "dl", "md", "do", "gf", "gm", "gx", "gw", "dr", "gz", "gt", "gk", "gy", "gr", "zg", "hd", "hb", "ad", "ho", "kc", "ke", "kb", "kt", "kh", "zn", "zk", "kx", "kq", "bz", "xu", "mq", "zw", "li", "mp", "dy", "mm", "mx", "ys", "mu", "mz", "nr", "nz", "nu", "nn", "lg", "gx", "ae", "om", "od", "re", "sy", "sz", "sb", "oy", "hs", "sx", "so", "uq", "ig", "ti", "tb", "ud", "wy", "wb", "xa", "jn", "zx", "zy", "la", "el" }
 

/*
**  the following are MIME-ish definitions for file I/O  
**
**  According to RFC-2045:
**
**  ``The term "character set" is used in MIME to refer to a method of
**    converting a sequence of octets into a sequence of characters.''
**
**  Which is a revision of previous definitions the RFC notes.
**
**
**  Content-Type: text/plain; charset=ISO-8859-1
**  Content-transfer-encoding: base64
**
*/
enum ContentType  { text };

enum ContentSubType  { plain, html, rtf, ltx, tex };

#define ETHCHARSETS 78

enum CharacterSet  { nocs, acis, acuwork, addisword1, addisword2, alpas, braille, branai, branaii, cbhalea, cbhaleb, dehai, dejene1, dejene2, ecoling, ed, enhpfr, ethcitap, ethcitas, ethcitau, ethiome, ethiomex, ethiop, ethiopic1, ethiopic2, ethiosoft, ethiosys, ethiosysx, ethiowalia, fidelxtr1, fidelxtr2, gezbausi, gezedit, gezedit98, gezfont, gezfree1, gezfree2, gezigna, gezi, gezii, geznewa, geznewb, geztype, geztypenet, ies, image, iso, jis, junet, laser, mainz, monotype1, monotype2, monotype3, monoalt, mononum, muletex, nci, ncic, ncic_et, omnitech, powergez, powergeznum, qubee, samwp, sam98, sera, sil1, sil2, sil3, tfanus, tfanusnew, unicode, visualgez, visualgez2k, wazema1, wazema2, all };

enum TransferVariant { notv, clike, decimal, dos, escd, esch, java, uname, uplus, utf7, utf8, utf16, xml, zerox };

enum ContentTransferEncoding  { bit7, bit8, base64, binary, quotedprintable };

enum Options { noOps, aynIsZero, debug, ethOnly=4, gColon=8, gQmark=16, gSpace=32, ungeminate=64, uppercase=128 };


#define _ContenTypeNames  { "text" };

#define _ContenSubTypeNames  { "plain", "html", "rtf", "ltx", "tex" };

#define _CharacterSetNames  { "none", "acis", "acuwork", "addisword1", "addisword2", "alpas", "braille", "branai", "branaii", "cbhalea", "cbhaleb", "dehai", "dejene1", "dejene2", "ecoling", "ed", "enhpfr", "ethcitap", "ethcitas", "ethcitau", "ethiome", "ethiomex", "ethiop", "ethiopic1", "ethiopic2", "ethiosoft", "ethiosys", "ethiosysx", "ethiowalia", "fidelxtr1", "fidelxtr2", "gezbausi", "gezedit", "gezedit98", "gezfont", "gezfree", "gezfree2", "gezigna", "gezi", "gezii", "geznewa", "geznewb", "geztype", "ies", "image", "iso/tc46/sc2", "jis", "junet", "laser", "mainz", "monotype1", "monotype2", "monotype3", "monoalt", "mononum", "muletex", "nci", "ncic", "ncic_et", "omnitech", "powergez", "powergeznum", "qubee", "samwp", "sam98", "sera", "sil1", "sil2", "sil3", "tfanus", "tfanusnew", "unicode", "visualgez", "visualgez2k", "all" };

#define _TransferVariantNames  { "none", "C-Like", "Debug", "DOS", "Java", "U-Name", "U-Plus", "UTF7", "UTF8", "UTF16", "0x" };

#define _ContentTransferEncodingNames  { "7bit", "8bit", "base64", "binary", "quoted printable" };

#define _Options { "none", "aynIsZero", "Debug", "Ethiopic Only", "gColon", "gSpace", "gQmark", "ungeminate", "UPPERCASE" };


typedef unsigned short FCHAR;



/*
**  The essential structure for communicating with libeth routines.
**  This could be broken into substructures but to date I have 
**  encountered no independent need for possible subsctructures.
*/
typedef struct {

   /* This is data that need to be communicated to the lexers at low levels
      for the configurable transliteration systems                          */

   boolean lastPunct;                                    /* lexer flag      */
   LS   *minor, *major, *top, *out;                      /* language info   */
   int lastChar, lexerState, form;                       /* text processing */

   /* These are basically the MIME fields  */

   enum CharacterSet       csIn,   csOut;
   enum TransferVariant    tvIn,   tvOut;
   enum ContentType        ctIn,   ctOut;
   enum ContentSubType    cstIn,  cstOut;


   /*  We don't need this just yet...
    *
    *  enum ContentTransferEncoding cteIn, cteOut;
    */


   /*  Various settings for optional ways to output the transfer variants,
    *  also for locale and corrective settings.
    */
   unsigned int options;


   /*  So far I have only found a need for the "fontFaceOut"
    *  "fontFaceIn" is added just  in case...
    */
   int  fontFaceIn, fontFaceOut;
   unsigned char* stringTop;
   FCHAR* holdChars;                                  /* pushed back tokens */

}  LibEthFlags;


#define _LET_FAIL 0
#define _LET_SUCCESS 1


#endif /* ifndef LIBETH_H */
