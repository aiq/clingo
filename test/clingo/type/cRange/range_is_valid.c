#include "clingo/lang/expect.h"
#include "clingo/type/cRange.h"

int main( void )
{
   init_tap_c_();

   cRange valid = { .min = 0, .max = 10 };
   expect_at_c_( range_is_valid_c( valid ) );

   cRange invalid = { .min = 0, .max = -10 };
   expect_at_c_( not range_is_valid_c( invalid ) );

   return finish_tap_c_();
}
