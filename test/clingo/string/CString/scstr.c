#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main( void )
{
   init_tap_c_();

   CString* s = new_string_c( "foobar" );
   const char* cstr = scstr_c( s );
   cChars chars = c_c( cstr );
   expect_at_c_( chars_is_c( chars, "foobar" ) );

   release_c( s );

   return finish_tap_c_();
}
