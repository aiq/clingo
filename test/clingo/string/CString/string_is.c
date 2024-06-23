#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main( void )
{
   init_tap_c_();

   CString* ascii = lit_c( "simple ascii text" );
   expect_at_c_(  string_is_c( ascii, "simple ascii text" ) );
   expect_at_c_( !string_is_c( ascii, "simple asci text" ) );
   release_c( ascii );

   CString* utf8 = lit_c( "АᏂ 🚀 Ω" );
   expect_at_c_(  string_is_c( utf8, "АᏂ 🚀 Ω" ) );
   expect_at_c_( !string_is_c( utf8, "А 🚀 Ω" ) );
   release_c( utf8 );

   CString* euro = lit_c( "€uro" );
   expect_at_c_(  string_is_c( euro, "€uro" ) );
   expect_at_c_( !string_is_c( euro, "Euro" ) );
   release_c( euro );

   return finish_tap_c_();
}
