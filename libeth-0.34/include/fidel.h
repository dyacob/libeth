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

/*
**      This file is fidel.h to go with generic lex based sera-to-fidel
**      parsers.  The first order (ge'ez) character names follow those
**      found in current Unicode proposals.  The addresses defined with 
**      the names are the Unicode assignments. Equivalent names in SERA 
**       are provided in comments.
**
**
**      #define  UNICODE   UNICODE    SERA
**               NAME      ADDRESS    NAME
*/

#ifndef FIDEL_H
#define FIDEL_H  1

/* letters given in traditional ordering */

#define ANSI     256 
#define UNIFIDEL 0x1200                  /* 4,608 */
#define UNILAST  0x137f                  /* 4,991 */
#define UNISIZE (UNILAST - UNIFIDEL + 1) /*   384 */
#define ROW      8

#define GIZ    0
#define KAIB   1
#define SALS   2
#define RABI   3
#define HAMS   4
#define SADS   5
#define SABI   6
#define DIQALA 7
#define DIQALA_GIZ  8
#define DIQALA_SALS 10
#define DIQALA_RABI 11
#define DIQALA_HAMS 12
#define DIQALA_SADS 13

#define HAE      UNIFIDEL        /* he */
#define LAE    (HAE + ROW)       /* le */
#define HHAE   (LAE + ROW)       /* He */
#define MAE   (HHAE + ROW)       /* me */
#define SZAE   (MAE + ROW)       /*`se */
#define RAE   (SZAE + ROW)       /* re */
#define SAE    (RAE + ROW)       /* se */
#define SHAE   (SAE + ROW)       /* xe */
#define QAE   (SHAE + ROW)       /* qe */
#define QXAE   (QAE + ROW + ROW) /* Qe */
#define BAE   (QXAE + ROW + ROW) /* be */
#define VAE    (BAE + ROW)       /* ve */
#define TAE    (VAE + ROW)       /* te */
#define CAE    (TAE + ROW)       /* ce */
#define HZAE   (CAE + ROW)       /*`he */
#define NAE   (HZAE + ROW + ROW) /* ne */
#define NYAE   (NAE + ROW)       /* Ne */
#define AE    (NYAE + ROW)       /*  e */
#define KAE     (AE + ROW)       /* ke */
#define KHAE   (KAE + ROW + ROW) /* Ke */
#define WAE   (KHAE + ROW + ROW) /* we */
#define OAE    (WAE + ROW)       /* `e */
#define ZAE    (OAE + ROW)       /* ze */
#define ZHAE   (ZAE + ROW)       /* Ze */
#define YAE   (ZHAE + ROW)       /* ye */
#define DAE    (YAE + ROW)       /* de */
#define DHAE   (DAE + ROW)       /* De */
#define JAE   (DHAE + ROW)       /* je */
#define GAE    (JAE + ROW)       /* ge */
#define GGAE   (GAE + ROW + ROW) /* Ge */
#define THAE  (GGAE + ROW)       /* Te */
#define CHAE  (THAE + ROW)       /* Ce */
#define PHAE  (CHAE + ROW)       /* Pe */
#define TSAE  (PHAE + ROW)       /* Se */
#define TSZAE (TSAE + ROW)       /*`Se */
#define FAE  (TSZAE + ROW)       /* fe */
#define PAE    (FAE + ROW)       /* pe */

/* defined extensions */
#define MYA   0x1358
#define RYA   (MYA + 1)
#define FYA   (RYA + 1)

/* define punctuation addresses */
#define SPACE         0x1360
#define WORDSPACE     0x1361
#define FULLSTOP      0x1362
#define COMMA         0x1363
#define SEMICOLON     0x1364
#define COLON         0x1365
#define PREFACECOLON  0x1366
#define SOSTNETEB     0x1367
#define PARAGRAPH     0x1368
#define SOFTSADIS     0x1360  /* I'm putting this at SPACE for now which
                                 I think creates no problems              */

/* define number addresses */
#define ONE           0x1369
#define TEN           ONE + 9
#define HUNDRED       TEN + 9
#define TENTHOUSAND   HUNDRED + 1


/* undefined extensions */
#define NUM_EXTENDED   64
#define EXTLAST  0x13bf       /* 5,055 */
#define QYAE (TENTHOUSAND + 4)   /*`qe */
#define KYAE  (QYAE + ROW + ROW) /*`ke */
#define XYAE  (KYAE + ROW + ROW) /* Xe */
#define GYAE  (XYAE + ROW + ROW) /*`ge */
#define MWAE  (QYAE + ROW)
#define BWAE  (MWAE + 1)
#define GYWAE (BWAE + 1)
#define FWAE (GYWAE + 1)
#define PWAE  (FWAE + 1)
#define CCAE  (GYAE + ROW + ROW)
#define SSAE  (CCAE + ROW + ROW)
#define CCHAE (SSAE + ROW + ROW)
#define ZZAE (CCHAE + ROW + ROW)

/* Private Use Additions */
#define PRIVATE_USE_BEGIN 0xe300    /* Change to 0xe000 later */
#define PRIVATE_USE_END   0xfdff    /* Change to 0xf8ff later */
#define NUM_SPECIAL       16
/* define glyph codes */
#define ORNAMENT          (PRIVATE_USE_END - 15)
#define FIDELLAND         (PRIVATE_USE_END - 14)
#define INVFIDELLAND      (PRIVATE_USE_END - 13)
#define AFRICA            (PRIVATE_USE_END - 12)
#define INVAFRICA         (PRIVATE_USE_END - 11)
/* define letter */
#define WWAE              (PRIVATE_USE_END - 10)  /* wWe */
/* define punctation */
#define GEMINATION        (PRIVATE_USE_END - 5)   /* stylized 0x0308    */
#define TEMHERTESLAQ      (PRIVATE_USE_END - 4)   /* stylized 0x00a1  ¡ */
#define NETEB             (PRIVATE_USE_END - 3)   /* stylized 0x002e  . */
#define LEFTQUOTE         (PRIVATE_USE_END - 2)   /* stylized 0x00ab << */
#define RIGHTQUOTE        (PRIVATE_USE_END - 1)   /* stylized 0x00bb >> */
#define EQUESTIONMARK      PRIVATE_USE_END        /* stylized 0x003f  ? */


#define UNITOTAL (UNISIZE+NUM_EXTENDED+NUM_SPECIAL) /* 462 */


#endif  /* FIDEL_H */
