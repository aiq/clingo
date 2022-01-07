#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"
#include "clingo/type/int16.h" // swap_int16_to_c

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 7 );

   // -------------------------------- value is written in the system byte order
   int16_t const* recVal = rec->mem;
   expect_c_( record_int16_c( rec, 12345 ) );
   expect_c_( rec->pos == 2 );
   expect_c_( rec->space == 5 );
   expect_c_( *recVal == 12345 ); 

   // ----------------------------------------- write with a specific byte order
   cByte const* recBig = rec->mem;
   int16_t const big = swap_int16_to_c( 0x3039, c_BigEndian );
   expect_c_( record_int16_c( rec, big ) );
   expect_c_( recBig[ 0 ] == 0x30 );
   expect_c_( recBig[ 1 ] == 0x39 );

   cByte const* recLittle = rec->mem;
   int16_t const little = swap_int16_to_c( 0x3039, c_LittleEndian );
   expect_c_( record_int16_c( rec, little ) );
   expect_c_( recLittle[ 0 ] == 0x39 );
   expect_c_( recLittle[ 1 ] == 0x30 );

   // --------------------------------------- try to record without enough space
   expect_c_( not record_int16_c( rec, 1 ) );
   expect_c_( rec->pos == 6 );
   expect_c_( rec->space == 1 );

   return finish_tap_c_();
}
