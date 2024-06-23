#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   int8_t res = 0;

   expect_at_c_( iadd8_c( 63, 64, &res ) );
   expect_at_c_( res == 127 );

   expect_at_c_( iadd8_c( 127, -26, &res ) );
   expect_at_c_( res == 101 );

   expect_at_c_( not iadd8_c( INT8_MAX, 1, &res ) );
   expect_at_c_( res == 101 );

   expect_at_c_( not iadd8_c( INT8_MIN, -1, &res ) );
   expect_at_c_( res == 101 );

   return finish_tap_c_();
}
