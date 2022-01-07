#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main()
{
   init_tap_c_();

   CString* s = str_c( "Pineapple" );

   cChars apple = right_string_c( s, 5 );
   expect_c_( chars_is_c( apple, "apple" ) );

   cChars pineapple = right_string_c( s, 9 );
   expect_c_( chars_is_c( pineapple, "Pineapple" ) );

   pineapple = right_string_c( s, 1024 );
   expect_c_( chars_is_c( pineapple, "Pineapple" ) );

   cChars empty = right_string_c( s, 0 );
   expect_c_( is_empty_c_( empty ) );

   release_c( s );

   return finish_tap_c_();
}
