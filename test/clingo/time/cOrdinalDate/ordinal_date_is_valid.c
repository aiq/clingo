#include "clingo/lang/expect.h"
#include "clingo/time/cOrdinalDate.h"

int main( void )
{
   init_tap_c_();

   expect_at_c_(  ordinal_date_is_valid_c( ordinal_date_c( 2014, 365 ) ) );
   expect_at_c_( !ordinal_date_is_valid_c( ordinal_date_c( 2014, 366 ) ) );

   expect_at_c_(  ordinal_date_is_valid_c( ordinal_date_c( 2012, 366 ) ) );
   expect_at_c_( !ordinal_date_is_valid_c( ordinal_date_c( 2012, 367 ) ) );

   return finish_tap_c_();
}
