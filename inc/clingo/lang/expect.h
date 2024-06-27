#ifndef CLINGO_LANG_EXPECT_H
#define CLINGO_LANG_EXPECT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clingo/apidecl.h"
#include "clingo/lang/func.h"

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************

*******************************************************************************/

extern char const* C_TapDesc;
extern char const* C_TapSkip;
extern char const* C_TapTodo;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 workflow
*******************************************************************************/

#define init_tap_c_()                                                          \
   init_tap_c( __FILE__, stdout )
CLINGO_API void init_tap_c( char const name[static 1], FILE* output );

CLINGO_API void tap_plan_c( int64_t n );

#define tap_c_( Result, ... )                                                  \
   tap_c( (Result), nargs_c_( __VA_ARGS__ ), __VA_ARGS__ )
CLINGO_API bool tap_c( bool result, int n, ... );

#define tap_desc_c_( Result, ... )                                             \
   tap_c_( (Result), C_TapDesc, __VA_ARGS__ )

#define tap_skip_c_( Result, ... )                                             \
   tap_c_( (Result), C_TapSkip, __VA_ARGS__ )

#define tap_todo_c_( Result, ... )                                             \
   tap_c_( (Result), C_TapTodo, __VA_ARGS__ )

CLINGO_API void tap_note_c( char const note[static 1] );

#define finish_tap_c_()                                                        \
   finish_tap_c( true )
CLINGO_API int finish_tap_c( bool withPlan );

/*******************************************************************************
 block
*******************************************************************************/

bool tap_block_begin_c( void );

bool tap_block_end_c( void );

#define tap_block_c_( Ok )                                                     \
if ( not (Ok) )                                                                \
for (                                                                          \
   bool makeBlock = tap_block_begin_c();                                       \
   makeBlock;                                                                  \
   makeBlock = tap_block_end_c()                                               \
)

#define tap_line_c_( K, ... )                                                  \
   tap_line_c( (K), nargs_c_( __VA_ARGS__  ), __VA_ARGS__ )
void tap_line_c( char const k[static 1], int n, ... );

#define tap_msg_line_c_( ... )            \
   tap_line_c_( "message", __VA_ARGS__ )

#define tap_exp_line_c_( ... )            \
   tap_line_c_( "expected", __VA_ARGS__ )

#define tap_got_line_c_( ... )            \
   tap_line_c_( "got", __VA_ARGS__ )

/*******************************************************************************
 checks
*******************************************************************************/

#define expect_block_at_c_( Result )                                           \
   tap_block_c_( expect_at_c_( Result ) )

#define expect_block_c_( Index, Result )                                       \
   tap_block_c_( expect_c_( (Index), (Result) ) )

#define expect_at_c_( Result )                                                 \
   tap_c_( (Result), C_TapDesc, "at line ", xstringify_c_( __LINE__ ) )

#define expect_c_( Index, Result )                                             \
   tap_c_( (Result), C_TapDesc, "test {i64}.", (Index)+1, " at line ", xstringify_c_( __LINE__ ) )

/*******************************************************************************
 check cmp results
*******************************************************************************/

#define expect_diff_c_( Result )                                               \
   expect_at_c_( diff_c( Result ) )

#define expect_eq_c_( Result )                                                 \
   expect_at_c_( eq_c( Result ) )

#define expect_gt_c_( Result )                                                 \
   expect_at_c_( gt_c( Result ) )

#define expect_gte_c_( Result )                                                \
   expect_at_c_( gte_c( Result ) )

#define expect_lt_c_( Result )                                                 \
   expect_at_c_( lt_c( Result ) )

#define expect_lte_c_( Result )                                                \
   expect_at_c_( lte_c( Result ) )

/*******************************************************************************
 control flow
*******************************************************************************/

#define abort_tap_c_()                                                         \
{                                                                              \
   tap_desc_c_( false, "abort at line " xstringify_c_( __LINE__ ) );           \
   exit( finish_tap_c_() );                                                    \
}

#define require_c_( Result )                                                   \
{                                                                              \
   if ( not (Result) )                                                         \
   {                                                                           \
      abort_tap_c_();                                                          \
   }                                                                           \
}

#endif
