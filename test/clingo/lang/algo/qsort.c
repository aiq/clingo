#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"
#include "clingo/type/char.h"

#define expect_( VarChars, Exp )                                               \
   expect_c_(                                                                  \
      chars_is_c( as_chars_c( VarChars ), (Exp) )                              \
   )

int main( void )
{
   init_tap_c_();

   cVarChars chars = scalars_c_( 128, char );

   //---------------------------------------------------------- sort short slice

   cVarChars quicksort = chars;
   quicksort.s = set_chars_c_( quicksort, "quicksort" );

   qsort_chars_c( quicksort );

   expect_( quicksort, "cikoqrstu" );

   //----------------------------------------- sort slice with many equal values

   cRecorder* rec = &make_recorder_c_( chars.s, chars.v );
   times_c_( 4, xyz )
   {
      record_chars_c_( rec, "abcdefghijklmnopqrstuvwxyz" );
   }
   cVarChars abcx4 = recorded_var_chars_c( rec );

   qsort_chars_c( abcx4 );

   expect_c_( recorded_is_c( rec, "aaaabbbbccccddddeeeeffffgggghhhhiiii"
                                  "jjjjkkkkllllmmmmnnnnooooppppqqqq"
                                  "rrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz" ) );

   printf( "res: %s\n", quicksort.v );

   return finish_tap_c_();
}
