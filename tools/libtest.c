
#include "etstdlib.h"
#include "etstdio.h"
#include "etmath.h"

int
main()
{
FCHAR fch, *target, *newTarget, FString[81];
char number[12], text[WSIZE];
int i, num;

/*---------------------Required Init--------------------------------------
**
**  maybe an init flags routine should be part of libeth??
**/
#define DEFLANG  tir 
extern LS LnS[];
LS* default_lang =& LnS[DEFLANG];

LibEthFlags* lethFlags;

lethFlags =  SetDefaultLibEthFlags (NIL, LETLANGMINOR, NIL);

/*------------------------------------------------------------------------*/


/**
*  Verified!
* 
   printf ("Test fidel_fget with pointer:\n");
   target = (FCHAR *) malloc (80*sizeof(FCHAR));
   newTarget = fidel_gets ( target, lethFlags );
   fidel_fputs ( target, stdout, lethFlags );
   fidel_fputs ( newTarget, stdout, lethFlags );

   printf ("Test fidel_fget with array:\n");
   newTarget = fidel_gets ( FString, lethFlags );
   fidel_fputs ( FString, stdout, lethFlags );
   fidel_fputs ( newTarget, stdout, lethFlags );
   free (target);
*/


/**
*  Verified!
*
* sget_fstring ( &target, "`100`80`7", lethFlags ); 
* fidel_fputs ( target, stdout, lethFlags );
* num = ftoi ( target );
* fprintf (stdout, "\nNum = %d\n", num);
* sget_fstring ( &target, "`10000`900`80`7", lethFlags ); 
* fidel_fputs ( target, stdout, lethFlags );
* num = ftoi ( target );
* fprintf (stdout, "\nNum = %d\n", num);
*/

printf ("\n");
strcpy ( number, "1" );
target = arabtof ( number );
fidel_fputs ( target, stdout, lethFlags );

printf ("\n");
strcpy ( number, "12" );
target = arabtof ( number );
fidel_fputs ( target, stdout, lethFlags );

printf ("\n");
strcpy ( number, "123" );
target = arabtof ( number );
fidel_fputs ( target, stdout, lethFlags );

printf ("\n");
strcpy ( number, "1,234" );
target = arabtof ( number );
fidel_fputs ( target, stdout, lethFlags );

free (target);
printf ("\n");
strcpy ( number, "54321" );
target = arabtof ( number );
fidel_fputs ( target, stdout, lethFlags );

free (target);
printf ("\n");
strcpy ( number, "123456" );
target = arabtof ( number );
fidel_fputs ( target, stdout, lethFlags );

/* int get_formNumber ( FCHAR fchar ); */

exit (0);
}
