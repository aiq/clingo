#include "clingo/lang/expect.h"
#include "clingo/type/c_ByteOrder.h"
#include "clingo/type/cByte.h"
#include "clingo/type/uint32.h"

int main( void )
{
   init_tap_c_();

   uint32_t const origVal = 0xa1b2c3d4;
   uint32_t swapVal = swap_four_bytes_c_( origVal );

   cByte const* origPtr = (void const*)&origVal;
   cByte const* swapPtr = (void const*)&swapVal;

   expect_at_c_( origVal == 0xa1b2c3d4 );

   expect_at_c_( origPtr[ 0 ] == swapPtr[ 3 ] );
   expect_at_c_( origPtr[ 1 ] == swapPtr[ 2 ] );
   expect_at_c_( origPtr[ 2 ] == swapPtr[ 1 ] );
   expect_at_c_( origPtr[ 3 ] == swapPtr[ 0 ] );

   return finish_tap_c_();
}
