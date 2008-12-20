/***********************************************************************************
 *
 *
 *
 ************************************************************************************/

#include "filter.h"
#include "dllapi.h"
#include "support.h"
#include "config.h"
KVFltInterfaceEx FilterFunc;
int pascal SQlTest(char * strin)
{
     return 100;
/*
     FILE *fpr=NULL;
     fpr=fopen("/home/oracle/ee","w+");
     if(fpr==NULL)
     {
	  printf("source file open error!\n");
     }
     strcpy(strout,strin);
     strcat(strout,"added");
     fwrite(strout,1,strlen(strout),fpr);
     return 1;*/
}

BOOL pascal MemOpen (struct tag_InputStream *p)
{
     //  fprintf(stderr, "mem open!\n");
   MemOperInfo *po = (MemOperInfo *)p->pInputStreamPrivateData;
   p->lcbFilesize= po->buf_len;
   po->cur_pos=0;
//   fprintf(stderr, "mem open!%d:%d:%d\n", po->buff,po->cur_pos, po->buf_len);
   return ( po->buff != NULL );
}

UINT pascal MemRead (struct tag_InputStream *p, BYTE *pc, UINT cb)
{
     //   fprintf(stderr, "mem read:%d!\n",cb);
     UINT ret=0;
     MemOperInfo *po = (MemOperInfo *)p->pInputStreamPrivateData;
     if(po->cur_pos+cb<po->buf_len)
     {
	  memcpy( pc,po->buff+po->cur_pos, cb);
	  po->cur_pos=po->cur_pos+cb;
	  ret=cb;
     }else if(po->cur_pos>=po->buf_len)
     {
	  ret=0;
     }else
     {
	  memcpy( pc,po->buff+po->cur_pos,po->buf_len-po->cur_pos );
	  ret=po->buf_len-po->cur_pos;
	  po->cur_pos=po->buf_len;
     }
     //fprintf(stderr, "mem read%s:%d!\n",pc,ret);
     return (ret); 
}

BOOL pascal MemSeek (struct tag_InputStream *p, long l, int w)
{
     //fprintf(stderr, "mem rseek!%d:%d\n",l,w);
   MemOperInfo *po = (MemOperInfo *)p->pInputStreamPrivateData;
   if(w==SEEK_SET)
	po->cur_pos=(unsigned int)l;
   else if(w==SEEK_CUR)
	po->cur_pos=po->cur_pos+(unsigned int)l;
   else
	po->cur_pos=po->buf_len+(unsigned int)l;
   return TRUE;
}

long pascal MemTell (struct tag_InputStream *p)
{
   MemOperInfo *po = (MemOperInfo *)p->pInputStreamPrivateData;
   // fprintf(stderr, "mem tell!%d :%d\n", po->cur_pos,po->buf_len);
   return ( po->cur_pos );
}

BOOL pascal MemClose (struct tag_InputStream *p)
{
//         fprintf(stderr, "mem close!\n");
   MemOperInfo *po = (MemOperInfo *)p->pInputStreamPrivateData;
   po->cur_pos=0;
   return (TRUE);
}

/***********************************************************************************
 *
 *
 *
 ************************************************************************************/
