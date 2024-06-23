#include "clingo/lang/expect.h"
#include "clingo/type/cRange.h"

int main( void )
{
   init_tap_c_();

   cRange a = { .min=22, .max=55 };
   cRange b = { .min=22, .max=53 };

   expect_at_c_( eq_range_c( a, a ) );
   expect_at_c_( not eq_range_c( a, b ) );

   return finish_tap_c_();
}
