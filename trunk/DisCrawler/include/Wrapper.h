#ifndef __WRAPPER_H__
#define __WRAPPER_H__
#include <string>
#include <map>
#include <list>
namespace apcpp
{
     struct WrapEle
     {
	  std::string name;
	  short type;
	  std::string WrapStr;
     };
     class Wrapper
     {
     private:
	  std::multimap<std::string,WrapEle> eles;
     public:
	  std::list<WrapEle> GetEle(const std::string &name);
	  bool AddEle(WrapEle &ele);
	  bool SetWrapper(std::string wrap);
	  std::string GetWrapper();
     };
}
#endif
