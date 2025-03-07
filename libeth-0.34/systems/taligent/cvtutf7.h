/* ================================================================ */
/*
File:   ConvertUTF7.h
Author: David B. Goldsmith
Copyright (C) 1994 Taligent, Inc. All rights reserved.

This code is copyrighted. Under the copyright laws, this code may not
be copied, in whole or part, without prior written consent of Taligent. 

Taligent grants the right to use this code as long as this ENTIRE
copyright notice is reproduced in the code.  The code is provided
AS-IS, AND TALIGENT DISCLAIMS ALL WARRANTIES, EITHER EXPRESS OR
IMPLIED, INCLUDING, BUT NOT LIMITED TO IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT
WILL TALIGENT BE LIABLE FOR ANY DAMAGES WHATSOEVER (INCLUDING,
WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS
INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY
LOSS) ARISING OUT OF THE USE OR INABILITY TO USE THIS CODE, EVEN
IF TALIGENT HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
BECAUSE SOME STATES DO NOT ALLOW THE EXCLUSION OR LIMITATION OF
LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES, THE ABOVE
LIMITATION MAY NOT APPLY TO YOU.

RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the
government is subject to restrictions as set forth in subparagraph
(c)(l)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 252.227-7013 and FAR 52.227-19.

This code may be protected by one or more U.S. and International
Patents.

TRADEMARKS: Taligent and the Taligent Design Mark are registered
trademarks of Taligent, Inc.
*/
/* ================================================================ */

/* ================================================================ */
/*      The following definitions are compiler-specific.
        I would use wchar_t for UCS2/UTF16, except that the C standard
        does not guarantee that it has at least 16 bits, so wchar_t is
        no more portable than unsigned short!
*/

/* typedef unsigned short  UCS2; */

/* ================================================================ */
/*      Each of these routines converts the text between *sourceStart and 
sourceEnd, putting the result into the buffer between *targetStart and
targetEnd. Note: the end pointers are *after* the last item: e.g. 
*(sourceEnd - 1) is the last item.

        The return result indicates whether the conversion was successful,
and if not, whether the problem was in the source or target buffers.

        After the conversion, *sourceStart and *targetStart are both
updated to point to the end of last text successfully converted in
the respective buffers.

		In ConvertUCS2toUTF7, optional indicates whether UTF-7 optional
characters should be directly encoded, and verbose controls whether the
shift-out character, "-", is always emitted at the end of a shifted
sequence.
*/
/*
typedef enum {
        ok,                             // conversion successful //
        sourceCorrupt,          // source contains invalid UTF-7 //
        targetExhausted         // insuff. room in target for conversion //
} ConversionResult;
*/
ConversionResult	ConvertUCS2toUTF7 (
                UCS2** sourceStart, UCS2* sourceEnd, 
                UTF7** targetStart, UTF7* targetEnd,
                int optional, int verbose);

ConversionResult	ConvertUTF7toUCS2 (
                UTF7** sourceStart, UTF7* sourceEnd, 
                UCS2** targetStart, UCS2* targetEnd);

UCS2*	LibEthConvertUTF7toUCS2 ();

/* ================================================================ */
