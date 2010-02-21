#ifndef _FILE_LIST_H_
#define _FILE_LIST_H_
#include <string>
#include <list>
#include "list_inter.hpp"
#include "Logger.hpp"
#ifdef __cplusplus 
extern "C"
{
#endif
  void *list_create();
#ifdef __cplusplus      
}
#endif
class file_list:public list_inter
{
public:
  file_list()
  {
    init_logs();
  }
  ~file_list()
  {}
  virtual void open(std::string source,std::string mark);
  virtual std::map<std::string,std::string> &GetList();
private:
  std::map<std::string,std::string> _list;
};
#endif
