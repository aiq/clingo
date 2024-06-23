#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main( void )
{
   init_tap_c_();

   CString* s = lit_c( "Pineapple" );

   cChars app = sub_string_c( s, 4, 7 );
   expect_at_c_( chars_is_c( app, "app" ) );

   cChars apple = sub_string_c( s, 4, 9 );
   expect_at_c_( chars_is_c( apple, "apple" ) );

   cChars neap = sub_string_c( s, 2, 6 );
   expect_at_c_( chars_is_c( neap, "neap" ) );

   cChars empty = sub_string_c( s, 5, 16 );
   expect_at_c_( is_empty_c_( empty ) );

   release_c( s );

   return finish_tap_c_();
}
