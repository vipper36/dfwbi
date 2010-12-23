#include <libxml++/libxml++.h>
#include <fastcgi++/manager.hpp>
#include <fastcgi++/request.hpp>
#include <fstream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <Theron/Actor.h>
#include <Theron/Receiver.h>
#include <Theron/Framework.h>
#include "IndexActor.hpp"
class QueryCollector
{
public:
    QueryCollector()
        {
        }
    inline void HandlerStatus(const OperateMessage &message, const Theron::Address /*from*/)
        {
            // Collect the message.
            mMessage = std::string(message.status);
        }

    inline std::string GetStatus() const
        {
            return mMessage;
        }
private:
    std::string mMessage;
};
class HelloWorld: public Fastcgipp::Request<char>
{
private:
    QueryCollector qc;
    Theron::Framework framework;
    Theron::Receiver receiver;
    Theron::ActorRef indexActor;
public:
    HelloWorld():framework(),
                 qc(),
                 receiver(),
                 indexActor(framework.CreateActor<IndexActor>())
        {
            receiver.RegisterHandler(&qc, &QueryCollector::HandlerStatus);
            std::map<std::string,std::string> indexMap;
            indexMap.insert(std::make_pair(std::string("dbname"),std::string("news")));
            indexMap.insert(std::make_pair(std::string("dbpath"),std::string("/srv/search/news1.db")));
            indexMap.insert(std::make_pair(std::string("dicpath"),std::string("/srv/search/")));
            indexActor.Push(MapMessage(MapMessage::ATTR,indexMap),receiver.GetAddress());
        }
    bool response()
        {
  
            wchar_t langString[] = { 0x0440, 0x0443, 0x0441, 0x0441, 0x043a, 0x0438, 0x0439, 0x0000 };
            out << "Set-Cookie: lang=" << langString << '\n';
       
            out << "Content-Type: text/html; charset=utf-8\r\n\r\n";
       
            if(environment.posts.size())
            {
                std::list<std::string> fList;
                for(Fastcgipp::Http::Environment<char>::Posts::iterator it=environment.posts.begin(); it!=environment.posts.end(); ++it)
                {
                    if(it->second.type!=Fastcgipp::Http::Post<char>::form)
                    {
                        std::stringstream ss;
                        ss.write(it->second.data.get(), it->second.size);
                        fList.push_back(ss.str());
                    }
                }
                if(fList.size()>0)
                {
                    for(std::list<std::string>::iterator it=fList.begin();it!=fList.end();++it)
                    {
                        try
                        {
                            std::stringstream ss(*it);
                            xmlpp::DomParser parser;
                            parser.set_substitute_entities(); 
                            parser.parse_stream(ss);
                            const xmlpp::Node* root = parser.get_document()->get_root_node();
                            const xmlpp::Node::NodeList docNode = root->get_children(Glib::ustring("Document"));
                            for(xmlpp::Node::NodeList::const_iterator it=docNode.begin();it!=docNode.end();++it)
                            {
                                search::IndexInfo *index=new search::IndexInfo();
                                const xmlpp::Element* doc = dynamic_cast<const xmlpp::Element*>(*it);
                                const xmlpp::Node::NodeList uid = doc->get_children(Glib::ustring("Uid"));
                                const xmlpp::Node::NodeList title = doc->get_children(Glib::ustring("Title"));
                                const xmlpp::Node::NodeList content = doc->get_children(Glib::ustring("Content"));
                                index->db=std::string("news");
                                if(uid.size()>0)
                                {
                                    const xmlpp::Element* ele = dynamic_cast<const xmlpp::Element*>(*(uid.begin()));
                                    const xmlpp::TextNode *text=ele->get_child_text();
                                    if(text!=NULL)
                                    {
                                        std::string value=std::string(text->get_content().c_str());
                                        index->uid=value;
                                    }
                                }
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
                                indexActor.Push(IndexMessage(index), receiver.GetAddress());
                                receiver.Wait();
                                out<<qc.GetStatus().c_str();
                            }
                            
                            out << "Finish index!"<< std::endl;
                        }
                        catch(const std::exception& ex)
                        {
                            out << "Input file error"<< std::endl;
                        }
                        
                    }
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
