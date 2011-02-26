#ifndef __REAL_ACTOR_H__
#define __REAL_ACTOR_H__
#include <Theron/Actor.h>
#include <iostream>
#include "OperateActor.hpp"
#include "TimerFactory.hpp"
#include <boost/bind.hpp>
#include <map>
#include <string>
class RealActor : public OperateActor
{
public:

    inline RealActor():OperateActor()
        {
            RegisterHandler(this, &RealActor::StockHandler);
            RegisterHandler(this, &RealActor::PriceReqHandler);
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            switch(message.type)
            {
            case OperateMessage::STATUS:
                Send(OperateMessage(OperateMessage::RESP,"RealActor ok"), from);
            default:
                break;
            }
        }
    void StockHandler(const StockMessage &message, const Theron::Address from)
        {
            stock::StockPrice stock=*message.rp;
            delete message.rp;
            if(attMap.size()>0)
            {
                if(stock.marcket==attMap["marcket"]&&stock.code==attMap["code"])
                {
                    std::cout<<stock.stockName<<std::endl;
                    switch(stock.type)
                    {
                    case stock::REAL:
                        RealMap.insert(std::make_pair(stock.time,stock));
                        break;
                    case stock::M1:
                        M1Map.insert(std::make_pair(stock.time,stock));
                        break;
                    case stock::DAY:
                        DayMap.insert(std::make_pair(stock.time,stock));
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    void PriceReqHandler(const PriceReqMessage &message, const Theron::Address from)
        {
            std::cout<<"RealActor:"<<message.req->code<<":"<<RealMap.size()<<":"<<M1Map.size()<<":"<<DayMap.size()<<std::endl;
            if(attMap.size()>0)
            {
                if(message.req->marcket==attMap["marcket"]&&message.req->code==attMap["code"])
                {
                    std::map<boost::posix_time::ptime,stock::StockPrice>::iterator begin;
                    std::map<boost::posix_time::ptime,stock::StockPrice>::iterator end;
                    switch(message.req->type)
                    {
                    case stock::REAL:
                        begin=RealMap.begin();
                        end=RealMap.end();
                        break;
                    case stock::M1:
                        begin=M1Map.begin();
                        end=M1Map.end();
                        break;
                    case stock::DAY:
                        begin=DayMap.begin();
                        end=DayMap.end();
                        break;
                    default:
                        break;
                    }
                    stock::StockPriceList *sl=new stock::StockPriceList();
                    sl->type=message.req->type;
                    sl->marcket=message.req->marcket;
                    sl->code=message.req->code;
                    for(std::map<boost::posix_time::ptime,stock::StockPrice>::iterator it=begin;it!=end;it++)
                    {
                        if(it->first<message.req->from)
                        {
                            continue;
                        }
                        else if(it->first<message.req->to)
                        {
                            sl->priceList.push_back(it->second);
                        }
                        else
                            break;
                    }
                    std::cout<<"send....."<<std::endl;
                    Send(PriceResMessage(sl,message.resKey), from);
                    
                }
            }
            delete message.req;
        }
private:
    std::map<boost::posix_time::ptime,stock::StockPrice> RealMap;
    std::map<boost::posix_time::ptime,stock::StockPrice> M1Map;
    std::map<boost::posix_time::ptime,stock::StockPrice> DayMap;
}; 
#endif
