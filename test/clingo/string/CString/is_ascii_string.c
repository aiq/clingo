#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main( void )
{
   init_tap_c_();

   CString* ascii = lit_c( "simple ascii text" );
   expect_at_c_( is_ascii_string_c( ascii ) );
   release_c( ascii );

   CString* utf8 = lit_c( "АᏂ 🚀 Ω" );
   expect_at_c_( not is_ascii_string_c( utf8 ) );
   release_c( utf8 );

   CString* euro = lit_c( "€uro" );
   expect_at_c_( not is_ascii_string_c( euro ) );
   release_c( euro );

   return finish_tap_c_();
}
