#include "clingo/io/c_ImpExpError.h"
#include "clingo/io/write.h"
#include "clingo/lang/expect.h"
#include "clingo/time/cOrdinalDate.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      cOrdinalDate od;
      int err;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   cOrdinalDate od = ordinal_date_c( 2014, 23 );
   testSlice tests = slice_c_( test,
      t_( od, cNoError_, "YYYY-CCC", "2014-023" ),
      t_( od, cNoError_, "YY/C", "14/23" ),
      t_( od, c_InvalidFormatString, "YYYY-CC", "" ),
      t_( od, cNoError_, "YYYY-DDD", "2014-DDD" )
   );

   for_each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 32 );

      write_ordinal_date_c( rec, t->od, t->fmt );
      bool res = ( rec->err == t->err );
      res &= recorded_is_c( rec, t->exp );

      tap_descf_c( res, "test: %s -> %s", t->fmt, t->exp );
   }

   return finish_tap_c_();
}
