#ifndef __TASKMANAGE_ACTOR_H__
#define __TASKMANAGE_ACTOR_H__
#include <Theron/Actor.h>
#include <iostream>
#include "OperateActor.hpp"
#include "TimerFactory.hpp"
#include <boost/bind.hpp>
#include "SearchInfo.hpp"
#include <map>
#include <string>
class TaskManageActor : public OperateActor 
{
public:

    inline TaskManageActor():OperateActor()
        {
            RegisterHandler(this, &TaskManageActor::ExtractResultHandler);
            Factory::TimerFactory *tFactory=Factory::TimerFactory::Instance();
            m_timer=tFactory->CreateTimer();
            m_timer->expires_from_now(boost::posix_time::seconds(1));
            m_timer->async_wait(boost::bind(&TaskManageActor::TimerHandler,this,boost::asio::placeholders::error));
            current= childrens.begin();
        }
    inline void TimerHandler(const boost::system::error_code& error)
        {
            std::cout<<"Get task info...."<<std::endl;
            if(urlMap.size()==0)
            {
                std::string file=attMap["file"];
                std::ifstream sif(file.c_str());
                std::string line;
                if(sif.is_open())
                {
                    while(!sif.eof())
                    {
                        std::getline(sif,line);
                        std::vector<std::string> resv;
                        boost::algorithm::split( resv, line, boost::algorithm::is_any_of(",") );
                        if(resv.size()>1)
                        {
                            std::vector<std::string> pv;
                            boost::algorithm::split( pv, resv[1], boost::algorithm::is_any_of("_") );
                            fetch::FetchTreeNode fn;
                            fn.info.type=fetch::NORMAL;
                            fn.info.url=resv[0];
                            for(std::vector<std::string>::iterator vit=pv.begin();vit!=pv.end();++vit)
                            {
                                fn.info.pathList.push_back(*vit);
                            }
                            fn.info.attMap.insert(std::make_pair(std::string("result_type"),std::string("URL")));
                            if(resv[2].length()>0)
                                fn.info.attMap.insert(std::make_pair(std::string("encode"),resv[2]));
                            if(resv[3].length()>0)
                                fn.info.attMap.insert(std::make_pair(std::string("content_url"),resv[3]));
                            if(resv[4].length()>0)
                                fn.info.attMap.insert(std::make_pair(std::string("url_xslt"),resv[4]));
                            if(resv[5].length()>0)
                                fn.info.attMap.insert(std::make_pair(std::string("content_xslt"),resv[5]));
                            urlMap.insert(std::make_pair(resv[0],fn));
                        }
                    }
                }
            }
            for(std::map<std::string,fetch::FetchTreeNode>::iterator it=urlMap.begin();it!=urlMap.end();++it)
            {
                boost::posix_time::ptime now=boost::posix_time::second_clock::local_time();
                if((it->second.update==boost::posix_time::not_a_date_time)||(now-it->second.update>boost::posix_time::hours(20)))
                {

                    fetch::FetchInfo *fi=new fetch::FetchInfo(it->second.info);
                    if(current==childrens.end())
                        current= childrens.begin();
                    Send(FetchTaskMessage(fi), current->second);
                    
                    ++current;
                    
                    it->second.update=now;
                }
            }
            m_timer->expires_from_now(boost::posix_time::seconds(5));
            m_timer->async_wait(boost::bind(&TaskManageActor::TimerHandler,this,boost::asio::placeholders::error));
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            switch(message.type)
            {
            case OperateMessage::STATUS:
                Send(OperateMessage(OperateMessage::RESP,"StockCollActor ok"), from);
                for(std::map<std::string,Theron::Address>::iterator it=childrens.begin();it!=childrens.end();++it)
                {
                    Send(message, it->second);
                }
                break;
            case OperateMessage::RESP:
                Send(message, parent);
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
    void ExtractResultHandler(const ExtractResultMessage &message, const Theron::Address from)
        {
            fetch::FetchResult result=*message.result;
            delete message.result;
            std::string pUrl=result.url;
            fetch::node_iterator ptNode=urlMap.find(pUrl);
            std::stringstream iss(result.result);
            try
            {
                if(result.type==fetch::URL)
                {
                    xmlpp::DomParser parser;
                    parser.set_substitute_entities(); 
                    parser.parse_stream(iss);
                    const xmlpp::Node* pNode = parser.get_document()->get_root_node();
                    const xmlpp::Node::NodeList urls = pNode->get_children(Glib::ustring("Urls"));
                    const xmlpp::Node::NodeList urllist = (*urls.begin())->get_children(Glib::ustring("Url"));
                    std::string site=getSite(result.url);
                    std::string prot=getProtocal(result.url);
                    for(xmlpp::Node::NodeList::const_iterator it=urllist.begin();it!=urllist.end();++it)
                    {
                        const xmlpp::Element* ele = dynamic_cast<const xmlpp::Element*>(*it);
                        std::string name=std::string(ele->get_attribute_value(Glib::ustring("name")).c_str());
                        std::string url=std::string(ele->get_attribute_value(Glib::ustring("url")).c_str());
                        std::string tmpsite=getSite(url);
                        if(tmpsite.length()==0)
                        {
                            if(url.length()>0)
                            {
                                if(url.find("/")==0)
                                {
                                    url=prot+site+url;
                                }else if(url.find("#")!=0&&url.find("javascript")!=0)
                                {
                                    url=result.url+"/"+url.c_str();
                                }
                                if(url.at(url.length()-1)='/')
                                    url=url.erase(url.length()-1,1);
                                tmpsite=getSite(url);
                            }
                        }
                        if(tmpsite.find(site)!=std::string::npos)
                        {
                            fetch::FetchTreeNode fn;
                            fn.info.type=fetch::NORMAL;
                            fn.info.url=url;
                            fn.info.pathList=ptNode->second.info.pathList;
                            fn.info.pathList.push_back(name);
                            if(ptNode!=urlMap.end())
                            {
                                for(std::map<std::string,std::string>::iterator fit=ptNode->second.info.attMap.begin();fit!=ptNode->second.info.attMap.end();++fit)
                                {
                                    if(fit->first!=std::string("result_type"))
                                        fn.info.attMap.insert(*fit);
                                }
                                fn.parent=ptNode;
                            }
                            std::pair<fetch::node_iterator,bool> iRet=urlMap.insert(std::make_pair(url,fn));
                            if(ptNode!=urlMap.end())
                            {
                                ptNode->second.childList.push_back(iRet.first);
                            }
                        }
                        
                    }
                }else if(result.type==fetch::CONTENT)
                {
                    
                    xmlpp::DomParser parser;
                    parser.set_substitute_entities(); 
                    parser.parse_stream(iss);
                    const xmlpp::Node* pNode = parser.get_document()->get_root_node();
                    const xmlpp::Node::NodeList title = pNode->get_children(Glib::ustring("Title"));
                    const xmlpp::Node::NodeList content = pNode->get_children(Glib::ustring("Content"));
                    search::IndexInfo *index=new search::IndexInfo();
                    index->uid=result.url;
                    index->db=std::string("news");
                    if(title.size()>0)
                    {
                        const xmlpp::Element* ele = dynamic_cast<const xmlpp::Element*>(*(title.begin()));
                        const xmlpp::TextNode *text=ele->get_child_text();
                        if(text!=NULL)
                        {
                            std::string value=std::string(text->get_content().c_str());
                            index->attMap.insert(std::make_pair(std::string("title"),value));
                        }
                    }
                    if(content.size()>0)
                    {
                        const xmlpp::Element* ele = dynamic_cast<const xmlpp::Element*>(*(content.begin()));
                        const xmlpp::TextNode *text=ele->get_child_text();
                        if(text!=NULL)
                        {
                            std::string value=std::string(text->get_content().c_str());
                            index->content=value;
                        }
                    }
                    if(current==childrens.end())
                        current= childrens.begin();
                    Send(IndexMessage(index), current->second);
                    ++current;
                }
            }catch(std::exception &e)
            {
                std::cout<<e.what()<<std::endl;
            }
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
    inline std::string getProtocal(std::string url)
        {
            size_t siteStart=url.find("://");
            if(siteStart!=std::string::npos)
                siteStart+=3;
            else
                return std::string("");
            return url.substr(0,siteStart);
        }
    std::map<std::string,Theron::Address>::iterator current;
    std::map<std::string,fetch::FetchTreeNode> urlMap;
    std::map<std::string,std::string> attMap;
    boost::asio::deadline_timer* m_timer;
}; 
#endif
