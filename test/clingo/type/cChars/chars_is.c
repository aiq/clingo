#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   cChars chars = c_c( "clingo" );

   expect_at_c_(  chars_is_c( chars, "clingo" ) );
   expect_at_c_( !chars_is_c( chars, "Clingo" ) );

   return finish_tap_c_();
}
