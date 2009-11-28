#ifndef _SEGMENT_H_
#define _SEGMENT_H_

#ifdef __cplusplus 
#include "command_inter.hpp"
#include "scws.h"
extern "C"
{
#endif
     void *Segment_create();
#ifdef __cplusplus      
}
#endif

class Segment_cmd:public command_inter
{
public:
     static Segment_cmd* Instance();
     
     virtual std::string handle(const std::string& param,const std::string& content);
protected:
     ~Segment_cmd();
     Segment_cmd();
private:
     static Segment_cmd* m_instance;
     scws_t m_s;
     std::string m_param;
};
#endif
