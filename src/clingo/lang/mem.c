#include "clingo/lang/mem.h"

#include <stdio.h>
#include <stdint.h>

/*******************************************************************************

*******************************************************************************/

extern inline void* alloc_c( int64_t size );
extern inline void* alloc_array_c( int64_t num, int64_t size );
extern inline void* realloc_c( void* ptr, int64_t size );
extern inline void* realloc_array_c( void* ptr, int64_t num, int64_t size );

void free_all_c( int n, ... )
{
   va_list list;

   va_start( list, n );

   for ( int i = 0; i < n; ++i )
   {
      void* val = va_arg( list, void* );
      free( val );
   }

   va_end( list );
}

