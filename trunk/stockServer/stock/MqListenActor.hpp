#ifndef __MQ_LISTEN_ACTOR_H__
#define __MQ_LISTEN_ACTOR_H__
#include <Theron/Actor.h>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "Messages.hpp"
#include <iostream>
#include <sstream>
#include "OperateActor.hpp"
#include "RabbitAmqp.hpp"

// A trivial actor that does nothing.
class MqListenActor : public OperateActor
{
public:

    inline MqListenActor():rc()
        {
            Factory::TimerFactory *tFactory=Factory::TimerFactory::Instance();
            m_timer=tFactory->CreateTimer();
            m_timer->expires_from_now(boost::posix_time::seconds(1));
            m_timer->async_wait(boost::bind(&MqListenActor::TimerHandler,this,boost::asio::placeholders::error));                
        }
    inline void HandleMqMsg(std::string msg,amqp_basic_properties_t *p)
        {
            std::cout<<msg<<std::endl;
            std::stringstream ss(msg);
            stock::StockPrice *stock=new stock::StockPrice();
            boost::archive::xml_iarchive ia(ss);
            ia >> BOOST_SERIALIZATION_NVP(*stock);
                
            StockMessage stockprice(stock);
            Send(stockprice, parent);
        }
    inline void Listen()
        {
            int port=atoi(attMap["port"].c_str());
            if(rc.Connect(attMap["host"],port));
            {
                rc.Listen(attMap["exchange"],attMap["key"],boost::bind(&MqListenActor::HandleMqMsg,this,_1,_2));
            }
        }
    inline void TimerHandler(const boost::system::error_code& error)
        {
            boost::thread lisThread(boost::bind(&MqListenActor::Listen,this));
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            switch(message.type)
            {
            case OperateMessage::STATUS:
                Send(OperateMessage(OperateMessage::RESP,"MqListenActor ok"), from);
            default:
                break;
            }
        }
private:
    boost::asio::deadline_timer* m_timer;
    AMQP::RabbitClient rc;
}; 
#endif
