#include "clingo/lang/expect.h"
#include "clingo/time/cOrdinalDate.h"

int main( void )
{
   init_tap_c_();

   cOrdinalDate od = ordinal_date_c( 2014, 125 );
   cOrdinalDate before = ordinal_date_c( 2013, 256 );
   cOrdinalDate after = ordinal_date_c( 2014, 126 );

   expect_eq_c_( cmp_ordinal_date_c( od, od ) );
   expect_gt_c_( cmp_ordinal_date_c( od, before ) );
   expect_lt_c_( cmp_ordinal_date_c( od, after ) );

   return finish_tap_c_();
}
