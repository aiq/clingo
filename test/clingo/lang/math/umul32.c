#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   uint32_t res = 0;

   expect_c_( umul32_c( 32769, 65536, &res ) );
   expect_c_( res == 2147549184 );

   // 4.294.967.296 > UINT32_MAX( 4.294.967.295 )
   expect_c_( not umul32_c( 65536, 65536, &res ) );
   expect_c_( res == 2147549184 );

   return finish_tap_c_();
}
