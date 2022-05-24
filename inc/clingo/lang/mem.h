#ifndef CLINGO_LANG_MEM_H
#define CLINGO_LANG_MEM_H

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "clingo/apidecl.h"
#include "clingo/lang/func.h"
#include "clingo/lang/math.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

#define cGib_  1073741824

#define cMib_     1048576

#define cKib_        1024

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 dynamic memory allocation
*******************************************************************************/

#define alloc_c_( Type )                                                       \
   alloc_c( sizeof_c_( Type ) )
CLINGO_API
inline void* alloc_c( int64_t size )
{
   size_t sz;
   if ( not int64_to_size_c( size, &sz ) ) return NULL;

   return ( size > 0 ) ? calloc( sz, 1 )
                       : NULL;
}

#define alloc_array_c_( Number, Type )                                         \
   alloc_array_c( (Number), sizeof_c_( Type ) )
CLINGO_API
inline void* alloc_array_c( int64_t num, int64_t size )
{
   must_be_positive_c_( num );
   must_be_positive_c_( size );

   int64_t fullSize = 0;
   if ( not imul64_c( num, size, &fullSize ) )
   {
      return NULL;
   }

   return alloc_c( fullSize );
}

#define free_all_c_( ... )                                                     \
   free_all_c( nargs_c_( __VA_ARGS__ ), __VA_ARGS__ )
CLINGO_API
void free_all_c( int n, ... );

CLINGO_API
inline void* realloc_c( void* ptr, int64_t size )
{
   size_t sz;
   if ( not int64_to_size_c( size, &sz ) ) return NULL;

   return ( size > 0 ) ? realloc( ptr, sz )
                       : NULL;
}

#define realloc_array_c_( Ptr, Number, Type )                                  \
   realloc_array_c( (Ptr), (Number), sizeof_c_( Type ) )
CLINGO_API
inline void* realloc_array_c( void* ptr, int64_t num, int64_t size )
{
   must_be_positive_c_( num );
   must_be_positive_c_( size );

   int64_t fullSize = 0;
   if ( not imul64_c( num, size, &fullSize ) )
   {
      return NULL;
   }

   return realloc_c( ptr, fullSize );
}

/*******************************************************************************
 general
*******************************************************************************/

#define stack_mem_c_( Size )                                                   \
(                                                                              \
   (void*)((uint8_t[]){ [(Size)-1]=0 })                                        \
)

#define ref_c_( Type, Value )                                                  \
(                                                                              \
   (Type const[1]){ Value }                                                    \
)

#define sizeof_c_( Type )                                                      \
(                                                                              \
   (int64_t)sizeof( Type )                                                     \
)

#endif
