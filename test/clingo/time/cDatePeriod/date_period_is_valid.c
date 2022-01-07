#include "clingo/lang/expect.h"
#include "clingo/time/cDatePeriod.h"

int main( void )
{
   init_tap_c_();

   cDatePeriod period = date_period_c( date_c( 2014, 3, 3 ),
                                       date_c( 2014, 3, 9 ) );
   expect_c_( date_period_is_valid_c( period ) );

   cDatePeriod invalid = date_period_c( null_date_c(),
                                        date_c( 2014, 3, 6 ) );
   expect_c_( not date_period_is_valid_c( invalid ) );

   return finish_tap_c_();
}
