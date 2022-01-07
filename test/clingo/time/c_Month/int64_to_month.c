#include "clingo/lang/expect.h"
#include "clingo/time/c_Month.h"

int main( void )
{
   init_tap_c_();

   c_Month month;

   expect_c_( int64_to_month_c( 1, &month ) );
   expect_c_( month == c_Jan );

   expect_c_( int64_to_month_c( 10, &month ) );
   expect_c_( month == c_Oct );

   expect_c_( int64_to_month_c( 12, &month ) );
   expect_c_( month == c_Dec );

   expect_c_( !int64_to_month_c( 1000, &month ) );

   return finish_tap_c_();
}
