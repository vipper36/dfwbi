#include <libxml++/libxml++.h>
#include <fastcgi++/manager.hpp>
#include <fastcgi++/request.hpp>
#include <fstream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <Theron/Actor.h>
#include <Theron/Receiver.h>
#include <Theron/Framework.h>
#include "QueryActor.hpp"
class QueryCollector
{
public:
    QueryCollector()
        {
        }
    inline void Handler(const QueryResponceMessage &message, const Theron::Address /*from*/)
        {
            // Collect the message.
            res=*message.res;
            delete message.res;
        }
    inline search::DocList &GetDocs()
        {
            return res;
        }

private:
    search::DocList res;
};
class HelloWorld: public Fastcgipp::Request<char>
{
private:
    QueryCollector qc;
    Theron::Framework framework;
    Theron::Receiver receiver;
    Theron::ActorRef queryActor;
public:
    HelloWorld():framework(),
                 qc(),
                 receiver(),
                 queryActor(framework.CreateActor<QueryActor>())
        {
            receiver.RegisterHandler(&qc, &QueryCollector::Handler);
            std::map<std::string,std::string> queryMap;

            queryMap.insert(std::make_pair(std::string("dbpath"),std::string("/srv/search/")));
            queryMap.insert(std::make_pair(std::string("dbnames"),std::string("news1.db")));
            queryMap.insert(std::make_pair(std::string("dicpath"),std::string("/srv/search/")));
            queryActor.Push(MapMessage(MapMessage::ATTR,queryMap),receiver.GetAddress());
            
            
        }
    bool response()
        {
  
            wchar_t langString[] = { 0x0440, 0x0443, 0x0441, 0x0441, 0x043a, 0x0438, 0x0439, 0x0000 };
            out << "Set-Cookie: lang=" << langString << '\n';
       
            out << "Content-Type: text/html; charset=utf-8\r\n\r\n";
       
            if(environment.posts.size())
            {
                std::map<std::string,std::string> params;
                for(Fastcgipp::Http::Environment<char>::Posts::iterator it=environment.posts.begin(); it!=environment.posts.end(); ++it)
                {

                    if(it->second.type==Fastcgipp::Http::Post<char>::form)
                    {
                        params.insert(std::make_pair(it->first,it->second.value));
                    }
                }
                std::map<std::string,std::string>::iterator fit=params.find("query");
                if(params.size()>0&&fit!=params.end())
                {
                    search::QueryInfo *qi=new search::QueryInfo();
                    qi->query=fit->second;
                    qi->vdb=std::string("news");
                    queryActor.Push(QueryMessage(qi,"null"), receiver.GetAddress());
                    receiver.Wait();
                    search::DocList &docs=qc.GetDocs();
                    std::cout<<"size:"<<docs.docList.size()<<std::endl;
                    xmlpp::Document doc;
                    xmlpp::Element* root=doc.create_root_node(Glib::ustring("DocumentList"));
                    
                    for(std::list<search::IndexInfo>::iterator it=docs.docList.begin();it!=docs.docList.end();++it)
                    {
                        xmlpp::Element* ele=root->add_child(Glib::ustring("Document"));
                        xmlpp::Element* uid=ele->add_child(Glib::ustring("Uid"));
                        xmlpp::Element* title=ele->add_child(Glib::ustring("Title"));
                        xmlpp::Element* content=ele->add_child(Glib::ustring("Content"));
                        uid->add_child_text(Glib::ustring(it->uid.c_str()));
                        content->add_child_text(Glib::ustring(it->content.c_str()));
                        title->add_child_text(Glib::ustring(it->attMap["title"].c_str()));
                    }
                    Glib::ustring docString=doc.write_to_string(Glib::ustring("utf-8"));
                    out << docString.c_str();
                }else
                {
                    out << "param error\n";
                }
            }
            else
                out << "No post data\n";
            return true;

        }
};


void error_log(const char* msg)
{
    using namespace std;
    using namespace boost;
    static ofstream error;
    if(!error.is_open())
    {
        error.open("/tmp/errlog", ios_base::out | ios_base::app);
        error.imbue(locale(error.getloc(), new posix_time::time_facet()));
    }

    error << '[' << posix_time::second_clock::local_time() << "] " << msg << endl;
}

int main()
{
    try
    {
        Fastcgipp::Manager<HelloWorld> fcgi;
        fcgi.handler();
    }
    catch(std::exception& e)
    {
        error_log(e.what());
    }
}
