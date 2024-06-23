#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   expect_at_c_( min_c_( 2.0, 3 ) == 2.0 );
   expect_at_c_( min_c_( 3.0, 2 ) == 2 );
   expect_at_c_( min_c_( NAN, 100 ) == 100 );

   return finish_tap_c_();
}
