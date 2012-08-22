#ifndef LISTENER_H
#define LISTENER_H
#include <queue>
#include <zmq.hpp>
#include "MqUtil.h"
#include <Theron/Framework.h>
#include <Theron/Actor.h>
#include "MqMessage.h"
#include <map>
class BaseMqMessageCollector
{
public:
    BaseMqMessageCollector(zmq::context_t *mContext)
    {
        m_context=mContext;
        m_issocket=new zmq::socket_t(*m_context,ZMQ_DEALER);
        m_issocket->connect("ipc://routing.ipc");
    }
    inline void Handler(const BaseMqMessage &message, const Theron::Address /*from*/)
    {
        MqUtil::SendMqMessage(m_issocket,message);
    }

private:
    zmq::socket_t *m_issocket;
    zmq::context_t *m_context;
};
class Listener
{
public:
    static const std::string LISTEN_IPC;
    explicit Listener(zmq::context_t *mContext);
    void AddDispatcher(std::string msg_type,Theron::ActorRef actor)
    {
        m_actorMap.insert(std::make_pair(msg_type,actor));
    }
    Theron::Address getReceiveAddr()
    {
        receiver.GetAddress();
    }
    void AddAddress(std::string msg_type,int sock_type,std::string Address,bool isBind=true);
    void start();
    void stop()
    {
        run=false;
    }
    ~Listener();
private:
    Theron::Receiver receiver;
    BaseMqMessageCollector collector;
    std::map<std::string,Theron::ActorRef> m_actorMap;
    std::string m_cid;
    std::map<std::string,zmq::socket_t *> m_SockMap;
    zmq::socket_t m_ilsocket;
    zmq::context_t *m_context;
    bool run;
};

#endif // LISTENACTOR_H
