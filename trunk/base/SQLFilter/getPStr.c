/******************************************************************************
 *                                                                            *
   Copyright © 2007 Autonomy Corp. All rights reserved. Other trademarks are
   registered trademarks and the properties of their respective owners.
   Product specifications and features are subject to change without notice.
   Use of Autonomy software is under license.
 *                                                                            *
 ******************************************************************************/

#if !defined(_WINDOWS) && !defined(WIN32)
/***********************************************************************
 *
 * getProfileString.c
 *
 ***********************************************************************/


#include <stdio.h>
#include <string.h>




/***********/
/* HEADERS */
/***********/
int myGetPrivateProfileString(char*, char*, char*, char*, int, char*);

/*+**************************/
/* CONSTANTS AND DATA TYPES */
/****************************/

#define INBUFSIZ 2048

/*+**************************************************************************
 *
 *   MODULE  :   
 *
 *   SUMMARY : 
 *	      
 *        
 ***************************************************************************/
int myGetPrivateProfileString(char * Application, char * Key, char * deflt, char *  ReturnString, int nSize, char *pszFileName)
{
  FILE*      fp;
  char*      tok;
  char*      val;
  char       c;
  char       i;
  char       Appl[40];
  char       section[INBUFSIZ]="";
  char       source[INBUFSIZ]="default";
  char       inibuf[INBUFSIZ];


  if (nSize > INBUFSIZ) nSize = INBUFSIZ;

#if defined (__mac_os)
  memcpy(ReturnString, deflt, nSize);
#else
  strncpy(ReturnString, deflt, nSize);
#endif

  if ((fp = fopen(pszFileName, "r" )) == NULL)
  {
      return(-1);
  }

  while (fgets(inibuf,INBUFSIZ - 1,fp) != NULL)
  {
	

	 if (inibuf[strlen(inibuf)-1] == '\n') inibuf[strlen(inibuf)-1] = '\0';
	
 	if ('\0'==inibuf[0] || inibuf[0]==';') continue;

#if defined (__mac_os)
	if ('\r' == inibuf[0]) strcpy(inibuf, &inibuf[1]);
#endif

    if (inibuf[0]=='[')
    {
      tok = (char *)strtok((char *)inibuf,"[]");

      strcpy(section,tok);
    }
    else if (!strcmp(section, Application) )
    {

      tok = (char *)strtok((char *)inibuf,"=");
  
      if (!strcmp(tok, Key))
      {
          char *p = tok + strlen(tok) + 1;
          if (*p == '\n') 
          {
              ReturnString[0] = '\0';
          }       
          else
          {
           	val = (char *)strtok(p,"\n");


              if (val) strncpy(ReturnString, val, nSize);
              else ReturnString[0] = '\0';
              if (nSize>1) ReturnString[nSize-1] = '\0';
           }
           break;
      }
    }
  }

  fclose(fp);

  return(strlen(ReturnString));
}

#endif /* !_WINDOWS */


