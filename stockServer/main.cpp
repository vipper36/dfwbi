#include <libxml++/libxml++.h>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <boost/program_options.hpp>
#include "Factory.hpp"
#include "TimerFactory.hpp"
#include "BaseException.hpp"
#include "MainManagerActor.hpp"
#include "MqActor.hpp"
#include "RingCollActor.hpp"
#include "MqListenActor.hpp"
#include "SimpleCollActor.hpp"

#include "HttpActor.hpp"
#include "RealActor.hpp"

#include <Theron/Receiver.h>
#include "Messages.hpp"
#include "StockCollActor.hpp"
namespace po = boost::program_options;
void RegActor(Factory::Factory *factory)
{
    factory->Register<MainManagerActor>("MainManagerActor");
    factory->Register<MqActor>("MqActor");
    factory->Register<RingCollActor>("RingCollActor");
    factory->Register<StockCollActor>("StockCollActor");
    factory->Register<HttpActor>("HttpActor");
    factory->Register<MqListenActor>("MqListenActor");
    factory->Register<SimpleCollActor>("SimpleCollActor");
    factory->Register<RealActor>("RealActor");
}
class StatusCollector
{
public:

    inline void Handler(const OperateMessage &message, const Theron::Address /*from*/)
        {
            // Collect the message.
            mMessage = std::string(message.status);
            std::cout<<message.status<<std::endl;
        }

    inline std::string GetStatus() const
        {
            return mMessage;
        }

private:

