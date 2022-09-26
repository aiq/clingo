#include "clingo/lang/expect.h"
#include "clingo/time/c_Month.h"

TEMP_SLICE_C_(
   test,
   {
      c_Month month;
      int8_t expF;
      int8_t expT;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( c_Jan, 31, 31 ),
      t_( c_Feb, 28, 29 ),
      t_( c_Mar, 31, 31 ),
      t_( c_Apr, 30, 30 ),
      t_( c_May, 31, 31 ),
      t_( c_Jun, 30, 30 ),
      t_( c_Jul, 31, 31 ),
      t_( c_Aug, 31, 31 ),
      t_( c_Sep, 30, 30 ),
      t_( c_Oct, 31, 31 ),
      t_( c_Nov, 30, 30 ),
      t_( c_Dec, 31, 31 )
   );

   for_each_c_( test const*, t, tests )
   {
      char const* monthStr = stringify_month_c( t->month );
      int8_t days;

      days = days_per_month_c( t->month, false );
      tap_descf_c( days == t->expF, "%s no leap year: %d", monthStr, days );
      days = days_per_month_c( t->month, true );
      tap_descf_c( days == t->expT, "%s leap year: %d", monthStr, days );
   }

   return finish_tap_c_();
}
