#include <stdio.h>
#include <stdlib.h>

char * lccs ( char* a, char* b );


#ifdef TEST

void
main (argc, argv)
  int argc;
  char **argv;
{

  if ( argc < 3 )
    {
      fprintf ( stderr, "\aTwo Strings Required!\n" );
      exit (1);
    }

  fprintf (stdout, "%s", lccs ( argv[1], argv[2] ) );
  exit (0);

}


#endif /* TEST */



/*
 *  Finds the longest common substring between to strings.
 *  If two or more substrings of equal length are found only
 *  the first will  be returned.  Substrings of unitary length
 *  are not returned.
 */


char *
lccs ( a, b )
	char* a;
	char* b;
{

register int i,j,k;
int xi, xj, length;
int maxXi = 0, maxLength = 0;
char* returnString;
int m = strlen ( a );
int n = strlen ( b );
char *x, *y;


  x = a;
  y = b;


  if ( m > n )  /* To minimize the test cycles we want x to be the smaller string */
    {
      x = b;
      y = a;
      i = m;
      m = n;
      n = i;
    }



  for ( k = 0; k < n; k++ )
    {
      /*  Break if we found a substring longer than our remaining string length  */
      if ( maxLength >= (m - k) )
        break;

      /*  Initialize this cycle  */
      j = k;
      xi = xj = 0;
      length = 0;


      for ( i = 0; i < m; i++ )
        if ( x[i] == y[j] )
          {
            if ( length == 0 )  /* save value of start of match */
              {
                xi = i;
                xj = j;
              }
            length++;
            j++;
          }
        else if ( length )
          break;

      if ( length > maxLength )
        {
          maxLength = length;
          maxXi = xi;
          j = k;
        }
    }


  if ( maxLength > 1 )
    {
      returnString = (char *) malloc ( (maxLength + 1) * sizeof (char) );
      strncpy ( returnString, &x[maxXi], maxLength );
      return ( returnString );
    }


  return ( NULL );

}
