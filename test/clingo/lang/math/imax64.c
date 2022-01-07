#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   expect_c_( imax64_c( -98765432101, 123123123123 ) == 123123123123 );

   return finish_tap_c_();
}
