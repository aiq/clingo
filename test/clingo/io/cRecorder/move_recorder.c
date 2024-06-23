#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"

#define expect_mem_( Chars, Exp )                                              \
   expect_at_c_( chars_is_c( (Chars), (Exp) ) )

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 10 );
   cChars mem = { rec->space, rec->mem };

   record_pad_c( rec, '_', 10 );
   expect_at_c_( rec->pos == 10 );
   expect_at_c_( rec->space == 0 );
   expect_mem_( mem, "__________" );

   expect_at_c_( move_recorder_c( rec, -8 ) );
   record_chars_c_( rec, "cd" );
   expect_mem_( mem, "__cd______" );
   
   expect_at_c_( move_recorder_c( rec, 2 ) );
   record_chars_c_( rec, "gh" );
   expect_mem_( mem, "__cd__gh__" );

   expect_at_c_( move_recorder_c( rec, 1 ) );
   record_chars_c_( rec, "j" );
   expect_mem_( mem, "__cd__gh_j" );

   expect_at_c_( move_recorder_c( rec, -10 ) );
   record_chars_c_( rec, "a" );
   expect_mem_( mem, "a_cd__gh_j" );

   expect_at_c_( not move_recorder_c( rec, -20 ) );
   expect_at_c_( not move_recorder_c( rec, 20 ) );

   return finish_tap_c_();
}
