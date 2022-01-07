#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

TEMP_SLICE_DEF_C_(
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
      t_( a, date_c( 2012, c_Jan,  3 ),  -3 ),
      t_( a, date_c( 2012, c_Jun, 11 ),   2 ),
      t_( a, date_c( 2012, c_Jan, 28 ),  -2 ),
      t_( a, date_c( 2012, c_Jun,  1 ),   1 ),
      t_( a, date_c( 2010, c_Aug, 30 ), -20 ),
      t_( a, date_c( 2014, c_Dec,  1 ),  31 )
   );

   for_each_c_( test const*, t, tests )
   {
      int64_t months = months_between_dates_c( t->a, t->b );

      tap_descf_c( months == t->exp, "months: %"PRIi64, months );
   }

   return finish_tap_c_();
}
