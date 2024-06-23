#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   int8_t res = 0;

   expect_at_c_( imul8_c( 9, 14, &res ) );
   expect_at_c_( res == 126 );

   expect_at_c_( imul8_c( -31, 4, &res ) );
   expect_at_c_( res == -124 );

   // 128 > INT8_MAX( 127 )
   expect_at_c_( not imul8_c( 16, 8, &res ) );
   expect_at_c_( res == -124 );

   // 132 < INT8_MIN( -128 )
   expect_at_c_( not imul8_c( -12, 11, &res ) );
   expect_at_c_( res == -124 );

   return finish_tap_c_();
}
