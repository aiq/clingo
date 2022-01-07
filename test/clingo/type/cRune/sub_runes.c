#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      char const* input;
      int64_t begIdx;
      int64_t endIdx;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "ананас", 0, 3, "ана" ),
      t_( "ананас", 2, 6, "анас" ),
      t_( "ананас", 3, 4, "н" ),
      t_( "ананас", 6, 2, "" ),
      t_( "ананас", 0, 7, "" )
   );

   for_each_c_( test const*, t, tests )
   {
      cChars chars = c_c( t->input );
      cChars sub = sub_runes_c( chars, t->begIdx, t->endIdx );
      bool res = chars_is_c( sub, t->exp );
      tap_descf_c( res, "test '%s' -> '%s'", t->input, t->exp );
   }

   return finish_tap_c_();
}
