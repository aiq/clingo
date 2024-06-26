#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"
#include "clingo/type/cRuneRange.h"

static bool is_ascii( cRune r )
{
   cRuneRange rng = utf16_rune_range_c( 0x00, 0x7F );
   return in_rune_range_c( rng, r );
}

TEMP_SLICE_C_(
   test,
   {
      char const* inp;
      c_check_rune check;
      bool exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "aoun", is_ascii, true ),
      t_( "äöüñ", is_ascii, false )
   );

   for_each_c_( i, test const*, t, tests )
   {
      cChars chars = c_c( t->inp );
      bool res = chars_runes_match_c( chars, t->check );

      expect_block_c_( i, res == t->exp )
      {
         tap_line_c_( "input", "{s}", t->inp );
         tap_exp_line_c_( "{bool}", t->exp );
         tap_got_line_c_( "{bool}", res );
      }
   }

   return finish_tap_c_();
}
