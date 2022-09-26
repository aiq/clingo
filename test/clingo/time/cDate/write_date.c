#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

TEMP_SLICE_C_(
   test,
   {
      cDate date;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   cDate apr01 = date_c( 2013, c_Apr, 1 );
   testSlice tests = slice_c_( test,
      t_( apr01, "YYYYMMDD", "20130401" ),
      t_( apr01, "YY-M-D", "13-4-1" )
   );

   for_each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 32 );

      bool res = write_date_c( rec, t->date, t->fmt );
      res &= recorded_is_c( rec, t->exp );

      tap_descf_c( res, "test: %s -> %s", t->fmt, t->exp );
   }

   return finish_tap_c_();
}

