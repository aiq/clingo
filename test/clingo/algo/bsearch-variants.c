#include "clingo/algo/bsearch.h"
#include "clingo/lang/expect.h"
#include "clingo/lang/mem.h"  // ref_c_

// ************************************* custom struct
struct intSlice
{
   int64_t s;
   int const* v;
};
typedef struct intSlice intSlice;

// ************************************* example that compares two values
int cmp_val_val( int a, int b )
{
   return a < b ? -1
                : a > b ? 1
                        : 0;
}
// int const* bsearch_val_val( intSlice slice, int val );
BSEARCH_C_(
   bsearch_val_val,  // FuncName
   intSlice,         // SliceType
   int const,        // ValueType
   int,              // SearchType
   cmp_val_val,      // CmpFunc
   *                 // Deref
)

// ************************************* example that compares value with pointer
int cmp_val_ptr( int a, int const* b )
{
   return cmp_val_val( a, *b );
}
// int const* bsearch_val_ptr( intSlice slice, int const* val );
BSEARCH_C_(
   bsearch_val_ptr,  // FuncName
   intSlice,         // SliceType
   int const,        // ValueType
   int const*,       // SearchType
   cmp_val_ptr,      // CmpFunc
   *                 // Deref
)

// ************************************* example that compare pointer with value
int cmp_ptr_val( int const* a, int b )
{
   return cmp_val_val( *a, b );
}
// int const* bsearch_ptr_val( intSlice slice, int val );
BSEARCH_C_(
   bsearch_ptr_val,  // FuncName
   intSlice,         // SliceType
   int const,        // ValueType
   int,              // SearchType
   cmp_ptr_val,      // CmpFunc
   /*optional*/      // Deref
)

// ************************************* example that compares two pointers
int cmp_ptr_ptr( int const* a, int const* b )
{
   return cmp_val_val( *a, *b );
}
// int const* bsearch_ptr_ptr( intSlice slice, int const* val );
BSEARCH_C_(
   bsearch_ptr_ptr,  // FuncName
   intSlice,         // SliceType
   int const,        // ValueType
   int const*,       // SearchType
   cmp_ptr_ptr,      // CmpFunc
   /*optional*/      // Deref
)

// ************************************* 
int main( void )
{
   init_tap_c_();

   intSlice slice = slice_c_( int, 1, 5, 10, 15, 20, 25, 30, 35 );

   int const* valValRes = bsearch_val_val( slice, 25 );
   expect_equal_c_( index_of_c_( slice, valValRes ), 5 );

   int const* valPtrRes = bsearch_val_ptr( slice, ref_c_( int, 35 ) );
   expect_equal_c_( index_of_c_( slice, valPtrRes ), 7 );

   int const* ptrValRes = bsearch_ptr_val( slice, 1 );
   expect_equal_c_( index_of_c_( slice, ptrValRes ), 0 );

   int const* ptrPtrRes = bsearch_ptr_ptr( slice, ref_c_( int, 5 ) );
   expect_equal_c_( index_of_c_( slice, ptrPtrRes ), 1 );

   return finish_tap_c_();
}
