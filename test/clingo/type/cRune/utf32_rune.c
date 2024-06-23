#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

#define expect_( Rune, Exp )                                                   \
   expect_at_c_(                                                                  \
      rune_is_c( (Rune), (Exp) )                                               \
   )

int main( void )
{
   init_tap_c_();

   expect_( utf32_rune_c( 0x56 ), "V" ); // 56
   expect_( utf32_rune_c( 0xe9 ), "é" ); // c3 a9
   expect_( utf32_rune_c( 0x0f3c ), "༼" ); // e0 bc bc
   expect_( utf32_rune_c( 0x0103ab ), "𐎫" ); // f0 90 8e ab

   return finish_tap_c_();
}
