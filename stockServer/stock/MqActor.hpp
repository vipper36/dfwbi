#ifndef __MQ_ACTOR_H__
#define __MQ_ACTOR_H__
#include <Theron/Actor.h>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "Messages.hpp"
#include <iostream>
#include <sstream>
#include "OperateActor.hpp"
#include "RabbitAmqp.hpp"

// A trivial actor that does nothing.
class MqActor : public OperateActor
{
public:

    inline MqActor():rc()
        {
            RegisterHandler(this, &MqActor::StockHandler);
            RegisterHandler(this, &MqActor::StockListHandler);
            RegisterHandler(this, &MqActor::PriceResHandler);
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            switch(message.type)
            {
            case OperateMessage::STATUS:
                Send(OperateMessage(OperateMessage::RESP,"MqActor ok"), from);
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
    void StockHandler(const StockMessage &message, const Theron::Address from)
        {
            stock::StockPrice stock=*message.rp;
            delete message.rp;
            std::stringstream ss;
            boost::archive::xml_oarchive oa(ss);
            oa << BOOST_SERIALIZATION_NVP(stock);
            std::cout<<"send:"<<stock.code<<std::endl;
            std::string keystr=stock.marcket+"."+stock.code;
            std::cout<<"key:"<<keystr<<std::endl;
            int port=atoi(attMap["port"].c_str());
            if(rc.Connect(attMap["host"],port));
            {
                rc.Send(ss.str(),attMap["exchange"],keystr);
            }
        }
    void StockListHandler(const StockListMessage &message, const Theron::Address from)
        {
            stock::StockPriceList stockList=*message.list;
            delete message.list;
            std::string keystr=stockList.marcket+"."+stockList.code;
            std::cout<<"key:"<<keystr<<std::endl;
            for(std::list<stock::StockPrice>::iterator it=stockList.priceList.begin();it!=stockList.priceList.end();++it)
            {
                stock::StockPrice stock=*it;
                std::stringstream ss;
                boost::archive::xml_oarchive oa(ss);
                oa << BOOST_SERIALIZATION_NVP(stock);
            
                int port=atoi(attMap["port"].c_str());
                if(rc.Connect(attMap["host"],port));
                {
                    rc.Send(ss.str(),attMap["exchange"],keystr);
                }
            }
            Send(OperateMessage(OperateMessage::SET,stockList.marcket+stockList.code), from);
        }
    void PriceResHandler(const PriceResMessage &message, const Theron::Address from)
        {
            stock::StockPriceList stockList=*message.list;
            delete message.list;
            std::stringstream ss;
            boost::archive::xml_oarchive oa(ss);
            oa << BOOST_SERIALIZATION_NVP(stockList);
            
            std::cout<<ss.str()<<std::endl;
            
            int port=atoi(attMap["port"].c_str());
            if(rc.Connect(attMap["host"],port));
            {
                rc.Send(ss.str(),"",std::string(message.resKey));
            }
        }
private:
    AMQP::RabbitClient rc;
    std::map<std::string,std::string> attMap;
}; 
#endif
