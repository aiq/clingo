#ifndef CLINGO_CONTAINER_COBJECT_VEC_H
#define CLINGO_CONTAINER_COBJECT_VEC_H

#include "clingo/apidecl.h"
#include "clingo/container/vec.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

OBJ_VEC_DEF_C_(
   CLINGO_API,      // LibApi
   CObjectVec,      // VecType
   CObject,         // ObjType
   object_vec_c,    // FuncName
   C_ObjectVecMeta  // Meta
)

#endif