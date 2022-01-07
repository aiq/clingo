#include "clingo/lang/expect.h"
#include "clingo/time/c_Month.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      c_Month month;
      int16_t expF;
      int16_t expT;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( c_Jan,   1,   1 ),
      t_( c_Feb,  32,  32 ),
      t_( c_Mar,  60,  61 ),
      t_( c_Apr,  91,  92 ),
      t_( c_May, 121, 122 ),
      t_( c_Jun, 152, 153 ),
      t_( c_Jul, 182, 183 ),
      t_( c_Aug, 213, 214 ),
      t_( c_Sep, 244, 245 ),
      t_( c_Oct, 274, 275 ),
      t_( c_Nov, 305, 306 ),
      t_( c_Dec, 335, 336 )
   );

   for_each_c_( test const*, t, tests )
   {
      char const* monthStr = stringify_month_c( t->month );
      int16_t days;

      days = first_month_day_of_year_c( t->month, false );
      tap_descf_c( days == t->expF, "%s no leap year: %d", monthStr, days );
      days = first_month_day_of_year_c( t->month, true );
      tap_descf_c( days == t->expT, "%s leap year: %d", monthStr, days );
   }

   return finish_tap_c_();
}
