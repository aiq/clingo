#include "clingo/lang/expect.h"
#include "clingo/type/uint32.h"

int main( void )
{
   init_tap_c_();

   cUint32Slice slice = slice_c_( uint32_t, 123456, 5648, 658, 79456, 658 );

   uint32_t const* min = min_uint32_c( slice );
   expect_c_( index_of_c_( slice, min ) == 2 );
   expect_c_( *min == 658 );

   return finish_tap_c_();
}
