#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   int16_t res = 0;

   expect_at_c_( isub16_c( 16789, 12345, &res ) );
   expect_at_c_( res == 4444 );

   expect_at_c_( isub16_c( 25491, -5491, &res ) );
   expect_at_c_( res == 30982 );

   expect_at_c_( not isub16_c( INT16_MAX, -1, &res ) );
   expect_at_c_( res == 30982 );

   expect_at_c_( not isub16_c( INT16_MIN, 1, &res ) );
   expect_at_c_( res == 30982 );

   return finish_tap_c_();
}
