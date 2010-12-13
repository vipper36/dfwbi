#ifndef __FT_LISTEN_ACTOR_H__
#define __FT_LISTEN_ACTOR_H__
#include <Theron/Actor.h>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "Messages.hpp"
#include <iostream>
#include <sstream>
#include "OperateActor.hpp"
#include "RabbitAmqp.hpp"

// A trivial actor that does nothing.
class FTListenActor : public OperateActor
{
public:

    inline FTListenActor():rc()
        {
            Factory::TimerFactory *tFactory=Factory::TimerFactory::Instance();
            m_timer=tFactory->CreateTimer();
            m_timer->expires_from_now(boost::posix_time::seconds(1));
            m_timer->async_wait(boost::bind(&FTListenActor::TimerHandler,this,boost::asio::placeholders::error));                
        }
    inline void HandleMqMsg(std::string msg,amqp_basic_properties_t *p)
        {
            std::stringstream ss(msg);
            fetch::FetchInfo *task=new fetch::FetchInfo();
            boost::archive::xml_iarchive ia(ss);
            ia >> BOOST_SERIALIZATION_NVP(*task);
                
            FetchTaskMessage taskMsg(task);
            Send(taskMsg, parent);
        }
    inline void Listen()
        {
            int port=atoi(attMap["port"].c_str());
            if(rc.Connect(attMap["host"],port));
            {
                rc.Listen(attMap["exchange"],attMap["key"],boost::bind(&FTListenActor::HandleMqMsg,this,_1,_2));
            }
        }
    inline void TimerHandler(const boost::system::error_code& error)
        {
            boost::thread lisThread(boost::bind(&FTListenActor::Listen,this));
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            switch(message.type)
            {
            case OperateMessage::STATUS:
                Send(OperateMessage(OperateMessage::RESP,"FTListenActor ok"), from);
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
