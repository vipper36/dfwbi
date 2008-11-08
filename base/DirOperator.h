/**
 * @file   DirOperator.h
 * @author 
 * @date   Mon Jul 23 10:50:36 2007
 * 
 * @brief  This file has the define of class DirOperator
 *
 */
#ifndef __DIR_OPERATOR_H__
#define __DIR_OPERATOR_H__
#include <dirent.h>
#include <string>
#include <list>/** 
 * 
 * 
 * @brief Diroperator manages the directory,in charge of open,close and read the dentries of dirctory.
 * @author xiaofei
 */

class DirOperator
{
  private:
    DIR *pDirHandle;
    std::string mPath;
    std::list<std::string> mDirentList;
  public:
    DirOperator(void);
    ~DirOperator(void);
    DirOperator(std::string &Path);
    bool SetPath(std::string &Path);
    bool Open();
    bool Close();
    std::list<std::string> *Read();
    std::list<std::string> *GetDentries();
    static bool isDirectory(std::string &Path);
};
#endif
