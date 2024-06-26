#include "clingo/io/FILE.h"
#include "clingo/lang/error.h"
#include "clingo/lang/expect.h"

#define expect_recorded_( Rec, Exp )                                           \
{                                                                              \
   expect_at_c_(                                                                  \
      recorded_is_c( (Rec), (Exp) )                                            \
   );                                                                          \
   reset_recorder_c( Rec );                                                    \
}

int main( void )
{
   init_tap_c_();

   cErrorStack* es = &error_stack_c_( 248 );
   void const* mem = es->mem;

   reset_error_stack_c( es );
   expect_at_c_( mem == es->mem );

   push_error_c_( es, &C_Eof );
   expect_at_c_( mem != es->mem );

   reset_error_stack_c( es );
   expect_at_c_( mem == es->mem );

   push_lit_error_c( es, "file error" );
   push_invalid_value_error_c( es, "other type" );
   push_error_c_( es, &C_Eof );
   expect_at_c_( mem != es->mem );

   reset_error_stack_c( es );
   expect_at_c_( mem == es->mem );

   return finish_tap_c_();
}