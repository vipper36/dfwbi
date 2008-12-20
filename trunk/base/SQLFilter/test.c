// t1.cpp : 定义控制台应用程序的入口点。
//
#include <stdlib.h> 
#include <stdio.h>
#include "filter.h"
typedef struct
{
     void* pInputStreamPrivateData;
}MEMI;
int main(int argc,char* argv[])
{
     if(argc <2)
     {
	  printf("use:test pdffile\n");
	  exit(0);
     }
     unsigned char in[1024*1024];
     unsigned char out[1024*1024];
     unsigned char filename[1024];
     memset(filename,0,sizeof(filename));
     memset(in,0,sizeof(in));
     memset(out,0,sizeof(out));

     if(argc<2)
	  printf("usage:decode filename!\n");
     FILE *fpr=NULL,*fpw=NULL;
     fpr=fopen(argv[1],"r");
     if(fpr==NULL)
     {
	  printf("source file open error!\n");
     }
     strcpy(filename,argv[1]);
     strcat(filename,".out");
     fpw=fopen(filename,"w");
     if(fpw==NULL)
     {
	  printf("target file open error!\n");
     }
     int rsize=fread(in,1,1024*1024,fpr);
     //rewind(fpr);
     //MemOperInfo min;
     //MEMI minfo;
     //min.buf_len=rsize;
     //min.buff=in;
     /*minfo.pInputStreamPrivateData=&min;
     MemOpen(&minfo);
     int i;
     for(i=0;i<3;i++)
     {
	  MemRead(&minfo,out,10);
	  printf("mem:%s\n",out);
	  memset(out,0,sizeof(out));
     
	  fread(out,1,10,fpr);
	  printf("file:%s\n",out);
	  memset(out,0,sizeof(out));
     }
      printf("________________-\n");
     fseek(fpr,0,SEEK_SET);
     MemSeek(&minfo,0,SEEK_SET);
     for(i=0;i<3;i++)
     {
	  MemRead(&minfo,out,10);
	  printf("mem:%s\n",out);
	  memset(out,0,sizeof(out));
     
	  fread(out,1,10,fpr);
	  printf("file:%s\n",out);
	  memset(out,0,sizeof(out));
     }
     fseek(fpr,5,SEEK_SET);
     MemSeek(&minfo,5,SEEK_SET);
           printf("________________-\n");
     for(i=0;i<3;i++)
     {
	  MemRead(&minfo,out,10);
	  printf("mem:%s\n",out);
	  memset(out,0,sizeof(out));
     
	  fread(out,1,10,fpr);
	  printf("file:%s\n",out);
	  memset(out,0,sizeof(out));
     }
     fseek(fpr,0,SEEK_SET);
     MemSeek(&minfo,0,SEEK_SET);
     fseek(fpr,5,SEEK_CUR);
     MemSeek(&minfo,5,SEEK_CUR);
      printf("________________-\n");
     for(i=0;i<3;i++)
     {
	  MemRead(&minfo,out,10);
	  printf("mem:%s\n",out);
	  memset(out,0,sizeof(out));
     
	  fread(out,1,10,fpr);
	  printf("file:%s\n",out);
	  memset(out,0,sizeof(out));
     }
     
     fseek(fpr,-15,SEEK_CUR);
     MemSeek(&minfo,-15,SEEK_CUR);
      printf("________________-\n");
     for(i=0;i<3;i++)
     {
	  MemRead(&minfo,out,10);
	  printf("mem:%s\n",out);
	  memset(out,0,sizeof(out));
     
	  fread(out,1,10,fpr);
	  printf("file:%s\n",out);
	  memset(out,0,sizeof(out));
     }
      printf("________________-\n");
     fseek(fpr,-30,SEEK_END);
     MemSeek(&minfo,-30,SEEK_END);
     for( i=0;i<3;i++)
     {
	  MemRead(&minfo,out,10);
	  printf("mem:%s\n",out);
	  memset(out,0,sizeof(out));
     
	  fread(out,1,10,fpr);
	  printf("file:%s\n",out);
	  memset(out,0,sizeof(out));
	  }*/
     int tar_len=0;
     if(rsize>0)
     {
	  FilterMem(in,rsize,out,&tar_len);
     }
     if(tar_len>0)
     {
	  fwrite(out,1,tar_len,fpw);
     }

     return 0;
}

