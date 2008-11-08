/**
 * @file   FileOperator.cpp
 * @author xiaofei
 * @date   Thu Jun 07 10:47:38 2007
 * 
 * @brief  This file implement the class FileOperator's interface.
 * 
 * 
 */
#include "Logger.h"
#include "BaseException.h"
#include "FileOperator.h"
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <iconv.h>
/** 
 * @brief This is the default constructor of FileOperator.
 * 
 *
 */
FileOperator::FileOperator()
{
    m_fileEncode=std::string("GB2312");
    m_fd=-1;
    m_size=-1;
}
/** 
 * @brief The Other constructor
 * 
 * @param[in] fileN The file Name with the path.
 * @param[in] encodeName Default value is "GB2312"
 *
 */
FileOperator::FileOperator(std::string &fileN,std::string encodeName)
    :m_FileName(fileN)
    ,m_fileEncode(encodeName)   
{
    m_fd=-1;
    m_size=-1;
}
/** 
 * @brief This is the destructor.
 * 
 */
FileOperator::~FileOperator()
{
    if(m_fd!=-1)
        close(m_fd);
}
/** 
 * @brief This function open the file for FileOperator,
 * and this function must be called before read & write.
 * 
 * @param[in] flag The open flag like O_RDWR
 * 
 * @return Alyway true
 * @exception BaseException
 */
bool FileOperator::Open(int flag)
{
    if(m_FileName.length()<1)
    {
        throw BaseException(FileOpenError,"File Name Not exist");
    }
    std::string openFile=m_FileName;
    if(flag&O_CREAT)
    {
        for(int i=0;access(openFile.c_str(),F_OK)==0;i++)
        {
            std::stringstream tmp;
            tmp<<m_FileName<<"("<<i<<")";
            openFile=tmp.str();
        }
    }
    m_fd=open(openFile.c_str(),flag,00666);
    if(m_fd<0)
    {
        throw BaseException(FileOpenError,"Can't open the file");
    }
    
    return true;
}

/** 
 * @brief Set the File name of FileOperator when not construct with a file name.
 * 
 * @param[in] fileN The file Name of FileOperator. 
 * 
 * @return Always true
 * 
 */

bool FileOperator::SetFileName(std::string &fileN)
{
    m_FileName=fileN;
    return true;
}
/** 
 * @brief The other open of FileOperator.
 * 
 * @param[in] fileN The file name to open.
 * @param[in] flag The open flag like O_RDWR.
 *
 * @return Always true
 * 
 */
bool FileOperator::Open(std::string &fileN,int flag)
{
    m_FileName=fileN;
    return Open(flag);
}
/** 
 *@brief Close the file when do not need to operate it. 
 * 
 * 
 * @return Always true
 * @exception BaseException
 */

bool FileOperator::Close()
{
    int ret=close(m_fd);
    if(ret<0)
    {
        throw BaseException(FileOpenError,"Can't close the file");
    }
    m_fd=-1;
    return true;
}
/** 
 *@brief Read the file. 
 * 
 * @param[out] buf 
 * @param[in] buf_len 
 * 
 * @return The number of items successfully read
 * @excetion BaseException
 */
int FileOperator::Read(char* buf,int buf_len)
{
    if(buf==NULL)
    {
        throw BaseException(BufNullException,"The Read Buf is NULL");
    }
    if(m_fd==-1)
    {
        throw BaseException(FileReadError,"The file is not open");
    }
    int ret=read(m_fd,buf,buf_len);
    if(ret<0)
    {
        throw BaseException(FileReadError,"File Read Error");
    }
    return ret;
}
/** 
 * @brief Try to lock the file exclusively.
 * 
 * 
 * @return true Lock correctly
 *         false Not.
 */
