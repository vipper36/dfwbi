/******************************************************************************
*
*
*
*******************************************************************************/
#pragma once 

#ifndef _OS_H_
#define _OS_H_


#if defined WIN32  && !defined _WINDOWS
#define _WINDOWS
#endif

#include <time.h>

#ifdef _WINDOWS

#include <windows.h>
#include <winbase.h>
#include <assert.h>
#include <io.h>
#include <direct.h>

#else

#define VDK_UNIX

#if defined(_FBSD32i)
#define VDK_FBSD
#endif

#define _access access
#define _mkdir  mkdir
#define GetPrivateProfileString myGetPrivateProfileString 

#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

#endif


#if defined (_SSOL26) || (_AOSF40) || (_IRIX62) || (_RS6K43) || (_ILNX21) || (_HPUX64i) || (_LNX64i) || (_XLNX64) || (_FBSD32i) || (_SOL64X) || (_SOL32X) || (_LNXPPC)
#include <dlfcn.h>
#elif defined (_HPUX11)
#include <dl.h>
#endif


#if defined (_HPUX11) || (_ILNX21) || (_RS6K43) || (_SSOL26) || (_HPUX64i) || (_LNX64i) || (_XLNX64) || (_FBSD32i) || (_SOL64X) || (_SOL32X) || (_LNXPPC)
#define LONGLONG long long
#define HINSTANCE void*
#endif

#define _MAX_PATH 4096
#define GPPSTRINGMAXSIZE     0x00000800

#endif //:~_OS_H_
