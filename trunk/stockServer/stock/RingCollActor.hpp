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

            Send(message, current->second);
            ++current;
            if(current==childrens.end())
                current= childrens.begin();
        }
    void StockListHandler(const StockListMessage &message, const Theron::Address from)
        {

            Send(message, current->second);
            ++current;
            if(current==childrens.end())
                current= childrens.begin();
        }
    void PriceResHandler(const PriceResMessage &message, const Theron::Address from)
        {
            Send(message, current->second);
            ++current;
            if(current==childrens.end())
                current= childrens.begin();
        }
private:
    std::map<std::string,Theron::Address>::iterator current;
    std::map<std::string,std::string> attMap;
}; 
#endif
