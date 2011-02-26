#ifndef __INDEX_ACTOR_H__
#define __INDEX_ACTOR_H__
#include <Theron/Actor.h>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/algorithm/string.hpp>
#include <unicode/ucnv.h> 
#include "Messages.hpp"
#include <iostream>
#include <sstream>
#include "OperateActor.hpp"
#include <xapian.h>
#include "Source/Result.h"
// A trivial actor that does nothing.
class IndexActor : public OperateActor
{
public:

    inline IndexActor():result(NULL)
        {
            RegisterHandler(this, &IndexActor::IndexHandler);
            RegisterHandler(this, &IndexActor::MapHandler);
        }
    inline ~IndexActor()
        {
            delete result;
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
            std::map<std::string,std::string>::iterator fit=attMap.find("dbpath");
            if(fit!=attMap.end())
                db=Xapian::WritableDatabase(fit->second,Xapian::DB_CREATE_OR_OPEN);
            fit=attMap.find("dicpath");
            if(fit!=attMap.end())
                result=new CResult(fit->second.c_str());
            else
                result=new CResult();
        }
    void IndexHandler(const IndexMessage &message, const Theron::Address from)
        {
            
            Xapian::Document doc;
            search::IndexInfo ii=*(message.index);
            delete message.index;
            if(ii.content.length()>0&&ii.db==attMap["dbname"])
            {
                std::string rowString=ii.attMap["title"]+ii.content;
  //              std::cout<<"row len:"<<rowString.length()<<"row:"<<rowString<<std::endl;
                std::string segString;
                char *output=new char[rowString.length()*9];
                char *input=new char[rowString.length()*3];
                memset(output,0,rowString.length()*9);
                memset(input,0,rowString.length()*3);
                try 
                {
                    UErrorCode  error = U_ZERO_ERROR;
                    ucnv_convert("GBK","UTF-8",input,  rowString.length()*3, rowString.c_str(), rowString.length(), &error );
                    
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
                std::list<std::pair<std::string,std::string> > segList;
                if(segString.length()>0)
                {
                    std::vector<std::string> resv;
                    std::stringstream segStream(segString);
                    while(!segStream.eof())
                    {

                        std::string line;
                        std::getline(segStream,line);
                        boost::algorithm::split( resv, line, boost::algorithm::is_any_of(" ") );
                        for(std::vector<std::string>::iterator it=resv.begin();it!=resv.end();++it)
                        {
                            std::vector<std::string> tmpv;
                            boost::algorithm::split( tmpv, *it, boost::algorithm::is_any_of("/") );
                            if(tmpv.size()>1)
                            {
                                //                              std::cout<<"word:"<<tmpv[0]<<std::endl;
                                segList.push_back(std::make_pair(tmpv[0],tmpv[1]));
                            }
                        }
                    }
                }
                doc.add_value(1,ii.uid);
                doc.add_value(2,ii.attMap["title"]);
                for(std::list<std::pair<std::string,std::string> >::iterator it=segList.begin();it!=segList.end();++it)
                {
                    if(it->second!="w")
                        doc.add_term(std::string("K")+it->first);
                }
                doc.set_data(ii.content);
                db.begin_transaction();
                db.add_document(doc);
                db.commit_transaction();
            }
            std::stringstream  so;
            so<<"doc count:"<<db.get_doccount()<<std::endl;
            Send(OperateMessage(OperateMessage::RESP,so.str()), from);
        }
    
private:
    Xapian::WritableDatabase db;
    CResult  *result;
}; 
#endif
