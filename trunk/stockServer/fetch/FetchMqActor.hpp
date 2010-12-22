#ifndef __FETCHMQ_ACTOR_H__
#define __FETCHMQ_ACTOR_H__
#include <Theron/Actor.h>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "Messages.hpp"
#include <iostream>
#include <sstream>
#include "OperateActor.hpp"
#include "RabbitAmqp.hpp"

// A trivial actor that does nothing.
class FetchMqActor : public OperateActor
{
public:

    inline FetchMqActor():rc()
        {
            RegisterHandler(this, &FetchMqActor::ExtractResultHandler);
            RegisterHandler(this, &FetchMqActor::FetchTaskHandler);
            RegisterHandler(this, &FetchMqActor::IndexHandler);
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            switch(message.type)
            {
            case OperateMessage::STATUS:
                Send(OperateMessage(OperateMessage::RESP,"FetchMqActor ok"), from);
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
    void ExtractResultHandler(const ExtractResultMessage &message, const Theron::Address from)
        {
            fetch::FetchResult result=*message.result;
            delete message.result;
            std::stringstream ss;
            boost::archive::xml_oarchive oa(ss);
            oa << BOOST_SERIALIZATION_NVP(result);
//            std::cout<<ss.str()<<std::endl;
            int port=atoi(attMap["port"].c_str());
            if(rc.Connect(attMap["host"],port));
            {
                rc.Send(ss.str(),attMap["exchange"],attMap["key"]);
            }
        }
    void FetchTaskHandler(const FetchTaskMessage &message, const Theron::Address from)
        {
            fetch::FetchInfo task=*message.fi;
            delete message.fi;
            std::stringstream ss;
            boost::archive::xml_oarchive oa(ss);
            oa << BOOST_SERIALIZATION_NVP(task);
//            std::cout<<ss.str()<<std::endl;
            int port=atoi(attMap["port"].c_str());
            if(rc.Connect(attMap["host"],port));
            {
                rc.Send(ss.str(),attMap["exchange"],attMap["key"]);
            }
        }
    void IndexHandler(const IndexMessage &message, const Theron::Address from)
        {
            search::IndexInfo index=*message.index;
            delete message.index;
            std::stringstream ss;
            boost::archive::xml_oarchive oa(ss);
            oa << BOOST_SERIALIZATION_NVP(index);
//            std::cout<<ss.str()<<std::endl;
            int port=atoi(attMap["port"].c_str());
            if(rc.Connect(attMap["host"],port));
            {
                rc.Send(ss.str(),attMap["se_exchange"],attMap["se_key"]);
            }
        }
    
private:
    AMQP::RabbitClient rc;
    std::map<std::string,std::string> attMap;
}; 
#endif
