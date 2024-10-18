#ifndef CLINGO_LANG_COBJECT_H
#define CLINGO_LANG_COBJECT_H

#include <inttypes.h>
#include <stdbool.h>

#include "clingo/apidecl.h"
#include "clingo/lang/func.h"
#include "clingo/lang/mem.h"

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************/

#define cOBJECT_CONFIG_DEFINITION_                                             \
   XMAP_C_( c_Release, 1 << 0 )                                                \
   XMAP_C_( c_Cleanup, 1 << 1 )                                                \
   XMAP_C_( c_DefaultObject, c_Release|c_Cleanup )

#define XMAP_C_( N, I ) N = I,
enum c_ObjectConfig { cOBJECT_CONFIG_DEFINITION_ };
#undef XMAP_C_

typedef void CObject;

typedef void ( *c_cleanup )( void* obj );

struct cMeta
{
   char const* desc;
   c_cleanup cleanup;
};

typedef struct cMeta cMeta;

struct cObjectInfo
{
   uint32_t refs;
   uint8_t config;
   cMeta const* meta;
};

typedef struct cObjectInfo cObjectInfo;

/**********++*******************************************************************
********************************************************************* Functions 
********************************************************************************
 init
*******************************************************************************/

#define default_object_info_c_( Meta )                                         \
(                                                                              \
   object_info_c_( (Meta), c_DefaultObject )                                   \
)

#define object_info_c_( Meta, Config )                                         \
(                                                                              \
   (cObjectInfo){                                                              \
      .refs = 0,                                                               \
      .config = (Config),                                                      \
      .meta = (Meta)                                                           \
   }                                                                           \
)

/*******************************************************************************
 lifecycle
*******************************************************************************/

#define new_object_c_( Type, Meta )                                            \
   new_object_c( sizeof_c_( Type ), Meta )
CLINGO_API
CObject* new_object_c( int64_t size, cMeta const meta[static 1] );

#define alloc_object_c_( Type, Info )                                          \
   alloc_object_c( sizeof_c_( Type ), Info )
CLINGO_API
CObject* alloc_object_c( int64_t size, cObjectInfo const info[static 1] );

#define let_object_c_( Type, Meta )                                            \
   let_object_c( stack_mem_c_( sizeof_object_c_( Type ) ), (Meta) )
CLINGO_API
CObject* let_object_c( void* mem, cMeta const meta[static 1] );

CLINGO_API
CObject* init_object_c( void* mem, cObjectInfo const info[static 1] );

CLINGO_API
uint32_t references_c( CObject const* obj );

#define release_all_c_( ... )                                                  \
   release_all_c( nargs_c_( __VA_ARGS__ ), __VA_ARGS__ )
CLINGO_API
void release_all_c( int n, ... );

CLINGO_API
CObject* release_c( CObject* obj );

#define replace_c_( Var, Obj )                                                 \
{                                                                              \
   release_c( Var );                                                           \
   Var = retain_c( Obj );                                                      \
}

CLINGO_API
CObject* retain_c( CObject* obj );

CLINGO_API
CObject* touch_c( CObject* obj );

/*******************************************************************************
 object info
*******************************************************************************/
CLINGO_API
cMeta const* get_meta_c( CObject const* obj );

CLINGO_API
cObjectInfo const* get_object_info_c( CObject const* obj );

CLINGO_API
bool meta_is_c( CObject const* obj, cMeta const exp[static 1] );

#define sizeof_object_c_( Type )                                               \
(                                                                              \
   sizeof_c_( cObjectInfo ) + sizeof_c_( Type )                                \
)

#endif
