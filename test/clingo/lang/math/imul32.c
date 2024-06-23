#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   int32_t res = 0;

   expect_at_c_( imul32_c( 32767, 65535, &res ) );
   expect_at_c_( res == 2147385345 );

   expect_at_c_( imul32_c( 32768, -65536, &res ) );
   expect_at_c_( res == -2147483648 );

   // 2.147.483.648 > INT32_MAX( 2.147.483.647 )
   expect_at_c_( not imul32_c( 32768, 65536, &res ) );
   expect_at_c_( res == -2147483648 );

   // -2.147.549.184 < INT32_MIN( -2.147.483.648 )
   expect_at_c_( not imul32_c( -32769, 65536, &res ) );
   expect_at_c_( res == -2147483648 );

   return finish_tap_c_();
}
