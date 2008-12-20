#include "support.h"


/*******************************************************************************
 *
 * Installable file system layer: the next 5 functions provide basic file
 * manipulation.
 *
 ******************************************************************************/

BOOL pascal myOpen (struct tag_InputStream *p)
{
   MyOpenInfo *po = (MyOpenInfo *)p->pInputStreamPrivateData;
   po->fp = fopen(po->pszName, "rb");
   return ( po->fp != NULL );
}

UINT pascal myRead (struct tag_InputStream *p, BYTE *pc, UINT cb)
{
   MyOpenInfo *po = (MyOpenInfo *)p->pInputStreamPrivateData;
   return ( fread( pc, 1, cb, po->fp ) ); 
}

BOOL pascal mySeek (struct tag_InputStream *p, long l, int w)
{
   MyOpenInfo *po = (MyOpenInfo *)p->pInputStreamPrivateData;
   if (!po->fp) return(1);
   return( !fseek(po->fp, l, w ) );
}

long pascal myTell (struct tag_InputStream *p)
{
   MyOpenInfo *po = (MyOpenInfo *)p->pInputStreamPrivateData;
   if (!po->fp) return(-1);
   return ( ftell(po->fp) );
}

BOOL pascal myClose (struct tag_InputStream *p)
{
   MyOpenInfo *po = (MyOpenInfo *)p->pInputStreamPrivateData;
   if (po->fp)
   {
      fclose( po->fp );
        po->fp = NULL;
   }
   return (TRUE);
}



/*******************************************************************************
 *
 * Memory abstraction: the variable g_MemoryAllocator is passed into all KeyView
 * filtering API entry points requiring it.
 *
 ******************************************************************************/
void * pascal myMalloc (struct tag_MemoryStream *pX, size_t cb)
{
   return ( malloc( cb ) );
}

void   pascal myFree (struct tag_MemoryStream *pX, void *ptr)
{
   free( ptr );
}

void * pascal myRealloc (struct tag_MemoryStream *pX, void *ptr, size_t cb)
{
   return ( realloc( ptr, cb ) );
}

void * pascal myCalloc (struct tag_MemoryStream *pX, size_t ne, size_t s)
{
   return ( calloc( ne, s ) );
}


/******************************************************************************
*
*SaveINIFileString
*
*******************************************************************************/

char* SaveINIFileString(char *szINIString)
{
    char *psz = NULL;
    int nLength = strlen(szINIString);
    if(nLength == 0)
    {
        return NULL;
    }

    psz = (char *)malloc(nLength + 1);

#ifdef _WINDOWS
    assert(psz != 0);
#endif

    strcpy(psz, szINIString);
    return psz;
}


/************************************************************************
 * This function checks to see if the INI file exists by making a call 
 * to GetPrivateProfileString().  If the file is found, no further 
 * action is required.  If the entry returns a blank, the path of the 
 * INI file is adjusted to match the current working directory and 
 * another attempt is made to read the first entry in the file.  If this 
 * also fails, a warning message is output, indicating the INI file was 
 * not found but that the input file will be converted using the internal
 * defaults.
 *************************************************************************/
void LocateINIFile(char *szExecutable, char *szINIFile)
{
   char szINIPath[_MAX_PATH];
   char szINIFileName[_MAX_PATH];
   char *pszINI = NULL;
   char *pszPath = NULL;
   char szReturnedString[GPPSTRINGMAXSIZE];
   
   /* Attempt to find the first entry in the ini file */
   GetPrivateProfileString("config0", "eKVFormat", "Not found", szReturnedString, GPPSTRINGMAXSIZE, szINIFile);
   if(strcmp(szReturnedString, "Not found") == 0)
   {
       /* entry not found, try further */
       char *pcTmp;

       for(pcTmp = szExecutable; *pcTmp != '\0'; pcTmp++)
       {
           *pcTmp = (char)tolower((int)((char)(*pcTmp)));
       }

       /* Determine the directory of the executable, if we can */
       strcpy( szINIPath, szExecutable );
       pszPath = strstr( szExecutable, "filter" );
       szINIPath[pszPath - szExecutable] = '\0';

       strcpy( szINIFileName, szINIFile );
       pszINI = strrchr( szINIFileName, '/' );
       if ( pszINI == NULL )
       {
           pszINI = strrchr( szINIFileName, '\\' );
       }
       if ( pszINI ) 
       {
           strcpy( szINIFileName, &pszINI[1] );

           if ( szINIFileName != NULL )
           {
              pszINI = szINIFileName;
           }
       }
       strcat( szINIPath, szINIFileName );

#ifdef _WINDOWS
       GetCurrentDirectory( _MAX_PATH, szINIPath );
       strcat( szINIPath, "\\" );
#else
       strcpy(szINIPath, "./");
#endif
       strcat( szINIPath, szINIFileName );    

       /* Attempt to find the first entry in the ini file */
       GetPrivateProfileString("config0", "eKVFormat", "Not found", szReturnedString, GPPSTRINGMAXSIZE, szINIPath);
       if(strcmp(szReturnedString, "Not found") != 0 )
       {
            strcpy( szINIFile, szINIPath );
       }
       else
       {
#if !defined (__mac_os)
            printf("File <%s> not found or is not formatted as expected!\n", szINIPath);
            printf("Conversion will proceed with internal defaults.\n");
#endif
       }
   }
}


/******************************************************************************
*
*
*
*******************************************************************************/

void FileTimeToUnixTime(LONGLONG pft, time_t* t)
{
 LONGLONG ll = 0 ;
#if !defined (MSWIN) && !defined(_ILNX21) && !defined(_LNX64i) && !defined(_XLNX64) && !defined(_FBSD32i) && !defined(_SOL64X)
   {
      int i;
      for (i = 0; i < 64; i+=8) {
         ll |= (LONGLONG)((BYTE)(pft>>i))<<(56-i);
      }
   }
#else
   ll = pft; 
#endif

#if defined (_WINDOWS)
   if (ll >= 116444736000000000)
   {
      ll = ll  - 116444736000000000;
   }
#else
   if (ll >= 116444736000000000LL)
   {
      ll = ll  - 116444736000000000LL;
   }
#endif

   else
   {
      ll = 0;
   }
#if defined (_HPUX64i) || (_LNX64i) || (_XLNX64) || (_SOL64X) || (_LNXPPC)
   *t = (unsigned int) (ll/10000000L);
#else
   *t = (unsigned long) (ll/10000000L);
#endif
}


