/**
 * @file   DirOperator.cpp
 * @author 
 * @date   Mon Jul 23 10:38:59 2007
 * 
 * @brief  This file implement the member functions of DirOperator class.
 * 
 * 
 */

#include "DirOperator.h"
#include "Logger.h"
#include "BaseException.h"
#include <sys/stat.h>
/** 
 * @brief The default constructor. 
 * 
 */
DirOperator::DirOperator(void)
{
}
/** 
 * @brief Use a path name to construct a DirOperator object.
 * 
 * @param[in] Path The directory's path.
 */
DirOperator::DirOperator(std::string &Path)
    :mPath(Path)
{
    pDirHandle=NULL;
}
/** 
 * @brief The destructor of DirOperator,if the DIR handle is not closed it will close the handle.
 * 
 */
DirOperator::~DirOperator(void)
{
    if(pDirHandle!=NULL)
        Close();
}
/** 
 * @brief Set the path of DirOperator object.
 * 
 * @param[in] Path The directory's path.
 * 
 * @return Always true.
 */
bool DirOperator::SetPath(std::string &Path)
{
    mPath=Path;
    return true;
}
/** 
 * @brief Open the DIR handle of DirOperator object.
 * 
 * 
 * @return Always true
 * @exception BaseException
 */
bool DirOperator::Open()
{
    if(mPath.length()>0&&isDirectory(mPath))
    {
        pDirHandle=opendir(mPath.c_str());
        if(pDirHandle==NULL)
        {
            throw BaseException(DirOpenError,"Directory open error");
        }
        MAINLOG.debugStream()<<"The DIR :"<<mPath<<"is open"<<MAINEND;
    }
    else
    {
        throw BaseException(DirOpenError,"Path wasn't set or is not a directory");
    }
    return true;
}
/** 
 * @brief Close the DIR handle.
 * 
 * 
 * @return Always true.
 * @exception BaseException
 */
bool DirOperator::Close()
{
    if(pDirHandle!=NULL)
    {
        int rtn=closedir(pDirHandle);
        if(rtn!=0)
        {
            throw BaseException(DirCloseError,"Directory Close error");
        }
        else
            pDirHandle=NULL;
    }
    else
    {
        throw BaseException(DirCloseError,"Directory was not open");
    }
    return true;
}
/** 
 * @brief Read the file's name(no directory name was read) in the directory.
 * 
 * 
 * @return The string list contain the file names.
 */
std::list<std::string>* DirOperator::Read()
{
    if(pDirHandle!=NULL)
    {
        struct dirent *dentry=readdir(pDirHandle);
        while(dentry!=NULL)
        {
            std::string fileName(dentry->d_name);
            std::string tmpStr=mPath+"/"+fileName;
            if(!isDirectory(tmpStr))
            {
                MAINLOG.debugStream()<<"The file Name is:"<<fileName<<MAINEND;
                mDirentList.push_back(fileName);
            }
            dentry=readdir(pDirHandle);
        }
        return &mDirentList;
    }
    else
    {
        throw BaseException(DirReadError,"Directory was not open");
    }
}
/** 
 * @brief Call the read function,and return the file name list.
 * 
 * 
 * @return The string list contain the file names.
 */
std::list<std::string> *DirOperator::GetDentries()
{
    Read();
    return &mDirentList;
}
/** 
 * @brief If object defined by the Path is a directory it will return true.
 * 
 * @param[in] Path 
 * 
 * @return true Is a directory
 *         false not.
 */
bool DirOperator::isDirectory(std::string &Path)
{
    struct stat dirStat;
    int rtn=stat(Path.c_str(),&dirStat);
    if(rtn!=0)
    {
        throw BaseException(FileReadError,"Get File Stat Error");
    }
    return dirStat.st_mode&S_IFDIR;
}
