#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main( void )
{
   init_tap_c_();

   CString* ascii = lit_c( "simple ascii text" );
   expect_c_( string_length_c( ascii ) == 17 );
   release_c( ascii );

   CString* utf8 = lit_c( "АᏂ 🚀 Ω" );
   expect_c_( string_length_c( utf8 ) == 6 );
   release_c( utf8 );

   CString* euro = lit_c( "€uro" );
   expect_c_( string_length_c( euro ) == 4 );
   release_c( euro );

   return finish_tap_c_();
}
