char
*search ( pat, text, n )
  char *pat, *text;
  int n;
{
int i, j, k, m, skip[MAXCHAR];  /* MAXCHAR = 256 */

  m = strlen(pat);
  if ( m==0 )
    return( text );
  for ( k=0; k<MAXCHAR; k++ )
    skip[k] = m;
  for ( k=0; k<m-1; k++ )
    skip[pat[k]] = m-k-1;

  for ( k=m-1; k < n; k += skip[text[k] & (MAXCHAR-1)] )
    {
       for ( j=m-1, i=k; j>=0 && text[i] == pat[j]; j-- ) 
         i--;
       if ( j == (-1) )
         return( text+i+1 );
    }
  return( NULL );
}
