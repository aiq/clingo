#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

#include <ctype.h>

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
      t_( "..!Hello, clingo!..", char_is_punct_c, "Hello, clingo!.." )
   );

   each_c_( test const*, t, tests )
   {
      cChars cs = trim_char_match_left_c( c_c( t->inp ), t->check );
      bool res = chars_is_c( cs, t->exp );

      tap_desc_c_( res, "{s:q} -> {s:q}", t->inp, t->exp );
   }

   return finish_tap_c_();
}
