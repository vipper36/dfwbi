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
	char szFileNameWithExtension[_MAX_PATH];

    strcpy(szFileNameWithExtension, filename);	

#if defined(_WINDOWS)
	strcat( szFileNameWithExtension, ".dll");
	return LoadLibrary( szFileNameWithExtension );

#elif defined(_HPUX11)
	strcat( szFileNameWithExtension, ".sl");
	return shl_load(szFileNameWithExtension, BIND_DEFERRED, 0L);

#elif defined (_RS6K43)
{
	strcat( szFileNameWithExtension, ".a");
    return dlopen(szFileNameWithExtension, RTLD_LAZY);
}	
#else
{
	strcat( szFileNameWithExtension, ".so");
    return dlopen(szFileNameWithExtension, RTLD_LAZY);
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

