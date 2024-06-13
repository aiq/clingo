#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

TEMP_SLICE_C_(
   test,
   {
      char const* input;
      int8_t exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "☂", 3 ),
      t_( "y", 1 ),
      t_( "®", 2 ),
      t_( "€", 3 ),
      t_( "𝄞", 4 ),
      t_( "yes", 1 )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cRune r = rune_c( t.input );
      int8_t res = rune_size_c( r );
      tap_desc_c_( res == t.exp, "test at index {i64}", i );
   }

   return finish_tap_c_();
}
