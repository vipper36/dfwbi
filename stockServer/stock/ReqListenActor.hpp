
#ifndef __REQ_LISTEN_ACTOR_H__
#define __REQ_LISTEN_ACTOR_H__
#include <Theron/Actor.h>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "Messages.hpp"
#include <iostream>
#include <sstream>
#include "OperateActor.hpp"
#include "RabbitAmqp.hpp"

// A trivial actor that does nothing.
class ReqListenActor : public OperateActor
{
public:

    inline ReqListenActor()
        {
            Factory::TimerFactory *tFactory=Factory::TimerFactory::Instance();
            m_timer=tFactory->CreateTimer();
            m_timer->expires_from_now(boost::posix_time::seconds(5));
            m_timer->async_wait(boost::bind(&ReqListenActor::TimerHandler,this,boost::asio::placeholders::error));                
        }
    inline void HandleReqMsg(std::string msg,amqp_basic_properties_t *p)
        {
            std::cout<<msg<<std::endl;

            char key[4096];
            memset(key,0,sizeof(key));
            strncpy(key,(char*)(p->reply_to.bytes),p->reply_to.len);
            std::cout<<key<<std::endl;


            std::stringstream ss(msg);
            stock::PriceReq *req=new stock::PriceReq();
            boost::archive::xml_iarchive ia(ss);
            ia >> BOOST_SERIALIZATION_NVP(*req);
            
            PriceReqMessage reqMsg(req,key);
            Send(reqMsg, parent);
        }
    inline void Listen()
        {
            int port=atoi(attMap["port"].c_str());
            if(rc.Connect(attMap["host"],port));
            {
                rc.Listen(attMap["exchange"],attMap["key"],boost::bind(&ReqListenActor::HandleReqMsg,this,_1,_2));
            }
        }
    inline void TimerHandler(const boost::system::error_code& error)
        {
            boost::thread lisThread(boost::bind(&ReqListenActor::Listen,this));
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            switch(message.type)
            {
            case OperateMessage::STATUS:
                Send(OperateMessage(OperateMessage::RESP,"ReqListenActor ok"), from);
            default:
                break;
            }
        }

private:
    boost::asio::deadline_timer* m_timer;
    AMQP::RabbitClient rc;
}; 
#endif
