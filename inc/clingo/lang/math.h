#ifndef CLINGO_LANG_MATH_H
#define CLINGO_LANG_MATH_H

#include "clingo/apidecl.h"
#include "clingo/lang/func.h"

/*******************************************************************************
******************************************************** Code Generation Macros 
********************************************************************************

*******************************************************************************/

#define ABS_C_(                                                                \
   FuncName, Type, EdgeValue                                                   \
)                                                                              \
bool FuncName( Type val, Type res[static 1] )                                  \
{                                                                              \
   if ( val == EdgeValue )                                                     \
   {                                                                           \
      return false;                                                            \
   }                                                                           \
                                                                               \
   *res = val < 0 ? -val                                                       \
                  : val;                                                       \
   return true;                                                                \
}

/**************************************/

#define ADD_C_(                                                                \
   FuncName, Type, MinValue, MaxValue                                          \
)                                                                              \
bool FuncName( Type a, Type b, Type res[static 1] )                            \
{                                                                              \
   if ( ( b > 0 and a > MaxValue - b ) or                                      \
        ( b < 0 and a < MinValue - b ) )                                       \
   {                                                                           \
      return false;                                                            \
   }                                                                           \
                                                                               \
   *res = a + b;                                                               \
   return true;                                                                \
}

/**************************************/

#define CONV_C_(                                                               \
   FuncName, FromType, ToType, MinValue, MaxValue                              \
)                                                                              \
bool FuncName( FromType src, ToType dst[static 1] )                            \
{                                                                              \
   must_exist_c_( dst );                                                       \
                                                                               \
   if ( in_range_c_( MinValue, src, MaxValue ) )                               \
   {                                                                           \
      *dst = (ToType)src;                                                      \
      return true;                                                             \
   }                                                                           \
                                                                               \
   return false;                                                               \
}

/**************************************/

#define MAX_C_(                                                                \
   FuncName, Type                                                              \
)                                                                              \
Type FuncName( Type a, Type b )                                                \
{                                                                              \
   return a > b ? a                                                            \
                : b;                                                           \
}

/**************************************/

#define MIN_C_(                                                                \
   FuncName, Type                                                              \
)                                                                              \
Type FuncName( Type a, Type b )                                                \
{                                                                              \
   return a < b ? a                                                            \
                : b;                                                           \
}

/**************************************/

#define MUL_C_(                                                                \
   FuncName, Type, TmpType, MinValue, MaxValue                                 \
)                                                                              \
bool FuncName( Type a, Type b, Type res[static 1] )                            \
{                                                                              \
   TmpType tmp = (TmpType) a * b;                                              \
   if ( not in_range_c_( MinValue, tmp, MaxValue ) )                           \
   {                                                                           \
      return false;                                                            \
   }                                                                           \
                                                                               \
   *res = (Type)tmp;                                                           \
   return true;                                                                \
}

/**************************************/

#define SUB_C_(                                                                \
   FuncName, Type, MinValue, MaxValue                                          \
)                                                                              \
bool FuncName( Type a, Type b, Type res[static 1] )                            \
{                                                                              \
   if ( ( b > 0 and a < MinValue + b ) or                                      \
        ( b < 0 and a > MaxValue + b ) )                                       \
   {                                                                           \
      return false;                                                            \
   }                                                                           \
                                                                               \
   *res = a - b;                                                               \
   return true;                                                                \
}


/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 abs
*******************************************************************************/

// ----------- FuncName,   Type,    EdgeValue
CLINGO_API inline ABS_C_( iabs8_c,    int8_t,  INT8_MIN )
CLINGO_API inline ABS_C_( iabs16_c,   int16_t, INT16_MIN )
CLINGO_API inline ABS_C_( iabs32_c,   int32_t, INT32_MIN )
CLINGO_API inline ABS_C_( iabs64_c,   int64_t, INT64_MIN )

#define abs_c_( Val, Res )                                                     \
   _Generic( ( *Res ),                                                         \
      int8_t: iabs8_c,                                                         \
      int16_t: iabs16_c,                                                       \
      int32_t: iabs32_c,                                                       \
      int64_t: iabs64_c                                                        \
   )( (Val), (Res) )

/*******************************************************************************
 add
*******************************************************************************/

