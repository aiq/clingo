#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   expect_diff_c_( strcmp( "a", "z" ) );
   expect_diff_c_( strcmp( "z", "a" ) );
   expect_eq_c_( strcmp( "a", "a" ) );

   expect_gt_c_( strcmp( "z", "a" ) );
   expect_gte_c_( strcmp( "z", "a" ) );
   expect_gte_c_( strcmp( "z", "z" ) );

   expect_lt_c_( strcmp( "a", "z" ) );
   expect_lte_c_( strcmp( "a", "z" ) );
   expect_lte_c_( strcmp( "a", "a" ) );

   return finish_tap_c_();
}
