#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

int main( void )
{
   init_tap_c_();

   cRune r = null_rune_c();
   expect_at_c_( not rune_is_valid_c( r ) );

   return finish_tap_c_();
}
