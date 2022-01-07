#include "clingo/lang/expect.h"
#include "clingo/lang/func.h"

int main( void )
{
   init_tap_c_();

   expect_c_( is_sign_c_( '+' ) );
   expect_c_( not is_sign_c_( '~' ) );
   expect_c_( is_sign_c_( '-' ) );

   return finish_tap_c_();
}
