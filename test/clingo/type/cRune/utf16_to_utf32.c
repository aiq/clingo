#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

TEMP_SLICE_C_(
   test,
   {
      uint16_t h;
      uint16_t l;
      uint32_t exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( 0xd834, 0xdd1e, 0x1d11e ),
      t_( 0xd83d, 0xde03, 0x1f603 ),
      t_( 0x2605, 0x0, 0x2605 )
   );

   for_each_c_( test const*, t, tests )
   {
      uint32_t val = utf16_to_utf32_c( t->h, t->l );
      expect_c_( val == t->exp );
   }

   return finish_tap_c_();
}
