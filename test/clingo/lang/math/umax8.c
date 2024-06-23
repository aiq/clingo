#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   expect_at_c_( umax8_c( 37, 213 ) == 213 );

   return finish_tap_c_();
}
