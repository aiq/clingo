#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   int32_t res = 0;

   expect_at_c_( iabs32_c( -1234567890, &res ) );
   expect_at_c_( res == 1234567890 );

   expect_at_c_( iabs32_c( 2111999555, &res ) );
   expect_at_c_( res == 2111999555 );

   expect_at_c_( not iabs32_c( INT32_MIN, &res ) );
   expect_at_c_( res == 2111999555 );

   return finish_tap_c_();
}
