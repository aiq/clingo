#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   uint8_t res = 0;

   expect_at_c_( umul8_c( 12, 11, &res ) );
   expect_at_c_( res == 132 );

   // 256 > UINT8_MAX( 255 )
   expect_at_c_( not umul8_c( 16, 16, &res ) );
   expect_at_c_( res == 132 );

   return finish_tap_c_();
}
