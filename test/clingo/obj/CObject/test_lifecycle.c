#include "clingo/lang/CPointer.h"

#include "clingo/lang/expect.h"

void test_int_pointer()
{
   int* value = alloc_default_pointer_c_( int );
   expect_equal_c_( references_c( value ), 0 );

   *value = 20;

   retain_c( value );
   expect_equal_c_( references_c( value ), 1 );

   retain_c( value );
   expect_equal_c_( references_c( value ), 2 );

   release_c( value );
   expect_equal_c_( references_c( value ), 1 );

   release_c( value );
}

int main( int argc, const char** args )
{
   begin_test_c( __FILE__, argc, args );

   test_int_pointer();

   return test_result_c();
}
