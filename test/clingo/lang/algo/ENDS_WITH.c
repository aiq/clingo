#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h" // chars_ends_with_c

int main( void )
{
   init_tap_c_();

   cChars chars = c_c( "James Bond" );
   expect_at_c_(  chars_ends_with_c_( chars, "Bond" ) );
   expect_at_c_( !chars_ends_with_c_( chars, "James" ) );

   expect_at_c_( !chars_ends_with_c_( chars, "bond" ) );

   expect_at_c_(  chars_ends_with_c(  chars, chars ) );

   return finish_tap_c_();
}
