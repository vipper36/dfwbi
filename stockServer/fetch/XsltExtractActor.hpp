#ifndef __XSLT_EXTRACT_ACTOR_H_
#define __XSLT_EXTRACT_ACTOR_H_
#include <boost/algorithm/string.hpp>
#include "boost/date_time/posix_time/posix_time.hpp" 
#include <Theron/Actor.h>
#include <iostream>
#include <sstream>
#include <tidy/tidy.h>
#include <tidy/buffio.h>
#include <curl/curl.h>
#include <unicode/ucnv.h>  
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>

#include "OperateActor.hpp"
#include "StockPrice.hpp"
int write_xml_res(void * ctx, const char *buffer, int len) {
    std::stringstream *stream=(std::stringstream *)ctx;
    stream->write((char*)buffer,len);
    return len;
}
int close_xml_res(void * ctx) {
    return 0;
}

class XsltExtractActor : public OperateActor
{
public:

    inline XsltExtractActor():urlxslt(NULL),contxslt(NULL)
        {
            RegisterHandler(this, &XsltExtractActor::ClassifyResultHandler);
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {            
            switch(message.type)
            {
            case OperateMessage::STATUS:
                std::cout<<"get status...."<<std::endl;
                Send(OperateMessage(OperateMessage::RESP,"XsltExtractActor ok"), from);
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
                if(urlxslt==NULL)
                {
                    std::map<std::string,std::string>::iterator fit= attMap.find("url");
                    if(fit!=attMap.end())
                        urlxslt= xsltParseStylesheetFile((xmlChar*)fit->second.c_str());
                    fit= attMap.find("content");
                    if(fit!=attMap.end())
                        contxslt = xsltParseStylesheetFile((xmlChar*)fit->second.c_str());
                }
            }
        }
    void ClassifyResultHandler(const ClassifyResultMessage &message, const Theron::Address from)
        {
            std::cout<<"extrat data...."<<message.result->type<<std::endl;
            std::string resultStr;
            switch(message.result->type)
            {
            case fetch::URL:
                resultStr=Transe(urlxslt,message.result->result);
                break;
            case fetch::CONTENT:
                resultStr=Transe(contxslt,message.result->result);
                break;
            default:
                break;
            }
            message.result->result=resultStr;
            Send(ExtractResultMessage(message.result),from);
        }
private:
    inline std::string Transe(xsltStylesheetPtr xslt,std::string &in)
        {
            std::string ret;
            if(xslt!=NULL)
            {
                std::stringstream ss(in);
                xmlpp::DomParser parser;
                try
                {
                    parser.set_substitute_entities(); 
                    parser.parse_stream(ss);
                }catch(std::exception &e)
                {
                    std::cout<<e.what()<<std::endl;
                    return ret;
                }
                xmlpp::Document *doc=parser.get_document();
                xmlDocPtr res;
                res = xsltApplyStylesheet(xslt, doc->cobj(), NULL);
                const char *params[1];
                params[0]=NULL;
                if(res!=NULL)
                {
                    std::stringstream oss;
                    xmlOutputBufferPtr buf;
                    buf = xmlOutputBufferCreateIO(write_xml_res, close_xml_res, &oss, NULL);
                    xsltSaveResultTo(buf, res, xslt);
                    ret=oss.str();
                    xmlOutputBufferClose(buf);
                }
                xmlFreeDoc(res);
                xsltCleanupGlobals();
            }
            return ret;
        }
    std::map<std::string,std::string> attMap;
    xsltStylesheetPtr urlxslt;
    xsltStylesheetPtr contxslt;
}; 
#endif
