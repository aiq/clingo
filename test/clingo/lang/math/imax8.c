#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   expect_at_c_( imax8_c( 93, -67 ) == 93 );

   return finish_tap_c_();
}
