#include "clingo/io/write_type.h"
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

   cRecorder* rec = &recorder_c_( 128 );

   expect_at_c_( write_char_c_( rec, 'a' ) );   // ""
   expect_recorded_( rec, "a" );

   expect_at_c_( write_char_c( rec, 'a', "c" ) );
   expect_recorded_( rec, "a" );

   expect_at_c_( write_char_c( rec, 'b', "q" ) );
   expect_recorded_( rec, "'b'" );

   expect_at_c_( write_char_c( rec, 'c', "Q" ) );
   expect_recorded_( rec, "\"c\"" );

   return finish_tap_c_();
}
