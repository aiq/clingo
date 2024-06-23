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
      t_( a, date_c( 2011, c_Apr,  8 ), -52 ),
      t_( a, date_c( 2012, c_May, 15 ),   5 )
   );

   each_c_( test const*, t, tests )
   {
      int64_t weeks = weeks_between_dates_c( t->a, t->b );

      tap_desc_c_( weeks == t->exp, "weeks: {i64}", weeks );
   }

   return finish_tap_c_();
}
