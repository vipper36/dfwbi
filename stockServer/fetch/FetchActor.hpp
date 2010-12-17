#ifndef __FETCH_ACTOR_H_
#define __FETCH_ACTOR_H__
#include <boost/algorithm/string.hpp>
#include "boost/date_time/posix_time/posix_time.hpp" 
#include <Theron/Actor.h>
#include <iostream>
#include <sstream>
#include <tidy/tidy.h>
#include <tidy/buffio.h>
#include <curl/curl.h>
#include <unicode/ucnv.h>  
#include "OperateActor.hpp"
#include "StockPrice.hpp"

// static size_t fetch_write(void *ptr, size_t size, size_t nmemb, TidyBuffer *out)
// {
//      uint r;
//      r = size * nmemb;
//      tidyBufAppend( out, ptr, r );
//      return(r);
// }
static size_t fetch_write(void *ptr, size_t size, size_t nmemb, std::stringstream *stream)
{
    stream->write((char*)ptr,size*nmemb);
    return size*nmemb;
}
class FetchActor : public OperateActor
{
public:

    inline FetchActor()
        {
            RegisterHandler(this, &FetchActor::FetchTaskHandler);          
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {            
            switch(message.type)
            {
            case OperateMessage::STATUS:
                std::cout<<"get status...."<<std::endl;
                Send(OperateMessage(OperateMessage::RESP,"FetchActor ok"), from);
                break;
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
    void FetchTaskHandler(const FetchTaskMessage &message, const Theron::Address from)
        {
            std::cout<<"get data.................."<<std::endl;

            std::string url=message.fi->url;
            char curl_errbuf[CURL_ERROR_SIZE];
            CURL *curl = curl_easy_init();
            int err;

            fetch::FetchResult *result=new fetch::FetchResult();
            fetch::FetchInfo fi=*(message.fi);
            delete message.fi;
            result->url=fi.url;
            result->pathList=fi.pathList;
            result->attMap=fi.attMap;
            int errCode=0;
            if(curl!=NULL) {
                curl_easy_setopt(curl, CURLOPT_URL,url.c_str());
                curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curl_errbuf);
//                curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
//                curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
                curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10);
                curl_easy_setopt(curl, CURLOPT_NOSIGNAL,1);
                curl_easy_setopt(curl, CURLOPT_TIMEOUT ,60);

                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fetch_write);
                
                std::stringstream iss;
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &iss);

                err=curl_easy_perform(curl);
                if ( !err ) 
                {
                    std::map<std::string,std::string>::iterator efit=fi.attMap.find("encode");
                    char *resStr=new char[iss.str().length()*3];
                    memset(resStr,0,iss.str().length()*3);
                    if(efit!=fi.attMap.end())
                    {
                        UErrorCode  error = U_ZERO_ERROR;
                        ucnv_convert("UTF-8",efit->second.c_str(),resStr,  iss.str().length()*3, iss.str().c_str(), iss.str().length(), &error );
                    }else
                    {
                        strcpy(resStr,iss.str().c_str());
                    }
                    TidyDoc tdoc;
//                TidyBuffer tidy_errbuf = {0};
//            TidyBuffer docbuf = {0};
                
                    tdoc = tidyCreate();
                    tidyOptSetInt(tdoc, TidyWrapLen, 4096);
//                tidySetErrorBuffer( tdoc, &tidy_errbuf );
                    tidyOptSetBool( tdoc, TidyXmlOut, yes );
                    tidyOptSetBool(tdoc, TidyQuoteNbsp, no);
                    tidyOptSetBool(tdoc, TidyForceOutput, yes); /* try harder */ 
//                tidyOptSetBool( tdoc, TidyXmlDecl, yes );  
                    tidyOptSetBool(tdoc, TidyQuiet, yes);
                    tidyOptSetBool(tdoc, TidyShowWarnings, no);
                    tidyOptSetValue(tdoc,TidyDoctype,"omit");

                    tidyOptSetBool(tdoc, TidyFixBackslash, yes);
                    
                    tidyOptSetBool(tdoc, TidyMark, no);

                    tidySetCharEncoding(tdoc,"utf8");
//                tidyBufInit(&docbuf);
//                    err = tidyParseBuffer(tdoc, &docbuf); 
                    err = tidyParseString(tdoc, resStr); 
                    if ( err >= 0 ) {
                        err = tidyCleanAndRepair(tdoc); /* fix any problems */ 
                        if ( err >= 0 ) {
//                            err=tidyRunDiagnostics(tdoc); /* load tidy error buffer */ 
//                            if ( err >= 0 ) {
//                                std::cout<<"tidy error:"<<tidy_errbuf.bp<<std::endl; /* show errors */ 
                            TidyBuffer outbuf = {0};
                            tidyBufInit(&outbuf);
                            tidySaveBuffer( tdoc, &outbuf );
                            std::stringstream hss;
                            hss<<(char*)outbuf.bp;
                            tidyBufFree(&outbuf);
                            result->result=hss.str();
                            std::map<std::string,std::string>::iterator tfit=fi.attMap.find("result_type");
                            if(tfit!=fi.attMap.end())
                            {
                                if(tfit->second=="URL")
                                    result->type=fetch::URL;        
                                else if(tfit->second=="CONTENT")
                                    result->type=fetch::CONTENT;        
                            }else
                                result->type=fetch::UNKNOWN; 
//                        }
//                        else
//                        {
//                                errCode=-5;
//                            }

                            
                        }else
                        {
                            errCode=-4;
                        }
                    }else
                    {
                        errCode=-3;
                    }
                    //                tidyBufFree(&tidy_errbuf);
//            tidyBufFree(&docbuf);
                    tidyRelease(tdoc);

                    delete [] resStr;
                }else
                {
                    errCode=-2;
                }
            }else
            {
                errCode=-1;
            }
            if(errCode<0)
            {
                std::stringstream ess;
                ess<<errCode;
                result->type=fetch::ERROR;
                result->result=ess.str();
            }
            curl_easy_cleanup(curl);
            Send(FetchResultMessage(result), from);
        }
private:

    std::map<std::string,std::string> attMap;
}; 
#endif
