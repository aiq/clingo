#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   int64_t res = 0;

   expect_at_c_( imul64_c( 32768, 65536, &res ) );
   expect_at_c_( res == 2147483648 );

   expect_at_c_( imul64_c( -32769, 65536, &res ) );
   expect_at_c_( res == -2147549184 );

   // 9.223.372.036.854.775.808 > INT64_MAX( 9.223.372.036.854.775.807 )
   expect_at_c_( not imul64_c( 2147483648, 4294967296, &res ) );
   expect_at_c_( res == -2147549184 );

   // -9.223.372.039.002.259.456 < INT64_MIN( −9.223.372.036.854.775.808 )
   expect_at_c_( not imul64_c( -2147483648, 4294967297, &res ) );
   expect_at_c_( res == -2147549184 );

   return finish_tap_c_();
}
