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
            RegisterHandler(this, &SimpleCollActor::StockHandler);
            RegisterHandler(this, &SimpleCollActor::PriceReqHandler);
            RegisterHandler(this, &SimpleCollActor::FetchTaskHandler);
            RegisterHandler(this, &SimpleCollActor::ExtractResultHanlde);
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            switch(message.type)
            {
            case OperateMessage::STATUS:
                Send(OperateMessage(OperateMessage::RESP,"SimpleCollActor ok"), from);
                for(std::map<std::string,Theron::Address>::iterator it=childrens.begin();it!=childrens.end();++it)
                {
                    Send(message, it->second);
                }
                break;
            case OperateMessage::RESP:
                Send(message, parent);
                break;
            default:
                break;
            }
        }
    void MapHandler(const MapMessage &message, const Theron::Address from)
        {
            if(message.type==MapMessage::ATTR)
            {
                attMap=message.map;
            }
        }
    void StockHandler(const StockMessage &message, const Theron::Address from)
        {
            Send(message, parent);
        }
    void PriceReqHandler(const PriceReqMessage &message, const Theron::Address from)
        {
            Send(message, parent);
        }
    void FetchTaskHandler(const FetchTaskMessage &message, const Theron::Address from)
        {
            Send(message, parent);
        }
    void ExtractResultHanlde(const ExtractResultMessage &message, const Theron::Address from)
        {
            Send(message, parent);
        }
private:
    std::map<std::string,std::string> attMap;
}; 
#endif
