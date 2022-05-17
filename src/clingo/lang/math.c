#include "clingo/lang/math.h"

/*******************************************************************************
 abs
*******************************************************************************/

extern inline bool iabs8_c( int8_t src, int8_t dst[static 1] );
extern inline bool iabs16_c( int16_t src, int16_t dst[static 1] );
extern inline bool iabs32_c( int32_t src, int32_t dst[static 1] );
extern inline bool iabs64_c( int64_t src, int64_t dst[static 1] );

/*******************************************************************************
 add
*******************************************************************************/

extern inline bool iadd8_c( int8_t a, int8_t b, int8_t res[static 1] );
extern inline bool iadd16_c( int16_t a, int16_t b, int16_t res[static 1] );
extern inline bool iadd32_c( int32_t a, int32_t b, int32_t res[static 1] );
extern inline bool iadd64_c( int64_t a, int64_t b, int64_t res[static 1] );

extern inline bool uadd8_c( uint8_t a, uint8_t b, uint8_t res[static 1] );
extern inline bool uadd16_c( uint16_t a, uint16_t b, uint16_t res[static 1] );
extern inline bool uadd32_c( uint32_t a, uint32_t b, uint32_t res[static 1] );
extern inline bool uadd64_c( uint64_t a, uint64_t b, uint64_t res[static 1] );

/*******************************************************************************
 max
*******************************************************************************/

extern inline int8_t imax8_c( int8_t a, int8_t b );
extern inline int16_t imax16_c( int16_t a, int16_t b );
extern inline int32_t imax32_c( int32_t a, int32_t b );
extern inline int64_t imax64_c( int64_t a, int64_t b );

extern inline uint8_t umax8_c( uint8_t a, uint8_t b );
extern inline uint16_t umax16_c( uint16_t a, uint16_t b );
extern inline uint32_t umax32_c( uint32_t a, uint32_t b );
extern inline uint64_t umax64_c( uint64_t a, uint64_t b );

/*******************************************************************************
 min
*******************************************************************************/

extern inline int8_t imin8_c( int8_t a, int8_t b );
extern inline int16_t imin16_c( int16_t a, int16_t b );
extern inline int32_t imin32_c( int32_t a, int32_t b );
extern inline int64_t imin64_c( int64_t a, int64_t b );

extern inline uint8_t umin8_c( uint8_t a, uint8_t b );
extern inline uint16_t umin16_c( uint16_t a, uint16_t b );
extern inline uint32_t umin32_c( uint32_t a, uint32_t b );
extern inline uint64_t umin64_c( uint64_t a, uint64_t b );

/*******************************************************************************
 mul
*******************************************************************************/

extern inline bool imul8_c( int8_t a, int8_t b, int8_t res[static 1] );
extern inline bool imul16_c( int16_t a, int16_t b, int16_t res[static 1] );
extern inline bool imul32_c( int32_t a, int32_t b, int32_t res[static 1] );
extern inline bool imul64_c( int64_t a, int64_t b, int64_t res[static 1] );

extern inline bool umul8_c( uint8_t a, uint8_t b, uint8_t res[static 1] );
extern inline bool umul16_c( uint16_t a, uint16_t b, uint16_t res[static 1] );
extern inline bool umul32_c( uint32_t a, uint32_t b, uint32_t res[static 1] );
extern inline bool umul64_c( uint64_t a, uint64_t b, uint64_t res[static 1] );

/*******************************************************************************
 sub
*******************************************************************************/

extern inline bool isub8_c( int8_t a, int8_t b, int8_t res[static 1] );
extern inline bool isub16_c( int16_t a, int16_t b, int16_t res[static 1] );
extern inline bool isub32_c( int32_t a, int32_t b, int32_t res[static 1] );
extern inline bool isub64_c( int64_t a, int64_t b, int64_t res[static 1] );

extern inline bool usub8_c( uint8_t a, uint8_t b, uint8_t res[static 1] );
extern inline bool usub16_c( uint16_t a, uint16_t b, uint16_t res[static 1] );
extern inline bool usub32_c( uint32_t a, uint32_t b, uint32_t res[static 1] );
extern inline bool usub64_c( uint64_t a, uint64_t b, uint64_t res[static 1] );


/*******************************************************************************
 conv
*******************************************************************************/

extern inline bool int64_to_size_c( int64_t src, size_t dest[static 1] );
extern inline bool size_to_int64_c( size_t src, int64_t dest[static 1] );
extern inline bool size_to_uint64_c( size_t src, uint64_t dest[static 1] );
extern inline bool uint64_to_size_c( uint64_t src, size_t dest[static 1] );

