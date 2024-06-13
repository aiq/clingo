#include "clingo/lang/expect.h"
#include "clingo/lang/locale.h"
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

   set_locale_c( LC_TIME, "C" ); // For every system the same output

   testSlice tests = slice_c_( test,
      t_( c_Mon, "Mon" ),
      t_( c_Tue, "Tue" ),
      t_( c_Wed, "Wed" ),
      t_( c_Thu, "Thu" ),
      t_( c_Fri, "Fri" ),
      t_( c_Sat, "Sat" ),
      t_( c_Sun, "Sun" )
   );

   for_each_c_( test const*, t, tests )
   {
      cVarChars varChars = scalars_c_( 16, char );
      varChars = get_weekday_abbrev_c( t->wd, varChars );
      cChars chars = as_c_( cChars, varChars );
      bool res = chars_is_c( chars, t->exp );

      tap_desc_c_( res, "test {s}", t->exp );
   }

   return finish_tap_c_();
}
