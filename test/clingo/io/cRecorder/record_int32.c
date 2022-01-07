#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"
#include "clingo/type/int32.h" // swap_int32_to_c

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 13 );

   // -------------------------------- value is written in the system byte order
   int32_t const* recVal = rec->mem;
   expect_c_( record_int32_c( rec, 1234567890 ) );
   expect_c_( rec->pos == 4 );
   expect_c_( rec->space == 9 );
   expect_c_( *recVal == 1234567890 ); 

   // ----------------------------------------- write with a specific byte order
   cByte const* recBig = rec->mem;
   int32_t const big = swap_int32_to_c( 0x499602d2, c_BigEndian );
   expect_c_( record_int32_c( rec, big ) );
   expect_c_( recBig[ 0 ] == 0x49 );
   expect_c_( recBig[ 1 ] == 0x96 );
   expect_c_( recBig[ 2 ] == 0x02 );
   expect_c_( recBig[ 3 ] == 0xd2 );

   cByte const* recLittle = rec->mem;
   int32_t const little = swap_int32_to_c( 0x499602d2, c_LittleEndian );
   expect_c_( record_int32_c( rec, little ) );
   expect_c_( recLittle[ 0 ] == 0xd2 );
   expect_c_( recLittle[ 1 ] == 0x02 );
   expect_c_( recLittle[ 2 ] == 0x96 );
   expect_c_( recLittle[ 3 ] == 0x49 );

   // --------------------------------------- try to record without enough space
   expect_c_( not record_int32_c( rec, 1 ) );
   expect_c_( rec->pos == 12 );
   expect_c_( rec->space == 1 );

   return finish_tap_c_();
}
