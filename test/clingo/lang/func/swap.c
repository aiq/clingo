#include "clingo/lang/func.h"
#include "clingo/lang/expect.h"
#include "clingo/type/cRange.h" // cRange

int main( void )
{
   init_tap_c_();

   // ----------------------------------------------------------------- swap int
   int x = 5;
   int y = 9;

   swap_c_( int, x, y, tmp_int );

   expect_c_( x == 9 );
   expect_c_( y == 5 );

   // --------------------------------------------------------------- swap float
   float fx = 1.0;
   float fy = 99.0;

   swap_c_( float, fx, fy, tmp_float );

   expect_c_( fx == 99.0 );
   expect_c_( fy == 1.0 );

   // ------------------------------------------------------------- swap structs
   cRange a = { .min = 1, .max = 5 };
   cRange z = { .min = 4, .max = 5 };

   swap_c_( cRange, a, z, tmp_range );

   expect_c_( a.min == 4 );
   expect_c_( a.max == 5 );

   expect_c_( z.min == 1 );
   expect_c_( z.max == 5 );

   return finish_tap_c_();
}
