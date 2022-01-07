#ifndef CLINGO_CONTAINER_CBIT_VEC_H
#define CLINGO_CONTAINER_CBIT_VEC_H

#include "clingo/io/cRecorder.h"
#include "clingo/lang/CObject.h"
#include "clingo/type/cByte.h"
#include "clingo/type/cRange.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

extern cMeta const C_BitVecMeta;

struct CBitVec;
typedef struct CBitVec CBitVec;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 create
*******************************************************************************/

CBitVec* new_bit_vec_c( int64_t n );

CBitVec* copy_bit_vec_c( CBitVec const* vec );

CBitVec* bit_vec_from_chars_c( cChars chars );

inline CBitVec* bit_vec_from_cstr_c( char const bitstr[static 1] )
{
   must_exist_c_( bitstr );
   return bit_vec_from_chars_c( c_c( bitstr ) );
}

/*******************************************************************************
 prop
*******************************************************************************/

int64_t bit_vec_size_c( CBitVec const* vec );

cByte get_from_bit_vec_c( CBitVec const* vec, int64_t pos );

int64_t find_index_of_bit_c( CBitVec const* vec,
                             cByte bit,
                             int64_t from );

int64_t popcount_bit_vec_c( CBitVec const* vec, cByte bit );

int64_t rfind_index_of_bit_c( CBitVec const* vec,
                              cByte bit,
                              int64_t from );

/*******************************************************************************
 set
*******************************************************************************/

void set_on_bit_vec_c( CBitVec* vec, int64_t pos, cByte bit );

void set_range_on_bit_vec_c( CBitVec* vec, cRange range, cByte bit );

/*******************************************************************************
 logic
*******************************************************************************/

CBitVec* bitand_bit_vec_c( CBitVec const* a, CBitVec const* b );

bool bitand_on_bit_vec_c( CBitVec* a, CBitVec const* b );

/**************************************/

CBitVec* bitor_bit_vec_c( CBitVec const* a, CBitVec const* b );

bool bitor_on_bit_vec_c( CBitVec* a, CBitVec const* b );

/**************************************/

CBitVec* compl_bit_vec_c( CBitVec const* vec );

bool compl_on_bit_vec_c( CBitVec* vec );

/**************************************/

CBitVec* xor_bit_vec_c( CBitVec const* a, CBitVec const* b );

bool xor_on_bit_vec_c( CBitVec* a, CBitVec const* b );

/*******************************************************************************
 shift
*******************************************************************************/

void shift_bit_vec_c( CBitVec* vec, int64_t distance, cByte fill );

/*******************************************************************************
 cmp
*******************************************************************************/

#define bit_vec_is_c_( Vec, Cstr )                                             \
   bit_vec_is_c( (Vec), c_c( Cstr ) )
bool bit_vec_is_c( CBitVec* vec, cChars chars );

int cmp_bit_vec_c( CBitVec const* a, CBitVec const* b );

inline bool eq_bit_vec_c( CBitVec const* a, CBitVec const* b )
{
   return eq_c( cmp_bit_vec_c( a, b ) );
}

/*******************************************************************************
 io
*******************************************************************************/

#define write_bit_vec_c_( Rec, Vec )                                           \
   write_bit_vec_c( (Rec), (Vec), "" )
bool write_bit_vec_c( cRecorder rec[static 1],
                      CBitVec const* vec,
                      char const fmt[static 1] );

#endif
