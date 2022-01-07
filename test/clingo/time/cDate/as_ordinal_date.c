#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

int main( void )
{
   init_tap_c_();

   cDate date = date_c( 1981, c_Apr, 5 );
   cOrdinalDate res = as_ordinal_date_c( date );
   expect_eq_c_( cmp_ordinal_date_c( res, ordinal_date_c( 1981, 95 ) ) );

   return finish_tap_c_();
}