int FilterMem(unsigned char* szSrc,unsigned int src_len,unsigned char *szTarget,unsigned int *tar_len)
{
     void    *pFilter = NULL;
     char    szDllName[1024];
     void    *pKVFILTER;
     char    *szDir = (char*)KVLIBDIR ;
     KVInputStream  inStream;
     KVFilterOutput OutStream;
     MemOperInfo minf;
     bzero(&inStream,sizeof(inStream));
     bzero(&OutStream,sizeof(OutStream));

     
     FilterLsv *lsv=(FilterLsv*)malloc(sizeof(FilterLsv));
     bzero(lsv,sizeof(FilterLsv));
     KVErrorCode        nRet = KVERR_Success;
     KVErrorCode (pascal *fpGetFilterInterfaceEx)( KVFltInterfaceEx*, int );

     strcpy(szDllName, szDir);
     strcat(szDllName, "kvfilter");

     pKVFILTER = myLoadLibrary(szDllName);
     if (!pKVFILTER)
     {
	  fprintf(stderr, "Can't load kvfilter!\n");
	  fprintf(stderr, "This executable must be in the same directory as the Filter binaries.\n");
	  nRet = KVERR_DLLNotFound;
	  goto jail;
     }

     fpGetFilterInterfaceEx = (KVErrorCode (pascal *)( KVFltInterfaceEx *, int ) )
	  myGetProcAddress(pKVFILTER, (char*)"KV_GetFilterInterfaceEx");

     if ( fpGetFilterInterfaceEx == NULL )
     {
	  fprintf(stderr, "Can't get interface function!\n");
	  nRet = KVERR_General;
	  goto jail;
     }

     nRet = (*fpGetFilterInterfaceEx)(&FilterFunc, KVFLTINTERFACE_REVISION);        
     if(KVERR_Success != nRet)
     {
	  fprintf(stderr, "Can't get Filter interface functions!\n");
	  goto jail;
     }

     lsv->fpKV_GetKvErrorCodeEx = (KVErrorCodeEx (pascal *)( void * ))myGetProcAddress(pKVFILTER, (char*)"KV_GetKvErrorCodeEx");
     lsv->fpKV_FilterConfig = (BOOL (pascal *)( void *, int, int, void * ))myGetProcAddress(pKVFILTER, (char*)"KV_FilterConfig");
//     lsv->gbSummary =TRUE;
     lsv->dwFlags=KVF_OOPLOGON|KVF_INPROCESS; ;
     pFilter = (*FilterFunc.fpInit)( &g_MemoryAllocator, NULL , szDir, KVCS_UTF8, lsv->dwFlags); /*|*/
        
     if ( pFilter == NULL )
     {
	  fprintf(stderr, "Error initializing filter!\n" );
	  nRet = KVERR_General;
	  goto jail;
     }
     if (!(*FilterFunc.fpSetSrcCharSet)(pFilter,KVCS_1252) )
     {
	  fprintf(stderr, "Error initializing filter!\n" );
	  nRet = KVERR_General;
	  goto jail;
     }
     if (lsv->fpKV_FilterConfig!=NULL)
     {
	  if (lsv->bInclRMark)
	  {
	       lsv->fpKV_FilterConfig(pFilter, KVFLT_INCLREVISIONMARK, TRUE, NULL);
	  }
	  if (lsv->szXMLConfigFile[0])
	  {
	       KVXConfigInfo xinfo;
	       BOOL bDone = FALSE;
	       int n = 0;

	       /* get config info for Verity-recognized formats */
	       while(!bDone)
	       {
		    memset(&xinfo, 0, sizeof(KVXConfigInfo));
		    if(GetKVXConfigInfo(lsv, &xinfo, n))
		    {
			 lsv->fpKV_FilterConfig(pFilter, KVFLT_SETXMLCONFIGINFO, 0, &xinfo);
			 FreeKVXConfigInfo(&xinfo);
			 n++;
		    }
		    else
		    {
			 bDone = TRUE;
		    }
	       }

	       /* get customized config info for other formats */
	       bDone = FALSE;
	       n = 100;
	       while(!bDone)
	       {
		    memset(&xinfo, 0, sizeof(KVXConfigInfo));
		    if(GetKVXConfigInfo(lsv, &xinfo, n))
		    {
			 lsv->fpKV_FilterConfig(pFilter, KVFLT_SETXMLCONFIGINFO, 0, &xinfo);
			 FreeKVXConfigInfo(&xinfo);
			 n++;
		    }
		    else
		    {
			 bDone = TRUE;
		    }
	       }
	  }            
	  if (lsv->szTempDir[0])
	  {
	       lsv->fpKV_FilterConfig(pFilter, KVFLT_SETTEMPDIRECTORY, 0, lsv->szTempDir);
	  }
	  if (lsv->szSrcPassword[0])
	  {
	       lsv->fpKV_FilterConfig(pFilter, KVFLT_SETSRCPASSWORD, 
				      strlen(lsv->szSrcPassword), lsv->szSrcPassword);
	  }
	  if (lsv->lpdfDirection >= LPDF_RAW)
	  {
	       lsv->fpKV_FilterConfig(pFilter, KVFLT_LOGICALPDF, 
				      lsv->lpdfDirection, NULL);
	  }
     }

     minf.buff=szSrc;
     minf.buf_len= src_len;
     inStream.pInputStreamPrivateData = (void *)&minf;
     inStream.fpOpen  = MemOpen;
     inStream.fpRead  = MemRead;
     inStream.fpSeek  = MemSeek;
     inStream.fpTell  = MemTell;
     inStream.fpClose = MemClose;
     nRet=FilterStream(pFilter,&inStream, szTarget,tar_len ,lsv);
	
jail:
     if ( nRet == KVERR_General )
     {
	  int kvErrorEx;
	  if ( lsv->fpKV_GetKvErrorCodeEx )
	  {
	       kvErrorEx = (*lsv->fpKV_GetKvErrorCodeEx)( pFilter );
	       if ( kvErrorEx != KVError_Last)
		    fprintf(stderr,"KvErrorCodeEx = %d \n ", kvErrorEx );
	       else
		    fprintf(stderr,"No more KvErrorCodeEx \n" );
	  }
     }
     free(lsv);
     if (pFilter!=NULL)
	  (*FilterFunc.fpShutdown)( pFilter );
    
     myFreeLibrary((HINSTANCE)pKVFILTER);

     return (nRet);
}
/*:   PrintSummaryInfo()
 *
 *
 ******************************************************************************/
