#include "clingo/container/CBitVec.h"
#include "clingo/lang/expect.h"

#define expect_( Vec, BinStr )                                                 \
   expect_at_c_( bit_vec_is_c_( (Vec), (BinStr) ) )

int main( void )
{
   init_tap_c_();

   { // ------------------------------------------------------------ short shift
      CBitVec* vec = bit_vec_from_cstr_c( "00010111" );
      expect_at_c_( bit_vec_size_c( vec ) == 8 );

      shift_bit_vec_c( vec, -1, 0 );
      expect_( vec, "00101110" );
  
      shift_bit_vec_c( vec, 1, 1 ); 
      expect_( vec, "10010111" );

      shift_bit_vec_c( vec, -3, 1 );
      expect_( vec, "10111111" );

      shift_bit_vec_c( vec, 3, 0 );
      expect_( vec, "00010111" );

      release_c( vec );
   }
   { // -------------------------------------------------------------- big shift
      CBitVec* vec = bit_vec_from_cstr_c( "00001111 00001111 00001111"
                                          "00001111 00001111 0000" );
      expect_at_c_( bit_vec_size_c( vec ) == 44 );

      shift_bit_vec_c( vec, -5, 1 );
      expect_( vec, "11100001 11100001 11100001"
                    "11100001 11100001 1111" );

      shift_bit_vec_c( vec, 6, 0 );
      expect_( vec, "00000011 10000111 10000111"
                    "10000111 10000111 1000" );

      shift_bit_vec_c( vec, -13, 1 );
      expect_( vec, "11110000 11110000 11110000"
                    "11110001 11111111 1111" );

      shift_bit_vec_c( vec, 16, 0 );
      expect_( vec, "00000000 00000000 11110000"
                    "11110000 11110000 1111" );

      release_c( vec );
   }

   return finish_tap_c_();
}
