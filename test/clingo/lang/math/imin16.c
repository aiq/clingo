#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   expect_at_c_( imin16_c( -23789, 17420 ) == -23789 );

   return finish_tap_c_();
}
