#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

int main( void )
{
   init_tap_c_();

   cRune dollar = build_rune_c_( 0x24, 0, 0, 0 );
   expect_at_c_( rune_is_c( dollar, "$" ) );
   expect_at_c_( not rune_is_c( dollar, "€" ) );

   cRune euro = build_rune_c_( 0xe2, 0x82, 0xac, 0 );
   expect_at_c_( rune_is_c( euro, "€" ) );
   expect_at_c_( not rune_is_c( euro, "$" ) );

   return finish_tap_c_();
}
