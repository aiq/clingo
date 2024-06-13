#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

TEMP_SLICE_C_(
   test,
   {
      cDate a;
      cDate b;
      int64_t exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   cDate a = date_c( 2012, c_Apr, 8 );
   testSlice tests = slice_c_( test,
      t_( a, date_c( 2012, c_Jan,  3 ), -96 ),
      t_( a, date_c( 2012, c_May, 11 ),  33 )
   );

   for_each_c_( test const*, t, tests )
   {
      int64_t days = days_between_dates_c( t->a, t->b );

      tap_desc_c_( days == t->exp, "test at index {i64}", days );
   }

   return finish_tap_c_();
}
