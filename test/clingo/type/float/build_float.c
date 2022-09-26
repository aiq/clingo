#include "clingo/lang/expect.h"
#include "clingo/type/float.h" 

TEMP_SLICE_C_(
   test,
   {
      uint8_t s;
      uint8_t e;
      uint32_t m;
      float exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( 1, 0x80, 0x48F5C3, -3.14f )
   );

   for_each_c_( test const*, t, tests )
   {
      cFloatInfo info = { t->s, t->e, t->m };
      float f = build_float_c( info );

      bool res = ( f == t->exp );

      tap_descf_c( res, "%x / %x / %x -> %f", t->s, t->e, t->m, t->exp );
   }

   return finish_tap_c_();
}
