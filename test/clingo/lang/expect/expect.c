#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   expect_c_( true );
   expect_c_( 12 == 12 );
   expect_c_( not false );

   return finish_tap_c_();
}