    std::string mMessage;
};
void GetStatus(std::list<std::pair<std::string,Theron::ActorRef> > actList,Theron::Receiver *receiver,StatusCollector *statusCollector,boost::asio::deadline_timer* timer,const boost::system::error_code& error)
{
    std::cout<<"Send status message...."<<std::endl;
    for(std::list<std::pair<std::string,Theron::ActorRef> >::iterator it=actList.begin();it!=actList.end();++it)
    {
        it->second.Push(OperateMessage(OperateMessage::STATUS,""),receiver->GetAddress());
    }
    timer->expires_from_now(boost::posix_time::seconds(5));
    timer->async_wait(boost::bind(GetStatus,actList,receiver,statusCollector,timer,error));
}
int main(int argc,char**argv)
{

    //Init Actor Factory 
    Factory::TimerFactory *tFactory=Factory::TimerFactory::Instance();
    Factory::Factory *factory=Factory::Factory::Instance();
    RegActor(factory);
    boost::asio::deadline_timer* timer=tFactory->CreateTimer();

    //Create Recieser and set the message handler.
    Theron::Receiver receiver;
    StatusCollector statusCollector;
    receiver.RegisterHandler(&statusCollector, &StatusCollector::Handler);

    //Store all the actors in this list
    std::list<std::pair<std::string,Theron::ActorRef> > actList;

    std::string configFile("config.xml");
    po::options_description desc("Allowed options");
    desc.add_options()
	("help,h", "usage message")
	("config,f", po::value(&configFile), "config file")
	;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    if (vm.count("help")) {
        std::cout << desc << "\n";
	std::cout << "usage:httpd -f [config file]" << "\n";
        Factory::Factory::Destroy();
	return 0;
    }
    std::map<std::string,std::string> stockList;
    
    try
    {
        //Create The actors by config file.
        xmlpp::DomParser parser;
        parser.set_substitute_entities(); 
        parser.parse_file(configFile);

        if(parser)
        {
            const xmlpp::Node* pNode = parser.get_document()->get_root_node();
            const xmlpp::Node::NodeList sysNode = pNode->get_children(Glib::ustring("SysServer"));
            for(xmlpp::Node::NodeList::const_iterator it=sysNode.begin();it!=sysNode.end();++it)
            {
                const xmlpp::Node::NodeList manNode = (*it)->get_children(Glib::ustring("Manager"));
                for(xmlpp::Node::NodeList::const_iterator mit=manNode.begin();mit!=manNode.end();++mit)
                {
                    std::string manName;
                    std::string manType;
                    const xmlpp::Element* manElement = dynamic_cast<const xmlpp::Element*>(*mit);
                    std::map<std::string,std::string> manAttMap;
                    if(manElement!=NULL)
                    {
                        xmlpp::Element::AttributeList attList=manElement->get_attributes();
                        for(xmlpp::Element::AttributeList::iterator ait=attList.begin();ait!=attList.end();++ait)
                        {
                            Glib::ustring aName=(*ait)->get_name();
                            Glib::ustring aValue=(*ait)->get_value();
                            if(aName==Glib::ustring("type"))
                            {
                                manType=std::string(aValue.c_str());
                            }
                            if(aName==Glib::ustring("name"))
                            {
                                manName=std::string(aValue.c_str());
                            }
                            manAttMap.insert(make_pair(std::string(aName.c_str()),std::string(aValue.c_str())));
                        }
                    }
                    if(manName.length()==0)
                        manName=manType;
                    Theron::ActorRef manActor=factory->CreateActor(manType);
                    manActor.Push(MapMessage(MapMessage::ATTR,manAttMap),receiver.GetAddress());
                    actList.push_back(make_pair(manName,manActor));
                    //finish init manager actor.

                    const xmlpp::Node::NodeList colNode = (*mit)->get_children(Glib::ustring("ActorCollection"));
                    for(xmlpp::Node::NodeList::const_iterator cit=colNode.begin();cit!=colNode.end();++cit)
                    {
                        std::string colName;
                        std::string colType;
                        int count=0;
                        const xmlpp::Element* colElement = dynamic_cast<const xmlpp::Element*>(*cit);
                        std::map<std::string,std::string> colAttMap;
                        if(colElement!=NULL)
                        {
                            xmlpp::Element::AttributeList attList=colElement->get_attributes();
                            for(xmlpp::Element::AttributeList::iterator ait=attList.begin();ait!=attList.end();++ait)
                            {
                                Glib::ustring aName=(*ait)->get_name();
                                Glib::ustring aValue=(*ait)->get_value();
                                if(aName==Glib::ustring("type"))
                                {
                                    colType=std::string(aValue.c_str());
                                }
                                if(aName==Glib::ustring("name"))
                                {
                                    colName=std::string(aValue.c_str());
                                }
                                if(aName==Glib::ustring("count"))
                                {
                                    count=atoi(aValue.c_str());
                                }
                                colAttMap.insert(make_pair(std::string(aName.c_str()),std::string(aValue.c_str())));
                            }
                        }
                        if(colName.length()==0)
                            colName=colType;
                        Theron::ActorRef colActor=factory->CreateActor(colType);
                        colActor.Push(MapMessage(MapMessage::ATTR,colAttMap),receiver.GetAddress());
                        manActor.Push(AddressMessage(AddressMessage::CHILD,colName,colActor.GetAddress()),receiver.GetAddress());
                        colActor.Push(AddressMessage(AddressMessage::PARENT,"",manActor.GetAddress()),receiver.GetAddress());
                        actList.push_back(make_pair(colName,colActor));
                        //finish init collection actor!

                        const xmlpp::Node::NodeList actNode = (*cit)->get_children(Glib::ustring("Actor"));
                        for(xmlpp::Node::NodeList::const_iterator ait=actNode.begin();ait!=actNode.end();++ait)
                        {
                            std::string actName;
                            std::string actType;
                            const xmlpp::Element* actElement = dynamic_cast<const xmlpp::Element*>(*ait);

                            std::map<std::string,std::string> actAttMap;
                            if(actElement!=NULL)
                            {
                                xmlpp::Element::AttributeList attList=actElement->get_attributes();
                                for(xmlpp::Element::AttributeList::iterator atit=attList.begin();atit!=attList.end();++atit)
                                {
                                    Glib::ustring aName=(*atit)->get_name();
                                    Glib::ustring aValue=(*atit)->get_value();
                                    if(aName==Glib::ustring("type"))
                                    {
                                        actType=std::string(aValue.c_str());
                                    }
                                    if(aName==Glib::ustring("name"))
                                    {
                                        actName=std::string(aValue.c_str());
                                    }
                                    actAttMap.insert(make_pair(std::string(aName.c_str()),std::string(aValue.c_str())));
                                }
                            }
                            if(actName.length()==0)
                                actName=actType;
                            for(int i=0;i<count;i++)
                            {
                                std::stringstream ss;
                                ss<<actName<<i;
                                Theron::ActorRef actorTmp=factory->CreateActor(actType);
                                actList.push_back(make_pair(ss.str(),actorTmp));
                                colActor.Push(AddressMessage(AddressMessage::CHILD,ss.str(),actorTmp.GetAddress()),receiver.GetAddress());
                                actorTmp.Push(AddressMessage(AddressMessage::PARENT,"",colActor.GetAddress()),receiver.GetAddress());
                                actorTmp.Push(MapMessage(MapMessage::ATTR,actAttMap),receiver.GetAddress());
                            }
                        }
                    }
                    //Get the message handler map.
                    std::map<std::string,std::string> msgMap;
                    const xmlpp::Node::NodeList msgNode = (*mit)->get_children(Glib::ustring("MsgHandle"));
                    if(colNode.size()>0)
                    {
                        const xmlpp::Node* hNode=*msgNode.begin();
                        const xmlpp::Node::NodeList mapNode = hNode->get_children(Glib::ustring("Msg"));
                        for(xmlpp::Node::NodeList::const_iterator hit=mapNode.begin();hit!=mapNode.end();++hit)
                        {
                            const xmlpp::Element* msgElement = dynamic_cast<const xmlpp::Element*>(*hit);
                            if(msgElement!=NULL)
                            {
                                Glib::ustring msgName=msgElement->get_attribute_value(Glib::ustring("name"));
                                const xmlpp::ContentNode *cNode=msgElement->get_child_text();
                                Glib::ustring chlName=cNode->get_content();
                                msgMap.insert(make_pair(std::string(msgName.c_str()),std::string(chlName.c_str())));
                            }
                        }
                    }

                    manActor.Push(MapMessage(MapMessage::MSG,msgMap),receiver.GetAddress());
                }
                const xmlpp::Node::NodeList logNode = (*it)->get_children(Glib::ustring("Log"));
                logNode.front();
            }
        }
    }
    catch(const Factory::BaseException& ex)
    {
        std::cout << "Exception caught: " << ex.what() << std::endl;
    }
    catch(const std::exception& ex)
    {
        std::cout << "Exception caught: " << ex.what() << std::endl;
    }
    //async send status message to all actor!!
    timer->expires_from_now(boost::posix_time::seconds(5));
    timer->async_wait(boost::bind(GetStatus,actList,&receiver,&statusCollector,timer,boost::asio::placeholders::error));

    tFactory->Run();
    //Clear actor list and destroy actor factory.
    actList.clear();
    Factory::TimerFactory::Destroy();
    Factory::Factory::Destroy();
    return 0;
} 

