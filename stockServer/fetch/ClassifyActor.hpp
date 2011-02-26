#ifndef __CLASSIFY_ACTOR_H_
#define __CLASSIFY_ACTOR_H_
#include <boost/algorithm/string.hpp>
#include "boost/date_time/posix_time/posix_time.hpp" 
#include <boost/regex.hpp>
#include <Theron/Actor.h>
#include <iostream>
#include <sstream>
#include <tidy/tidy.h>
#include <tidy/buffio.h>
#include <curl/curl.h>
#include <unicode/ucnv.h>  
#include "OperateActor.hpp"
#include "StockPrice.hpp"

class ClassifyActor : public OperateActor
{
public:

    inline ClassifyActor()
        {
            RegisterHandler(this, &ClassifyActor::FetchResultHandler);          
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {            
            switch(message.type)
            {
            case OperateMessage::STATUS:
                std::cout<<"get status...."<<std::endl;
                Send(OperateMessage(OperateMessage::RESP,"ClassifyActor ok"), from);
                break;
            default:
                break;
            }
        }

    void FetchResultHandler(const FetchResultMessage &message, const Theron::Address from)
        {
            if(message.result->type==fetch::UNKNOWN)
            {
                std::map<std::string,std::string>::iterator tfit=message.result->attMap.find("result_type");
                if(tfit!=message.result->attMap.end())
                {
                    if(tfit->second=="URL")
                        message.result->type=fetch::URL;        
                    else if(tfit->second=="CONTENT")
                        message.result->type=fetch::CONTENT;        
                }else
                {
                    std::map<std::string,std::string>::iterator fit=message.result->attMap.find("content_url");
                    if(fit!=message.result->attMap.end())
                    {
                        std::cout<<"express:"<<fit->second<<std::endl;
                        std::cout<<"url:"<<message.result->url<<std::endl;
                        boost::regex expression(fit->second);
                        if(boost::regex_match(message.result->url,expression))
                            message.result->type=fetch::CONTENT;
                        std::cout<<"type:"<<message.result->type<<std::endl;
                    }
                    if(message.result->type==fetch::UNKNOWN)
                        message.result->type=fetch::URL;
                }
            }
            Send(ClassifyResultMessage(message.result),from);            
        }
private:

    inline std::string getSite(std::string url)
        {
            size_t siteStart=url.find("://");
            if(siteStart!=std::string::npos)
                siteStart+=3;
            else
                return std::string("");
            size_t siteend=url.find("/",siteStart);
            if(siteend!=std::string::npos)
                return url.substr(siteStart,siteend-siteStart);
            else
                return url.substr(siteStart);
        }
}; 
#endif
