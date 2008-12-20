#pragma once 

#ifndef _FILTER_H_
#define _FILTER_H_

#include "os.h"


typedef struct
{
     unsigned int cur_pos;
     unsigned char *buff;
     unsigned int buf_len;
}MemOperInfo;
typedef struct 
{
    int	                dwFlags;
    LPDF_DIRECTION      lpdfDirection;
    int                 gbSummary;
    char                szXMLConfigFile[_MAX_PATH];
    char                szTempDir[_MAX_PATH];
    char                szSrcPassword[MAX_PASSWORD_LEN];
    KVErrorCodeEx       (pascal *fpKV_GetKvErrorCodeEx)( void * );
    int                 (pascal *fpKV_FilterConfig)( void *, int, int, void * );
    BOOL                bInclRMark;

} FilterLsv;
BOOL pascal MemOpen (struct tag_InputStream *p);
UINT pascal MemRead (struct tag_InputStream *p, BYTE *pc, UINT cb);
BOOL pascal MemSeek (struct tag_InputStream *p, long l, int w);
long pascal MemTell (struct tag_InputStream *p);
BOOL pascal MemClose (struct tag_InputStream *p);
int pascal FilterMem(unsigned char* szSrc,unsigned int src_len,unsigned char *szTarget,unsigned int *tar_len);
int pascal  FilterStream(void *pFilter, KVInputStream  *IO, unsigned char* szTar, unsigned int *tarLen,FilterLsv *lsv);
int pascal SQlTest(char * strin);
#endif //:~_FILTER_H_

