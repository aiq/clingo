#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   uint8_t res = 0;

   expect_at_c_( uadd8_c( 213, 37, &res ) );
   expect_at_c_( res == 250 );

   expect_at_c_( not uadd8_c( UINT8_MAX, 1, &res ) );
   expect_at_c_( res == 250 );

   return finish_tap_c_();
}
