#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"
#include "clingo/type/cRuneRange.h"

static bool not_ascii( cRune r )
{
   cRuneRange rng = utf16_rune_range_c( 0x00, 0x7F );
   return not in_rune_range_c( rng, r );
}

TEMP_SLICE_C_(
   test,
   {
      char const* inp;
      c_check_rune check;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "let the ♫ play", not_ascii, "♫ play" ),
      t_( "let the music play", not_ascii, "" )
   );

   for_each_c_( i, test const*, t, tests )
   {
      cChars chars = c_c( t->inp );
      char const* ptr = find_rune_match_c( chars, t->check );
      cChars sub = ptr != NULL ? (cChars)atween_c_( ptr, end_c_( chars ) )
                               : c_c( "" );

      expect_block_c_( i, chars_is_c( sub, t->exp ) )
      {
         tap_exp_line_c_( "{s}", t->exp );
         tap_got_line_c_( "{cs}", sub );
      }
   }

   return finish_tap_c_();
}