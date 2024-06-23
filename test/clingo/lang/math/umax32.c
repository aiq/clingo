#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   expect_at_c_( umax32_c( 1234567890, 2147483647 ) == 2147483647 );

   return finish_tap_c_();
}
