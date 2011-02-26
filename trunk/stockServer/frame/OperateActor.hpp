#ifndef __OPERATE_ACTOR_H__
#define __OPERATE_ACTOR_H__
#include <Theron/Actor.h>
#include <iostream>
#include "Messages.hpp"
class OperateActor : public Theron::Actor
{
public:

    inline OperateActor()
    {
        RegisterHandler(this, &OperateActor::OperateHandler);
        RegisterHandler(this, &OperateActor::MapHandler);
        RegisterHandler(this, &OperateActor::AddressHandler);
    }
protected:
    virtual void OperateHandler(const OperateMessage &message, const Theron::Address from)=0;
    void AddressHandler(const AddressMessage &message, const Theron::Address from)
        {
            switch(message.type)
            {
            case AddressMessage::PARENT:
                parent=message.address;
                break;
            case AddressMessage::CHILD:
                childrens.insert(std::make_pair(std::string(message.name),message.address));
                break;
            case AddressMessage::LOG:
                log=message.address;
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
    std::map<std::string,Theron::Address> childrens;
    Theron::Address parent;
    Theron::Address log;
    std::map<std::string,std::string> attMap;
    
}; 
#endif
