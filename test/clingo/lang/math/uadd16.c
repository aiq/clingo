#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   uint16_t res = 0;

   expect_c_( uadd16_c( 32767, 12345, &res ) );
   expect_c_( res == 45112 );

   expect_c_( not uadd16_c( UINT16_MAX, 1, &res ) );
   expect_c_( res == 45112 );

   return finish_tap_c_();
}
