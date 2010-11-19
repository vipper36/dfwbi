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
            std::cout<<"RingCollActor constructed\n"<<std::endl;
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            Send(OperateMessage(OperateMessage::STATUS,"ok"), from);
        }
    void MapHandler(const MapMessage &message, const Theron::Address from)
        {
            Send(OperateMessage(OperateMessage::STATUS,"ok"), from);
        }
}; 
#endif
