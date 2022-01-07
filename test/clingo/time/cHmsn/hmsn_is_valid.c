#include "clingo/lang/expect.h"
#include "clingo/time/cHmsn.h"

int main( void )
{
   init_tap_c_();

   expect_c_(  hmsn_is_valid_c( hms_c( 1, 20, 0 ) ) );
   expect_c_( !hmsn_is_valid_c( hms_c( 1, 65, 9 ) ) );
   expect_c_(  hmsn_is_valid_c( hmsn_c( 0, 15, 9, 5 ) ) );

   return finish_tap_c_();
}
