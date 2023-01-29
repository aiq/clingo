#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 4 );

   uint32_t const first = 0x33333333;
   uint32_t const second = 0x77777777;

   uint8_t const* firstPtr = rec->mem;
   expect_c_( record_mem_c( rec, 1, &first ) );
   expect_c_( *firstPtr == 0x33 );

   uint16_t const* secondPtr = rec->mem;
   expect_c_( record_mem_c( rec, 2, &second ) );
   expect_c_( *secondPtr == 0x7777 );

   expect_c_( not record_mem_c( rec, 3, "abc" ) ); // to large
   expect_c_( rec->pos == 3 );
   expect_c_( rec->space == 1 );

   return finish_tap_c_();
}