void pascal PrintSummaryInfo( KVSummaryInfoEx *pSI, FILE *fpOut )
{
    int n;

   for ( n=0; n < pSI->nElem; ++n )
   {
      fprintf( fpOut, "%d %d ", pSI->pElem[n].isValid, pSI->pElem[n].type );

      switch( pSI->pElem[n].type )
      {
         case KV_String:
         {
            fprintf( fpOut, "\"%s\"", pSI->pElem[n].data );
         }
         break;

         case KV_Int4:
         {
            fprintf( fpOut, "%d", pSI->pElem[n].data );
         }
         break;

         case KV_DateTime:
         {
#if defined (_HPUX64i) || (_LNX64i) || (_XLNX64)
            long        rtnValue = 0;
#else
            LONGLONG    rtnValue = 0;
#endif  
            memcpy(&rtnValue, pSI->pElem[n].data, 8); 

            if(n == 9)
            {
#if !defined (_WINDOWS) && !defined(_ILNX21) && !defined(_LNX64i) && !defined(_XLNX64) && !defined (_FBSD32i)
  
                  /* if it is big endian, swap bytes */
                  LONGLONG NN = 0;
                  unsigned char *a, *b, *c;
                  a = (unsigned char *) &rtnValue;
                  b = a+ sizeof(LONGLONG) -1;
                  c = (unsigned char *) &NN;
 
                  while (a <= b)
                  {
                     *c = *b;
                     b--;
                     c++;
                  }
                  rtnValue = NN;
#endif
                 fprintf(fpOut, "%ld Minutes", (long)(rtnValue / 600000000));
            }
            else
            {
                 time_t timer;
                 char * timeStr = NULL;
                 char * linefeed = NULL;
                 FileTimeToUnixTime(rtnValue, &timer);
                 timeStr = ctime(&timer);
                 if ( timeStr )
                    linefeed = strchr(timeStr, '\012');
                 if ( linefeed != NULL)
                    *linefeed = '\0';
                 if ( timeStr )
                    fprintf(fpOut,"%s", timeStr);

            }
         }
         break;

         case KV_ClipBoard:
         {
            fprintf( fpOut, "Clipboard data" );
         }
         break;

         case KV_Bool:
         {
            fprintf( fpOut, "%s", pSI->pElem[n].data? "true": "false" );
         }
         break;

         case KV_Unicode:
         {
            int len = 0;
            BYTE *p = (BYTE *)pSI->pElem[n].data;

            if (p)
            {
               for (; *p!= 0 || *(p+1) != 0; p+=2,len+=2);
            }
                    
            fprintf( fpOut, "\"");
            if (p)
            {
               fwrite(pSI->pElem[n].data, 1, len+2, fpOut);
            }
            fprintf( fpOut, "\"");

         }
         break;

         case KV_IEEE8:
         {
            fprintf( fpOut, "%lf", *((double *)pSI->pElem[n].data) );
         }
         break;

         case KV_Other:
         {
            fprintf( fpOut, "other" );
         }
         break;

         default:
         {
            if ( pSI->pElem[n].isValid )
            {
               fprintf( fpOut, "Bad element type!" );
            }
         }
         break;
      }

      fprintf( fpOut, " %s\n", pSI->pElem[n].isValid? pSI->pElem[n].pcType : "(null)");

   }
}

