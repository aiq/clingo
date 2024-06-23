#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

int main( void )
{
   init_tap_c_();

   cChars euroChars = c_c( "€" );
   cRune euro = make_rune_c( euroChars );
   expect_at_c_( rune_is_c( euro, "€" ) );

   cRune invalidEuro = make_rune_c( left_c_( cChars, euroChars ,2 ) );
   expect_at_c_( not rune_is_valid_c( invalidEuro ) );

   return finish_tap_c_();
}
