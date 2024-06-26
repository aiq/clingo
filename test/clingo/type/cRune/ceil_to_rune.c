#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

int main( void )
{
   init_tap_c_();

   // rune/size -> ®/2 =/1 ☂/3
   cChars chars = c_c( "®=☂" );
   expect_at_c_( ceil_to_rune_c( chars, 1 ) == ptr_for_c_( chars,  2 ) );
   expect_at_c_( ceil_to_rune_c( chars, 2 ) == ptr_for_c_( chars,  2 ) );
   expect_at_c_( ceil_to_rune_c( chars, 3 ) == ptr_for_c_( chars,  3 ) );
   expect_at_c_( ceil_to_rune_c( chars, 4 ) == ptr_for_c_( chars, -1 ) );



   return finish_tap_c_();
}
