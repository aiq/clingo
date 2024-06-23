#include "clingo/lang/expect.h"
#include "clingo/time/cMonthDay.h"

#include <locale.h>

TEMP_SLICE_C_(
   test,
   {
      char const* inp;
      char const* fmt;
      cMonthDay exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "12 01", "MM DD", month_day_c( 12, 1 ) )
   );

   each_c_( test const*, t, tests )
   {
      cScanner* sca = &cstr_scanner_c_( t->inp );

      cMonthDay md;
      bool res = read_month_day_c( sca, &md, t->fmt );
      res &= eq_c( cmp_month_day_c( md, t->exp ) );

      tap_desc_c_( res, "res: {s}, with {s}", t->inp, t->fmt );
   }

   return finish_tap_c_();
}
