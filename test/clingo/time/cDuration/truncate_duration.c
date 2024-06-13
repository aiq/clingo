#include "clingo/lang/expect.h"
#include "clingo/time/cDuration.h"

TEMP_SLICE_C_(
   test,
   {
      cDuration dur;
      int64_t fac;
      cDuration exp;
      cDuration expTail;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   cDuration dur = duration_c( 1, 15, 30, 918273645 );
   testSlice tests = slice_c_( test,
      t_( dur, C_Nsec, dur,
          nsecs_c( 0 ) ),
      t_( dur, C_Usec, duration_c( 1, 15, 30, 918273000 ),
          nsecs_c( 645 ) ),
      t_( dur, C_Msec, duration_c( 1, 15, 30, 918000000 ),
          nsecs_c( 273645 ) ),
      t_( dur, C_Sec, duration_c( 1, 15, 30, 0 ),
          nsecs_c( 918273645 ) ),
      t_( dur, 2*C_Sec, duration_c( 1, 15, 30, 0 ),
          nsecs_c( 918273645 ) ),
      t_( dur, C_Min, duration_c( 1, 15, 0, 0 ),
          duration_c( 0, 0, 30, 918273645 ) ),
      t_( dur, 10*C_Min, duration_c( 1, 10, 0, 0 ),
          duration_c( 0, 5, 30, 918273645 ) ),
      t_( dur, C_Hour, duration_c( 1, 0, 0, 0 ),
          duration_c( 0, 15, 30, 918273645 ) )
   );

   for_each_c_( test const*, t, tests )
   {
      cDuration tail;
      cDuration dur = truncate_duration_c( t->dur, t->fac, &tail );

      bool res = eq_duration_c( dur, t->exp ) and
                 eq_duration_c( tail, t->expTail );
      tap_c_( res, "" );
   }

   return finish_tap_c_();
}
