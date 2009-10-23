#ifndef _STATUS_H_
#define _STATUS_H_

#ifdef __cplusplus 
#include "command_inter.hpp"
extern "C"
{
#endif
     void *status_create();
#ifdef __cplusplus      
}
#endif
class status_cmd:public command_inter
{
public:
     status_cmd()
	  {
	  }
     ~status_cmd()
	  {}
     virtual std::string handle(const std::string& param,const std::string& content);
private:
};
#endif
