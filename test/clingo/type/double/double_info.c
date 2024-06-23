#include "clingo/io/write.h"
#include "clingo/lang/expect.h"
#include "clingo/type/double.h"

TEMP_SLICE_C_(
   test,
   {
      double val;
      uint8_t s;
      uint16_t e;
      uint64_t m;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( 3.14, 0, 0x400, 0x91eb851eb851f )
   );

   each_c_( test const*, t, tests )
   {
      cDoubleInfo info = double_info_c( t->val );

      bool res = true;
      res &= ( info.sign == t->s );
      res &= ( info.exponent == t->e );
      res &= ( info.mantissa == t->m );

      tap_desc_c_( res, "{d} -> {u8:x} / {u16:x} / {u64:x}", t->val, t->s, t->e, t->m );
   }

   return finish_tap_c_();
}
