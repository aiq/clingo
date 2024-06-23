#include "clingo/lang/expect.h"
#include "clingo/time/cTzOffset.h"

TEMP_SLICE_C_(
   test,
   {
      cTzOffset a;
      cTzOffset b;
      cDuration exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   cTzOffset utc  = utc_c();
   cTzOffset almt = tz_c( +600 );
   cTzOffset pst  = tz_c( -800 );

   testSlice tests = slice_c_( test,
      t_( utc, almt, hours_c( 6 ) ),
      t_( almt, utc, hours_c( -6 ) ),
      t_( utc, pst, hours_c( -8 ) ),
      t_( pst, utc, hours_c( 8 ) ),
      t_( pst, almt, hours_c( 14 ) ),
      t_( almt, pst, hours_c( -14 ) )
   );

   each_c_( test const*, t, tests )
   {
      cDuration dur = between_tz_offsets_c( t->a, t->b );

      bool res = eq_c( cmp_duration_c( dur, t->exp ) );

      cRecorder* rec = &recorder_c_( 256 );
      write_duration_c_( rec, dur );
      tap_desc_c_( res, "test: {rec}", rec );
   }

   return finish_tap_c_();
}
