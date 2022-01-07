#include "clingo/lang/expect.h"
#include "clingo/time/c_Month.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      c_Month month;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( c_Jan, "c_Jan" ),
      t_( c_Feb, "c_Feb" ),
      t_( c_Mar, "c_Mar" ),
      t_( c_Apr, "c_Apr" ),
      t_( c_May, "c_May" ),
      t_( c_Jun, "c_Jun" ),
      t_( c_Jul, "c_Jul" ),
      t_( c_Aug, "c_Aug" ),
      t_( c_Sep, "c_Sep" ),
      t_( c_Oct, "c_Oct" ),
      t_( c_Nov, "c_Nov" ),
      t_( c_Dec, "c_Dec" )
   );

   for_each_c_( test const*, t, tests )
   {
      cChars chars = c_c( stringify_month_c( t->month ) );
      bool res = chars_is_c( chars, t->exp );

      tap_descf_c( res, "test %s", t->exp );
   }

   return finish_tap_c_();
}
