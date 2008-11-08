/**
 * @file   FileOperator.h
 * @author 
 * @date   Thu Jun 07 10:28:35 2007
 * 
 * @brief  This File define the class that manage the file read and write.
 * 
 * 
 */

#ifndef __FILE_OPERATRO_H__
#define __FILE_OPERATRO_H__
#include <string>
/** 
 * 
 * 
 * @brief This class is in charge of file raed and write.
 * @author xiaofei
 * 
 */
class FileOperator
{
  private:
    std::string m_FileName;
    std::string m_fileEncode;
    int m_fd;
    int m_size;
  public:
    FileOperator();
    FileOperator(std::string &fileN,std::string encodeName=std::string("GB2312"));
    ~FileOperator();
    bool Open(int flag);
    bool SetFileName(std::string &fileN);
    bool Open(std::string &fileN,int flag);
    bool LockFile();
    bool UnlockFile();
    bool Close();
    int Read(char* buf,int buf_len);
    int GetFileSize();
    int ReadAll(char* buf);
    int Write(char* buf,int buf_len);
    std::string GetEncodeName();
    bool SetEncodeName(std::string &encodeName);
    static bool GB2312_2_Other(const char* encodeName,char *in, int inLen, char *out, int outLen);
    static bool Other_2_GB2312(const char* encodeName,char *in, int inLen, char *out, int outLen);
    static bool dos2unix(char* buf);
};  
#endif
