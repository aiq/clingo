#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

int main( void )
{
   init_tap_c_();

   cRune umbrella = rune_c( "☂" );

   expect_at_c_(  rune_is_c( umbrella, "☂" ) );
   expect_at_c_( !rune_is_c( umbrella, "y" ) );

   return finish_tap_c_();
}
