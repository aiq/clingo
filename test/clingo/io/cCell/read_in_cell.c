#include "clingo/io/cCell.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      char const* str;
      cCell exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "(8c )", cell_c_( 8, 0, ' ' ) ),
      t_( "(16l-)", cell_c_( 16, -1, '-' ) ),
      t_( "(256r.)", cell_c_( 256, 1, '.' ) )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cScanner *sca = &cstr_scanner_c_( t.str );
      cCell cell;

      bool res = read_in_cell_c( sca, &cell );
      res &= cell.orient == t.exp.orient;
      res &= cell.size == t.exp.size;
      res &= cell.pad == t.exp.pad;

      tap_desc_c_( res, "test at index {i64}", i );
   }

   return finish_tap_c_();
}
