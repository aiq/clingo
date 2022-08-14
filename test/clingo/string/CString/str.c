#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main( void )
{
   init_tap_c_();

   char const* cstr = "banjo";

   CString* str = lit_c( cstr );

   expect_c_( string_is_c( str, "banjo" ) );
   expect_c_( scstr_c( str ) == cstr );

   release_c( str );

   return finish_tap_c_();
}
