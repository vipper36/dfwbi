
#ifndef __SREQ_LISTEN_ACTOR_H__
#define __SREQ_LISTEN_ACTOR_H__
#include <Theron/Actor.h>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "Messages.hpp"
#include <iostream>
#include <sstream>
#include "OperateActor.hpp"
#include "RabbitAmqp.hpp"

// A trivial actor that does nothing.
class SreqListenActor : public OperateActor
{
public:

    inline SreqListenActor()
        {
            Factory::TimerFactory *tFactory=Factory::TimerFactory::Instance();
            m_timer=tFactory->CreateTimer();
            m_timer->expires_from_now(boost::posix_time::seconds(5));
            m_timer->async_wait(boost::bind(&SreqListenActor::TimerHandler,this,boost::asio::placeholders::error));                
        }
    inline void HandleReqMsg(std::string msg,amqp_basic_properties_t *p)
        {
            std::cout<<msg<<std::endl;

            char key[4096];
            memset(key,0,sizeof(key));
            strncpy(key,(char*)(p->reply_to.bytes),p->reply_to.len);
            std::cout<<key<<std::endl;


            std::stringstream ss(msg);
            search::QueryInfo *qi=new search::QueryInfo();
            boost::archive::xml_iarchive ia(ss);
            ia >> BOOST_SERIALIZATION_NVP(*qi);
            
            QueryMessage queryMsg(qi,key);
            Send(queryMsg, parent);
        }
    inline void Listen()
        {
            int port=atoi(attMap["port"].c_str());
            if(rc.Connect(attMap["host"],port));
            {
                rc.Listen(attMap["exchange"],attMap["key"],boost::bind(&SreqListenActor::HandleReqMsg,this,_1,_2));
            }
        }
    inline void TimerHandler(const boost::system::error_code& error)
        {
            boost::thread lisThread(boost::bind(&SreqListenActor::Listen,this));
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            switch(message.type)
            {
            case OperateMessage::STATUS:
                Send(OperateMessage(OperateMessage::RESP,"SreqListenActor ok"), from);
            default:
                break;
            }
        }

private:
    boost::asio::deadline_timer* m_timer;
    AMQP::RabbitClient rc;
}; 
#endif
