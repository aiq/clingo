#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main( void )
{
   init_tap_c_();

   CString* s = lit_c( "foobar" );
   cChars chars = sc_c( s );
   expect_at_c_( chars_is_c( chars, "foobar" ) );

   release_c( s );

   return finish_tap_c_();
}
