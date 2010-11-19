#ifndef __SIMPLECOLL_ACTOR_H__
#define __SIMPLECOLL_ACTOR_H__
#include <Theron/Actor.h>
#include <iostream>
#include "OperateActor.hpp"
#include "TimerFactory.hpp"
#include <boost/bind.hpp>
class SimpleCollActor : public OperateActor
{
public:

    inline SimpleCollActor():OperateActor(),io()
        {
            Factory::TimerFactory *tFactory=Factory::TimerFactory::Instance();
            m_timer=tFactory->CreateTimer();
            m_timer->expires_from_now(boost::posix_time::seconds(1));
            m_timer->async_wait(boost::bind(&SimpleCollActor::TimerHandler,this,boost::asio::placeholders::error));                
        }
    inline void TimerHandler(const boost::system::error_code& error)
        {
            for(std::list<std::pair<std::string,Theron::Address> >::iterator it=addList.begin();it!=addList.end();++it)
            {
                //   Send(OperateMessage(OperateMessage::STATUS,"ok"), it->second);
            }
            m_timer->expires_from_now(boost::posix_time::seconds(1));
            m_timer->async_wait(boost::bind(&SimpleCollActor::TimerHandler,this,boost::asio::placeholders::error));
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            Send(OperateMessage(OperateMessage::STATUS,"ok"), from);
        }
    void MapHandler(const MapMessage &message, const Theron::Address from)
        {
            
        }
private:
    std::list<std::pair<std::string,Theron::Address> > addList;
    boost::asio::io_service io;
    boost::asio::deadline_timer* m_timer;
    bool startd;
}; 
#endif
