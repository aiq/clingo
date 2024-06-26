#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

TEMP_SLICE_C_(
   test,
   {
      char const* inp;
      c_check_char check;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "abcDEF", char_is_upper_c, "DEF" )
   );

   for_each_c_( i, test const*, t, tests )
   {
      cChars chars = c_c( t->inp );
      char const* ptr = find_char_match_c( chars, t->check );
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
