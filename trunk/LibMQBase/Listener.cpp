#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <sstream>
#include "Listener.h"
const std::string Listener::LISTEN_IPC="ipc://listener.ipc";
Listener::Listener(zmq::context_t *mContext):collector(mContext),m_ilsocket(*m_context,ZMQ_DEALER),run(true)
{
    receiver.RegisterHandler(&collector, &BaseMqMessageCollector::Handler);
    m_context=mContext;
    m_ilsocket.bind(LISTEN_IPC.c_str());
}
Listener::~Listener()
{
    for(std::map<std::string,zmq::socket_t *>::iterator it=m_SockMap.begin();it!=m_SockMap.end();++it)
    {
        delete it->second;
    }
}
 void Listener::AddAddress(std::string msg_type,int sock_type,std::string Address,bool isBind)
{
    zmq::socket_t *tmpSocket=new zmq::socket_t(*m_context,sock_type);
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::stringstream ss;
    ss<<uuid;
    m_cid=ss.str();
    tmpSocket->setsockopt( ZMQ_IDENTITY, m_cid.data(), m_cid.size());
    if(isBind)
        tmpSocket->bind(Address.c_str());
    else
        tmpSocket->connect(Address.c_str());
    m_SockMap.insert(std::make_pair(msg_type,tmpSocket));
}
void Listener::start()
{
    int map_size=m_SockMap.size();
    if(map_size>0)
    {
        zmq::pollitem_t *items=new zmq::pollitem_t[map_size+1];
        items[0]={ m_ilsocket, 0, ZMQ_POLLIN, 0 };

        std::map<int,std::string> indexMap;
        int i=1;
        for(std::map<std::string,zmq::socket_t *>::iterator it=m_SockMap.begin();it!=m_SockMap.end();++it,i++)
        {
            zmq::pollitem_t item={*(it->second),0,ZMQ_POLLIN, 0};
            items[i]=item;
            indexMap.insert(std::make_pair(i,it->first));
        }
        while(run)
        {
            zmq::poll (items, map_size+1, -1);
            if (items [0].revents & ZMQ_POLLIN)
            {
                BaseMqMessage mq_msg=MqUtil::RecvMqMessage(&m_ilsocket);
                if(mq_msg.getMsg().size()>0)
                {
                    std::string type=mq_msg.getHeadAtt("type");
                    if(type.length()>0)
                    {
                        std::map<std::string,zmq::socket_t *>::iterator fit=m_SockMap.find(type);
                        if(fit!=m_SockMap.end())
                        {
                            MqUtil::SendMqMessage(fit->second,mq_msg);
                        }
                    }
                }
            }
            for(std::map<int,std::string>::iterator it=indexMap.begin();it!=indexMap.end();++it)
            {
                if (items [it->first].revents & ZMQ_POLLIN)
                {
                    std::map<std::string,zmq::socket_t *>::iterator fit=m_SockMap.find(it->second);
                    if(fit!=m_SockMap.end())
                    {
                        BaseMqMessage mq_msg=MqUtil::RecvMqMessage(fit->second);
                        if(mq_msg.getMsg().size()>0)
                        {
                            std::map<std::string,Theron::ActorRef>::iterator ait=m_actorMap.find(it->second);
                            if(ait!=m_actorMap.end())
                            {
                                ait->second.Push(mq_msg,receiver.GetAddress());
                            }

                        }
                    }
                }
            }

        }
        delete [] items;
    }
}
