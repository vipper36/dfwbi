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
    void StockHandler(const StockMessage &message, const Theron::Address from)
        {
            stock::StockPrice stock=*message.rp;
            delete message.rp;
            if(attMap.size()>0)
            {
                if(stock.marcket==attMap["marcket"]&&stock.code==attMap["code"])
                {
                    priceMap.insert(std::make_pair(stock.time,stock));
                    std::cout<<stock.stockName<<std::endl;
                }
            }
        }
    void PriceReqHandler(const PriceReqMessage &message, const Theron::Address from)
        {
            if(attMap.size()>0)
            {
                if(message.req->marcket==attMap["marcket"]&&message.req->code==attMap["code"])
                {
                    stock::StockPriceList *sl=new stock::StockPriceList();
                    sl->type=message.req->type;
                    sl->marcket=message.req->marcket;
                    sl->code=message.req->code;
                    for(std::map<boost::posix_time::ptime,stock::StockPrice>::iterator it=priceMap.begin();it!=priceMap.end();it++)
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
                    Send(PriceResMessage(sl), from);
                    
                }
            }
            delete message.req;
        }
private:
    std::map<std::string,std::string> attMap;
    std::map<boost::posix_time::ptime,stock::StockPrice> priceMap;
}; 
#endif
