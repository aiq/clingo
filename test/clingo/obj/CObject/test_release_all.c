#include "clingo/lang/CPointer.h"
#include "clingo/lang/expect.h"

int main( int argc, const char** args )
{
   begin_test_c( __FILE__, argc, args );

   int* v1 = alloc_default_pointer_c_( int );
   int* v2 = alloc_default_pointer_c_( int );
   expect_equal_c_( references_c( v1 ), 0 );
   expect_equal_c_( references_c( v2 ), 0 );

   retain_c( v2 );
   retain_c( v2 );
   expect_equal_c_( references_c( v1 ), 0 );
   expect_equal_c_( references_c( v2 ), 2 );

   release_all_c_( v1, v2 );
   expect_equal_c_( references_c( v2 ), 1 );

   release_c( v2 );

   return test_result_c();
}
