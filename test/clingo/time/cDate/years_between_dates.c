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

   cDate a = date_c( 2012, 4, 8 );
   testSlice tests = slice_c_( test,
      t_( a, date_c( 1983, c_Apr,  8 ), -29 ),
      t_( a, date_c( 2020, c_Jan, 19 ),   7 )
   );

   for_each_c_( test const*, t, tests )
   {
      int64_t years = years_between_dates_c( t->a, t->b );

      tap_desc_c_( years == t->exp, "years: {i64}", years );
   }

   return finish_tap_c_();
}
