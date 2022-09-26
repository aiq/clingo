#include "clingo/io/read_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      char const* str;
      cRange exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "[-213,-78]", closed_range_c_( -213, -78 ) ),
      t_( "[0..1984)", closed_open_range_c_( 0, 1984 ) ),
      t_( "(-56;56]", open_closed_range_c_( -56, 56 ) ),
      t_( "(64..256)", open_range_c_( 64, 256 ) )
   );

   for_each_c_( test const*, t, tests )
   {
      cScanner* sca = &cstr_scanner_c_( t->str );

      cRange dst;
      bool res = read_range_c( sca, &dst, "" );
      res &= eq_range_c( dst, t->exp );

      tap_descf_c( res, "test %s", t->str );
   }

   return finish_tap_c_();
}
