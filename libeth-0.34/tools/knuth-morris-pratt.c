
void 
preprocpat ( pat, next )
  char *pat;
  int next[];
{

int i, j;

  i = 0;
  j = next[0] = -1;
  do 
    { 
      if ( j==(-1) || pat[i]==pat[j] ) 
        {
            i++;
            j++;
            next[i] = (pat[j]==pat[i]) ? next[j] : j;
        }
      else j = next[j]; 
    }
  while ( pat[i] != EOS );
}


char 
*search ( pat, text )
  char *pat, *text;
{
int next[MAXPATLEN], j;

  if ( *pat == EOS )
    return( text );
  preprocpat( pat, next );

  for ( j=0; *text != EOS; ) 
    {
      if ( j==(-1) || pat[j] == *text )
        { 
          text++; j++; 
          if ( pat[j] == EOS )
            return( text-j );
        }
      else 
        j = next[j];
    }

  return( NULL );

}
