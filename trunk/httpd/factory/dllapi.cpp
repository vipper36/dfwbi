/******************************************************************************
 *
 *dynamic link library function  for different platforms 
 *
 *******************************************************************************/

#include "dllapi.hpp"
#include <string.h>

/******************************************************************
 *
 * Porting Load library function to different platforms 
 *
 *******************************************************************/

HINSTANCE myLoadLibrary(char *filename)
{

#if defined(_WINDOWS)
     return LoadLibrary( filename );

#elif defined(_HPUX11)
     return shl_load(filename, BIND_DEFERRED, 0L);
#else
     {
	  return dlopen(filename, RTLD_LAZY);
     }
#endif
}


/******************************************************************
 *
 * Porting GetProcAddress for different platforms                  
 *
 * *****************************************************************/
void * myGetProcAddress(HINSTANCE hInst, char *funcName)
{
#if defined(_WINDOWS)
     return GetProcAddress( hInst, funcName );
#elif defined (_HPUX11)
     int result = 0;
     void *fp = NULL;
     shl_findsym((shl_t*)&hInst, funcName, TYPE_UNDEFINED, &fp);
     if (result) fp = NULL;
     return fp;
#else
     return dlsym( hInst, funcName ); 
#endif
}

/******************************************************************
 *
 * Porting Free library function to different platforms 
 *
 *******************************************************************/
void myFreeLibrary(HINSTANCE hKVFILTER)
{
#if defined(_WINDOWS)
     FreeLibrary( hKVFILTER );
#elif defined(_HPUX11)
     shl_unload((shl_t)hKVFILTER);
#else
     dlclose(hKVFILTER);
#endif
}

