#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <sstream>
#include "Listener.h"
Listener::Listener(std::string mAdd,int type,zmq::context_t *mContext):collector(mContext)
{
    receiver.RegisterHandler(&collector, &BaseMqMessageCollector::Handler);
    m_context=mContext;
    m_socket=new zmq::socket_t(*m_context,type);
    m_ilsocket=new zmq::socket_t(*m_context,ZMQ_DEALER);

    m_Address=mAdd;
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::stringstream ss;
    ss<<uuid;
    m_cid=ss.str();
    m_socket->setsockopt( ZMQ_IDENTITY, m_cid.data(), m_cid.size());
    m_socket->connect(m_Address.c_str());
    m_ilsocket->bind("ipc://routing.ipc");
}
void Listener::start()
{
    zmq::pollitem_t items [] =
    {
        { *m_socket, 0, ZMQ_POLLIN, 0 },
        { *m_ilsocket, 0, ZMQ_POLLIN, 0 }
    };
    while(1)
    {
        zmq::poll (&items [0], 2, -1);
        if (items [0].revents & ZMQ_POLLIN)
        {
            BaseMqMessage mq_msg=MqUtil::RecvMqMessage(m_socket);
            if(mq_msg.getMsg().size()>0)
            {
                m_actor.Push(mq_msg,receiver.GetAddress());
            }
        }
        if (items [1].revents & ZMQ_POLLIN)
        {
            BaseMqMessage mq_msg=MqUtil::RecvMqMessage(m_socket);
            if(mq_msg.getMsg().size()>0)
            {
                MqUtil::SendMqMessage(m_socket,mq_msg);
            }
        }
    }
}
