#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   int32_t res = 0;

   expect_c_( isub32_c( 65535, 123456789, &res ) );
   expect_c_( res == -123391254 );

   expect_c_( isub32_c( -16156565, 546648, &res ) );
   expect_c_( res == -16703213 );

   expect_c_( not isub32_c( INT32_MAX, -1, &res ) );
   expect_c_( res == -16703213 );

   expect_c_( not isub32_c( INT32_MIN, 1, &res ) );
   expect_c_( res == -16703213 );

   return finish_tap_c_();
}
