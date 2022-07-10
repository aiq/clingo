#include "clingo/io/FILE.h"
#include "clingo/lang/error.h"
#include "clingo/lang/expect.h"

#define expect_recorded_( Rec, Exp )                                           \
{                                                                              \
   expect_c_(                                                                  \
      recorded_is_c( (Rec), (Exp) )                                            \
   );                                                                          \
   reset_recorder_c( Rec );                                                    \
}

int main( void )
{
   init_tap_c_();

   cErrorStack* es = &error_stack_c_( 248 );
   cRecorder* rec = &recorder_c_( 1024 );

   push_error_c_( es, &C_Eof );
   push_lit_str_error_c( es, "file error" );
   push_read_error_c( es, "some type" );
   write_error_c( rec, es->err, "" );
   expect_recorded_( rec, "not able to read 'some type': file error: EOF" );

   push_invalid_value_error_c( es, "other type" );
   write_error_c( rec, es->err, "" );
   expect_recorded_( rec, "invalid 'other type' value: not able to read 'some type': file error: EOF" );

   return finish_tap_c_();
}