#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   expect_at_c_( umin16_c( 32767, 12345 ) == 12345 );

   return finish_tap_c_();
}
