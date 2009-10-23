#ifndef __COMMAND_INTER_H__
#define __COMMAND_INTER_H__
class command_inter
{
public:
     virtual ~command_inter(){};
     virtual std::string handle(const std::string &param, const std::string& content)=0;
};
#endif