// ----------- FuncName,   Type,       MinValue,   MaxValue
CLINGO_API inline ADD_C_( iadd8_c,    int8_t,     INT8_MIN,   INT8_MAX )
CLINGO_API inline ADD_C_( iadd16_c,   int16_t,    INT16_MIN,  INT16_MAX )
CLINGO_API inline ADD_C_( iadd32_c,   int32_t,    INT32_MIN,  INT32_MAX )
CLINGO_API inline ADD_C_( iadd64_c,   int64_t,    INT64_MIN,  INT64_MAX )

CLINGO_API inline ADD_C_( uadd8_c,    uint8_t,    0,          UINT8_MAX )
CLINGO_API inline ADD_C_( uadd16_c,   uint16_t,   0,          UINT16_MAX )
CLINGO_API inline ADD_C_( uadd32_c,   uint32_t,   0,          UINT32_MAX )
CLINGO_API inline ADD_C_( uadd64_c,   uint64_t,   0,          UINT64_MAX )

#define add_c_( A, B, Res )                                                    \
   _Generic( ( *Res ),                                                         \
      int8_t: iadd8_c,                                                         \
      int16_t: iadd16_c,                                                       \
      int32_t: iadd32_c,                                                       \
      int64_t: iadd64_c,                                                       \
      uint8_t: uadd8_c,                                                        \
      uint16_t: uadd16_c,                                                      \
      uint32_t: uadd32_c,                                                      \
      uint64_t: uadd64_c                                                       \
   )( (A), (B), (Res) )

/*******************************************************************************
 conv
*******************************************************************************/

CLINGO_API inline CONV_C_(
   int64_to_size_c,  // FuncName
   int64_t,          // FromType
   size_t,           // ToType
   0,                // MinValue
   INT64_MAX         // MaxValue
)

CLINGO_API inline CONV_C_(
   size_to_int64_c,  // FuncName
   size_t,           // FromType
   int64_t,          // ToType
   0,                // MinValue
   INT64_MAX         // MaxValue
)

CLINGO_API inline CONV_C_(
   size_to_uint64_c, // FuncName
   size_t,           // FromType
   uint64_t,         // ToType
   0,                // MinValue
   UINT64_MAX        // MaxValue
)

CLINGO_API inline CONV_C_(
   uint64_to_size_c,    // FuncName
   uint64_t,            // FromType
   size_t,              // ToType
   0,                   // MinValue
   SIZE_MAX             // MaxValue
)

/*******************************************************************************
 max
*******************************************************************************/

// ----------- FuncName,   Type
CLINGO_API inline MAX_C_( imax8_c,    int8_t )
CLINGO_API inline MAX_C_( imax16_c,   int16_t )
CLINGO_API inline MAX_C_( imax32_c,   int32_t )
CLINGO_API inline MAX_C_( imax64_c,   int64_t )

CLINGO_API inline MAX_C_( umax8_c,    uint8_t )
CLINGO_API inline MAX_C_( umax16_c,   uint16_t )
CLINGO_API inline MAX_C_( umax32_c,   uint32_t )
CLINGO_API inline MAX_C_( umax64_c,   uint64_t )

#define max_c_( A, B )                                                         \
   _Generic( ( (A) + (B) ),                                                    \
      int8_t: imax8_c,                                                         \
      int16_t: imax16_c,                                                       \
      int32_t: imax32_c,                                                       \
      int64_t: imax64_c,                                                       \
      uint8_t: umax8_c,                                                        \
      uint16_t: umax16_c,                                                      \
      uint32_t: umax32_c,                                                      \
      uint64_t: umax64_c,                                                      \
      float: fmaxf,                                                            \
      double: fmax,                                                            \
      long double: fmaxl                                                       \
   )( (A), (B) )

/*******************************************************************************
 min
*******************************************************************************/

// ----------- FuncName,   Type
CLINGO_API inline MIN_C_( imin8_c,    int8_t )
CLINGO_API inline MIN_C_( imin16_c,   int16_t )
CLINGO_API inline MIN_C_( imin32_c,   int32_t )
CLINGO_API inline MIN_C_( imin64_c,   int64_t )

CLINGO_API inline MIN_C_( umin8_c,    uint8_t )
CLINGO_API inline MIN_C_( umin16_c,   uint16_t )
CLINGO_API inline MIN_C_( umin32_c,   uint32_t )
CLINGO_API inline MIN_C_( umin64_c,   uint64_t )

