/******************************************************************************
*
*
*
*******************************************************************************/
#pragma once 

#ifndef _DLLAPI_H_
#define _DLLAPI_H_

#include "os.hpp"
#ifdef __cplusplus
extern "C"
{
#endif

HINSTANCE   myLoadLibrary   ( char* );
void        myFreeLibrary   ( HINSTANCE );
void *      myGetProcAddress( HINSTANCE, char* );
#ifdef __cplusplus
}
#endif


#endif //:~_DLLAPI_H_

