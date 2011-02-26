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
            RegisterHandler(this, &SimpleCollActor::StockMessageHandler);
            RegisterHandler(this, &SimpleCollActor::PriceReqMessageHandler);
            RegisterHandler(this, &SimpleCollActor::FetchTaskMessageHandler);
            RegisterHandler(this, &SimpleCollActor::ExtractResultMessageHandler);
            RegisterHandler(this, &SimpleCollActor::IndexMessageHandler);
            RegisterHandler(this, &SimpleCollActor::QueryMessageHandler);
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
    void StockMessageHandler(const StockMessage &message, const Theron::Address from)
        {
            Send(message, parent);
        }
    void PriceReqMessageHandler(const PriceReqMessage &message, const Theron::Address from)
        {
            Send(message, parent);
        }
    void FetchTaskMessageHandler(const FetchTaskMessage &message, const Theron::Address from)
        {
            Send(message, parent);
        }
    void ExtractResultMessageHandler(const ExtractResultMessage &message, const Theron::Address from)
        {
            Send(message, parent);
        }
    void IndexMessageHandler(const IndexMessage &message, const Theron::Address from)
        {
            Send(message, parent);
        }
    void QueryMessageHandler(const QueryMessage &message, const Theron::Address from)
        {
            Send(message, parent);
        }
private:

}; 
#endif
