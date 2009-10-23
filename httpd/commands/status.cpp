#include <iostream>
#include "status.h"
void *status_create()
{
     status_cmd *ret=new status_cmd();
     return (void*)ret;
}
std::string status_cmd::handle(const std::string& param,const std::string& content)
{
  std::string ret("hello world");
  return ret;
}
