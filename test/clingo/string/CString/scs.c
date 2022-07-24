#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main( void )
{
   init_tap_c_();

   CString* s = str_c( "foobar" );
   cChars chars = scs_c( s );
   expect_c_( chars_is_c( chars, "foobar" ) );

   release_c( s );

   return finish_tap_c_();
}
