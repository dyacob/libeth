#include <stdio.h>
#include <libeth/libeth.h>

int
main ()
{
LibEthFlags* lethFlags;
FCHAR* uniString;


  lethFlags = SetDefaultLibEthFlags (NIL, LETLANGMINOR, NIL);

  sget_fstring (&uniString, "IgziabHEr", lethFlags);
  if ( isRedWord (uniString, lethFlags) )
    fprintf (stdout, "IgziabHEr:  Yes!\n");

  sget_fstring (&uniString, "none", lethFlags);
  if ( isRedWord (uniString, lethFlags) )
    fprintf (stdout, "none:  Yes!\n");

  sget_fstring (&uniString, "yesus : kristos", lethFlags);
  if ( isRedWord (uniString, lethFlags) )
    fprintf (stdout, "yesus kristos:  Yes!\n");

  sget_fstring (&uniString, "kristos", lethFlags);
  if ( isRedWord (uniString, lethFlags) )
    fprintf (stdout, "kristos:  Yes!\n");

  exit (0);
}
