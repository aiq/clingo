#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   int16_t res = 0;

   expect_c_( imul16_c( 127, 127, &res ) );
   expect_c_( res == 16129 );

   expect_c_( imul16_c( -248, 127, &res ) );
   expect_c_( res == -31496 );

   // 32.768 > INT16_MAX( 32.767 )
   expect_c_( not imul16_c( 256, 128, &res ) );
   expect_c_( res == -31496 );

   // -32.896 < INT16_MIN( -32.768 )
   expect_c_( not imul16_c( 257, -128, &res ) );
   expect_c_( res == -31496 );

   return finish_tap_c_();
}
