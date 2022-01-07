#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

int main( void )
{
   init_tap_c_();

   cRune x = rune_c( "x" );
   cRune snowman = rune_c( "☃" ); // U+2603

   expect_c_(  eq_rune_c( x, x ) );
   expect_c_(  eq_rune_c( snowman, snowman ) );
   expect_c_( !eq_rune_c( x, snowman ) );

   return finish_tap_c_();
}
