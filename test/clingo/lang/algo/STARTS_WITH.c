#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h" // chars_starts_with_c

int main( void )
{
   init_tap_c_();

   cChars chars = c_c( "James Bond" );
   expect_at_c_(  chars_starts_with_c_( chars, "James" ) );
   expect_at_c_( !chars_starts_with_c_( chars, "Bond" ) );

   expect_at_c_( !chars_starts_with_c_( chars, "james" ) );

   expect_at_c_(  chars_starts_with_c(  chars, chars ) );

   return finish_tap_c_();
}
