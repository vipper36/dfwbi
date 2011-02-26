#ifndef __MAINMANAGER_ACTOR_H__
#define __MAINMANAGER_ACTOR_H__
#include <Theron/Actor.h>
#include <iostream>
#include "OperateActor.hpp"
#include "Messages.hpp"
class MainManagerActor : public OperateActor
{
public:

    inline MainManagerActor()
        {
            RegisterHandler(this, &MainManagerActor::StockMessageHandler);
            RegisterHandler(this, &MainManagerActor::StockListMessageHandler);
            RegisterHandler(this, &MainManagerActor::PriceResMessageHandler);
            RegisterHandler(this, &MainManagerActor::PriceReqMessageHandler);
            RegisterHandler(this, &MainManagerActor::MapHandler);
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            switch(message.type)
            {
            case OperateMessage::STATUS:
                Send(OperateMessage(OperateMessage::RESP,"MainManagerActor ok"), from);
                for(std::map<std::string,Theron::Address>::iterator it=childrens.begin();it!=childrens.end();++it)
                {
                    Send(message, it->second);
                }
                break;
            case OperateMessage::RESP:
                Send(message, parent);
                break;
            case OperateMessage::SET:
                for(std::map<std::string,Theron::Address>::iterator it=childrens.begin();it!=childrens.end();++it)
                {
                    Send(message, it->second);
                }
                break;
            default:
                break;
            }
        }
    void MapHandler(const MapMessage &message, const Theron::Address from)
        {
            if(message.type==MapMessage::MSG)
            {
                msgMap=message.map;
            }
            if(message.type==MapMessage::ATTR)
            {
                attMap=message.map;
            }
        }
    void StockMessageHandler(const StockMessage &message, const Theron::Address from)
        {
            std::map<std::string,std::string>::iterator fit=msgMap.find("StockMessage");
            if(fit!=msgMap.end())
            {
                Send(message,childrens[fit->second]);
            }
        }
    void StockListMessageHandler(const StockListMessage &message, const Theron::Address from)
        {
            std::map<std::string,std::string>::iterator fit=msgMap.find("StockListMessage");
            if(fit!=msgMap.end())
            {
                Send(message,childrens[fit->second]);
            }
        }
    void PriceResMessageHandler(const PriceResMessage &message, const Theron::Address from)
        {
            std::map<std::string,std::string>::iterator fit=msgMap.find("PriceResMessage");
            if(fit!=msgMap.end())
            {
                Send(message,childrens[fit->second]);
            }
        }
    void PriceReqMessageHandler(const PriceReqMessage &message, const Theron::Address from)
        {
            std::map<std::string,std::string>::iterator fit=msgMap.find("PriceReqMessage");
            if(fit!=msgMap.end())
            {
                Send(message,childrens[fit->second]);
            }
        }
    
private:
    std::map<std::string,std::string> msgMap;
}; 
#endif
