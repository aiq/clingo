#include "clingo/lang/expect.h"
#include "clingo/lang/func.h"

int main( void )
{
   init_tap_c_();

   expect_c_( '+' == sign_c_( 100 ) );
   expect_c_( '+' == sign_c_( 0 ) );
   expect_c_( '-' == sign_c_( -100 ) );

   return finish_tap_c_();
}
