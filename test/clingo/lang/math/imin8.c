#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   expect_c_( imin8_c( 93, -67 ) == -67 );

   return finish_tap_c_();
}
