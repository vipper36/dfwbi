#pragma once 

#ifndef _SUPPORT_H_
#define _SUPPORT_H_

#include "os.h"


typedef struct
{
   FILE  *fp;
   char  *pszName;
}
MyOpenInfo;


BOOL pascal        myOpen               ( struct tag_InputStream* );
UINT pascal        myRead               ( struct tag_InputStream*, BYTE*, UINT );
BOOL pascal        mySeek               ( struct tag_InputStream*, long, int );
long pascal        myTell               ( struct tag_InputStream* );
BOOL pascal        myClose              ( struct tag_InputStream* );
void * pascal      myMalloc             ( struct tag_MemoryStream*, size_t );
void   pascal      myFree               ( struct tag_MemoryStream*, void* );
void * pascal      myRealloc            ( struct tag_MemoryStream*, void*, size_t );
void * pascal      myCalloc             ( struct tag_MemoryStream*, size_t, size_t );

char*              SaveINIFileString    ( char* );
void               ShowUsage            ( char* );
void               LocateINIFile        ( char*, char* );
void               FileTimeToUnixTime   ( LONGLONG, time_t*);


static KVMemoryStream g_MemoryAllocator =
{
   NULL, myMalloc, myFree, myRealloc, myCalloc
};

#endif //:~_SUPPORT_H_
