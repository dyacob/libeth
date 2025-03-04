#include <stdio.h>
#include <libeth/libeth.h>

int
main ( argc, argv )
  int argc;
  char **argv;
{
LibEthFlags* lethFlags;
FCHAR *uniString, *uniCh, *uniFound, fch;
unsigned char *string, testString[] = "leqwanWaqWa";
int* changeList=NULL;


  lethFlags = SetDefaultLibEthFlags (NIL, LETLANGMINOR, NIL);

  if (argc > 1)
    string = argv[1];
  else
    string = testString;


  sget_fstring (&uniCh, "qWa", lethFlags);
  sget_fstring (&uniString, string, lethFlags);


  printf ("Looking for ");
  fidel_puts (uniCh, lethFlags);
  printf (" in ");
  fidel_puts (uniString, lethFlags);
  printf (":\n");

  printf ("  strchr(");
  uniFound = fidel_strchr (uniString, uniCh[0]);
  if (uniFound != NULL)
    fidel_puts (uniFound, lethFlags);
  printf(") [");
  uniFound = fidel_syllabic_strchr (uniString, uniCh[0], amh, LETHC_WAdown);
  fidel_puts (uniFound, lethFlags);
  printf ("]\n");

  printf ("  strrchr(");
  uniFound = fidel_strrchr (uniString, uniCh[0]);
  if (uniFound != NULL)
    fidel_puts (uniFound, lethFlags);
  printf(") [");
  uniFound = fidel_syllabic_strrchr (uniString, uniCh[0], amh, LETHC_WAdown);
  fidel_puts (uniFound, lethFlags);
  printf ("]\n");

  printf ("  memchr(");
  uniFound = fidel_memchr (uniString, uniCh[0], 6);
  if (uniFound != NULL)
    fidel_puts (uniFound, lethFlags);
  printf(") [");
  uniFound = fidel_syllabic_memchr (uniString, uniCh[0], 6, amh, LETHC_WAdown);
  fidel_puts (uniFound, lethFlags);
  printf ("]\n");

  if (changeList != NULL)
    free (changeList);
  free (uniCh);
  free (uniString);

  sget_fstring (&uniCh, "`sWaHWan", lethFlags);
  sget_fstring (&uniString, string, lethFlags);

  printf ("StrCmp = %i\n", fidel_syllabic_fstrcmp (uniString, uniCh, amh, LETHC_WAdown | LETHC_PHONETIC) );
  printf ("StrNCmp = %i\n", fidel_syllabic_fstrncmp (uniString, uniCh, 3, amh, LETHC_WAdown | LETHC_PHONETIC) );

  exit (0);
}
