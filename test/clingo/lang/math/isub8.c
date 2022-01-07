#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   int8_t res = 0;

   expect_c_( isub8_c( 63, 64, &res ) );
   expect_c_( res == -1 );

   expect_c_( isub8_c( 101, -26, &res ) );
   expect_c_( res == 127 );

   expect_c_( not isub8_c( INT8_MAX, -1, &res ) );
   expect_c_( res == 127 );

   expect_c_( not isub8_c( INT8_MIN, 1, &res ) );
   expect_c_( res == 127 );

   return finish_tap_c_();
}
