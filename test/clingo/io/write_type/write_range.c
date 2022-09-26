#include "clingo/io/write_type.h"
#include "clingo/io/write.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
   // "" / "c" / "o" / "co" / "oc"
      t_( "", "[-123..45]" ),
      t_( "c", "[-123..45]" ),
      t_( "o", "(-122..44)" ),
      t_( "co", "[-123..44)" ),
      t_( "oc", "(-122..45]" ),
   // delimiter
      t_( "/,", "[-123,45]" ),
      t_( "co/;", "[-123;44)" ),
      t_( "o/|", "(-122|44)" ),
   // "dbg"
      t_( "dbg", "{ .min=-123, .max=45 }" )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cRecorder* rec = &recorder_c_( 128 );
      cRange rng = { .min=-123, .max=45 };

      bool res = write_range_c( rec, rng, t.fmt );
      res &= recorded_is_c( rec, t.exp );

      tap_descf_c( res, "test at index %"PRIi64, i );
   }

   return finish_tap_c_();
}
