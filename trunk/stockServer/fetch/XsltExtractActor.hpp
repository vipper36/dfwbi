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
#include <libxml/HTMLparser.h>
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

    inline XsltExtractActor()
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

    void ClassifyResultHandler(const ClassifyResultMessage &message, const Theron::Address from)
        {
          //  std::cout<<"extrat data...."<<message.result->type<<std::endl;
            std::string resultStr;
            switch(message.result->type)
            {
            case fetch::URL:
            {
                std::map<std::string,std::string>::iterator fit=message.result->attMap.find("url_xslt");
                if(fit!=message.result->attMap.end())
                {
                    resultStr=Transe(fit->second,message.result->result);
                }
            }
            break;
            case fetch::CONTENT:
            {
                std::map<std::string,std::string>::iterator fit=message.result->attMap.find("content_xslt");
                if(fit!=message.result->attMap.end())
                {
                    resultStr=Transe(fit->second,message.result->result);
                }
            }
            break;
            default:
                break;
            }
            message.result->result=resultStr;
            Send(ExtractResultMessage(message.result),from);
        }
private:
    inline std::string Transe(std::string &xsltfile,std::string &in)
        {

            xsltStylesheetPtr xslt= xsltParseStylesheetFile((xmlChar*)xsltfile.c_str());

            std::string ret;
            if(xslt!=NULL)
            {
                xmlDocPtr doc=htmlParseDoc((xmlChar*)in.c_str(),"utf8");
                if(doc==NULL)
                    return ret;
                xmlDocPtr res;
                res = xsltApplyStylesheet(xslt, doc, NULL);
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
                xmlFreeDoc(doc);
            }
            xsltFreeStylesheet(xslt);
            xsltCleanupGlobals();
            return ret;
        }
}; 
#endif
