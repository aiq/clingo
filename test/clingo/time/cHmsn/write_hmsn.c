#include "clingo/lang/expect.h"
#include "clingo/io/write.h"
#include "clingo/time/cHmsn.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      cHmsn hmsn;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   cHmsn hmsn = hmsn_c( 18, 3, 12, 10234567 );
   testSlice tests = slice_c_( test,
      t_( hmsn, "hhmmss", "180312" ),
      t_( hmsn, "hh:mm:ss.i", "18:03:12.01" ),
      t_( hmsn, "hh:mm:ss.iii", "18:03:12.010" ),
      t_( hmsn, "+kk:mm:ss.u ap", "+06:03:12.010234 pm" ),
      t_( hmsn, "_k:_m AP", " 6: 3 PM" )
   );

   for_each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 32 );

      bool res = write_hmsn_c( rec, t->hmsn, t->fmt );
      res &= recorded_is_c( rec, t->exp );

      tap_descf_c( res, "test: '%s' -> '%s'", t->fmt, turn_into_cstr_c( rec ) );
   }

   return finish_tap_c_();
}
