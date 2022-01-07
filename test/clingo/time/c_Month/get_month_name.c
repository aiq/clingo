#include "clingo/lang/expect.h"
#include "clingo/lang/locale.h"
#include "clingo/time/c_Month.h"
#include "clingo/type/cChars.h"

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

   set_locale_c( LC_TIME, "C" ); // For every system the same output

   testSlice tests = slice_c_( test,
      t_( c_Jan, "January" ),
      t_( c_Feb, "February" ),
      t_( c_Mar, "March" ),
      t_( c_Apr, "April" ),
      t_( c_May, "May" ),
      t_( c_Jun, "June" ),
      t_( c_Jul, "July" ),
      t_( c_Aug, "August" ),
      t_( c_Sep, "September" ),
      t_( c_Oct, "October" ),
      t_( c_Nov, "November" ),
      t_( c_Dec, "December" )
   );

   for_each_c_( test const*, t, tests )
   {
      cVarChars varChars = scalars_c_( 16, char );
      varChars = get_month_name_c( t->month, varChars );
      cChars chars = as_chars_c( varChars );
      bool res = chars_is_c( chars, t->exp );

      tap_descf_c( res, "test %s", t->exp );
   }

   return finish_tap_c_();
}
