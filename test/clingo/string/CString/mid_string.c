#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main()
{
   init_tap_c_();

   CString* s = lit_c( "Pineapple" );

   cChars pineapple = mid_string_c( s, 0 );
   expect_at_c_( chars_is_c( pineapple, "Pineapple" ) );

   cChars apple = mid_string_c( s, 4 );
   expect_at_c_( chars_is_c( apple, "apple" ) );

   cChars empty = mid_string_c( s, 1024 ); // to high value
   expect_at_c_( is_empty_c_( empty ) );

   release_c( s );

   return finish_tap_c_();
}
