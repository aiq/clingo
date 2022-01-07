#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main( void )
{
   init_tap_c_();

   CString* ascii = str_c( "simple ascii text" );
   expect_c_( is_ascii_string_c( ascii ) );
   release_c( ascii );

   CString* utf8 = str_c( "АᏂ 🚀 Ω" );
   expect_c_( not is_ascii_string_c( utf8 ) );
   release_c( utf8 );

   CString* euro = str_c( "€uro" );
   expect_c_( not is_ascii_string_c( euro ) );
   release_c( euro );

   return finish_tap_c_();
}
