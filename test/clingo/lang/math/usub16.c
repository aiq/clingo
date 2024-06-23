#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   uint16_t res = 0;

   expect_at_c_( usub16_c( 45112, 12345, &res ) );
   expect_at_c_( res == 32767 );

   expect_at_c_( not usub16_c( 127, 128, &res ) );
   expect_at_c_( res == 32767 );

   return finish_tap_c_();
}
