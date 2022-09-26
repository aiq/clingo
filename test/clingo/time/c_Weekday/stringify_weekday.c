#include "clingo/lang/expect.h"
#include "clingo/time/c_Weekday.h"
#include "clingo/type/cChars.h"

TEMP_SLICE_C_(
   test,
   {
      c_Weekday wd;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( c_Mon, "c_Mon" ),
      t_( c_Tue, "c_Tue" ),
      t_( c_Wed, "c_Wed" ),
      t_( c_Thu, "c_Thu" ),
      t_( c_Fri, "c_Fri" ),
      t_( c_Sat, "c_Sat" ),
      t_( c_Sun, "c_Sun" )
   );

   for_each_c_( test const*, t, tests )
   {
      cChars chars = c_c( stringify_weekday_c( t->wd ) );
      bool res = chars_is_c( chars, t->exp );

      tap_descf_c( res, "test %s", t->exp );
   }

   return finish_tap_c_();
}
