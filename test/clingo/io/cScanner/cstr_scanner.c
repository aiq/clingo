#include "clingo/io/cScanner.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cScanner* sca = &cstr_scanner_c_( "scan a string" );

   cChars chars = unscanned_chars_c_( sca );
   expect_c_( chars_is_c( chars, "scan a string" ) );

   return finish_tap_c_();
}
