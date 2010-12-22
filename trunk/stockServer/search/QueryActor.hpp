#ifndef __QUERY_ACTOR_H__
#define __QUERY_ACTOR_H__
#include <Theron/Actor.h>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "Messages.hpp"
#include <iostream>
#include <sstream>
#include "OperateActor.hpp"

// A trivial actor that does nothing.
class QueryActor : public OperateActor
{
public:

    inline QueryActor()
        {
            RegisterHandler(this, &QueryActor::QueryHandler);
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            switch(message.type)
            {
            case OperateMessage::STATUS:
                Send(OperateMessage(OperateMessage::RESP,"IndexActor ok"), from);
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
            std::string dbpath;
            std::map<std::string,std::string>::iterator fit=attMap.find("dbpath");
            if(fit!=attMap.end())
                dbpath=fit->second;
            else
                dbpath=std::string("./");
            fit=attMap.find("dbnames");
            if(fit!=attMap.end())
            {
                std::vector<std::string> resv;
                boost::algorithm::split( resv, fit->second, boost::algorithm::is_any_of(",") );
                for(std::vector<std::string>::iterator it=resv.begin();it!=resv.end();++it)
                {
                    std::cout<<"dbname:"<<dbpath+*it<<std::endl;
                    Xapian::Database tmpdb(dbpath+*it);
                    std::cout<<"doc count:"<<tmpdb.get_doccount()<<std::endl;
                    db.add_database(tmpdb);
                }
            }
            std::cout<<"doc count:"<<db.get_doccount()<<std::endl;
            fit=attMap.find("dicpath");
            if(fit!=attMap.end())
                result=new CResult(fit->second.c_str());
            else
                result=new CResult();
        }
    void QueryHandler(const QueryMessage &message, const Theron::Address from)
        {
            search::QueryInfo qi=*(message.query);
            std::string resKey(message.resKey);
            delete message.query;
            std::string segString;
            char *output=new char[qi.query.length()*9];
            char *input=new char[qi.query.length()*3];
            memset(output,0,qi.query.length()*9);
            memset(input,0,qi.query.length()*3);
            try 
            {
                UErrorCode  error = U_ZERO_ERROR;
                ucnv_convert("GBK","UTF-8",input,  qi.query.length()*3, qi.query.c_str(), qi.query.length(), &error );
                
                
                bool ret = result->ParagraphProcessing(input, output);
                if (ret)
                {
                    int oLen=strlen(output);
                    char *utf8out=new char[oLen*3];
                    memset(utf8out,0,oLen*3);
                    ucnv_convert("UTF-8","GBK",utf8out,  oLen*3, output, oLen, &error );
                    
                    segString=std::string(utf8out);
                    delete [] utf8out;
                }
            }
            catch (...) {
            }
            delete [] output;
            delete [] input;
            std::list<std::string> segList;
            if(segString.length()>0)
            {
                std::vector<std::string> resv;
                boost::algorithm::split( resv, segString, boost::algorithm::is_any_of(" ") );
                for(std::vector<std::string>::iterator it=resv.begin();it!=resv.end();++it)
                {
                    std::vector<std::string> tmpv;
                    boost::algorithm::split( tmpv, *it, boost::algorithm::is_any_of("/") );
                    if(tmpv.size()>1&&tmpv[1]!="w")
                        segList.push_back(std::string("K")+tmpv[0]);
                }
            }
            search::DocList *dList=new search::DocList();
            if(segList.size()>0)
            {
                Xapian::Query query(Xapian::Query::OP_AND,segList.begin(), segList.end());
                
                while(1)
                {
                    try
                    {
                        db.reopen();
                        Xapian::Enquire  enquire(db);
                        enquire.set_query(query);
                        Xapian::MSet matches = enquire.get_mset(0, 100);
                        for (Xapian::MSetIterator i = matches.begin(); i != matches.end(); ++i) {
                            Xapian::Document doc = i.get_document();
                            search::IndexInfo info;
                            info.uid=doc.get_value(1);
                            info.attMap.insert(std::make_pair(std::string("title"),doc.get_value(2)));
                            info.content=doc.get_data();
                            dList->docList.push_back(info);
                        }
                        break;
                    }catch(Xapian::DatabaseModifiedError exception)
                    {
                        std::cout<<"try agian"<<std::endl;
                    }catch(...)
                    {
                        break;
                    }
                    
                }
                

            }
            Send(QueryResponceMessage(dList,resKey.c_str()), from);
            
        }
    
private:
    Xapian::Database db;
    CResult  *result;
    std::map<std::string,std::string> attMap;
}; 
#endif
