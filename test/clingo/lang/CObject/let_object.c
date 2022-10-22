#include "clingo/lang/CObject.h"
#include "clingo/lang/expect.h"

struct Counter
{
   int64_t val;
};
typedef struct Counter Counter;

static void cleanup( void* instance )
{
   Counter* counter = instance;
   counter->val += 1;
}

cMeta const CounterMeta = {
   .desc = stringify_c_( Counter ),
   .cleanup = &cleanup
};

int main( void )
{
   init_tap_c_();

   Counter* counter = let_object_c_( Counter, &CounterMeta );
   expect_c_( counter->val == 0 );

   release_c( counter );
   expect_c_( counter->val == 1 );

   release_c( counter );
   expect_c_( counter->val == 2 );

   return finish_tap_c_();
}