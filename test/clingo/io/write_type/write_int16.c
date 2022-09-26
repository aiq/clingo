#include "clingo/io/write_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      int16_t val;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
   // ""/"d"
      t_( 18, "", "18" ),
      t_( 18, "d", "18" ),
   // "x"/"X"/"0x"/"0X"
      t_( 28, "x", "1c" ),
      t_( 28, "0x", "1c" ),
      t_( -28, "X", "-1C" ),
      t_( -28, "0X", "FFE4" ),
   // "o"/"0o"
      t_( 56, "o", "70" ),
      t_( 56, "0o", "70" ),
      t_( -56, "o", "-70" ),
      t_( -56, "0o", "177710" ),
   // "b"/"B"/"0b"/"0B"
      t_( 2821, "b", "1o11""ooooo1o1" ),
      t_( 2821, "0b", "1o11""ooooo1o1" ),
      t_( -2821, "B", "-1011""00000101" ),
      t_( -2821, "0B", "11110100""11111011" ),
   // sign
      t_( 18, "+", "+18" ),
      t_( 18, "+xq", "'+12'" ),
      t_( 18, "+0xq", "'12'" ), // sign does not work for 0? cases
   // quote
      t_( 18, "q", "'18'" ),
      t_( 18, "Q", "\"18\"" ),
   // cell
      t_( 18, "+Q(10c.)", "...\"+18\".." )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cRecorder* rec = &recorder_c_( 128 );

      bool res = write_int16_c( rec, t.val, t.fmt );
      res &= recorded_is_c( rec, t.exp );

      tap_descf_c( res, "test at index %"PRIi64, i );
   }

   return finish_tap_c_();
}
