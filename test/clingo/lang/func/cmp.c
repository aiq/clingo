#include "clingo/lang/expect.h"
#include "clingo/lang/func.h"
#include "clingo/type/int64.h"

int main( void )
{
   init_tap_c_();

   int less = cmp_int64_c( -100, 100 );
   int equal = cmp_int64_c( 64, 64 );
   int greater = cmp_int64_c( 128, 64 );

   expect_c_( lt_c( less ) );
   expect_c_( not lt_c( equal ) );
   expect_c_( not lt_c( greater ) );

   expect_c_( lte_c( less ) );
   expect_c_( lte_c( equal ) );
   expect_c_( not lte_c( greater ) );

   expect_c_( not eq_c( less ) );
   expect_c_( eq_c( equal ) );
   expect_c_( not eq_c( greater ) );

   expect_c_( not gte_c( less ) );
   expect_c_( gte_c( equal ) );
   expect_c_( gte_c( greater ) );

   expect_c_( not gt_c( less ) );
   expect_c_( not gt_c( equal ) );
   expect_c_( gt_c( greater ) );

   return finish_tap_c_();
}
