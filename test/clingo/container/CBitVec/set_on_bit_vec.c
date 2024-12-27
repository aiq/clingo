#include "clingo/container/CBitVec.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      char const* inp;
      cInt64s positions;
      cByte val;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_(
         .inp = "0000 0000 0000 000",
         .positions = (cInt64s)slice_c_( int64_t, 0, 3, 4, 7, 10, 11, 14 ),
         .val = 1,
         .exp = "1001 1001 0011 001"
      ),
      t_(
         .inp = "1001 1001 0011 001",
         .positions = (cInt64s)slice_c_( int64_t, 19 ),
         .val = 1,
         .exp = "1001 1001 0011 0010 0001"
      )
   );

   for_each_c_( i, test const*, t, tests )
   {
      CBitVec* vec = bit_vec_from_cstr_c( t->inp );
      each_c_( int64_t const*, pos, t->positions )
      {
         set_on_bit_vec_c( vec, *pos, t->val );
      }
      expect_block_c_( i, bit_vec_is_c_( vec, t->exp ) )
      {
         tap_exp_line_c_( "{s}", t->exp );
         tap_got_line_c_( "{t:01/80/4}", bit_vec_tape_c( vec ) );
      }
      release_c( vec );
   }

   return finish_tap_c_();
}
