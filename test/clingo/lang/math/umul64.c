#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   uint64_t res = 0;

   expect_c_( umul64_c( 2147483648, 4294967297, &res ) );
   expect_c_( res == 9223372039002259456ULL );

   // 18.446.744.073.709.551.616 > UINT64_MAX( 18.446.744.073.709.551.615 )
   expect_c_( not umul64_c( 4294967296, 4294967296, &res ) );
   expect_c_( res == 9223372039002259456ULL );

   return finish_tap_c_();
}
