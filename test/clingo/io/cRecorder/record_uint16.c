#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"
#include "clingo/type/uint16.h" // swap_uint16_to_c

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 7 );

   // -------------------------------- value is written in the system byte order
   uint16_t const* recVal = rec->mem;
   expect_c_( record_uint16_c( rec, 25386 ) );
   expect_c_( rec->pos == 2 );
   expect_c_( rec->space == 5 );
   expect_c_( *recVal == 25386 );

   // ----------------------------------------- write with a specific byte order
   cByte const* recBig = rec->mem;
   uint16_t const big = swap_uint16_to_c( 0x632a, c_BigEndian );
   expect_c_( record_uint16_c( rec, big ) );
   expect_c_( recBig[ 0 ] == 0x63 );
   expect_c_( recBig[ 1 ] == 0x2A );

   cByte const* recLittle = rec->mem;
   uint16_t const little = swap_uint16_to_c( 0x632a, c_LittleEndian );
   expect_c_( record_uint16_c( rec, little ) );
   expect_c_( recLittle[ 0 ] == 0x2A );
   expect_c_( recLittle[ 1 ] == 0x63 );

   // --------------------------------------- try tp record without enough space
   expect_c_( not record_uint16_c( rec, 1 ) );
   expect_c_( rec->pos == 6 );
   expect_c_( rec->space == 1 );

   return finish_tap_c_();
}
