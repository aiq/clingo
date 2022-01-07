#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   uint8_t res = 0;

   expect_c_( usub8_c( 213, 37, &res ) );
   expect_c_( res == 176 );

   expect_c_( not usub8_c( 10, 11, &res ) );
   expect_c_( res == 176 );

   return finish_tap_c_();
}
