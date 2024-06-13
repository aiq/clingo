#include "clingo/lang/expect.h"
#include "clingo/time/cDuration.h"

TEMP_SLICE_C_(
   test,
   {
      cDuration dur;
      int64_t exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( secs_c( 4851 ),
          1*C_Hour + 20*C_Min + 51*C_Sec ),
      t_( mins_c( 132 ),
          2*C_Hour + 12*C_Min ),
      t_( usecs_c( 40851123456L ),
          11*C_Hour + 20*C_Min + 51*C_Sec + 123456*C_Usec )
   );

   for_each_c_( test const*, t, tests )
   {
      bool res = ( t->dur._v == t->exp );

      tap_desc_c_( res, "test: {i64}", index_of_c_( tests, t ) );
   }

   return finish_tap_c_();
}
