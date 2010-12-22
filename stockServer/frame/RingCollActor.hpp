#ifndef __RINGCOLL_ACTOR_H__
#define __RINGCOLL_ACTOR_H__
#include <Theron/Actor.h>
#include <iostream>
#include "OperateActor.hpp"
// A trivial actor that does nothing.
class RingCollActor : public OperateActor
{
public:

    inline RingCollActor()
        {            
            RegisterHandler(this, &RingCollActor::StockHandler);
            RegisterHandler(this, &RingCollActor::StockListHandler);
            RegisterHandler(this, &RingCollActor::PriceResHandler);
            RegisterHandler(this, &RingCollActor::FetchTaskHandler);
            RegisterHandler(this, &RingCollActor::ClassifyResultHandle);
            RegisterHandler(this, &RingCollActor::ExtractResultHandle);
            RegisterHandler(this, &RingCollActor::FetchResultHandler);
            RegisterHandler(this, &RingCollActor::IndexHandle);
            RegisterHandler(this, &RingCollActor::QueryHandle);
            RegisterHandler(this, &RingCollActor::QueryResponceHandle);
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
    void MapHandler(const MapMessage &message, const Theron::Address from)
        {
            if(message.type==MapMessage::ATTR)
            {
                attMap=message.map;
            }
        }
    void StockHandler(const StockMessage &message, const Theron::Address from)
        {
            if(from!=parent)
                Send(message, parent);
            else
            {
                Send(message, current->second);
                ++current;
                if(current==childrens.end())
                    current= childrens.begin();
            }
        }
    void StockListHandler(const StockListMessage &message, const Theron::Address from)
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
    void PriceResHandler(const PriceResMessage &message, const Theron::Address from)
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
    void FetchTaskHandler(const FetchTaskMessage &message, const Theron::Address from)
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
    void FetchResultHandler(const FetchResultMessage &message, const Theron::Address from)
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
    void ClassifyResultHandle(const ClassifyResultMessage &message, const Theron::Address from)
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
    void ExtractResultHandle(const ExtractResultMessage &message, const Theron::Address from)
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
    void IndexHandle(const IndexMessage &message, const Theron::Address from)
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
    void QueryHandle(const QueryMessage &message, const Theron::Address from)
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
    void QueryResponceHandle(const QueryResponceMessage &message, const Theron::Address from)
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
private:
    std::map<std::string,Theron::Address>::iterator current;
    std::map<std::string,std::string> attMap;
}; 
#endif
