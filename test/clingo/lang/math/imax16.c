#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   expect_c_( imax16_c( -23789, 17420 ) == 17420 );

   return finish_tap_c_();
}
