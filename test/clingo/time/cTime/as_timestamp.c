#include "clingo/lang/expect.h"
#include "clingo/time/C_TimeFormats.h"
#include "clingo/time/cTime.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      cTime inp;
      cTimestamp exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( make_time_c( 2009, c_Feb, 13, 23, 31, 30, 0, utc_c() ),
          unix_timestamp_c( secs_c( 1234567890 ) ) ),
      t_( make_time_c( 2001, c_Jan,  1,  0,  0,  0, 0, utc_c() ),
          unix_timestamp_c( secs_c( 978307200 ) ) )
   );

   for_each_c_( test const*, t, tests )
   {
      cTimestamp res = as_timestamp_c( t->inp );
      expect_c_( eq_timestamp_c( res, t->exp ) );
   }

   return finish_tap_c_();
}