#define min_c_( A, B )                                                         \
   _Generic( ( (A) + (B) ),                                                    \
      int8_t: imin8_c,                                                         \
      int16_t: imin16_c,                                                       \
      int32_t: imin32_c,                                                       \
      int64_t: imin64_c,                                                       \
      uint8_t: umin8_c,                                                        \
      uint16_t: umin16_c,                                                      \
      uint32_t: umin32_c,                                                      \
      uint64_t: umin64_c,                                                      \
      float: fminf,                                                            \
      double: fmin,                                                            \
      long double: fminl                                                       \
   )( (A), (B) )

/*******************************************************************************
 mul
*******************************************************************************/

// ----------- FuncName,   Type,    TmpType, MinValue,   MaxValue
CLINGO_API inline MUL_C_( imul8_c,    int8_t,  int16_t, INT8_MIN,   INT8_MAX )
CLINGO_API inline MUL_C_( imul16_c,   int16_t, int32_t, INT16_MIN,  INT16_MAX )
CLINGO_API inline MUL_C_( imul32_c,   int32_t, int64_t, INT32_MIN,  INT32_MAX )
CLINGO_API inline bool imul64_c( int64_t a, int64_t b, int64_t res[static 1] )
{
   if (
         ( a > 0 and b > 0 and a > ( INT64_MAX / b ) ) or
         ( a > 0 and b < 0 and b < ( INT64_MIN / a ) ) or
         ( a < 0 and b > 0 and a < ( INT64_MIN / b ) ) or
         ( a < 0 and b < 0 and b < ( INT64_MAX / a ) )
      )
   {
      return false;
   }

   *res = a * b;
   return true;
}

// ----------- FuncName,   Type.       TmpType,    MinValue,   MaxValue
CLINGO_API inline MUL_C_( umul8_c,    uint8_t,    uint16_t,   0,          UINT8_MAX )
CLINGO_API inline MUL_C_( umul16_c,   uint16_t,   uint32_t,   0,          UINT16_MAX )
CLINGO_API inline MUL_C_( umul32_c,   uint32_t,   uint64_t,   0,          UINT32_MAX )
CLINGO_API inline bool umul64_c( uint64_t a, uint64_t b, uint64_t res[static 1] )
{
   if ( a > b )
   {
      return umul64_c( b, a, res );
   }
   if ( a > UINT32_MAX )
   {
      return false;
   }
   uint32_t c = b >> 32;
   uint32_t d = UINT32_MAX & b;
   uint64_t r = a * c;
   uint64_t s = a * d;
   if ( r > UINT32_MAX )
   {
      return false;
   }
   r <<= 32;
   return uadd64_c( s, r, res );
}

#define mul_c_( A, B, Res )                                                    \
   _Generic( ( *Res ),                                                         \
      int8_t: imul8_c,                                                         \
      int16_t: imul16_c,                                                       \
      int32_t: imul32_c,                                                       \
      int64_t: imul64_c,                                                       \
      uint8_t: umul8_c,                                                        \
      uint16_t: umul16_c,                                                      \
      uint32_t: umul32_c,                                                      \
      uint64_t: umul64_c                                                       \
   )( (A), (B), (Res) )

/*******************************************************************************
 sub
*******************************************************************************/

// ----------- FuncName,   Type,       MinValue,   MaxValue
CLINGO_API inline SUB_C_( isub8_c,    int8_t,     INT8_MIN,   INT8_MAX )
CLINGO_API inline SUB_C_( isub16_c,   int16_t,    INT16_MIN,  INT16_MAX )
CLINGO_API inline SUB_C_( isub32_c,   int32_t,    INT32_MIN,  INT32_MAX )
CLINGO_API inline SUB_C_( isub64_c,   int64_t,    INT64_MIN,  INT64_MAX )

CLINGO_API inline SUB_C_( usub8_c,    uint8_t,    0,          UINT8_MAX )
CLINGO_API inline SUB_C_( usub16_c,   uint16_t,   0,          UINT16_MAX )
CLINGO_API inline SUB_C_( usub32_c,   uint32_t,   0,          UINT32_MAX )
CLINGO_API inline SUB_C_( usub64_c,   uint64_t,   0,          UINT64_MAX )

#define sub_c_( A, B, Res )                                                    \
   _Generic( ( *Res )                                                          \
      int8_t: isub8_c,                                                         \
      int16_t: isub16_c,                                                       \
      int32_t: isub32_c,                                                       \
      int64_t: isub64_c,                                                       \
      uint8_t: usub8_c,                                                        \
      uint16_t: usub16_c,                                                      \
      uint32_t: usub32_c,                                                      \
      uint64_t: usub64_c                                                       \
   )( (A), (B), (Res) )

#endif
