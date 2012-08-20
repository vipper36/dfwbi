#ifndef LISTENER_H
#define LISTENER_H
#include <queue>
#include <zmq.hpp>
#include "MqUtil.h"
#include <Theron/Framework.h>
#include <Theron/Actor.h>
#include "MqMessage.h"
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
    explicit Listener(std::string mAdd,int type,zmq::context_t *mContext);
    void setActor(Theron::ActorRef actor)
    {
        m_actor=actor;
    }
    Theron::Address getReceiveAddr()
    {
        receiver.GetAddress();
    }
    void start();
    ~Listener()
    {
        delete m_socket;
        delete m_ilsocket;
    }

private:
    Theron::Receiver receiver;
    BaseMqMessageCollector collector;
    Theron::ActorRef m_actor;
    std::string m_cid;
    std::string m_Address;
    zmq::socket_t *m_socket;
    zmq::socket_t *m_ilsocket;
    zmq::context_t *m_context;
};

#endif // LISTENACTOR_H
