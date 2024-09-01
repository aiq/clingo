#include "clingo/container/map.h"

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************/

float const C_MaxMapLoad = 0.85f;

/**********++*******************************************************************
********************************************************************* Functions 
********************************************************************************
 util
*******************************************************************************/

extern inline float calculate_load_c( int64_t cap, int64_t count );

extern inline int64_t fibonacci_hash_index_c( uint64_t hash, uint8_t shift );

extern inline uint64_t compine_hashes_c( cUint64s hashes );

/*******************************************************************************
 info
*******************************************************************************/

extern inline int64_t map_cap_c( cMapInfo const info[static 1] );

extern inline float map_load_c( cMapInfo const info[static 1] );

extern inline bool map_is_empty_c( cMapInfo const info[static 1] );

/*******************************************************************************
 itr
*******************************************************************************/

extern inline cMapItr start_map_itr_c();

extern inline bool map_itr_is_valid_c( cMapItr itr );
