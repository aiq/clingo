#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   uint32_t res = 0;

   expect_c_( usub32_c( 2147483647, 1234567890, &res ) );
   expect_c_( res == 912915757 );

   expect_c_( not usub32_c( 0, 1, &res ) );
   expect_c_( res == 912915757 );

   return finish_tap_c_();
}