bool FileOperator::LockFile()
{
    struct stat fileStat;
    int rtn=fstat(m_fd,&fileStat);
    if(rtn!=0)
    {
        LOG(ERROR,"Get File Stat Error");
        return false;
    }
    int mode = fileStat.st_mode;
     	/* remove group execute permission from mode */
    mode &= ~S_IXGRP;
        /* set 'set group id bit' in mode */
    mode |= S_ISGID;
    if (fchmod(m_fd, mode) < 0) {
        LOG(ERROR,"Change mode Error");
        return false;
    }
    struct flock lck;
    lck.l_type = F_WRLCK;	/* setting a write lock */
    lck.l_whence = 0;	/* offset l_start from beginning of file */
    lck.l_start = (off_t)0;	
    lck.l_len = (off_t)0;	/* until the end of the file */
    if (fcntl(m_fd, F_SETLK, &lck) <0) {
        if (errno == EAGAIN || errno == EACCES) {
            LOG(ERROR, "File busy try again later!\n");
            return false;
        }
    }
    return true;
}
/** 
 * @brief Try to unlock the file.
 * 
 * 
 * @return true Unlock correctly
 *         false Not.
 */
bool FileOperator::UnlockFile()
{
    struct flock lck;
    lck.l_type = F_UNLCK;	/* setting a write lock */
    lck.l_whence = 0;	/* offset l_start from beginning of file */
    lck.l_start = (off_t)0;	
    lck.l_len = (off_t)0;	/* until the end of the file */
    if (fcntl(m_fd, F_SETLK, &lck) <0) {
        LOG(ERROR, "Unlock file error");
            return false;
    }
    return true;
}

/** 
 * @brief Call this function to Get the size of the file.
 * 
 * 
 * @return The size of the file.
 */
int FileOperator::GetFileSize()
{
    struct stat fileStat;
    int rtn=fstat(m_fd,&fileStat);
    if(rtn!=0)
    {
        throw BaseException(FileReadError,"Get File Stat Error");
    }
    m_size=fileStat.st_size;
    return m_size;
}
/** 
 * @brief Read all the information in the file. 
 * 
 * @param[out] buf The target memery buffer. 
 * 
 * @return The number of items successfully read
 * @exception BaseException
 */
int FileOperator::ReadAll(char* buf)
{
    if(buf==NULL)
    {
        throw BaseException(BufNullException,"The Read Buf is NULL");
    }
    if(m_size<0)
        GetFileSize();
    MAINLOG.debugStream()<<"The file size is:"<<m_size<<MAINEND;
    std::auto_ptr<char> tmpBuf(new char[m_size+1]);
    if(tmpBuf.get()==NULL)
    {
        throw BaseException(BufNullException,"Get tmp Buffer error");
    }
    memset(tmpBuf.get(),0,m_size+1);
    int rtn=Read(tmpBuf.get(),m_size);
    if(rtn>0)
    {
        dos2unix(tmpBuf.get());
        MAINLOG.debugStream()<<"The encode setting is:"<<m_fileEncode<<MAINEND;
        if(m_fileEncode=="GB2312"||m_fileEncode=="")
        {
            LOG(DEBUG,"Don't need convert!");
            memcpy(buf,tmpBuf.get(),rtn);
        }
        else
        {
                /// if the file's encoding is not GB2312, need to convert the encoding to GB2312 first. 
            int tmpLen=m_size*2+1;
            std::auto_ptr<char> transBuf(new char[tmpLen]);
            if(transBuf.get()==NULL)
            {
                throw BaseException(BufNullException,"Get tmp buffer error");
            }
            memset(transBuf.get(),0,tmpLen);
            if(Other_2_GB2312(m_fileEncode.c_str(),tmpBuf.get(), rtn, transBuf.get(), tmpLen))
            {
                rtn=strlen(transBuf.get());
                memcpy(buf,transBuf.get(),rtn);
            }
            else
            {
                throw BaseException(CodeConvertError,"Can't convert the file content");
            }
            
        }
    }
    return rtn;
}
/** 
 * @brief Write the items in the buffer to the file.
 * 
 * @param[in] buf 
 * @param[in] buf_len 
 * 
 * @return The number of items successfully read
 */
