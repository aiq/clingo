#include "clingo/lang/expect.h"
#include "clingo/type/uint64.h"

uint64_t check_range( uint64_t from, uint64_t exp )
{
   uint64_t val = from;
   for ( ; val <= exp; ++val )
   {
      if ( next_pow2_uint64_c( val ) != exp )
      {
         break;
      }
   }
   return val;
}

int main( void )
{
   init_tap_c_();

   expect_at_c_( check_range( 0, 0 ) == 1 );
   // --------------------------------------------------------------- first byte
   // HEX: oo oo oo oo oo oo oo o1 -> oo oo oo oo oo oo oo 8o
   expect_at_c_( check_range( 1, 1 ) == 2 );
   expect_at_c_( check_range( 2, 2 ) == 3 );
   expect_at_c_( check_range( 3, 4 ) == 5 );
   expect_at_c_( check_range( 5, 8 ) == 9 );

   expect_at_c_( check_range( 9, 16 ) == 17 );
   expect_at_c_( check_range( 17, 32 ) == 33 );
   expect_at_c_( check_range( 33, 64 ) == 65 );
   expect_at_c_( check_range( 65, 128 ) == 129 );

   // -------------------------------------------------------------- second byte
   // HEX: oo oo oo oo oo oo o1 oo -> oo oo oo oo oo oo 8o oo
   expect_at_c_( check_range( 129, 256 ) == 257 );
   expect_at_c_( check_range( 257, 512 ) == 513 );
   expect_at_c_( check_range( 513, 1024 ) == 1025 );
   expect_at_c_( check_range( 1025, 2048 ) == 2049 );

   expect_at_c_( check_range( 2049, 4096 ) == 4097 );
   expect_at_c_( check_range( 4097, 8192 ) == 8193 );
   expect_at_c_( check_range( 8193, 16384 ) == 16385 );
   expect_at_c_( check_range( 16385, 32768 ) == 32769 );

   // --------------------------------------------------------------- third byte
   // HEX: oo oo oo oo oo o1 oo oo -> oo oo oo oo oo 8o oo oo
   expect_at_c_( check_range( 32769, 65536 ) == 65537 );
   expect_at_c_( check_range( 65537, 131072 ) == 131073 );
   expect_at_c_( check_range( 131073, 262144 ) == 262145 );
   expect_at_c_( check_range( 262145, 524288 ) == 524289 );

   expect_at_c_( check_range( 524289, 1048576 ) == 1048577 );
   expect_at_c_( check_range( 1048577, 2097152 ) == 2097153 );
   expect_at_c_( check_range( 2097153, 4194304 ) == 4194305 );
   expect_at_c_( check_range( 4194305, 8388608 ) == 8388609 );

   return finish_tap_c_();
}
