#ifndef __DEBUG_FUNCS__H__
#define __DEBUG_FUNCS__H__


/******************************************************************************/
/*                         Define debugging functions                         */
/******************************************************************************/
#ifdef DEBUG


#include <cstdio>   // printf


#define DTHROW(error) throw error
#define DTHROW_IF(cond, error) if ( cond ) { DTHROW(error); }
#define IF_DEBUG(statement) statement
#define LOG(...) printf(__VA_ARGS__)


/******************************************************************************/
/*                          Void debugging functions                          */
/******************************************************************************/
#else


#define DTHROW(error) ( (void)0 )
#define DTHROW_IF(cond, error) ( (void)0 )
#define IF_DEBUG(statement) ( (void)0 )
#define LOG(...) ( (void)0 )


#endif//DEBUG
#endif//__DEBUG_FUNCS__H__
