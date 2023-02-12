#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

#include "clingo/io/print.h"

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
      t_( "..!Hello, clingo!..", char_is_punct_c, "..!Hello, clingo" )
   );

   for_each_c_( test const*, t, tests )
   {
      cChars cs = trim_char_match_right_c( c_c( t->inp ), t->check );
      bool res = chars_is_c( cs, t->exp );
      
      pjotln_c_( xyz, 128, c_c( t->inp ), " ", cs );

      tap_descf_c( res, "'%s' -> '%s'", t->inp, t->exp );
   }

   return finish_tap_c_();
}
