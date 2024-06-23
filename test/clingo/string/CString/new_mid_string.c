#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main( void )
{
   init_tap_c_();

   CString* s = lit_c( "Pineapple" );

   CString* pineapple = new_mid_string_c( s, 0 );
   expect_at_c_( string_is_c( pineapple, "Pineapple" ) );

   CString* apple = new_mid_string_c( s, 4 );
   expect_at_c_( string_is_c( apple, "apple" ) );

   CString* empty = new_mid_string_c( s, 1024 ); // to high value
   expect_at_c_( string_is_empty_c( empty ) );

   release_all_c_( s, pineapple, apple );

   return finish_tap_c_();
}
