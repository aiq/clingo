#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

TEMP_SLICE_C_(
   test,
   {
      uint32_t inp;
      uint16_t val;
      uint16_t low;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( 0x1d11e, 0xd834, 0xdd1e ),
      t_( 0x1f603, 0xd83d, 0xde03 ),
      t_( 0x2605, 0x2605, 0x0 )
   );

   for_each_c_( test const*, t, tests )
   {
      uint16_t low = 0;
      uint16_t high = utf32_to_utf16_c( t->inp, &low );
      expect_c_( t->val == high );
      expect_c_( t->low == low );
   }

   return finish_tap_c_();
}