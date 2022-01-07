#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   expect_c_( imin32_c( 2111999555, -1234567890 ) == -1234567890 );

   return finish_tap_c_();
}
