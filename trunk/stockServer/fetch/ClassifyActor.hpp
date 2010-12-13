#ifndef __CLASSIFY_ACTOR_H_
#define __CLASSIFY_ACTOR_H_
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

    void MapHandler(const MapMessage &message, const Theron::Address from)
        {
            if(message.type==MapMessage::ATTR)
            {
                attMap=message.map;
            }
        }
    void FetchResultHandler(const FetchResultMessage &message, const Theron::Address from)
        {
            if(message.result->type!=fetch::ERROR)
            {
                try
                {
                    std::cout<<"classify data:"<<message.result->type<<std::endl;
//                std::cout<<"data:"<<message.result->result<<std::endl;
                    std::stringstream ss(message.result->result);
                    xmlpp::DomParser parser;
                    parser.set_substitute_entities(); 
                    parser.parse_stream(ss);
                    xmlpp::Node::PrefixNsMap nsMap;
                    const xmlpp::Node* root = parser.get_document()->get_root_node();
                    Glib::ustring prefix;
                    if(root->get_namespace_uri().length()>0)
                    {
                        if(root->get_namespace_prefix().length()>0)
                            prefix=root->get_namespace_prefix();
                        else
                            prefix=Glib::ustring("ns");
                        nsMap.insert(std::make_pair(prefix,root->get_namespace_uri()));
                    }
                    Glib::ustring anpath;
                    if(prefix.length()>0)
                        anpath=Glib::ustring("//")+prefix+":a";
                    else
                        anpath=Glib::ustring("//a");
                    const xmlpp::NodeSet  anckor = root->find(anpath,nsMap);
                    std::string site=getSite(message.result->url);
                    int ourUrl=0;
                    for(xmlpp::NodeSet::const_iterator it=anckor.begin();it!=anckor.end();++it)
                    {
                        const xmlpp::Element *ele= dynamic_cast<const xmlpp::Element*>(*it);
                        if(ele!=NULL)
                        {
                            Glib::ustring value(ele->get_attribute_value(Glib::ustring("href")));
                            std::string tmpsite=getSite(std::string(value.c_str()));
                            if(tmpsite.length()>0&&tmpsite==site)
                                ourUrl++;
                        }
                    }
                    Glib::ustring textpath;
                    if(prefix.length()>0)
                        textpath=Glib::ustring("//")+prefix+":*/text()";
                    else
                        textpath=Glib::ustring("//*/text()");
                    const xmlpp::NodeSet  textSet = root->find(textpath,nsMap);
                    int textLen=0;
                    for(xmlpp::NodeSet::const_iterator it=textSet.begin();it!=textSet.end();++it)
                    {
                        if((*it)->get_name()==Glib::ustring("text"))
                        {
                            const xmlpp::TextNode *ele= dynamic_cast<const xmlpp::TextNode*>(*it);
                            if(ele!=NULL)
                            {
                                Glib::ustring value(ele->get_content());
                                textLen+=value.length();
                            }
                        }
                    }
                    std::cout<<"url:"<<message.result->url<<"--urlCount:"<<anckor.size()<<"--outCount"<<ourUrl<<"--outRate"<<double(ourUrl)/double(anckor.size())<<"--textCount:"<<textSet.size()<<"--TextLen:"<<textLen<<"--avrLen:"<<double(textLen)/double(anckor.size())<<std::endl;
                }catch(std::exception &e)
                {
                    std::cout<<e.what()<<std::endl;
                }
            }
            if(message.result->type==fetch::UNKNOWN)
            {
                message.result->type=fetch::URL;
                
            }
            Send(ClassifyResultMessage(message.result),from);            
        }
private:
    std::map<std::string,std::string> attMap;
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
