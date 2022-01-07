#include "clingo/lang/expect.h"
#include "clingo/time/year.h"

int main( void )
{
   init_tap_c_();

   expect_c_( year_in_century_c( 1492 ) == 92 );
   expect_c_( year_in_century_c( 2021 ) == 21 );

   return finish_tap_c_();
}
