#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   cChars chars = c_c( "James Bond" );
   expect_c_(  chars_starts_with_c_( chars, "James" ) );
   expect_c_( !chars_starts_with_c_( chars, "Bond" ) );

   expect_c_( !chars_starts_with_c_( chars, "james" ) );

   expect_c_(  chars_starts_with_c(  chars, chars ) );

   return finish_tap_c_();
}
