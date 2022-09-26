#include "clingo/lang/expect.h"
#include "clingo/type/double.h"

TEMP_SLICE_C_(
   test,
   {
      double d;
      bool exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( 1.0, true ),
      t_( 0.5, true ),
      t_( 0.25, true ),
      t_( 0.2, false ),
      t_( 0.125, true ),
      t_( 0.1, false )
   );

   for_each_c_( test const*, t, tests )
   {
      float f;
      bool res = double_to_float_c( t->d, &f );

      tap_descf_c( res == t->exp, "%f", t->d );
   }

   return finish_tap_c_();
}