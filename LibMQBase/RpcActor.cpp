#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "RpcActor.h"
RpcActor::RpcActor(const Parameters address):m_timeout(5000)
{
    m_timeout=address.timeout;
    m_context=address.mContext;
    m_socket=new zmq::socket_t(*m_context,ZMQ_REQ);
    m_isconnect=false;
    m_Address=address.mValue;
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::stringstream ss;
    ss<<uuid;
    m_cid=ss.str();
    m_socket->setsockopt( ZMQ_IDENTITY, m_cid.data(), m_cid.size());
    m_socket->connect(m_Address.c_str());
    RegisterHandler(this, &RpcActor::ReqMessageHandler);
}

void RpcActor::ReqMessageHandler(const IXReqMessage &msg, const Theron::Address from)
{
    IXMqMessage<std::map<std::string,std::string> > mq_msg;
    mq_msg.setIXMsg(msg);
    mq_msg.addHeadAtt("type","rpc");
    if(MqUtil::SendMqMessage(m_socket,mq_msg))
    {
        zmq::pollitem_t items [] =
        {
            { *m_socket, 0, ZMQ_POLLIN, 0 }
        };
        zmq::poll (&items [0], 1, m_timeout);
        if (items [0].revents & ZMQ_POLLIN)
        {
            BaseMqMessage rmsg=MqUtil::RecvMqMessage(m_socket);
            Send(rmsg, from);
        }
        else
        {
            BaseMqMessage rmsg;
            rmsg.addHeadAtt("type","timeout");
            Send(rmsg, from);
        }

    }
}
