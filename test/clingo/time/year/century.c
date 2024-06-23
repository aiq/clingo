#include "clingo/lang/expect.h"
#include "clingo/time/year.h"

int main( void )
{
   init_tap_c_();

   expect_at_c_( century_c( 1492 ) == 14 );
   expect_at_c_( century_c( 2021 ) == 20 );

   return finish_tap_c_();
}
