#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"

#define expect_mem_( Chars, Exp )                                              \
   expect_c_( chars_is_c( (Chars), (Exp) ) )

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 10 );
   cChars mem = { rec->space, rec->mem };

   record_pad_c( rec, '_', 10 );
   expect_c_( rec->pos == 10 );
   expect_c_( rec->space == 0 );
   expect_mem_( mem, "__________" );

   expect_c_( move_recorder_to_c( rec, 2 ) );
   record_chars_c_( rec, "cd" );
   expect_mem_( mem, "__cd______" );

   expect_c_( move_recorder_to_c( rec, 6 ) );
   record_chars_c_( rec, "gh" );
   expect_mem_( mem, "__cd__gh__" );

   expect_c_( move_recorder_to_c( rec, 9 ) );
   record_chars_c_( rec, "j" );
   expect_mem_( mem, "__cd__gh_j" );

   expect_c_( move_recorder_to_c( rec, 0 ) );
   record_chars_c_( rec, "a" );
   expect_mem_( mem, "a_cd__gh_j" );

   expect_c_( not move_recorder_to_c( rec, 20 ) );

   return finish_tap_c_();
}
