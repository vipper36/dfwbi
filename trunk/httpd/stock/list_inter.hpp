#ifndef __LIST_INTER_H__
#define __LIST_INTER_H__
#include <string>
#include <map>
#include <list>
class list_inter
{
public:
  virtual ~list_inter(){};
  virtual void open(std::string source,std::string mark)=0;
  virtual std::map<std::string,std::string> &GetList()=0;
};
#endif
