#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main( void )
{
   init_tap_c_();

   CString* ascii = str_c( "simple ascii text" );
   expect_c_(  string_is_c( ascii, "simple ascii text" ) );
   expect_c_( !string_is_c( ascii, "simple asci text" ) );
   release_c( ascii );

   CString* utf8 = str_c( "АᏂ 🚀 Ω" );
   expect_c_(  string_is_c( utf8, "АᏂ 🚀 Ω" ) );
   expect_c_( !string_is_c( utf8, "А 🚀 Ω" ) );
   release_c( utf8 );

   CString* euro = str_c( "€uro" );
   expect_c_(  string_is_c( euro, "€uro" ) );
   expect_c_( !string_is_c( euro, "Euro" ) );
   release_c( euro );

   return finish_tap_c_();
}
