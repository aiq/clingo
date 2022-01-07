#include <stddef.h>
#include <stdint.h>

_Static_assert( sizeof( size_t ) == 8, "size_t must be a 64 bit value" );

_Static_assert( sizeof( uint8_t )  == 1, "uint8_t must be a 8 bit value" );
_Static_assert( sizeof( uint16_t ) == 2, "uint16_t must be a 16 bit value" );
_Static_assert( sizeof( uint32_t ) == 4, "uint32_t must be a 32 bit value" );
_Static_assert( sizeof( uint64_t ) == 8, "uint64_t must be a 64 bit value" );

_Static_assert( sizeof( int8_t )  == 1, "int8_t must be a 8 bit value" );
_Static_assert( sizeof( int16_t ) == 2, "int16_t must be a 16 bit value" );
_Static_assert( sizeof( int32_t ) == 4, "int32_t must be a 32 bit value" );
_Static_assert( sizeof( int64_t ) == 8, "int64_t must be a 64 bit value" );
