#include "clingo/lang/expect.h"
#include "clingo/type/c_ByteOrder.h"
#include "clingo/type/cByte.h"
#include "clingo/type/uint16.h"

int main( void )
{
   init_tap_c_();

   uint16_t const origVal = 0x12cd;
   uint16_t swapVal = swap_two_bytes_c_( origVal );

   cByte const* origPtr = (void const*)&origVal;
   cByte const* swapPtr = (void const*)&swapVal;

   expect_c_( origVal == 0x12cd );

   expect_c_( origPtr[ 0 ] == swapPtr[ 1 ] );
   expect_c_( origPtr[ 1 ] == swapPtr[ 0 ] );

   return finish_tap_c_();
}
