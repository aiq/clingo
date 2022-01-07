#include "clingo/lang/expect.h"
#include "clingo/type/bool.h"

int main( void )
{
   init_tap_c_();

   expect_lt_c_( cmp_bool_c( false,  true ) );
   expect_eq_c_( cmp_bool_c( false, false ) );
   expect_eq_c_( cmp_bool_c(  true,  true ) );
   expect_gt_c_( cmp_bool_c(  true, false ) );

   return finish_tap_c_();
}
