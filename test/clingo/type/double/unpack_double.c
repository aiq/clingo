#include "clingo/lang/expect.h"
#include "clingo/type/double.h"
#include "clingo/type/uint64.h" // for build_uint64_c_

int main( void )
{
   init_tap_c_();

   uint64_t ordered = build_uint64_c_( 0x01234567, 0x89ABCDEF );
   expect_at_c_( unpack_double_c( ordered ) == 3512700564088504e-318 );

   uint64_t min = build_uint64_c_( 0x00000000, 0x00000001 );
   expect_at_c_( unpack_double_c( min ) == 5e-324 );

   uint64_t max = build_uint64_c_( 0x7fefffff, 0xffffffff );
   expect_at_c_( unpack_double_c( max ) == 1.7976931348623157e308 );

   return finish_tap_c_();
}
