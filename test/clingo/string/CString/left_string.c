#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main( void )
{
   init_tap_c_();

   CString* s = lit_c( "Pineapple" );

   cChars pine = left_string_c( s, 4 );
   expect_at_c_( chars_is_c( pine, "Pine" ) );

   cChars pineapple = left_string_c( s, 9 );
   expect_at_c_( chars_is_c( pineapple, "Pineapple" ) );

   pineapple = left_string_c( s, 1024 );
   expect_at_c_( chars_is_c( pineapple, "Pineapple" ) );

   cChars empty = left_string_c( s, 0 );
   expect_at_c_( is_empty_c_( empty ) );

   release_c( s );

   return finish_tap_c_();
}
