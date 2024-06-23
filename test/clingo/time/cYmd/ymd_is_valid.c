#include "clingo/lang/expect.h"
#include "clingo/time/cYmd.h"

int main( void )
{
   init_tap_c_();

   expect_at_c_(  ymd_is_valid_c( ymd_c( 2018, c_Jul,  8 ) ) );
   expect_at_c_( !ymd_is_valid_c( ymd_c( 2018, c_Dec+1,  8 ) ) );
   expect_at_c_( !ymd_is_valid_c( ymd_c( 1983, c_Dec, 64 ) ) );

   return finish_tap_c_();
}
