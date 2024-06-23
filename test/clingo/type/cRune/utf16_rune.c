#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

#define expect_( Rune, Exp )                                                   \
   expect_at_c_(                                                                  \
      rune_is_c( (Rune), (Exp) )                                               \
   )

int main( void )
{
   init_tap_c_();

   expect_( utf16_rune_c( 0x56 ), "V" );
   expect_( utf16_rune_c( 0xe9 ), "é" );
   expect_( utf16_rune_c( 0x2602 ), "☂" );

   return finish_tap_c_();
}
