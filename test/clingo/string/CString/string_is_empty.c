#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main( void )
{
   init_tap_c_();

   CString* str = lit_c( "something" );
   CString* empty = empty_string_c();
   CString* nothing = new_string_c( "" );

   expect_c_( not string_is_empty_c( str ) );
   expect_c_( string_is_empty_c( empty ) );
   expect_c_( string_is_empty_c( nothing ) );

   release_c( str );

   return finish_tap_c_();
}
