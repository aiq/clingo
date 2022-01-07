#include "clingo/io/cRecorder.h" // for cRecorder
#include "clingo/lang/chunk.h"
#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   cChars slice = c_c( "abc" );
   cCharChunk chunk;

   // -------------------------------------------------------------- valid cases
   init_front_char_chunk_c( &chunk, 1, slice );
   expect_c_( valid_chunk_c_( chunk ) );

   init_front_char_chunk_c( &chunk, 3, slice );
   expect_c_( valid_chunk_c_( chunk ) );

   init_front_char_chunk_c( &chunk, 4, slice );
   expect_c_( valid_chunk_c_( chunk ) );

   // ------------------------------------------------------------ invalid cases
   init_front_char_chunk_c( &chunk, 0, slice );
   expect_c_( not valid_chunk_c_( chunk ) );

   // --------------------------------------------------------- iteration - next
   cRecorder* rec = &recorder_c_( 8 );
   init_front_char_chunk_c( &chunk, 2, c_c( "abcdefg" ) );
   while ( valid_chunk_c_( chunk ) )
   {
      record_chars_c( rec, chars_c( chunk.s, chunk.v ) );
      next_chunk_c_( chunk );
   }
   expect_c_( recorded_is_c( rec, "abcdefg" ) );

   // --------------------------------------------------------- iteration - prev
   reset_recorder_c( rec );
   init_back_char_chunk_c( &chunk, 2, c_c( "abcdefg" ) );
   while ( valid_chunk_c_( chunk ) )
   {
      record_chars_c( rec, chars_c( chunk.s, chunk.v ) );
      prev_chunk_c_( chunk );
   }
   expect_c_( recorded_is_c( rec, "fgdebca" ) );

   return finish_tap_c_();
}
