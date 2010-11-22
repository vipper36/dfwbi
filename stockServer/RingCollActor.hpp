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
            RegisterHandler(this, &RingCollActor::StockRealHandler);
            current=childrens.begin();
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            Send(OperateMessage(OperateMessage::STATUS,"ok"), from);
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
