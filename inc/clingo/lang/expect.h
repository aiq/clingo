#ifndef CLINGO_LANG_EXPECT_H
#define CLINGO_LANG_EXPECT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clingo/apidecl.h"
#include "clingo/lang/func.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 workflow
*******************************************************************************/

#define init_tap_c_()                                                          \
   init_tap_c( __FILE__, stdout )
CLINGO_API
void init_tap_c( char const name[static 1], FILE* output );

CLINGO_API
void tap_plan_c( int64_t n );

CLINGO_API
void tap_c( bool result );

CLINGO_API
void tap_desc_c( bool result, char const desc[static 1] );

CLINGO_API
void tap_descf_c( bool result, char const format[static 1], ... );

CLINGO_API
void tap_note_c( char const note[static 1] );

CLINGO_API
void tap_skip_c( bool result, char const reason[static 1] );

CLINGO_API
void tap_todo_c( bool result, char const explanation[static 1] );

#define finish_tap_c_()                                                        \
   finish_tap_c( true )
CLINGO_API
int finish_tap_c( bool withPlan );

/*******************************************************************************
 checks
*******************************************************************************/

#define expect_c_( Result )                                                    \
   tap_desc_c( (Result), "at line " xstringify_c_( __LINE__ ) )

/*******************************************************************************
 check cmp results
*******************************************************************************/

#define expect_diff_c_( Result )                                               \
   expect_c_( diff_c( Result ) )

#define expect_eq_c_( Result )                                                 \
   expect_c_( eq_c( Result ) )

#define expect_gt_c_( Result )                                                 \
   expect_c_( gt_c( Result ) )

#define expect_gte_c_( Result )                                                \
   expect_c_( gte_c( Result ) )

#define expect_lt_c_( Result )                                                 \
   expect_c_( lt_c( Result ) )

#define expect_lte_c_( Result )                                                \
   expect_c_( lte_c( Result ) )

/*******************************************************************************
 control flow
*******************************************************************************/

#define abort_tap_c_()                                                         \
{                                                                              \
   tap_desc_c( false, "abort at line " xstringify_c_( __LINE__ ) );            \
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
