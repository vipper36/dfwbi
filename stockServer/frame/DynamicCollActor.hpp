#ifndef __DYNAMICCOLL_ACTOR_H__
#define __DYNAMICCOLL_ACTOR_H__
#include <Theron/Actor.h>
#include <iostream>
#include "OperateActor.hpp"
#include "TimerFactory.hpp"
#include <boost/bind.hpp>
#include <map>
#include <string>
class DynamicCollActor : public OperateActor
{
public:

    inline DynamicCollActor():OperateActor()
        {
            RegisterHandler(this, &DynamicCollActor::StockHandler);
            RegisterHandler(this, &DynamicCollActor::PriceReqHandler);
            RegisterHandler(this, &DynamicCollActor::PriceResHandler);
            factory=Factory::Factory::Instance();
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            switch(message.type)
            {
            case OperateMessage::STATUS:
                Send(OperateMessage(OperateMessage::RESP,"DynamicCollActor ok"), from);
                // for(std::map<std::string,Theron::Address>::iterator it=childrens.begin();it!=childrens.end();++it)
                // {
                //     Send(message, it->second);
                // }
                break;
            case OperateMessage::RESP:
                Send(message, parent);
                break;
            default:
                break;
            }
        }

    void StockHandler(const StockMessage &message, const Theron::Address from)
        {
            std::stringstream nss;
            nss<<message.rp->marcket<<message.rp->code<<"_"<<message.rp->type;
            std::string childName=nss.str();            
            
            std::map<std::string,Theron::Address>::iterator cit=childrens.find(childName);
            if(cit!=childrens.end())
            {
                Send(message, cit->second);
            }else
            {
                std::map<std::string,std::string>::iterator fit=attMap.find("subType");
                if(fit!=attMap.end())
                {
                    std::map<std::string,std::string> actAttMap;
                    actAttMap.insert(make_pair(std::string("marcket"),message.rp->marcket));
                    actAttMap.insert(make_pair(std::string("code"),message.rp->code));
                    Theron::ActorRef tmp=factory->CreateActor(fit->second);
                    subList.push_back(tmp);
                    childrens.insert(make_pair(childName,tmp.GetAddress()));

                    Send(MapMessage(MapMessage::ATTR,actAttMap), tmp.GetAddress());
                    Send(message, tmp.GetAddress());
                }
            }
        }
    void PriceReqHandler(const PriceReqMessage &message, const Theron::Address from)
        {
            std::cout<<"DynamicCollActor"<<message.req->code<<std::endl;
            std::stringstream nss;
            nss<<message.req->marcket<<message.req->code<<"_"<<message.req->type;
            std::string childName=nss.str();            
            
            std::map<std::string,Theron::Address>::iterator cit=childrens.find(childName);
            if(cit!=childrens.end())
            {
                Send(message, cit->second);
            }else
            {
                stock::StockPriceList *sl=new stock::StockPriceList();
                sl->type=message.req->type;
                sl->marcket=message.req->marcket;
                sl->code=message.req->code;
                Send(PriceResMessage(sl,message.resKey), from);
                delete message.req;
            }
        }
    void PriceResHandler(const PriceResMessage &message, const Theron::Address from)
        {
            Send(message, parent);
        }
private:
    Factory::Factory *factory;
    std::list<Theron::ActorRef> subList;
}; 
#endif
