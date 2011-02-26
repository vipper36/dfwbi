#ifndef __SEARCHMQ_ACTOR_H__
#define __SEARCHMQ_ACTOR_H__
#include <Theron/Actor.h>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "Messages.hpp"
#include <iostream>
#include <sstream>
#include "OperateActor.hpp"
#include "RabbitAmqp.hpp"

// A trivial actor that does nothing.
class SearchMqActor : public OperateActor
{
public:

    inline SearchMqActor():rc()
        {
            RegisterHandler(this, &SearchMqActor::QueryResponceHandler);
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

    void QueryResponceHandler(const QueryResponceMessage &message, const Theron::Address from)
        {
            search::DocList result=*message.res;
            delete message.res;
            std::stringstream ss;
            boost::archive::xml_oarchive oa(ss);
            oa << BOOST_SERIALIZATION_NVP(result);
            int port=atoi(attMap["port"].c_str());
            if(rc.Connect(attMap["host"],port));
            {
                rc.Send(ss.str(),"",std::string(message.resKey));
            }
        }    
private:
    AMQP::RabbitClient rc;
}; 
#endif
