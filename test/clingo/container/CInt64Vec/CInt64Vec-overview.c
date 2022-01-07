#include "clingo/container/CInt64Vec.h"
#include "clingo/io/cRecorder.h"
#include "clingo/io/write_type.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   CInt64Vec* vec = retain_c( make_int64_vec_c( 1 ) );
   cVecInfo const* info = info_of_int64_vec_c( vec );

   expect_c_( vec_is_empty_c( info ) );
   expect_c_( info->cap == 1 );
   expect_c_( info->count == 0 );

   add_to_int64_vec_c( vec, 100 );
   add_to_int64_vec_c( vec, 200 );

   expect_c_( not vec_is_empty_c( info ) );
   expect_c_( info->cap > 1 );
   expect_c_( info->count == 2 );

   add_many_to_int64_vec_c_( vec, 300, 400, 500 );

   expect_c_( *get_from_int64_vec_c( vec, 0 ) == 100 );
   expect_c_( *get_from_int64_vec_c( vec, 2 ) == 300 );
   expect_c_( *get_from_int64_vec_c( vec, 4 ) == 500 );

   set_on_int64_vec_c( vec, 4, 555 );
   expect_c_( *get_from_int64_vec_c( vec, 4 ) == 555 );

   insert_into_int64_vec_c( vec, 3, 350 );
   expect_c_( info->count == 6 );

   cRecorder* rec = &recorder_c_( 128 );
   {
      cInt64Slice slice = slice_of_int64_vec_c( vec );
      for_each_c_( int64_t const*, i, slice )
      {
         write_int64_c_( rec, *i );
         if ( i != rbegin_c_( slice ) )
         {
            record_char_c( rec, ' ' );
         }
      }
   }
   expect_c_( recorded_is_c( rec, "100 200 300 350 400 555" ) );

   resize_int64_vec_c( vec, info->count );
   expect_c_( info->cap == info->count );

   release_all_c_( vec );

   return finish_tap_c_();
}
