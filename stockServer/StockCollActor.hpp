#ifndef __STOCKCOLL_ACTOR_H__
#define __STOCKCOLL_ACTOR_H__
#include <Theron/Actor.h>
#include <iostream>
#include "OperateActor.hpp"
#include "TimerFactory.hpp"
#include <boost/bind.hpp>
#include <map>
#include <string>
class StockCollActor : public OperateActor 
{
public:

    inline StockCollActor():OperateActor()
        {
            RegisterHandler(this, &StockCollActor::StockRealHandler);
            Factory::TimerFactory *tFactory=Factory::TimerFactory::Instance();
            m_timer=tFactory->CreateTimer();
            m_timer->expires_from_now(boost::posix_time::seconds(5));
            m_timer->async_wait(boost::bind(&StockCollActor::TimerHandler,this,boost::asio::placeholders::error));                
        }
    inline void TimerHandler(const boost::system::error_code& error)
        {
            std::cout<<"Send http message...."<<std::endl;
            if(stockMap.size()==0)
            {
                std::string file=attMap["file"];
                std::string mark=attMap["marcket"];
                std::ifstream sif(file.c_str());
                std::string line;
                if(sif.is_open())
                {
                    while(!sif.eof())
                    {
                        std::getline(sif,line);
                        std::cout<<line<<std::endl;
                        std::vector<std::string> resv;
                        boost::algorithm::split( resv, line, boost::algorithm::is_any_of(",") );
                        if(resv.size()>1)
                        {
                            stockMap.insert(std::make_pair(mark+resv[0],resv[1]));                                   
                        }
                    }
                }
            }            
            std::map<Theron::Address,std::string> actMap;
            std::map<std::string,std::string>::iterator mit=stockMap.begin();
            int count=ceil(double(stockMap.size())/childrens.size());

            for(std::map<std::string,Theron::Address>::iterator it=childrens.begin();it!=childrens.end();++it)
            {
                std::stringstream sstock;
                for(int i=0;i<count&&mit!=stockMap.end();i++)
                {
                    sstock<<mit->first<<",";
                    mit++;
                }
                OperateMessage op(OperateMessage::HTTP_GET,sstock.str());
                Send(op, it->second);
            }
            m_timer->expires_from_now(boost::posix_time::seconds(5));
            m_timer->async_wait(boost::bind(&StockCollActor::TimerHandler,this,boost::asio::placeholders::error));
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
            Send(message, parent);
        }
private:
    std::map<std::string,std::string> stockMap;
    std::map<std::string,std::string> attMap;
    boost::asio::deadline_timer* m_timer;
}; 
#endif
