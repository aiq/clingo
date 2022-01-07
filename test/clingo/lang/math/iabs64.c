#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   int64_t res = 0;

   expect_c_( iabs64_c( -98765432101, &res ) );
   expect_c_( res == 98765432101 );

   expect_c_( iabs64_c( 123123123123, &res ) );
   expect_c_( res == 123123123123 );

   expect_c_( not iabs64_c( INT64_MIN, &res ) );
   expect_c_( res == 123123123123 );

   return finish_tap_c_();
}
