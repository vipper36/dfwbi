#include "ChlXpath.h"
#include <sstream>
#include <iostream>
bool ChlXpath::AddPath(std::string nodePath,std::string titlePath)
{
     pathList.push_back(make_pair(nodePath,titlePath));
}
bool ChlXpath::SetWapper(std::string &wrapper)
{
     std::stringstream ss(wrapper);
     while(!ss.eof())
     {
	  std::string tmp;
	  getline(ss,tmp);
	  size_t pos=tmp.find("##");
	  if(pos!=std::string::npos)
	  {
	       std::string nodePath=tmp.substr(0,pos);
	       std::string titlePath=tmp.substr(pos+2);
	       pathList.push_back(make_pair(nodePath,titlePath));
	  }
     }
}
std::string ChlXpath::GetWrapper()
{
     std::stringstream ss;
     for(PathList::iterator it=pathList.begin();it!=pathList.end();++it)
     {
	  ss<<it->first<<"##"<<it->second<<"\n";
     }
     return ss.str();
}
PathList &ChlXpath::GetPathList()
{
     return pathList;
}
