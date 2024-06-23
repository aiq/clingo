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
      t_( "(8)", cell_c_( 8, '<', ' ' ) ),
      t_( "(12<)", cell_c_( 12, '<', ' ' ) ),
      t_( "(8= )", cell_c_( 8, '=', ' ' ) ),
      t_( "(16<-)", cell_c_( 16, '<', '-' ) ),
      t_( "(256>.)", cell_c_( 256, '>', '.' ) )
   );

   for_each_c_( i, test const*, t, tests )
   {
      cScanner *sca = &cstr_scanner_c_( t->str );
      cCell cell;

      bool res = scan_cell_c( sca, &cell );
      res &= cell.orient == t->exp.orient;
      res &= cell.size == t->exp.size;
      res &= cell.pad == t->exp.pad;

      expect_c_( i, res );
   }

   return finish_tap_c_();
}
