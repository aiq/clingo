#include "clingo/lang/error_type.h"

#include <stdint.h>
#include "clingo/io/write.h"

/*******************************************************************************
************************************************************************* types
********************************************************************************
 basic
*******************************************************************************/

static bool note_errno_error( cRecorder rec[static 1], cError const* err )
{
   must_be_c_( err->type == &C_ErrnoError );
   cErrnoErrorData const* errd = get_error_data_c( err );
   char* errStr = strerror( errd->number );
   if ( errStr == NULL ) return false;

   return record_chars_c_( rec, errStr );
}
cErrorType const C_ErrnoError = {
   .desc = stringify_c_( C_ErrnoError ),
   .note = &note_errno_error
};

bool push_errno_error_c( cErrorStack es[static 1], int number )
{
   cErrnoErrorData d = { .number=number };
   return push_error_c( es, &C_ErrnoError, &d, sizeof_c_( cErrnoErrorData ) );
}

/*******************************************************************************
 
*******************************************************************************/

static bool note_lit_error( cRecorder rec[static 1], cError const* err )
{
   must_be_c_( err->type == &C_LitError );
   cLitErrorData const* errd = get_error_data_c( err );
   return record_chars_c_( rec, errd->str );
}
cErrorType const C_LitError = {
   .desc = stringify_c_( C_LitError ),
   .note = &note_lit_error
};

bool push_lit_error_c( cErrorStack es[static 1], char const str[static 1] )
{
   cLitErrorData d = { .str=str };
   return push_error_c( es, &C_LitError, &d, sizeof_c_( cLitErrorData ) );
}

/*******************************************************************************
 
*******************************************************************************/

static bool note_text_error( cRecorder rec[static 1], cError const* err )
{
   must_be_c_( err->type == &C_TextError );
   cTextErrorData const* errd = get_error_data_c( err );
   return record_chars_c_( rec, errd->str );
}
cErrorType const C_TextError = {
   .desc = stringify_c_( C_TextError ),
   .note = &note_text_error
};

bool push_text_error_c( cErrorStack es[static 1], int n, ... )
{
   cRecorder* rec = &make_fix_recorder_c_( es->space, es->mem );
   va_list list;
   va_start( list, n );
   bool res = write_list_c( rec, n, list );
   va_end( list );
   if ( res == false ) return false;

   if ( not record_char_c( rec, '\0' ) ) return false;

   es->space = rec->space;
   es->mem = rec->mem;
   reset_recorder_c( rec );
   cTextErrorData d = { .str=rec->mem };
   return push_error_c( es, &C_TextError, &d, sizeof_c_( cTextErrorData ) );
}

/*******************************************************************************
 
*******************************************************************************/

#define Zero_ 0

#define cOverflowErrors_                                                       \
   cXMAP_(  push_iadd8_error_c,  0,   int8_t, "{i} + {i}" )                    \
   cXMAP_( push_iadd16_error_c,  1,  int16_t, "{i} + {i}" )                    \
   cXMAP_( push_iadd32_error_c,  2,  int32_t, "{i} + {i}" )                    \
   cXMAP_( push_iadd64_error_c,  3,  int64_t, "{i} + {i}" )                    \
   cXMAP_(  push_uadd8_error_c,  4,  uint8_t, "{u} + {u}" )                    \
   cXMAP_( push_uadd16_error_c,  5, uint16_t, "{u} + {u}" )                    \
   cXMAP_( push_uadd32_error_c,  6, uint32_t, "{u} + {u}" )                    \
   cXMAP_( push_uadd64_error_c,  7, uint64_t, "{u} + {u}" )                    \
                                                                               \
   cXMAP_(  push_imul8_error_c,  8,   int8_t, "{i} * {i}" )                    \
   cXMAP_( push_imul16_error_c,  9,  int16_t, "{i} * {i}" )                    \
   cXMAP_( push_imul32_error_c, 10,  int32_t, "{i} * {i}" )                    \
   cXMAP_( push_imul64_error_c, 11,  int64_t, "{i} * {i}" )                    \
   cXMAP_(  push_umul8_error_c, 12,  uint8_t, "{u} * {u}" )                    \
   cXMAP_( push_umul16_error_c, 13, uint16_t, "{u} * {u}" )                    \
   cXMAP_( push_umul32_error_c, 14, uint32_t, "{u} * {u}" )                    \
   cXMAP_( push_umul64_error_c, 15, uint64_t, "{u} * {u}" )                    \
                                                                               \
   cXMAP_(  push_isub8_error_c, 16,   int8_t, "{i} - {i}" )                    \
   cXMAP_( push_isub16_error_c, 17,  int16_t, "{i} - {i}" )                    \
   cXMAP_( push_isub32_error_c, 18,  int32_t, "{i} - {i}" )                    \
   cXMAP_( push_isub64_error_c, 19,  int64_t, "{i} - {i}" )                    \
   cXMAP_(  push_usub8_error_c, 20,  uint8_t, "{u} - {u}" )                    \
   cXMAP_( push_usub16_error_c, 21, uint16_t, "{u} - {u}" )                    \
   cXMAP_( push_usub32_error_c, 22, uint32_t, "{u} - {u}" )                    \
   cXMAP_( push_usub64_error_c, 23, uint64_t, "{u} - {u}" )

static bool write_overflow_error( cRecorder rec[static 1], cOverflowErrorData const* errd )
{
   switch ( errd->op )
   {
      #define cXMAP_( FuncName, Op, Type, Fmt )   \
         case Op: return write_c_( rec, Fmt, errd->a, errd->b, " overflows "#Type" range" );
         cOverflowErrors_
      #undef cXMAP_
   }
   return record_chars_c_( rec, "unknown format" );
}

static bool note_overflow_error( cRecorder rec[static 1], cError const* err )
{
   must_be_c_( err->type == &C_OverflowError );
   cOverflowErrorData const* errd = get_error_data_c( err );
   return write_overflow_error( rec, errd );
}
cErrorType const C_OverflowError = {
   .desc = stringify_c_( C_OverflowError ),
   .note = &note_overflow_error
};

#define PUSH_OVERFLOW_ERROR_( FuncName, Type, Op )                             \
bool FuncName( cErrorStack es[static 1], Type a, Type b )                      \
{                                                                              \
   cOverflowErrorData d = { .op=Op, .a=(uint64_t)a, .b=(uint64_t)b };          \
   int64_t errdSize = sizeof_c_( cOverflowErrorData );                         \
   return push_error_c( es, &C_OverflowError, &d, errdSize );                  \
}

#define cXMAP_( FuncName, Op, Type, Fmt ) PUSH_OVERFLOW_ERROR_( FuncName, Type, Op )
cOverflowErrors_
#undef cXMAP_
