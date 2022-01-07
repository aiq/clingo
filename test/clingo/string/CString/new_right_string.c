#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main()
{
   init_tap_c_();

   CString* s = str_c( "Pineapple" );

   CString* apple = new_right_string_c( s, 5 );
   expect_c_( string_is_c( apple, "apple" ) );

   CString* pineapple = new_right_string_c( s, 9 );
   expect_c_( string_is_c( pineapple, "Pineapple" ) );

   CString* pineapple2 = new_right_string_c( s, 1024 );
   expect_c_( string_is_c( pineapple2, "Pineapple" ) );

   CString* empty = new_right_string_c( s, 0 );
   expect_c_( string_is_empty_c( empty ) );

   release_all_c_( s, apple, pineapple, pineapple2 );

   return finish_tap_c_();
}
