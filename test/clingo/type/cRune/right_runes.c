#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

TEMP_SLICE_C_(
   test,
   {
      char const* input;
      int64_t maxLen;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "ананас", 6, "ананас" ),
      t_( "ананас", 4, "анас" ),
      t_( "ананас", 0, "" )
   );

   for_each_c_( test const*, t, tests )
   {
      cChars chars = c_c( t->input );
      cChars right = right_runes_c( chars, t->maxLen );
      bool res = chars_is_c( right, t->exp );
      tap_desc_c_( res, "test {s:q} -> {s:q}", t->input, t->exp );
   }

   return finish_tap_c_();
}
