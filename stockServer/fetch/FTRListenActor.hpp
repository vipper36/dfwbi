#ifndef __FTR_LISTEN_ACTOR_H__
#define __FTR_LISTEN_ACTOR_H__
#include <Theron/Actor.h>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "Messages.hpp"
#include <iostream>
#include <sstream>
#include "OperateActor.hpp"
#include "RabbitAmqp.hpp"

// A trivial actor that does nothing.
class FTRListenActor : public OperateActor
{
public:

    inline FTRListenActor():rc()
        {
            Factory::TimerFactory *tFactory=Factory::TimerFactory::Instance();
            m_timer=tFactory->CreateTimer();
            m_timer->expires_from_now(boost::posix_time::seconds(1));
            m_timer->async_wait(boost::bind(&FTRListenActor::TimerHandler,this,boost::asio::placeholders::error));                
        }
    inline void HandleMqMsg(std::string msg,amqp_basic_properties_t *p)
        {
            std::cout<<msg<<std::endl;
            std::stringstream ss(msg);
            fetch::FetchResult *result=new fetch::FetchResult();
            boost::archive::xml_iarchive ia(ss);
            ia >> BOOST_SERIALIZATION_NVP(*result);
                
            ExtractResultMessage resultMsg(result);
            Send(resultMsg, parent);
        }
    inline void Listen()
        {
            int port=atoi(attMap["port"].c_str());
            if(rc.Connect(attMap["host"],port));
            {
                rc.Listen(attMap["exchange"],attMap["key"],boost::bind(&FTRListenActor::HandleMqMsg,this,_1,_2));
            }
        }
    inline void TimerHandler(const boost::system::error_code& error)
        {
            boost::thread lisThread(boost::bind(&FTRListenActor::Listen,this));
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            switch(message.type)
            {
            case OperateMessage::STATUS:
                Send(OperateMessage(OperateMessage::RESP,"FTRListenActor ok"), from);
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
private:
    std::map<std::string,std::string> attMap;
    boost::asio::deadline_timer* m_timer;
    AMQP::RabbitClient rc;
}; 
#endif
