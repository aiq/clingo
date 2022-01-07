#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   expect_c_( umax16_c( 32767, 12345 ) == 32767 );

   return finish_tap_c_();
}
