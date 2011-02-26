#ifndef __RINGCOLL_ACTOR_H__
#define __RINGCOLL_ACTOR_H__
#include <Theron/Actor.h>
#include <iostream>
#include "Messages.hpp"
#include "OperateActor.hpp"
// A trivial actor that does nothing.
class RingCollActor : public OperateActor
{
public:

    inline RingCollActor()
        {            
            RegisterHandler(this, &RingCollActor::StockMessageHandler);
            RegisterHandler(this, &RingCollActor::StockListMessageHandler);
            RegisterHandler(this, &RingCollActor::PriceResMessageHandler);
            RegisterHandler(this, &RingCollActor::FetchTaskMessageHandler);
            RegisterHandler(this, &RingCollActor::FetchResultMessageHandler);
            RegisterHandler(this, &RingCollActor::ClassifyResultMessageHandler);
            RegisterHandler(this, &RingCollActor::ExtractResultMessageHandler);
            RegisterHandler(this, &RingCollActor::IndexMessageHandler);
            RegisterHandler(this, &RingCollActor::QueryMessageHandler);
            RegisterHandler(this, &RingCollActor::QueryResponceMessageHandler);
            current=childrens.begin();
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            switch(message.type)
            {
            case OperateMessage::STATUS:
                Send(OperateMessage(OperateMessage::RESP,"RingCollActor ok"), from);
                for(std::map<std::string,Theron::Address>::iterator it=childrens.begin();it!=childrens.end();++it)
                {
                    Send(message, it->second);
                }
                break;
            case OperateMessage::RESP:
                Send(message, parent);
                break;
            case OperateMessage::SET:
                if(from!=parent)
                {
                    Send(message, parent);
                }
                break;
            default:
                break;
            }
        }
    template<typename MSG>
    void MSGHandler(const MSG &message, const Theron::Address from)
        {
            if(from!=parent)
                Send(message, parent);
            else
            {
                if(current==childrens.end())
                    current= childrens.begin();
                Send(message, current->second);
                ++current;
            }
        }
    void StockMessageHandler(const StockMessage &message, const Theron::Address from)
        {
            MSGHandler(message,from);
        }
    void StockListMessageHandler(const StockListMessage &message, const Theron::Address from)
        {
            MSGHandler(message,from);
        }
    void PriceResMessageHandler(const PriceResMessage &message, const Theron::Address from)
        {
            MSGHandler(message,from);
        }
    void FetchTaskMessageHandler(const FetchTaskMessage &message, const Theron::Address from)
        {
            MSGHandler(message,from);
        }
    void FetchResultMessageHandler(const FetchResultMessage &message, const Theron::Address from)
        {
            MSGHandler(message,from);
        }
    void ClassifyResultMessageHandler(const ClassifyResultMessage &message, const Theron::Address from)
        {
            MSGHandler(message,from);
        }
    void ExtractResultMessageHandler(const ExtractResultMessage &message, const Theron::Address from)
        {
            MSGHandler(message,from);
        }
    void IndexMessageHandler(const IndexMessage &message, const Theron::Address from)
        {
            MSGHandler(message,from);
        }
    void QueryMessageHandler(const QueryMessage &message, const Theron::Address from)
        {
            MSGHandler(message,from);
        }
    void QueryResponceMessageHandler(const QueryResponceMessage &message, const Theron::Address from)
        {
            MSGHandler(message,from);
        }
private:
    std::map<std::string,Theron::Address>::iterator current;
}; 
#endif
