#ifndef __HTTP_ACTOR_H_
#define __HTTP_ACTOR_H__
#include <Theron/Actor.h>
#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <unicode/ucnv.h>  
#include "OperateActor.hpp"
size_t write_string(void *ptr, size_t size, size_t nmemb, std::stringstream *stream)
{
    stream->write((char*)ptr,size*nmemb);
    return size*nmemb;
}
class HttpActor : public OperateActor
{
public:

    inline HttpActor()
        {
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            switch(message.type)
            {
            case OperateMessage::STATUS:
                Send(OperateMessage(OperateMessage::RESP,"ok"), from);
                break;
            case OperateMessage::HTTP_GET:
            {
                
                std::stringstream ss;
                std::string url="http://hq.sinajs.cn/list=";
                url=url+message.status;
                CURL *curl = curl_easy_init();
                if(curl!=NULL) {
                    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA,&ss);
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_string);
                    CURLcode res = curl_easy_perform(curl);
                    sina::string_parser<std::string::const_iterator> strP_;
                    sina::price_parser<std::string::const_iterator> priceP_;
                    while(!ss.eof())
                    {
                        using boost::spirit::standard::space;

                        std::string line;
                        std::getline(ss,line);
                        char result[line.length()*2];
                        UErrorCode  error = U_ZERO_ERROR;  
                        ucnv_convert("UTF-8","GBK",result,  sizeof(result), line.c_str(), line.length(), &error );  
                        
                        std::string lineCon(result);
                        std::size_t startpPos=lineCon.rfind("hq_str_")+7;
                        std::size_t equPos=lineCon.rfind("=\"");
                        std::size_t endPos=lineCon.rfind("\";");
                        
                        RealPrice rp;
                        rp.marcket=lineCon.substr(startpPos,2);
                        rp.code=lineCon.substr(startpPos+2,equPos-startpPos-2);
                        
                    }
                    /* always cleanup */ 
                    curl_easy_cleanup(curl);
                }
            }
                break;
            default:
                break;
            }
        }
    void MapHandler(const MapMessage &message, const Theron::Address from)
        {
        }
}; 
#endif
