#include "clingo/container/CByteVec.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   CByteVec* vec = make_byte_vec_c( 1 );
   cVecInfo const* info = info_of_byte_vec_c( vec );

   expect_c_( vec_is_empty_c( info ) );
   expect_c_( info->cap == 1 );
   expect_c_( info->count == 0 );

   add_to_byte_vec_c( vec, 0xBA );
   add_to_byte_vec_c( vec, 0xBE );

   expect_c_( not vec_is_empty_c( info ) );
   expect_c_( info->cap > 1 );
   expect_c_( info->count == 2 );

   add_many_to_byte_vec_c_( vec, 0xBE, 0xEF, 0xC0, 0xDE );

   expect_c_( info->count == 6 );

   expect_c_( *get_from_byte_vec_c( vec, 0 ) == 0xBA );
   expect_c_( *get_from_byte_vec_c( vec, 3 ) == 0xEF );
   expect_c_( *get_from_byte_vec_c( vec, 5 ) == 0xDE );

   *get_var_from_byte_vec_c( vec, 3 ) = 0xBA;
   set_on_byte_vec_c( vec, 5, 0x11 );
   expect_c_( *get_from_byte_vec_c( vec, 3 ) == 0xBA );

   insert_into_byte_vec_c( vec, 5, 0xC0 );

   expect_c_( *get_from_byte_vec_c( vec, 6 ) == 0x11 );
   expect_c_( info->count == 7 );

   cRecorder* rec = &recorder_c_( 128 );
   write_byte_vec_c( rec, vec, "X//2" );

   expect_c_( recorded_is_c( rec, "BABE BEBA C0C0 11" ) );

   resize_byte_vec_c( vec, info->count );
   expect_c_( info->cap == info->count );

   release_c( vec );

   return finish_tap_c_();
}