/*******************************************************************************
 *
 * function:   DoSummaryInfoStream()
 *
 *
 ******************************************************************************/
static void pascal DoSummaryInfoStream(  void             *pKVFilter,
					 KVFltInterfaceEx  *pInterface,
					 KVInputStream    *pInput,
					 FILE             *fpOut )
{
     KVSummaryInfoEx   si;

     memset( &si, 0, sizeof(si) );
     if ( KVERR_Success != (*pInterface->fpGetOLESummaryInfo)( pKVFilter, pInput, &si ) )
     {
	  fprintf( fpOut, "Error obtaining summary information\n" );
	  return;
     }

     if ( si.nElem == 0 )
     {
	  fprintf( fpOut, "No summary information\n" );
	  goto theend;
     }

     PrintSummaryInfo(&si, fpOut);

theend:
     (*pInterface->fpFreeOLESummaryInfo)( pKVFilter, &si );
}

/*******************************************************************************
 *
 * function:   FilterStream()
 *
 * summary:    Takes an input file specification and filters the output to an output file
 *             using the KeyView filtering API.
 *             Uses stream-based filtering instead of file-based.
 *
 ******************************************************************************/
int  FilterStream(void *pFilter, KVInputStream  *IO, unsigned char* szTar, unsigned int *tarLen,FilterLsv *lsv)
{
     adDocDesc      DocDesc = {0};
     KVErrorCode    kvstatus = KVERR_Success;
     KVErrorCode    nRet = KVERR_Success;
     void           *pStream = NULL;
     BOOL           bStreamOpen = FALSE;
     FILE *fp=stderr;
     KVFilterOutput filterOut={0};
     pStream = (*FilterFunc.fpOpenStream)(pFilter, IO);


     if (!pStream)
     {
	  fprintf(stderr, "Error opening input stream\n");
	  nRet = KVERR_badInputStream;
	  goto slammer;
     }

     bStreamOpen = TRUE;
    
     /* Check if KeyView can filter this stream.
      */
     kvstatus = (*FilterFunc.fpCanFilterStream)( pFilter, pStream );

     nRet = kvstatus;

     if (kvstatus != KVERR_Success) 
     {
	  if (bStreamOpen) 
	  {
	       if ( !(*FilterFunc.fpCloseStream)( pFilter, pStream ) ) 
	       {
		    fprintf(stderr, "Error: Unable to filter(fpCanFilterStream returns %d)\n",  kvstatus );
		    fprintf( stderr, "Error in KVCloseStream()\n" );
		    nRet = KVERR_General;
	       }
	  }
        
	  return(nRet);
     }

     if ( lsv->gbSummary )
     {
	  /*
	   *  Do summary extraction.
	   */        
	  DoSummaryInfoStream((void*)pFilter, (KVFltInterfaceEx*)(&FilterFunc), IO, fp);
     }
     else
     {
	  unsigned char *cur_pos=szTar;
	  *tarLen=0;
	  while ( 1 )
	  {
	       kvstatus = (*FilterFunc.fpFilterStream)( pFilter, pStream, &filterOut, NULL );
           
	       if (kvstatus != KVERR_Success )
	       {
		    fprintf(stderr, "Error filtering stream:%d\n",kvstatus );
		    nRet = kvstatus;
		    goto slammer;
	       }
        
	       /* 
	       ** Check if we're done filtering...
	       */
	       
	       if ( filterOut.cbText == 0 )
	       {
		    break;
	       }
	       memcpy(cur_pos,filterOut.pcText,filterOut.cbText);
	       *tarLen=*tarLen+filterOut.cbText;
	       /* The caller is responsible for free'ing the memory allocated
		* by the KVFilterStream() function. The KeyView filtering API used
		* our g_MemoryAllocator to allocate the memory...
		*/
	       (*g_MemoryAllocator.fpFree)( &g_MemoryAllocator, filterOut.pcText );
	  }
     }

slammer:

     /*
     ** Load KVCloseStream
     */
     if (pStream)
     {
	  if ( !(*FilterFunc.fpCloseStream)( pFilter, pStream ) )
	  {
	       fprintf(stderr, "Error closing stream\n" );
	       nRet = KVERR_General;
	  }
     }

     return (nRet); 
}


