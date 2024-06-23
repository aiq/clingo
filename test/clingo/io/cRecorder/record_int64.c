#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"
#include "clingo/type/int64.h" // swap_int64_to_c

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 27 );

   // -------------------------------- value is written in the system byte order
   int64_t const* recVal = rec->mem;
   expect_at_c_( record_int64_c( rec, 11223344556677 ) );
   expect_at_c_( rec->pos == 8 );
   expect_at_c_( rec->space == 19 );
   expect_at_c_( *recVal == 11223344556677 );
   
   // ----------------------------------------- write with a specific byte order
   cByte const* recBig = rec->mem;
   int64_t const big = swap_int64_to_c( 0x00ab789cd456ef23, c_BigEndian );
   expect_at_c_( record_int64_c( rec, big ) );
   expect_at_c_( recBig[ 0 ] == 0x00 );
   expect_at_c_( recBig[ 1 ] == 0xab );
   expect_at_c_( recBig[ 2 ] == 0x78 );
   expect_at_c_( recBig[ 3 ] == 0x9c );
   expect_at_c_( recBig[ 4 ] == 0xd4 );
   expect_at_c_( recBig[ 5 ] == 0x56 );
   expect_at_c_( recBig[ 6 ] == 0xef );
   expect_at_c_( recBig[ 7 ] == 0x23 );

   cByte const* recLittle = rec->mem;
   int64_t const little = swap_int64_to_c( 0x00ab789cd456ef23, c_LittleEndian );
   expect_at_c_( record_int64_c( rec, little ) );
   expect_at_c_( recLittle[ 0 ] == 0x23 );
   expect_at_c_( recLittle[ 1 ] == 0xef );
   expect_at_c_( recLittle[ 2 ] == 0x56 );
   expect_at_c_( recLittle[ 3 ] == 0xd4 );
   expect_at_c_( recLittle[ 4 ] == 0x9c );
   expect_at_c_( recLittle[ 5 ] == 0x78 );
   expect_at_c_( recLittle[ 6 ] == 0xab );
   expect_at_c_( recLittle[ 7 ] == 0x00 );

   // --------------------------------------- try to record without enough space
   expect_at_c_( not record_int64_c( rec, 123 ) );
   expect_at_c_( rec->pos == 24 );
   expect_at_c_( rec->space == 3 );

   return finish_tap_c_();
}
