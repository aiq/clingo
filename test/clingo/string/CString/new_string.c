#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main( void )
{
   init_tap_c_();

   char const* cstr = "a string text";

   CString* str = new_string_c( cstr );

   expect_c_( string_is_c( str, "a string text" ) );
   expect_c_( string_cstr_c( str ) != cstr );

   release_c( str );

   return finish_tap_c_();
}
