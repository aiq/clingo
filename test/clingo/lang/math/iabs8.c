#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   int8_t res = 0;

   expect_at_c_( iabs8_c( -67, &res ) );
   expect_at_c_( res == 67 );

   expect_at_c_( iabs8_c( 93, &res ) );
   expect_at_c_( res == 93 );

   expect_at_c_( not iabs8_c( INT8_MIN, &res ) );
   expect_at_c_( res == 93 );

   return finish_tap_c_();
}