/***********************************************************************************
 *
 *
 *
 ************************************************************************************/

void PrintFilterErrMsg( char *szTitle, KVErrorCode error )
{
     char szError[40];

     *szError = '\0';
     switch (error)
     {
     case KVERR_Success:
	  wsprintf(szError, "KVERR_Success");
	  break;

     case KVERR_DLLNotFound:
	  wsprintf(szError, "KVERR_DLLNotFound");
	  break;

     case KVERR_processCancelled:
	  wsprintf(szError, "KVERR_processCancelled");
	  break;
         
     case KVERR_OutOfCore:
	  wsprintf(szError, "KVERR_OutOfCore");
	  break;

     case KVERR_badInputStream:
	  wsprintf(szError, "KVERR_badInputStream");
	  break;

     case KVERR_badOutputType:
	  wsprintf(szError, "KVERR_badOutputType");
	  break;

     case KVERR_General:
	  wsprintf(szError, "KVERR_General");
	  break;

     case KVERR_FormatNotSupported:
	  wsprintf(szError, "KVERR_FormatNotSupported");
	  break;

     case KVERR_PasswordProtected:
	  wsprintf(szError, "KVERR_PasswordProtected");
	  break;

     case KVERR_ADSNotFound:
	  wsprintf(szError, "KVERR_ADSNotFound");
	  break;
      
     case KVERR_AutoDetFail:
	  wsprintf(szError, "KVERR_AutoDetFail");
	  break;

     case KVERR_AutoDetNoFormat:
	  wsprintf(szError, "KVERR_AutoDetNoFormat");
	  break;

     case KVERR_ReaderInitError:
	  wsprintf(szError, "KVERR_ReaderInitError");
	  break;

     case KVERR_NoReader:
	  wsprintf(szError, "KVERR_NoReader");
	  break;

     case KVERR_CreateOutputFileFailed:
	  wsprintf(szError, "KVERR_CreateOutputFileFailed");
	  break;

     case KVERR_CreateTempFileFailed:
	  wsprintf(szError, "KVERR_CreateTempFileFailed");
	  break;

     case KVERR_ErrorWritingToOutputFile:
	  wsprintf(szError, "KVERR_ErrorWritingToOutputFile");
	  break;

     case KVERR_CreateProcessFailed:
	  wsprintf(szError, "KVERR_CreateProcessFailed");
	  break;

     case KVERR_WaitForChildFailed:
	  wsprintf(szError, "KVERR_WaitForChildFailed");
	  break;

     case KVERR_ChildTimeOut:
	  wsprintf(szError, "KVERR_ChildTimeOut");
	  break;

     case KVERR_ArchiveFileNotFound:
	  wsprintf(szError, "KVERR_ArchiveFileNotFound");
	  break;

     case KVERR_ArchiveFatalError:
	  wsprintf(szError, "KVERR_ArchiveFatalError");
	  break;

     default:
	  wsprintf(szError, "%d", error);
     }

     printf("%s: error code returned is %s\n", szTitle, szError);
}

/***********************************************************************************
 *
 *
 *
 ************************************************************************************/


