#include "clingo/io/cRecorder.h" // for cRecorder
#include "clingo/lang/chunk.h"
#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

CHUNK_C_( char const, cChars, cCharChunk )

int main( void )
{
   init_tap_c_();

   cChars slice = c_c( "abc" );
   cCharChunk chunk;

   // -------------------------------------------------------------- valid cases
   chunk = (cCharChunk)front_chunk_c_( 1, slice );
   expect_c_( valid_chunk_c_( chunk ) );

   chunk = (cCharChunk)front_chunk_c_( 3, slice );
   expect_c_( valid_chunk_c_( chunk ) );

   chunk = (cCharChunk)front_chunk_c_( 4, slice );
   expect_c_( valid_chunk_c_( chunk ) );

   // ------------------------------------------------------------ invalid cases
   chunk = (cCharChunk)front_chunk_c_( 0, slice );
   expect_c_( not valid_chunk_c_( chunk ) );

   // --------------------------------------------------------- iteration - next
   cRecorder* rec = &recorder_c_( 8 );
   chunk = (cCharChunk)front_chunk_c_( 2, c_c( "abcdefg" ) );
   while ( valid_chunk_c_( chunk ) )
   {
      record_chars_c( rec, (cChars){ chunk.s, chunk.v } );
      next_chunk_c_( chunk );
   }
   expect_c_( recorded_is_c( rec, "abcdefg" ) );

   // --------------------------------------------------------- iteration - prev
   reset_recorder_c( rec );
   chunk = (cCharChunk)back_chunk_c_( 2, c_c( "abcdefg" ) );
   while ( valid_chunk_c_( chunk ) )
   {
      record_chars_c( rec, (cChars){ chunk.s, chunk.v } );
      prev_chunk_c_( chunk );
   }
   expect_c_( recorded_is_c( rec, "fgdebca" ) );

   return finish_tap_c_();
}
