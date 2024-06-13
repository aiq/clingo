#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

TEMP_SLICE_C_(
   test,
   {
      char const* input;
      uint32_t exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "A", 0x41 ),
      t_( "ö", 0xf6 ),
      t_( "Ж", 0x0416 ),
      t_( "€", 0x20ac ),
      t_( "𝄞", 0x1d11e ),
      t_( "α", 0x03b1 ),
      t_( "😎", 0x01f60e )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cRune r = rune_c( t.input );
      uint32_t res = rune_code_c( r );
      tap_desc_c_( res == t.exp, "test at index {i64}", i );
   }

   return finish_tap_c_();
}
