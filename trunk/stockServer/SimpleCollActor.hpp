#ifndef __SIMPLECOLL_ACTOR_H__
#define __SIMPLECOLL_ACTOR_H__
#include <Theron/Actor.h>
#include <iostream>
#include "OperateActor.hpp"
#include "TimerFactory.hpp"
#include <boost/bind.hpp>
#include <map>
#include <string>
class SimpleCollActor : public OperateActor
{
public:

    inline SimpleCollActor():OperateActor()
        {
            RegisterHandler(this, &SimpleCollActor::StockRealHandler);
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            if(message.type==OperateMessage::STATUS)
            {
                Send(OperateMessage(OperateMessage::RESP,"ok"), from);
            }
        }
    void MapHandler(const MapMessage &message, const Theron::Address from)
        {
            if(message.type==MapMessage::ATTR)
            {
                attMap=message.map;
            }
        }
    void StockRealHandler(const StockRealMessage &message, const Theron::Address from)
        {
            Send(message, parent);
        }
private:
    std::map<std::string,std::string> attMap;
}; 
#endif
