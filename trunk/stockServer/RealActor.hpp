#ifndef __REAL_ACTOR_H__
#define __REAL_ACTOR_H__
#include <Theron/Actor.h>
#include <iostream>
#include "OperateActor.hpp"
#include "TimerFactory.hpp"
#include <boost/bind.hpp>
#include <map>
#include <string>
class RealActor : public OperateActor
{
public:

    inline RealActor():OperateActor()
        {
            RegisterHandler(this, &RealActor::StockRealHandler);
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
            stock::RealPrice stock=*message.rp;
            delete message.rp;
            std::stringstream ss;
            boost::archive::xml_oarchive oa(ss);
            oa << BOOST_SERIALIZATION_NVP(stock);
            std::cout<<ss.str()<<std::endl;
        }
private:
    std::map<std::string,std::string> attMap;
}; 
#endif
