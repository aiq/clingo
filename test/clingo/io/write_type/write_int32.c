#include "clingo/io/write_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      int32_t val;
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
      t_( 1234567, "x", "12d687" ),
      t_( 1234567, "0x", "12d687" ),
      t_( -0x12d687, "X", "-12D687" ),
      t_( -0x12d687, "0X", "FFED2979" ),
      // "o"/"0o"
      t_( 123456, "o", "361100" ),
      t_( 123456, "0o", "361100" ),
      t_( -123456, "o", "-361100" ),
      t_( -123456, "0o", "37777416700" ),
      // "b"/"B"/"0b"/"0B"
      t_( 123456789, "b", "111""o1o11o11""11oo11o1""ooo1o1o1" ),
      t_( 123456789, "0b", "111""o1o11o11""11oo11o1""ooo1o1o1" ),
      t_( -123456789, "b", "-111""o1o11o11""11oo11o1""ooo1o1o1" ),
      t_( -123456789, "0B", "11111000""10100100""00110010""11101011" ),
      // sign
      t_( 190, "+", "+190" ),
      t_( -190, "+", "-190" ),
      t_( 190, "+X", "+BE" ),
      t_( -190, "+0X", "FFFFFF42" ), // sign does not work for 0? cases
      // quote
      t_( 1, "+dq", "'+1'" ),
      t_( 42, "+oQ", "\"+52\"" ),
      // cell
      t_( 12, "0x(8>0)", "0000000c" ),
      t_( 18, "+q(10=.)", "...'+18'.." )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cRecorder* rec = &recorder_c_( 128 );

      bool res = write_int32_c( rec, t.val, t.fmt );
      res &= recorded_is_c( rec, t.exp );

      tap_c_( res, C_TapDesc, "test at index {i64}", i );
   }

   return finish_tap_c_();
}
