#include "clingo/lang/expect.h"
#include "clingo/lang/locale.h"
#include "clingo/time/c_Month.h"
#include "clingo/type/cChars.h"

TEMP_SLICE_C_(
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

   set_locale_c( LC_TIME, "C" ); // For every system the same output

   testSlice tests = slice_c_( test,
      t_( c_Jan, "Jan" ),
      t_( c_Feb, "Feb" ),
      t_( c_Mar, "Mar" ),
      t_( c_Apr, "Apr" ),
      t_( c_May, "May" ),
      t_( c_Jun, "Jun" ),
      t_( c_Jul, "Jul" ),
      t_( c_Aug, "Aug" ),
      t_( c_Sep, "Sep" ),
      t_( c_Oct, "Oct" ),
      t_( c_Nov, "Nov" ),
      t_( c_Dec, "Dec" )
   );

   for_each_c_( test const*, t, tests )
   {
      cVarChars varChars = scalars_c_( 16, char );
      varChars = get_month_abbrev_c( t->month, varChars );
      cChars chars = as_c_( cChars, varChars );
      bool res = chars_is_c( chars, t->exp );

      tap_desc_c_( res, "test {s}", t->exp );
   }

   return finish_tap_c_();
}
