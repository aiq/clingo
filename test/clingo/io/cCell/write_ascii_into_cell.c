#include "clingo/io/cCell.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      cCell cell;
      char const* ascii;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( cell_c_( 6, '<', '.' ), "abc", "abc..." ),
      t_( cell_c_( 6, '=', '_' ), "cde", "__cde_" ),
      t_( cell_c_( 6, '>', ' ' ), "def", "   def" ),
      t_( cell_c_( 4, '>', '+' ), "abcdef", "abcd" )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   for_each_c_( i, test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 128 );

      bool res = write_ascii_into_cell_c( rec, c_c( t->ascii ), &t->cell );
      res &= rec->pos == t->cell.size;
      res &= recorded_is_c( rec, t->exp );

      expect_c_( i, res );
   }

   return finish_tap_c_();
}
