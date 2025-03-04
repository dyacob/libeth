#include <stdio.h>
#include <libeth/fidel.h>
#include <libeth/etstdlib.h>
#include <libeth/etstdio.h>
#include <libeth/exports.h>

int 
main (argc,argv)
  int argc;
  char **argv;
{

int i,j;
LibEthFlags* lethFlags;
unsigned int outHash[256];
LETCHAR* OutFidel;


lethFlags  =  SetDefaultLibEthFlags (NIL, NIL, NIL);
lethFlags->csOut = sera;

OutFidel = WazemaFidel;

  for ( i=0x20; i <= 0xff; i++ )
    {
      outHash[i] = j = 0;

      while ( j < UNITOTAL && !(i == OutFidel[j].fidel[0] && OutFidel[j].vowel == NOCH && OutFidel[j].set == SET0) )
        while ( ++j < UNITOTAL && OutFidel[j].fidel == NOCH );

      if ( j == UNITOTAL )
        continue;

      if ( outHash[i] == 0 )
        outHash[i] = j + UNIFIDEL;
    } 

  printf ("int WazemaA1HashTable[224] = {\n");

  for ( i=0x20; i <= 0xff; i++ )  
   {
     printf ("\n/* ");
     for (j = i; j < i+16; j++ )
       if ( 0x80 <= j && j <= 0xa0 )
         printf ("   0x%x,",j);
       else
         printf ("      %c,",j);
     printf (" */\n   ");

     for (j = i; j < i+16; j++ )
       printf (" 0x%04x,", outHash[j]);
     printf ("\n");

     i+= 15;
   }

  printf ("\n};\n");

  for ( i=0x20; i <= 0xff; i++ )  
   {
     printf ("%02x = ", i);
     if (outHash[i])
       fidel_putc (outHash[i], lethFlags);
     else
     printf ("0");
     printf ("\n");
   }
  
  exit (0);

}
