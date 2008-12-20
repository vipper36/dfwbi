/******************************************************************************
*
*
*
*******************************************************************************/
#pragma once 

#ifndef _DLLAPI_H_
#define _DLLAPI_H_

#include "os.h"

HINSTANCE   myLoadLibrary   ( char* );
void        myFreeLibrary   ( HINSTANCE );
void *      myGetProcAddress( HINSTANCE, char* );


#endif //:~_DLLAPI_H_

