#include <stdio.h>
#include <libeth/fidel.h>
#include <libeth/etctype.h>
#include <libeth/etstdlib.h>
#include <libeth/sysinfo.h>


int 
main (argc,argv)
  int argc;
  char **argv;
{

FCHAR fch;
unsigned char * letter;
char * fchName;
int i,n;
int guess = 2;
LibEthFlags * mylflags;

if ( argc > 1 )
		guess = atoi ( argv[1] );

mylflags  =  SetDefaultLibEthFlags (NIL, NIL, NIL);


  for ( fch = HAE; fch <= TENTHOUSAND; fch++ )
    {
      if (! isethiopicdefined ( fch ) )
        {
          printf ( "0x%4X\t\t", fch );
          for ( i=0; i<guess; i++ )
            printf ( "\t" );
          printf ( "# <UNDEFINED>\n" );
          continue;
        }

        mylflags->tvOut = notv;
        mylflags->csOut = acuwork;
        mylflags->options = noOps;
        letter = fidel_sputc ( fch, mylflags );


        mylflags->tvOut = uname;
        mylflags->csOut = unicode;
        mylflags->options = uppercase;
        fchName = fidel_sputc ( fch, mylflags );

        printf ( "0x%4X\t", fch );

        if ( letter == NULL ) {
          for ( i=0; i<guess; i++ )
            printf ( "\t" );
        } else {
          n = strlen ( letter );

          for ( i=0; i<(n-1); i++ )
            printf ( "0x%02X ", letter[i] );

            printf ( "0x%02X", letter[i] );

          for ( i=0; i<guess-n; i++ )
            printf ( "\t" );
			
        }
        printf ( "\t# %s\n", fchName );

        free ( letter );
        free ( fchName );
    } 

  exit (0);

}
