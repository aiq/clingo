#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

int main( void )
{
   init_tap_c_();

   cOrdinalDate od = ordinal_date_c( 1981, 95 );
   cDate res = from_ordinal_date_c( od );
   expect_at_c_( eq_date_c( res, date_c( 1981, c_Apr, 5 ) ) );

   return finish_tap_c_();
}
