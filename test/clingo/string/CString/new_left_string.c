#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main( void )
{
   init_tap_c_();

   CString* s = str_c( "Pineapple" );

   CString* pine = new_left_string_c( s, 4 );
   expect_c_( string_is_c( pine, "Pine" ) );

   CString* pineapple = new_left_string_c( s, 9 );
   expect_c_( string_is_c( pineapple, "Pineapple" ) );

   CString* pineapple2 = new_left_string_c( s, 1024 );
   expect_c_( string_is_c( pineapple2, "Pineapple" ) );

   CString* empty = new_left_string_c( s, 0 );
   expect_c_( string_is_empty_c( empty ) );

   release_all_c_( s, pine, pineapple, pineapple2 );

   return finish_tap_c_();
}
