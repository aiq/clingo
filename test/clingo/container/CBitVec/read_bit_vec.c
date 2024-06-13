#include "clingo/container/CBitVec.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      char const* txt;
      char const* fmt;
      char const* exp;
      char const* tail;
   }
)
#define t_( ... )((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
   // bits
      t_( "oooo111111 o11ooo1111 ooo1", "", "oooo111111 o11ooo1111 ooo1", "" ),
      t_( "o1o1 o1o1 ", "", "o1o1o1o1", " " ),
   // list
      t_( "4-9, 11 - 12, 16-19, 23  ", "list", "oooo111111 o11ooo1111 ooo1", "  " ),
      t_( "1-2,4,6,8,12,14;", "list", "o11o1o1o1o oo1o1", ";" ),
   // zip
      t_( "4z6i_2i3z4i3z+/", "zip", "oooo111111 o11ooo1111 ooo1", "/" ),
      t_( "_2i_+_+_+3z+_+", "zip", "o11o1o1o1o oo1o1", "" )
   );

   for_each_c_( test const*, t, tests )
   {
      cScanner* sca = &cstr_scanner_c_( t->txt );

      CBitVec* vec;
      if ( not read_bit_vec_c( sca, &vec, t->fmt ) )
      {
         tap_c_( false, C_TapDesc, "{s}", t->txt );
         continue;
      }

      cRecorder* rec = &recorder_c_( 128 );
      require_c_( write_bit_vec_c_( rec, vec ) );

      bool res = recorded_is_c( rec, t->exp ) and
                 unscanned_is_c( sca, t->tail );
      release_c( vec );

      tap_desc_c_( res, "{s}", t->txt );
   }

   return finish_tap_c_();
}