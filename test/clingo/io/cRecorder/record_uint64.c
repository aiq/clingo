#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"
#include "clingo/type/uint64.h" // swap_uint64_to_c

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 27 );

   // -------------------------------- value is written in the system byte order
   uint64_t const* recVal = rec->mem;
   expect_at_c_( record_uint64_c( rec, 7441822896345675318 ) );
   expect_at_c_( rec->pos == 8 );
   expect_at_c_( rec->space == 19 );
   expect_at_c_( *recVal == 7441822896345675318 );

   // ----------------------------------------- write with a specific byte order
   cByte const* recBig = rec->mem;
   uint64_t const big = swap_uint64_to_c( 0x00fe12dc34ba5678, c_BigEndian );
   expect_at_c_( record_uint64_c( rec, big ) );
   expect_at_c_( recBig[ 0 ] == 0x00 );
   expect_at_c_( recBig[ 1 ] == 0xfe );
   expect_at_c_( recBig[ 2 ] == 0x12 );
   expect_at_c_( recBig[ 3 ] == 0xdc );
   expect_at_c_( recBig[ 4 ] == 0x34 );
   expect_at_c_( recBig[ 5 ] == 0xba );
   expect_at_c_( recBig[ 6 ] == 0x56 );
   expect_at_c_( recBig[ 7 ] == 0x78 );

   cByte const* recLittle = rec->mem;
   uint64_t const little = swap_uint64_to_c( 0x00fe12dc34ba5678,
                                             c_LittleEndian);
   expect_at_c_( record_uint64_c( rec, little ) );
   expect_at_c_( recLittle[ 0 ] == 0x78 );
   expect_at_c_( recLittle[ 1 ] == 0x56 );
   expect_at_c_( recLittle[ 2 ] == 0xba );
   expect_at_c_( recLittle[ 3 ] == 0x34 );
   expect_at_c_( recLittle[ 4 ] == 0xdc );
   expect_at_c_( recLittle[ 5 ] == 0x12 );
   expect_at_c_( recLittle[ 6 ] == 0xfe );
   expect_at_c_( recLittle[ 7 ] == 0x00 );

   // --------------------------------------- try to record without enough space
   expect_at_c_( not record_uint64_c( rec, 123 ) );
   expect_at_c_( rec->pos == 24 );
   expect_at_c_( rec->space == 3 );

   return finish_tap_c_();
}
