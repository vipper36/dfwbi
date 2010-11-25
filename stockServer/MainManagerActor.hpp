#ifndef __MAINMANAGER_ACTOR_H__
#define __MAINMANAGER_ACTOR_H__
#include <Theron/Actor.h>
#include <iostream>
#include "OperateActor.hpp"
#include "Messages.hpp"
class MainManagerActor : public OperateActor
{
public:

    inline MainManagerActor()
        {
            RegisterHandler(this, &MainManagerActor::StockHandler);
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            Send(OperateMessage(OperateMessage::STATUS,"ok"), from);
        }
    void MapHandler(const MapMessage &message, const Theron::Address from)
        {
            if(message.type==MapMessage::MSG)
            {
                msgMap=message.map;
            }
        }
    void StockHandler(const StockMessage &message, const Theron::Address from)
        {
            std::map<std::string,std::string>::iterator fit=msgMap.find("StockMessage");
            if(fit!=msgMap.end())
            {
                Send(message,childrens[fit->second]);
            }
        }
private:
    std::map<std::string,std::string> msgMap;
}; 
#endif
