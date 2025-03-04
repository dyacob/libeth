
normalize, catch form
reject bogus chars and forms (return 0)


int
get_fidelNumber ( fch )
{
FCHAR fch;
char formNumber, mod, order;
int fidelValue;


  formNumber = fch%8;
  fch -= formNumber;

  if ( (formNumber > SABI)
       || (fch == SHAE)
       || (fch == QXAE)
       || (fch == VAE)
       || (fch == CAE)
       || (fch == NYAE)
       || (fch == KHAE)
       || (fch == ZHAE)
       || (fch == DHAE)
       || (fch == JAE)
       || (fch == GGAE)
       || (fch == CHAE)
     )
    return ( 0 );

  fch -= UNIFIDEL;
  fch /= 8;


  if ( fch > SHAE )
    fch -= 1;
  if ( fch > QXAE )
    fch -= 1;
  if ( fch > VAE )
    fch -= 1;
  if ( fch > CAE )
    fch -= 1;
  if ( fch > NYAE )
    fch -= 1;
  if ( fch > KHAE )
    fch -= 1;
  if ( fch > ZHAE )
    fch -= 1;
  if ( fch > DHAE )
    fch -= 1;
  if ( fch > JAE )
    fch -= 1;
  if ( fch > GGAE )
    fch -= 1;
  if ( fch > CHAE )
    fch -= 1;


  order = fch/10;
  mod   = fch%10;

  fidelValue = ( pow (10, (int)order) * mod ) * formNumber;

  return ( fidelValue );
}
