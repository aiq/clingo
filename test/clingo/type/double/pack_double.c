#include "clingo/lang/expect.h"
#include "clingo/type/double.h"
#include "clingo/type/uint64.h" // for build_uint64_c_

int main( void )
{
   init_tap_c_();

   double ordered = 3512700564088504e-318;
   uint64_t expOrdered = build_uint64_c_( 0x01234567, 0x89ABCDEF );
   expect_c_( pack_double_c( ordered ) == expOrdered );

   double min = 5e-324;
   uint64_t expMin = build_uint64_c_( 0x00000000, 0x00000001 );
   expect_c_( pack_double_c( min ) == expMin );

   double max = 1.7976931348623157e308;
   uint64_t expMax = build_uint64_c_( 0x7fefffff, 0xffffffff );
   expect_c_( pack_double_c( max ) == expMax );

   return finish_tap_c_();;
}
