#ifndef __FETCHROUTE_ACTOR_H__
#define __FETCHROUTE_ACTOR_H__
#include <Theron/Actor.h>
#include <iostream>
#include "OperateActor.hpp"
#include "Messages.hpp"
class FetchRouteActor : public OperateActor
{
public:

    inline FetchRouteActor()
        {
            RegisterHandler(this, &FetchRouteActor::FetchTaskHandler);
            RegisterHandler(this, &FetchRouteActor::FetchResultHandler);
            RegisterHandler(this, &FetchRouteActor::ClassifyResultHandle);
            RegisterHandler(this, &FetchRouteActor::ExtractResultHanlde);
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            switch(message.type)
            {
            case OperateMessage::STATUS:
                Send(OperateMessage(OperateMessage::RESP,"FetchRouteActor ok"), from);
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
    void FetchTaskHandler(const FetchTaskMessage &message, const Theron::Address from)
        {
            std::map<std::string,std::string>::iterator fit=msgMap.find("FetchTaskMessage");
            
            if(fit!=msgMap.end())
            {

                Send(message,childrens[fit->second]);
            }
        }
    void FetchResultHandler(const FetchResultMessage &message, const Theron::Address from)
        {

            std::map<std::string,std::string>::iterator fit=msgMap.find("FetchResultMessage");
            
            if(fit!=msgMap.end())
            {

                Send(message,childrens[fit->second]);
            }
        }
    void ClassifyResultHandle(const ClassifyResultMessage &message, const Theron::Address from)
        {
            std::cout<<"classify  route........................"<<std::endl;
            std::map<std::string,std::string>::iterator fit=msgMap.find("ClassifyResultMessage");
            
            if(fit!=msgMap.end())
            {

                Send(message,childrens[fit->second]);
            }
        }
    void ExtractResultHanlde(const ExtractResultMessage &message, const Theron::Address from)
        {
            std::map<std::string,std::string>::iterator fit=msgMap.find("ExtractResultMessage");
            
            if(fit!=msgMap.end())
            {

                Send(message,childrens[fit->second]);
            }
        }

    
private:
    std::map<std::string,std::string> msgMap;
}; 
#endif
