#include <stdio.h>
#include <libeth/libeth.h>

int
main ( argc, argv )
  int argc;
  char **argv;
{
LibEthFlags* lethFlags;
FCHAR *uniString, *uniChs, *uniFound, *uniNeedle, fch;
unsigned char *string, testString[] = "hele`alemayehu";
int* changeList=NULL, i;
FCHAR *fstring, *target, *ftarget;


  lethFlags = SetDefaultLibEthFlags (NIL, LETLANGMINOR, NIL);

  if (argc > 1)
    string = argv[1];
  else
    string = testString;


  sget_fstring (&uniChs, "lobo`1:", lethFlags);
  sget_fstring (&uniNeedle, "alem", lethFlags);
  sget_fstring (&uniString, string, lethFlags);


  printf ("Looking for ");
  fidel_puts (uniChs, lethFlags);
  printf (" in ");
  fidel_puts (uniString, lethFlags);
  printf (":\n");

  printf ("  strstr(");
  uniFound = fidel_syllabic_strstr (uniString, uniNeedle, amh, LETHC_PHONETIC);
  if (uniFound != NULL)
    fidel_puts (uniFound, lethFlags);
  printf (")\n");

  printf ("  strcspn(");
  i = fidel_syllabic_strcspn (uniString, uniChs, amh, LETHC_PHONETIC);
  printf("%i)\n", i);

  printf ("  strpbrk(");
  uniFound = fidel_syllabic_strpbrk (uniString, uniChs, amh, LETHC_PHONETIC);
  if (uniFound != NULL)
    fidel_puts (uniFound, lethFlags);
  printf(")\n");

  printf ("  strspn(");
  i = fidel_syllabic_strspn (uniString, uniChs, amh, LETHC_PHONETIC);
  printf("%i)\n", i);

  if (changeList != NULL)
    free (changeList);
  free (uniChs);
  free (uniString);

  sget_fstring (&uniChs, ":  :|:", lethFlags);
  sget_fstring (&uniString, "selam : yonas caw:|:dan'El", lethFlags);

  i=0;
  uniFound = fidel_syllabic_strtok (uniString, uniChs, amh, LETHC_PHONETIC);
  printf ("%i: ", i++);
  fidel_puts (uniFound, lethFlags);
      printf("\n");
  while ( (uniFound = fidel_syllabic_strtok (NULL, uniChs, amh, LETHC_PHONETIC)) != NULL )
    {
      printf ("%i: ", i++);
      fidel_puts (uniFound, lethFlags);
      printf("\n");
    }


  target = (FCHAR *) malloc (20*sizeof(FCHAR));
  sget_fstring (&fstring, "`alem", lethFlags);
  sget_fstring (&ftarget, "welb", lethFlags);
  fidel_strcpy (target, ftarget);

  uniFound = fidel_strcat (target, fstring);
  printf ("\nfirst : ");
  fidel_puts (target, lethFlags);
  printf ("\nsecond : ");
  fidel_puts (uniFound, lethFlags);
  printf ("\nthird : ");
  uniFound = fidel_strncat (target, target, 3);
  fidel_puts (uniFound, lethFlags);
  printf ("\n");

  exit (0);
}
