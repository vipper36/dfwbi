#ifndef __CHLXPATH_H__
#define __CHLXPATH_H__
#include <list>
#include <string>
typedef std::pair<std::string,std::string> PathPair;
typedef std::list<PathPair>  PathList;
class ChlXpath
{
private:
     PathList pathList;
public:
     bool AddPath(std::string nodePath,std::string titlePath);
     bool SetWapper(std::string &wrapper);
     std::string GetWrapper();
     PathList &GetPathList();
};
#endif
