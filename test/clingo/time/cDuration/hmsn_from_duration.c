#include "clingo/lang/expect.h"
#include "clingo/time/cDuration.h"

TEMP_SLICE_C_(
   test,
   {
      cDuration dur;
      cHmsn exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( nsecs_c( 1*C_Hour + 12*C_Min + 53*C_Sec + 654321*C_Usec ),
          hmsn_c( 1, 12, 53, 654321000 ) ),
      t_( nsecs_c( 34*C_Min + 47*C_Sec ),
          hms_c( 0, 34, 47 ) ),
      t_( nsecs_c( -2*C_Hour - 34*C_Min - 56*C_Sec - 987654321*C_Nsec ),
          hmsn_c( -2, -34, -56, -987654321 ) )
   );

   each_c_( test const*, t, tests )
   {
      cHmsn x = hmsn_from_duration_c( t->dur );

      bool res = eq_c( cmp_hmsn_c( x, t->exp ) );
      tap_desc_c_( res, "{i64}:{i64}:{i64}:{i64}", x.hour, x.min, x.sec, x.nsec );
   }

   return finish_tap_c_();
}
