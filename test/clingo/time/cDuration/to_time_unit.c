#include "clingo/lang/expect.h"
#include "clingo/time/cDuration.h"

int main( void )
{
   init_tap_c_();

   expect_at_c_( to_time_unit_c( 3, C_Min, C_Sec ) == 180 );
   expect_at_c_( to_time_unit_c( 62, C_Min, C_Hour ) == 1 );

   return finish_tap_c_();
}
