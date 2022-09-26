#include "clingo/lang/expect.h"
#include "clingo/time/c_Month.h"

TEMP_SLICE_C_(
   test,
   {
      c_Month month;
      c_Month exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( c_Jan, c_Jan ),
      t_( c_Feb, c_Jan ),
      t_( c_Mar, c_Jan ),
      t_( c_Apr, c_Apr ),
      t_( c_May, c_Apr ),
      t_( c_Jun, c_Apr ),
      t_( c_Jul, c_Jul ),
      t_( c_Aug, c_Jul ),
      t_( c_Sep, c_Jul ),
      t_( c_Oct, c_Oct ),
      t_( c_Nov, c_Oct ),
      t_( c_Dec, c_Oct )
   );

   for_each_c_( test const*, t, tests )
   {
      c_Month const res = first_month_of_quarter_c( t->month );

      tap_descf_c( res == t->exp, "%s -> %s", stringify_month_c( t->month ),
                                              stringify_month_c( res ) );
   }

   return finish_tap_c_();
}
