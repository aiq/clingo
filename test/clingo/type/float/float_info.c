#include "clingo/lang/expect.h"
#include "clingo/type/float.h" 

TEMP_SLICE_C_(
   test,
   {
      float val;
      uint8_t s;
      uint8_t e;
      uint32_t m;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( 3.14f, 0, 0x80, 0x48F5C3 )
   );

   for_each_c_( test const*, t, tests )
   {
      cFloatInfo info = float_info_c( t->val );

      bool res = true;
      res &= info.sign == t->s;
      res &= info.exponent == t->e;
      res &= info.mantissa == t->m;

      tap_desc_c_( res, "{f} -> {u8:x} / {u8:x} / {u32:x}", t->val, t->s, t->e, t->m );
   }

   return finish_tap_c_();
}
