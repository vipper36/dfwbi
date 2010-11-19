#ifndef __MQ_ACTOR_H__
#define __MQ_ACTOR_H__
#include <Theron/Actor.h>
#include <iostream>
#include "OperateActor.hpp"
// A trivial actor that does nothing.
class MqActor : public OperateActor
{
public:

    inline MqActor()
    {
        std::cout<<"MqActor"<<std::endl;
    }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            Send(OperateMessage(OperateMessage::STATUS,"ok"), from);
        }
    void MapHandler(const MapMessage &message, const Theron::Address from)
        {
            
        }
}; 
#endif
