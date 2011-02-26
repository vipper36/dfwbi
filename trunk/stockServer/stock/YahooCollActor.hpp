#ifndef __YAHOOCOLL_ACTOR_H__
#define __YAHOOCOLL_ACTOR_H__
#include <Theron/Actor.h>
#include <iostream>
#include "OperateActor.hpp"
#include "TimerFactory.hpp"
#include <boost/bind.hpp>
#include <map>
#include <string>
class YahooCollActor : public OperateActor 
{
public:

    inline YahooCollActor():OperateActor()
        {
            RegisterHandler(this, &YahooCollActor::StockListHandler);
            Factory::TimerFactory *tFactory=Factory::TimerFactory::Instance();
            m_timer=tFactory->CreateTimer();
            m_timer->expires_from_now(boost::posix_time::seconds(5));
            m_timer->async_wait(boost::bind(&YahooCollActor::TimerHandler,this,boost::asio::placeholders::error));                
        }
    inline void TimerHandler(const boost::system::error_code& error)
        {
            if(stockMap.size()==0)
            {
                std::map<std::string,Theron::Address>::iterator curr=childrens.begin();
                std::string file=attMap["file"];
                std::string mark=attMap["marcket"];
                std::ifstream sif(file.c_str());
                std::string line;
                if(sif.is_open())
                {
                    while(!sif.eof())
                    {
                        std::getline(sif,line);
                        std::vector<std::string> resv;
                        boost::algorithm::split( resv, line, boost::algorithm::is_any_of(",") );
                        if(resv.size()>1)
                        {
                            stockMap.insert(std::make_pair(mark+resv[0],resv[1]));
                            OperateMessage op(OperateMessage::HTTP_GET,mark+"|"+resv[0]+"|"+resv[1]);
                            Send(op, curr->second);
                            ++curr;
                            if(curr==childrens.end())
                                curr=childrens.begin();
                        }
                    }
                }
                m_timer->expires_from_now(boost::posix_time::seconds(5));
                m_timer->async_wait(boost::bind(&YahooCollActor::TimerHandler,this,boost::asio::placeholders::error));
            }else if(stockMap.size()!=stockFin.size())
            {   
                std::cout<<"finish check....:"<<stockMap.size()<<":"<<stockFin.size()<<std::endl;
                m_timer->expires_from_now(boost::posix_time::seconds(5));
                m_timer->async_wait(boost::bind(&YahooCollActor::TimerHandler,this,boost::asio::placeholders::error));
            }
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            switch(message.type)
            {
            case OperateMessage::STATUS:
                Send(OperateMessage(OperateMessage::RESP,"YahooCollActor ok"), from);
                for(std::map<std::string,Theron::Address>::iterator it=childrens.begin();it!=childrens.end();++it)
                {
                    Send(message, it->second);
                }
                break;
            case OperateMessage::RESP:
                Send(message, parent);
                break;
            case OperateMessage::SET:
            {
                std::string codeStr(message.status);
                if(codeStr.substr(0,2)==attMap["marcket"])
                {
                    stockFin.insert(message.status);
                }
                break;
            }
            default:
                break;
            }
        }
    void StockListHandler(const StockListMessage &message, const Theron::Address from)
        {
            Send(message, parent);
        }
    
private:
    std::map<std::string,std::string> stockMap;
    std::set<std::string> stockFin;
    boost::asio::deadline_timer* m_timer;
}; 
#endif
