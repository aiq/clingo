#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   expect_at_c_( umin8_c( 37, 213 ) == 37 );

   return finish_tap_c_();
}
