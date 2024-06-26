#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

TEMP_SLICE_C_(
   test,
   {
      char const* inp;
      c_check_char check;
      bool exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "abcDEF", char_is_alpha_c, true ),
      t_( "abcDEF", char_is_digit_c, false )
   );

   for_each_c_( i, test const*, t, tests )
   {
      cChars chars = c_c( t->inp );
      bool res = chars_match_c( chars, t->check );

      expect_block_c_( i, res == t->exp )
      {
         tap_line_c_( "input", "{s}", t->inp );
         tap_exp_line_c_( "{bool}", t->exp );
         tap_got_line_c_( "{bool}", res );
      }
   }

   return finish_tap_c_();
}
