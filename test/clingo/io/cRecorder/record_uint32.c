#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"
#include "clingo/type/uint32.h" // swap_uint32_to_c

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 13 );

   // -------------------------------- value is written in the system byte order
   uint32_t const* recVal = rec->mem;
   expect_at_c_( record_uint32_c( rec, 773388221 ) );
   expect_at_c_( rec->pos == 4 );
   expect_at_c_( rec->space == 9 );
   expect_at_c_( *recVal == 773388221 );

   // ----------------------------------------- write with a specific byte order
   cByte const* recBig = rec->mem;
   uint32_t const big = swap_uint32_to_c( 0x2e18f7bd, c_BigEndian );
   expect_at_c_( record_uint32_c( rec, big ) );
   expect_at_c_( recBig[ 0 ] == 0x2e );
   expect_at_c_( recBig[ 1 ] == 0x18 );
   expect_at_c_( recBig[ 2 ] == 0xf7 );
   expect_at_c_( recBig[ 3 ] == 0xbd );

   cByte const* recLittle = rec->mem;
   uint32_t const little = swap_uint32_to_c( 0x2e18f7bd, c_LittleEndian );
   expect_at_c_( record_uint32_c( rec, little ) );
   expect_at_c_( recLittle[ 0 ] == 0xbd );
   expect_at_c_( recLittle[ 1 ] == 0xf7 );
   expect_at_c_( recLittle[ 2 ] == 0x18 );
   expect_at_c_( recLittle[ 3 ] == 0x2e );

   // --------------------------------------- try to record without enough space
   expect_at_c_( not record_uint32_c( rec, 1 ) );
   expect_at_c_( rec->pos == 12 );
   expect_at_c_( rec->space == 1 );

   return finish_tap_c_();
}
