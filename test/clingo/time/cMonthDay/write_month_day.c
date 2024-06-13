#include "clingo/lang/expect.h"
#include "clingo/lang/locale.h"
#include "clingo/time/cMonthDay.h"

TEMP_SLICE_C_(
   test,
   {
      cMonthDay md;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   set_locale_c( LC_TIME, "C" ); // For every system the same output

   cMonthDay md = month_day_c( 12, 1 );
   testSlice tests = slice_c_( test,
      t_( md, "MM DD", "12 01" ),
      t_( md, "MMM D", "Dec 1" )
   );

   for_each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 128 );

      bool res = write_month_day_c( rec, t->md, t->fmt );
      res &= recorded_is_c( rec, t->exp );

      tap_desc_c_( res, "test: {s}", t->exp );
   }

   return finish_tap_c_();
}
