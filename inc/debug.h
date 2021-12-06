#pragma once
/******************************************************************************/
/*                         Define debugging functions                         */
/******************************************************************************/
#ifdef DEBUG

#include <stdio.h>   // fprintf, stderr


#define DTHROW_IF(cond, error) if ( cond ) { throw error; }
#define LOG(...) fprintf(stderr, __VA_ARGS__)


/******************************************************************************/
/*                          Void debugging functions                          */
/******************************************************************************/
#else


#define DTHROW_IF(cond, error)  ( (void)0 )
#define LOG(...)                ( (void)0 )


#endif//DEBUG
