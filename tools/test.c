#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void
main()
{
char* string;
char Line[] = "hi:yonas bye|bye";

 /* 
  *  strlen:  if no chars found
  *       0:  if first char is in accept list
  */
  printf ( "%i chars\n", strcspn("abcdfghjk","aeiou") );
 /*
  *       0:  if no chars found
  *       0:  if first char is not in reject list
  */
  printf ( "%i chars\n", strspn("bacdfghjk","aeiou") );
  printf ( "%i chars\n", strspn("bcdfghjk","aeiou") );

  printf ("%s", string = strtok (Line, ": |") );
  while ( (string = strtok (NULL, ": |")) != NULL )
    printf ("-%s", string);
  printf("\n");
}
