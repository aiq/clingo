#include "clingo/io/write.h"
#include "clingo/lang/expect.h"
#include "clingo/type/double.h"

TEMP_SLICE_C_(
   test,
   {
      uint8_t s;
      uint16_t e;
      uint64_t m;
      double exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( 1, 0x400, 0x91eb851eb851f, -3.14 )
   );

   for_each_c_( test const*, t, tests )
   {
      cDoubleInfo info = { t->s, t->e, t->m };
      double d = build_double_c( info );

      bool res = ( d == t->exp );

      cRecorder* rec = &recorder_c_( 128 );
      {
         char const* fmt = "{u8:x} / {u16:x} / {u64:x} -> {d}";
         write_c_( rec, fmt, t->s, t->e, t->m, t->exp );
      }
      tap_desc_c_( res, "{rec}", rec );
   }

   return finish_tap_c_();
}
