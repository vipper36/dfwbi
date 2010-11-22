#ifndef __HTTP_ACTOR_H_
#define __HTTP_ACTOR_H__
#include <boost/algorithm/string.hpp>
#include "boost/date_time/posix_time/posix_time.hpp" 
#include <Theron/Actor.h>
#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <unicode/ucnv.h>  
#include "OperateActor.hpp"
#include "StockPrice.hpp"

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
                std::cout<<"get status...."<<std::endl;
                Send(OperateMessage(OperateMessage::RESP,"ok"), from);
                break;
            case OperateMessage::HTTP_GET:
            {
                std::cout<<"get data...."<<std::endl;
                std::stringstream ss;
                std::string url="http://60.28.2.64/list=";
                url=url+message.status;
                CURL *curl = curl_easy_init();
                if(curl!=NULL) {

                    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA,&ss);
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_string);

                    CURLcode res = curl_easy_perform(curl);
                    
                    while(!ss.eof())
                    {

                        std::string line;
                        std::getline(ss,line);
                        char result[line.length()*2];
                        UErrorCode  error = U_ZERO_ERROR;  
                        ucnv_convert("UTF-8","GBK",result,  sizeof(result), line.c_str(), line.length(), &error );  
                        
                        std::string lineCon(result);
                        std::size_t startpPos=lineCon.rfind("hq_str_");
                        std::size_t equPos=lineCon.rfind("=\"");
                        std::size_t endPos=lineCon.rfind("\";");
                        
                        stock::RealPrice rp;
                        if(startpPos!=std::string::npos&&endPos!=std::string::npos)
                        {
                            startpPos+=7;
                            rp.marcket=lineCon.substr(startpPos,2);
                            rp.code=lineCon.substr(startpPos+2,equPos-startpPos-2);
                            std::string csvStr=lineCon.substr(equPos+2,endPos-equPos-2);
                            std::vector<std::string> resv;
                            boost::algorithm::split( resv, csvStr, boost::algorithm::is_any_of(",") );
                            std::vector<std::string>::iterator pit=resv.begin();
                            if(pit!=resv.end())
                            {
                                rp.stockName=*pit;
                                ++pit;
                                for(std::list<std::string>::iterator it=stock::TAGS.begin();it!=stock::TAGS.end()&&pit!=resv.end();++it)
                                {
                                    std::cout<<*pit<<std::endl;
                                    rp.priceMap.insert(make_pair(*it,atof(pit->c_str())));
                                    ++pit;
                                }
                                std::stringstream timestr;
                                //boost::date_time::time_input_facet<boost::posix_time::ptime,char> tf("%Y-%m-%d %H:%M:%S",1);

                                //timestr.imbue(std::locale(std::locale::classic(), &tf));
                                if(pit!=resv.end())
                                {
                                    timestr<<*pit;
                                    ++pit;
                                        
                                    if(pit!=resv.end())
                                        timestr<<" "<<*pit;
                                
                                    //timestr>>rp.time;
                                    rp.time=boost::posix_time::time_from_string(timestr.str());
                                }
                                StockRealMessage stockprice(rp);
                                Send(stockprice, parent);
                            }                            
                        }
                    }

                    /* always cleanup */ 
                    if(curl!=NULL)
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
private:
}; 
#endif
