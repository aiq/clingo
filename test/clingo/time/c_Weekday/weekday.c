#include "clingo/lang/expect.h"
#include "clingo/time/c_Weekday.h"

TEMP_SLICE_C_(
   test,
   {
      int32_t year;
      c_Month month;
      int8_t day;
      c_Weekday exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( 1789, c_Jul, 14, c_Tue ),
      t_( 1892, c_Jan, 18, c_Mon ),
      t_( 1949, c_May, 23, c_Mon ),
      t_( 1989, c_Nov,  9, c_Thu ),
      t_( 2012, c_Apr,  8, c_Sun )
   );

   for_each_c_( test const*, t, tests )
   {
      bool res = weekday_c( t->year, t->month, t->day ) == t->exp;

      tap_descf_c( res, "test: %d.%d.%d -> %s",
                   t->year, t->month, t->day, stringify_weekday_c( t->exp ) );
   }

   return finish_tap_c_();
}
