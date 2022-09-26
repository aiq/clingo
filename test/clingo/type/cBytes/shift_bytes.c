#include "clingo/io/print.h"
#include "clingo/lang/expect.h"
#include "clingo/type/cBytes.h"

TEMP_SLICE_C_(
   test,
   {
      cVarBytes inp;
      int64_t offset;
      cBytes exp;
   }
)
#define t_( ... )((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_(
         slice_c_( cByte, 0x01, 0x02, 0x03, 0x04, 0x05 ),
         -4,
         slice_c_( cByte, 0x05, 0x02, 0x03, 0x04, 0x05 )
      ),
      t_(
         slice_c_( cByte, 0x01, 0x02, 0x03, 0x04, 0x05 ),
         -1,
         slice_c_( cByte, 0x02, 0x03, 0x04, 0x05, 0x05 )
      ),
      t_(
         slice_c_( cByte, 0x01, 0x02, 0x03, 0x04, 0x05 ),
         -5,
         slice_c_( cByte, 0x01, 0x02, 0x03, 0x04, 0x05 )
      ),
      t_(
         slice_c_( cByte, 0x01, 0x02, 0x03, 0x04, 0x05 ),
         4,
         slice_c_( cByte, 0x01, 0x02, 0x03, 0x04, 0x01 )
      ),
      t_(
         slice_c_( cByte, 0x01, 0x02, 0x03, 0x04, 0x05 ),
         1,
         slice_c_( cByte, 0x01, 0x01, 0x02, 0x03, 0x04 )
      ),
      t_(
         slice_c_( cByte, 0x01, 0x02, 0x03, 0x04, 0x05 ),
         5,
         slice_c_( cByte, 0x01, 0x02, 0x03, 0x04, 0x05 )
      )
   );

   for_each_c_( test const*, t, tests )
   {
      shift_bytes_c( t->inp, t->offset );
      bool res = eq_c( cmp_bytes_c( as_c_( cBytes, t->inp ), t->exp ) );
      expect_c_( res );
   }

   return finish_tap_c_();
}
