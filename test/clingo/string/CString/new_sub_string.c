#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main( void )
{
   init_tap_c_();

   CString* s = lit_c( "Pineapple" );

   CString* app = new_sub_string_c( s, 4, 7 );
   expect_c_( string_is_c( app, "app" ) );

   CString* apple = new_sub_string_c( s, 4, 9 );
   expect_c_( string_is_c( apple, "apple" ) );

   CString* neap = new_sub_string_c( s, 2, 6 );
   expect_c_( string_is_c( neap, "neap" ) );

   CString* empty = new_sub_string_c( s, 5, 16 );
   expect_c_( string_is_empty_c( empty ) );

   release_all_c_( s, app, apple, neap );

   return finish_tap_c_();
}
