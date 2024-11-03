#ifndef CLINGO_CONTAINER_CBITVEC_H
#define CLINGO_CONTAINER_CBITVEC_H

#include "clingo/apidecl.h"
#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/lang/CObject.h"
#include "clingo/type/cByte.h"
#include "clingo/type/cRange.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

CLINGO_API extern cMeta const C_BitVec;

struct CBitVec;
typedef struct CBitVec CBitVec;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 create
*******************************************************************************/

CLINGO_API CBitVec* new_bit_vec_c( int64_t n );

CLINGO_API CBitVec* copy_bit_vec_c( CBitVec const* vec );

CLINGO_API CBitVec* bit_vec_from_chars_c( cChars chars );

CLINGO_API inline CBitVec* bit_vec_from_cstr_c( char const bitstr[static 1] )
{
   must_exist_c_( bitstr );
   return bit_vec_from_chars_c( c_c( bitstr ) );
}

CLINGO_API bool resize_bit_vec_c( CBitVec* vec, int64_t n );

/*******************************************************************************
 prop
*******************************************************************************/

CLINGO_API int64_t bit_vec_size_c( CBitVec const* vec );

CLINGO_API cByte get_from_bit_vec_c( CBitVec const* vec, int64_t pos );

CLINGO_API int64_t find_index_of_bit_c( CBitVec const* vec,
                             cByte bit,
                             int64_t from );

CLINGO_API int64_t popcount_bit_vec_c( CBitVec const* vec, cByte bit );

CLINGO_API int64_t rfind_index_of_bit_c( CBitVec const* vec,
                              cByte bit,
                              int64_t from );

/*******************************************************************************
 set
*******************************************************************************/

CLINGO_API bool set_on_bit_vec_c( CBitVec* vec, int64_t pos, cByte bit );

CLINGO_API bool set_range_on_bit_vec_c( CBitVec* vec, cRange range, cByte bit );

/*******************************************************************************
 logic
*******************************************************************************/

CLINGO_API CBitVec* bitand_bit_vec_c( CBitVec const* a, CBitVec const* b );

CLINGO_API bool bitand_on_bit_vec_c( CBitVec* a, CBitVec const* b );

/**************************************/

CLINGO_API CBitVec* bitor_bit_vec_c( CBitVec const* a, CBitVec const* b );

CLINGO_API bool bitor_on_bit_vec_c( CBitVec* a, CBitVec const* b );

/**************************************/

CLINGO_API CBitVec* compl_bit_vec_c( CBitVec const* vec );

CLINGO_API bool compl_on_bit_vec_c( CBitVec* vec );

/**************************************/

CLINGO_API CBitVec* xor_bit_vec_c( CBitVec const* a, CBitVec const* b );

CLINGO_API bool xor_on_bit_vec_c( CBitVec* a, CBitVec const* b );

/*******************************************************************************
 shift
*******************************************************************************/

CLINGO_API void shift_bit_vec_c( CBitVec* vec, int64_t distance, cByte fill );

/*******************************************************************************
 cmp
*******************************************************************************/

#define bit_vec_is_c_( Vec, Cstr )                                             \
   bit_vec_is_c( (Vec), c_c( Cstr ) )
CLINGO_API bool bit_vec_is_c( CBitVec* vec, cChars chars );

CLINGO_API int cmp_bit_vec_c( CBitVec const* a, CBitVec const* b );

CLINGO_API inline bool eq_bit_vec_c( CBitVec const* a, CBitVec const* b )
{
   return eq_c( cmp_bit_vec_c( a, b ) );
}

/*******************************************************************************
 io
*******************************************************************************/

#define read_bit_vec_c_( Sca, Vec )                                            \
   read_bit_vec_c( (Sca), (Vec), "" )
CLINGO_API bool read_bit_vec_c( cScanner sca[static 1],
                                CBitVec* vec[static 1],
                                char const fmt[static 1] );

#define write_bit_vec_c_( Rec, Vec )                                           \
   write_bit_vec_c( (Rec), (Vec), "" )
CLINGO_API bool write_bit_vec_c( cRecorder rec[static 1],
                                 CBitVec const* vec,
                                 char const fmt[static 1] );

#endif
