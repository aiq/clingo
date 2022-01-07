#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

int main( void )
{
   init_tap_c_();

   cRune valid = rune_c( "a" );
   expect_c_( rune_is_valid_c( valid ) );

   cRune invalid = { .ctrl=0xffffffff };
   expect_c_( not rune_is_valid_c( invalid ) );

   // € = e2 82 ac
   cRune euro = build_rune_c_( 0xe2, 0x82, 0, 0 );
   expect_c_( not rune_is_valid_c( euro ) );

   return finish_tap_c_();
}