int FileOperator::Write(char* buf,int buf_len)
{
    if(buf==NULL)
    {
        throw BaseException(BufNullException,"The Write Buf is NULL");
    }
    if(m_fd==-1)
    {
        throw BaseException(FileWriteError,"The file is not open");
    }
    int ret;
//    MAINLOG.debugStream()<<"The Buffer is:"<<buf<<"The buffer length is:"<<buf_len<<MAINEND;
    MAINLOG.debugStream()<<"The encode setting is:"<<m_fileEncode<<MAINEND;
    if(m_fileEncode=="GB2312"||m_fileEncode=="")
    {
        LOG(DEBUG,"Don't need convert!");
        ret=write(m_fd,buf,buf_len);
        if(ret!=buf_len)
        {
            throw BaseException(FileWriteError,"File write Error");
        }
    }
    else
    {
        /// if the file's encoding is not GB2312, need to convert the GB2312 encoding to the file's encoding first. 
        int tmpLen=buf_len*2+1;
        std::auto_ptr<char> transBuf(new char[tmpLen]);
        if(transBuf.get()==NULL)
        {
            throw BaseException(BufNullException,"Get tmp buffer error");
        }
        memset(transBuf.get(),0,tmpLen);
        if(GB2312_2_Other(m_fileEncode.c_str(),buf, buf_len, transBuf.get(), tmpLen))
        {
            tmpLen=strlen(transBuf.get());
            ret=write(m_fd,transBuf.get(),tmpLen);
            if(ret!=tmpLen)
            {
                throw BaseException(FileWriteError,"File write Error");
            }
        }else
        {
            throw BaseException(CodeConvertError,"Can't convert the file content");
        }
        
    }
    return ret;
}
/** 
 * @brief Get the file's encoding.
 * 
 * 
 * @return The encoding name.
 */
std::string FileOperator::GetEncodeName()
{
    return m_fileEncode;
}
/** 
 * @brief Set the file's encoding.
 * 
 * @param[in] encodeName 
 * 
 * @return Always true.
 */
bool FileOperator::SetEncodeName(std::string &encodeName)
{
    m_fileEncode=encodeName;
    return true;
}
/** 
 * @brief Convert the other kind of encoding to GB2312.
 * 
 * @param[in] encodeName 
 * @param[in] in 
 * @param[in] inLen 
 * @param[out] out 
 * @param[in] outLen 
 * 
 * @return Always true
 * @exception BaseException
 */
bool FileOperator::Other_2_GB2312(const char* encodeName,char *in, int inLen, char *out, int outLen)
{
    iconv_t cd = iconv_open( "GBK", encodeName );
    if( (int)cd == -1 )
    {
        throw BaseException(CodeConvertError,"Can't open convert");
    }
    char *pin = in, *pout = out;
    int  inLen_ = inLen + 1;
    int  outLen_ = outLen;

    iconv( cd, &pin, (size_t*)&inLen_, &pout, (size_t*)&outLen_ );
    iconv_close(cd);
    return true;
}
/** 
 * @brief Convert GB2312 to the other encoding.
 * 
 * @param[in] encodeName 
 * @param[in] in 
 * @param[in] inLen 
 * @param[out] out 
 * @param[in] outLen 
 * 
 * @return Always true
 * @exception BaseException
 */
bool FileOperator::GB2312_2_Other(const char* encodeName,char *in, int inLen, char *out, int outLen)
{
    iconv_t cd = iconv_open( encodeName,"GBK" );
    if( (int)cd == -1 )
    {
        throw BaseException(CodeConvertError,"Can't open convert");
    }
    char *pin = in, *pout = out;
    int  inLen_ = inLen + 1;
    int  outLen_ = outLen;

    iconv( cd, &pin, (size_t*)&inLen_, &pout, (size_t*)&outLen_ );
    iconv_close(cd);
    return true;
}
/** 
 * @brief Delete the '\r' from the buffer.
 * 
 * @param[in] buf 
 * @param[out] buf  
 * @return Always true. 
 */
bool FileOperator::dos2unix(char* buf)
{
    if(strstr(buf,"\r")==NULL)
        return true;
    else
    {
        char *tmpBuf=new char[strlen(buf)+1];
        char *pFind,*pStart,*pTarget;
        if(tmpBuf==NULL)
        {
            throw BaseException(BufNullException,"Get tmp buffer error");
        }
        memset(tmpBuf,0,strlen(buf)+1);
        pStart=buf;
        pTarget=tmpBuf;
        pFind=strstr(pStart,"\r");
        while(pFind!=NULL)
        {
            int len=pFind-pStart;
            strncpy(pTarget,pStart,len);
            pTarget=pTarget+len;
            pStart=pFind+1;
            pFind=strstr(pStart,"\r");
        }
        if(*pStart!='\0')
            strcpy(pTarget,pStart);
        memset(buf,0,strlen(buf));
        strcpy(buf,tmpBuf);
        delete tmpBuf;
        return true;
    }
    
}