BOOL GetKVXConfigInfo(FilterLsv *lsv, KVXConfigInfo *pXInfo, int n)
{
     BOOL bRet = TRUE;
     char szSection[16];
     char szReturnedString[GPPSTRINGMAXSIZE];

     sprintf(szSection, "config%d", n);
     GetPrivateProfileString(szSection, "eKVFormat", "Not found", szReturnedString, GPPSTRINGMAXSIZE, lsv->szXMLConfigFile);
     if(strcmp(szReturnedString, "Not found") == 0)
     {
	  bRet = FALSE;
     }
     else
     {
	  pXInfo->eKVFormat = FindFormatID(szReturnedString);

	  GetPrivateProfileString(szSection, "szRoot", "", szReturnedString, GPPSTRINGMAXSIZE, lsv->szXMLConfigFile);
	  pXInfo->pszRoot = SaveINIFileString(szReturnedString);
        
	  GetPrivateProfileString(szSection, "szInMetaElement", "", szReturnedString, GPPSTRINGMAXSIZE, lsv->szXMLConfigFile);
	  pXInfo->pszInMeta = SaveINIFileString(szReturnedString);

	  GetPrivateProfileString(szSection, "szExMetaElement", "", szReturnedString, GPPSTRINGMAXSIZE, lsv->szXMLConfigFile);
	  pXInfo->pszExMeta = SaveINIFileString(szReturnedString);

	  GetPrivateProfileString(szSection, "szInContentElement", "", szReturnedString, GPPSTRINGMAXSIZE, lsv->szXMLConfigFile);
	  pXInfo->pszInContent = SaveINIFileString(szReturnedString);

	  GetPrivateProfileString(szSection, "szExContentElement", "", szReturnedString, GPPSTRINGMAXSIZE, lsv->szXMLConfigFile);
	  pXInfo->pszExContent = SaveINIFileString(szReturnedString);

	  GetPrivateProfileString(szSection, "szInAttribute", "", szReturnedString, GPPSTRINGMAXSIZE, lsv->szXMLConfigFile);
	  pXInfo->pszInAttribute = SaveINIFileString(szReturnedString);
     }
     return bRet;
}

/***********************************************************************************
 *
 *
 *
 ************************************************************************************/


BOOL FreeKVXConfigInfo(KVXConfigInfo *pXInfo)
{
     BOOL bRet = TRUE;

     if(!pXInfo) return bRet;

     if(pXInfo->pszRoot) 
	  free(pXInfo->pszRoot);
     if(pXInfo->pszInMeta)
	  free(pXInfo->pszInMeta);
     if(pXInfo->pszExMeta)
	  free(pXInfo->pszExMeta);
     if(pXInfo->pszInContent)
	  free(pXInfo->pszInContent);
     if(pXInfo->pszExContent)
	  free(pXInfo->pszExContent);
     if(pXInfo->pszInAttribute)
	  free(pXInfo->pszInAttribute);

     return bRet;
}

/***********************************************************************************
 *
 *
 *
 ************************************************************************************/

ENdocFmt FindFormatID(char *szInputString)
{
     if (strcmp(szInputString, "MS_Word_XML_Fmt") == 0)
	  return MS_Word_XML_Fmt;
     if (strcmp(szInputString, "MS_Excel_XML_Fmt") == 0)
	  return MS_Excel_XML_Fmt;
     if (strcmp(szInputString, "MS_Visio_XML_Fmt") == 0)
	  return MS_Visio_XML_Fmt;
     if (strcmp(szInputString, "SO_Text_XML_Fmt") == 0)
	  return SO_Text_XML_Fmt;
     if (strcmp(szInputString,  "SO_Spreadsheet_XML_Fmt") == 0)
	  return SO_Spreadsheet_XML_Fmt;
     if (strcmp(szInputString, "SO_Presentation_XML_Fmt") == 0)
	  return SO_Presentation_XML_Fmt;
   
     return Unknown_Fmt;
}



/*******************************************************************************
 *
 * function:   AutoDetectFile()
 *
 * summary:    Print out the format informaton for a file.
 *
 ******************************************************************************/
KVErrorCode AutoDetectFile(void *pContext, char *szFile)
{
   
     ADDOCINFO DocInfo;
     KVErrorCode eErr = KVERR_Success;
     BOOL    bVal;        
  
     bVal = FilterFunc.fpGetDocInfoFile(pContext, szFile,  &DocInfo );
	
    
     if (!bVal || (DocInfo.eClass == AutoDetFail) ||
	 (DocInfo.eClass == AutoDetNoFormat))
     {
	  if( !bVal || (DocInfo.eClass == AutoDetFail) )
	  {
	       eErr = KVERR_AutoDetFail;
	  }
	  else
	  {
	       eErr = KVERR_AutoDetNoFormat;
	  }
	  goto slammer;
     }

     printf("The file %s \n", szFile);
     printf("Class ID:			%d\n", DocInfo.eClass);
     printf("Format ID:			%d\n", DocInfo.eFormat);
     printf("Major Version:		%ld\n", DocInfo.lVersion);
     printf("Attributes:			%u\n", DocInfo.ulAttributes);
    
     printf("\n");

slammer:
     return(eErr);
}

/***********************************************************************************
 *
 *
 *
 ************************************************************************************/
