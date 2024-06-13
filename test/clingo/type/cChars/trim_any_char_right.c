#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

TEMP_SLICE_C_(
   test,
   {
      char const* inp;
      char const* set;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "..!Hello, clingo!..", "!.", "..!Hello, clingo" ),
      t_( "18:03:12.010", "0", "18:03:12.01" )
   );

   for_each_c_( test const*, t, tests )
   {
      cChars cs = trim_any_char_right_c_( c_c( t->inp ), t->set );
      bool res = chars_is_c( cs, t->exp );

      tap_desc_c_( res, "{s:q} -> {s:q} -> {s:q}", t->inp, t->set, t->exp );
   }

   return finish_tap_c_();
}
