#include <stdio.h>
#include <libeth/libeth.h>

int
main ( argc, argv )
  int argc;
  char **argv;
{
LibEthFlags* lethFlags;
FCHAR *uniString, *simpleString;
unsigned char *string, testString[] = "`alem`SeHey";
int* changeList=NULL;


  lethFlags = SetDefaultLibEthFlags (NIL, LETLANGMINOR, NIL);

  if (argc > 1)
    string = argv[1];
  else
    string = testString;


  sget_fstring (&uniString, string, lethFlags);
  printf (" Original: ");
  fidel_puts (uniString, lethFlags);
  puts (" ");
  sget_fstring (&uniString, string, lethFlags);
  simpleString = fidel_simplify (uniString, LETHC_PHONETIC, amh, changeList);
  printf (" PHONETIC: ");
  fidel_puts (simpleString, lethFlags);
  puts (" ");
  printf (" |   HEHA: ");
  simpleString = fidel_simplify (uniString, LETHC_PHONETIC | LETHC_HEHA, amh, changeList);
  fidel_puts (simpleString, lethFlags);
  puts (" ");
  printf (" |     EA: ");
  simpleString = fidel_simplify (uniString, LETHC_PHONETIC | LETHC_HEHA | LETHC_EA, amh, changeList);
  fidel_puts (simpleString, lethFlags);
  puts (" ");
  simpleString = fidel_simplify (uniString, LETHC_PHONETIC | LETHC_HEHA | LETHC_EA | LETHC_GOKOQO, amh, changeList);
  printf (" | GOKOQO: ");
  fidel_puts (simpleString, lethFlags);
  puts (" ");
  simpleString = fidel_simplify (uniString, LETHC_PHONETIC | LETHC_HEHA | LETHC_EA | LETHC_GUKUQU, amh, changeList);
  printf (" | GUKUQU: ");
  fidel_puts (simpleString, lethFlags);
  puts (" ");
  simpleString = fidel_simplify (uniString, LETHC_PHONETIC | LETHC_HEHA | LETHC_EA | LETHC_FAMILY, amh, changeList);
  printf (" | FAMILY: ");
  fidel_puts (simpleString, lethFlags);
  puts (" ");

  simpleString = fidel_simplify (uniString, LETHC_WAdown, amh, changeList);
  printf ("   WAdown: ");
  fidel_puts (simpleString, lethFlags);
  puts (" ");

  simpleString = fidel_simplify (uniString, LETHC_WAup, amh, changeList);
  printf ("     WAup: ");
  fidel_puts (simpleString, lethFlags);
  puts (" ");

  if (changeList != NULL)
    free (changeList);
  free (simpleString);
  free (uniString);

  exit (0);
}
