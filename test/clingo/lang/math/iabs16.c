#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   int16_t res = 0;

   expect_at_c_( iabs16_c( -23789, &res ) );
   expect_at_c_( res == 23789 );

   expect_at_c_( iabs16_c( 17420, &res ) );
   expect_at_c_( res == 17420 );

   expect_at_c_( not iabs16_c( INT16_MIN, &res ) );
   expect_at_c_( res == 17420 );

   return finish_tap_c_();
}
