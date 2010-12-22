#ifndef __SEARCHROUTE_ACTOR_H__
#define __SEARCHROUTE_ACTOR_H__
#include <Theron/Actor.h>
#include <iostream>
#include "OperateActor.hpp"
#include "Messages.hpp"
class SearchRouteActor : public OperateActor
{
public:

    inline SearchRouteActor()
        {
            RegisterHandler(this, &SearchRouteActor::IndexHandler);
            RegisterHandler(this, &SearchRouteActor::QueryHanlde);
            RegisterHandler(this, &SearchRouteActor::QueryResponceHandle);
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            switch(message.type)
            {
            case OperateMessage::STATUS:
                Send(OperateMessage(OperateMessage::RESP,"SearchRouteActor ok"), from);
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
        }
    void IndexHandler(const IndexMessage &message, const Theron::Address from)
        {
            std::map<std::string,std::string>::iterator fit=msgMap.find("IndexMessage");
            
            if(fit!=msgMap.end())
            {

                Send(message,childrens[fit->second]);
            }
        }
    void QueryHanlde(const QueryMessage &message, const Theron::Address from)
        {
            std::map<std::string,std::string>::iterator fit=msgMap.find("QueryMessage");
            
            if(fit!=msgMap.end())
            {

                Send(message,childrens[fit->second]);
            }
        }
    void QueryResponceHandle(const QueryResponceMessage &message, const Theron::Address from)
        {
            std::map<std::string,std::string>::iterator fit=msgMap.find("QueryResponceMessage");
            
            if(fit!=msgMap.end())
            {

                Send(message,childrens[fit->second]);
            }
        }
private:
    std::map<std::string,std::string> msgMap;
}; 
#endif
