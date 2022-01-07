#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   uint32_t res = 0;

   expect_c_( uadd32_c( 2147483647, 1234567890, &res ) );
   expect_c_( res == 3382051537 );

   expect_c_( not uadd32_c( UINT32_MAX, 1, &res ) );
   expect_c_( res == 3382051537 );

   return finish_tap_c_();
}
