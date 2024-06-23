#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

int main( void )
{
   init_tap_c_();

   cRune x = rune_c( "x" );
   expect_at_c_( rune_is_c( x, "x" ) );

   cRune y = rune_c( "yz" );
   expect_at_c_( rune_is_c( y, "y" ) );

   cRune snowman = rune_c( "☃ needs an ☂" );
   expect_at_c_( rune_is_c( snowman, "☃" ) );

   return finish_tap_c_();
}
