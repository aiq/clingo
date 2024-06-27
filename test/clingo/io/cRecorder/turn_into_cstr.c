#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cRecorder* rec = NULL;
   char const* cstr = "";

   rec = &null_recorder_c_();
   cstr = turn_into_cstr_c( rec );
   expect_eq_c_( strcmp( cstr, "" ) );

   rec = &recorder_c_( 4 );
   cstr = turn_into_cstr_c( rec );
   expect_eq_c_( strcmp( cstr, "" ) );

   record_chars_c_( rec, "ab" );
   cstr = turn_into_cstr_c( rec );
   expect_eq_c_( strcmp( cstr, "ab" ) );

   record_cstr_c( rec, "abc" );
   cstr = turn_into_cstr_c( rec );
   expect_eq_c_( strcmp( cstr, "abc" ) );

   record_chars_c_( rec, "" );
   cstr = turn_into_cstr_c( rec );
   expect_eq_c_( strcmp( cstr, "" ) );

   record_chars_c_( rec, "abcd" );
   cstr = turn_into_cstr_c( rec );
   expect_eq_c_( strcmp( cstr, "" ) );

   return finish_tap_c_();
}
