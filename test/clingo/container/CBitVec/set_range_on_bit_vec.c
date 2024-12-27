#include "clingo/container/CBitVec.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      char const* inp;
      cRange rng;
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
         .inp = "1000 0001 0000 001",
         .rng = closed_range_c_( 5, 9 ),
         .val = 1,
         .exp = "1000 0111 1100 001"
      ),
      t_(
         .inp = "1000 0111 1100 001",
         .rng = closed_range_c_( 6, 8 ),
         .val = 0,
         .exp = "1000 0100 0100 001"
      ),
      t_(
         .inp = "1000 0100 0100 001",
         .rng = closed_range_c_( 17, 19 ),
         .val = 1,
         .exp = "1000 0100 0100 0010 0111"
      ),
      t_(
         .inp = "1000 0100 0100 0010 0111",
         .rng = closed_range_c_( 18, 25 ),
         .val = 0,
         .exp = "1000 0100 0100 0010 0100"
      )
   );

   for_each_c_( i, test const*, t, tests )
   {
      CBitVec* vec = bit_vec_from_cstr_c( t->inp );
      set_range_on_bit_vec_c( vec, t->rng, t->val );
      expect_block_c_( i, bit_vec_is_c_( vec, t->exp ) )
      {
         tap_exp_line_c_( "{s}", t->exp );
         tap_got_line_c_( "{:01/80/4}", bit_vec_tape_c( vec ) );
      }
      release_c( vec );
   }

   return finish_tap_c_();
}
