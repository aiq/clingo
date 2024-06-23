#include "clingo/lang/expect.h"
#include "clingo/type/c_ByteOrder.h"
#include "clingo/type/cByte.h"
#include "clingo/type/uint64.h"

int main( void )
{
   init_tap_c_();

   uint64_t const origVal = 0xabcdef0123456789;
   uint64_t swapVal = swap_eight_bytes_c_( origVal );

   cByte const* origPtr = (void const*)&origVal;
   cByte const* swapPtr = (void const*)&swapVal;

   expect_at_c_( origVal == 0xabcdef0123456789 );

   expect_at_c_( origPtr[ 0 ] == swapPtr[ 7 ] );
   expect_at_c_( origPtr[ 1 ] == swapPtr[ 6 ] );
   expect_at_c_( origPtr[ 2 ] == swapPtr[ 5 ] );
   expect_at_c_( origPtr[ 3 ] == swapPtr[ 4 ] );

   expect_at_c_( origPtr[ 4 ] == swapPtr[ 3 ] );
   expect_at_c_( origPtr[ 5 ] == swapPtr[ 2 ] );
   expect_at_c_( origPtr[ 6 ] == swapPtr[ 1 ] );
   expect_at_c_( origPtr[ 7 ] == swapPtr[ 0 ] );

   return finish_tap_c_();
}
