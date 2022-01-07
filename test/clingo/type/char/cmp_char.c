#include "clingo/lang/expect.h"
#include "clingo/type/char.h"

int main( void )
{
   init_tap_c_();

   expect_lt_c_( cmp_char_c( '6', 'N' ) );
   expect_eq_c_( cmp_char_c( 'N', 'N' ) );
   expect_gt_c_( cmp_char_c( 'n', 'N' ) );

   return finish_tap_c_();
}
