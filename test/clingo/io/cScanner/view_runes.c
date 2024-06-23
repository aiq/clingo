#include "clingo/io/cScanner.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cScanner* sca = &cstr_scanner_c_( "a 🥛🔑📊" );

   // ------------------------------------------------------------- view 4 runes
   cChars runes = view_runes_c( sca, 4 );
   expect_at_c_( chars_is_c( runes,"a 🥛🔑" ) );
   expect_at_c_( sca->pos == 10 );
   expect_at_c_( sca->space == 4 );

   // ------------------------------------------------------ try to view outside
   runes = view_runes_c( sca, 2 );
   expect_at_c_( is_empty_c_( runes ) );
   expect_at_c_( sca->pos == 10 );
   expect_at_c_( sca->space == 4 );

   return finish_tap_c_();
}
