#include "clingo/lang/expect.h"
#include "clingo/type/cRuneRange.h"

int main( void )
{
   init_tap_c_();

   cRuneRange ascii = utf32_rune_range_c( 0x0000, 0x007F );
   cRuneRange digits = rune_range_c( "0", "9" );
   cRuneRange buginese = utf16_rune_range_c( 0x1A00, 0x1A1F );

   expect_at_c_(  in_rune_range_c_( ascii,    "a" ) );
   expect_at_c_( !in_rune_range_c_( digits,   "a" ) );
   expect_at_c_( !in_rune_range_c_( buginese, "a" ) );

   expect_at_c_(  in_rune_range_c_( ascii,    "5" ) );
   expect_at_c_(  in_rune_range_c_( digits,   "5" ) );
   expect_at_c_( !in_rune_range_c_( buginese, "a" ) );

   expect_at_c_( !in_rune_range_c_( ascii,    "ᨒ" ) );
   expect_at_c_( !in_rune_range_c_( digits,   "ᨒ" ) );
   expect_at_c_(  in_rune_range_c_( buginese, "ᨒ" ) );

   expect_at_c_(  eq_rune_range_c( ascii, ascii ) );
   expect_at_c_( !eq_rune_range_c( ascii, digits ) );

   return finish_tap_c_();
}
