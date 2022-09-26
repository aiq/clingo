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
      t_( "ананас", 4, "анан" ),
      t_( "ананас", 0, "" )
   );

   for_each_c_( test const*, t, tests )
   {
      cChars chars = c_c( t->input );
      cChars left = left_runes_c( chars, t->maxLen );
      bool res = chars_is_c( left, t->exp );
      tap_descf_c( res, "test '%s' -> '%s'", t->input, t->exp );
   }

   return finish_tap_c_();
}
