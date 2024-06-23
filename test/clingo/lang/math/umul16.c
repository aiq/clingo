#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   uint16_t res = 0;

   expect_at_c_( umul16_c( 257, 128, &res ) );
   expect_at_c_( res == 32896 );

   // 65.536 > UINT16_MAX( 65.535 )
   expect_at_c_( not umul16_c( 256, 256, &res ) );
   expect_at_c_( res == 32896 );

   return finish_tap_c_();
}
