#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

#define expect_( Rune, Exp )                                                   \
   expect_at_c_(                                                                  \
      rune_is_c( rune_c( Rune ), (Exp) )                                       \
   )

int main( void )
{
   init_tap_c_();

   cChars chars = c_c( "abcd€f®!" );

   expect_( nth_rune_c( chars, 0 ), "a" );
   expect_( nth_rune_c( chars, 4 ), "€" );
   expect_( nth_rune_c( chars, 5 ), "f" );
   expect_( nth_rune_c( chars, 6 ), "®" );
   expect_( nth_rune_c( chars, 7 ), "!" );
   expect_at_c_( nth_rune_c( chars, 8 ) == NULL );

   expect_( nth_rune_c( chars, -1 ), "!" );
   expect_( nth_rune_c( chars, -2 ), "®" );
   expect_( nth_rune_c( chars, -3 ), "f" );
   expect_( nth_rune_c( chars, -4 ), "€" );
   expect_( nth_rune_c( chars, -8 ), "a" );
   expect_at_c_( nth_rune_c( chars, -9 ) == NULL );

   return finish_tap_c_();
}
