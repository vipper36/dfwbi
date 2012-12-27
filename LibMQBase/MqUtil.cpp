#include "MqUtil.h"
#include "ContextManager.h"
bool MqUtil::SendMqMessage(zmq::socket_t *socket,const MqMessage &msg)
{
    bool headSend=true;
    bool idSend=true;
    bool ret=false;
    std::string id=msg.getIdentify();
    std::string head=msg.getHead();
    std::string bodyStr=msg.getMsg();
    if(id.size()>0)
    {
        zmq::message_t id_message(id.size());
        memcpy(id_message.data(), id.data(), id.size());
        idSend=socket->send(id_message,ZMQ_SNDMORE);
        if(idSend)
        {
            zmq::message_t empty_msg;
            idSend=socket->send(empty_msg,ZMQ_SNDMORE);
        }
    }
    if(idSend)
    {
        zmq::message_t head_message(head.size());
        memcpy(head_message.data(), head.data(), head.size());
        headSend=socket->send(head_message,ZMQ_SNDMORE);
    }
    if(headSend)
    {
        zmq::message_t body_message(bodyStr.size());
        memcpy(body_message.data(), bodyStr.data(), bodyStr.size());
        ret=socket->send(body_message,0);
    }
    return ret;
}

BaseMqMessage MqUtil::RecvMqMessage(zmq::socket_t *socket)
{
    std::list<std::string> msgList;
    while(1)
    {
        zmq::message_t rmessage;
        bool isrecv=socket->recv(&rmessage);

        int size = rmessage.size();
        std::string data(static_cast<char*>(rmessage.data()), size);

        if(!isrecv)
            break;
        msgList.push_back(data);
        int64_t more;
        size_t more_size = sizeof (more);
        socket->getsockopt(ZMQ_RCVMORE, &more, &more_size);
        if(!more)
            break;
    }
    BaseMqMessage msg;
    if(msgList.size()>0)
    {
        std::list<std::string>::reverse_iterator it=msgList.rbegin();
        if(it!=msgList.rend())
        {
            msg.setMsg(*it);
        }
        ++it;
        if(it!=msgList.rend())
        {
            msg.setHead(*it);
        }
        ++it;
        if(it!=msgList.rend())
        {
            std::list<std::string>::iterator bit=msgList.begin();
            std::cout<<*it<<std::endl;
            msg.setIdentify(*bit);
        }
    }

    return msg;
}
