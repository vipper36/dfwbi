#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <sstream>
#include "Listener.h"
#include "ContextManager.h"
Listener::Listener(Parameters params)
{
    isStop=false;
    RegisterHandler(this, &Listener::LoopHandler);
    RegisterHandler(this, &Listener::OperHandler);
    ContextManager *cm=ContextManager::Instance();

    m_ilsocket=new zmq::socket_t(*(cm->getZmqContext()),ZMQ_DEALER);
    m_ilsocket->bind(params.interAdd.c_str());

    m_olsocket=new zmq::socket_t(*(cm->getZmqContext()),params.outerType);
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::stringstream ss;
    ss<<uuid;
    std::string cid=ss.str();
    m_olsocket->setsockopt( ZMQ_IDENTITY, cid.data(), cid.size());

    if(params.outerBind)
        m_olsocket->bind(params.outerAdd.c_str());
    else
        m_olsocket->connect(params.outerAdd.c_str());

    m_listenInter=params.listenInter;

    m_items=new zmq::pollitem_t[2];
    m_items[0]= { *m_ilsocket, 0, ZMQ_POLLIN, 0 };
    m_items[1]= { *m_olsocket, 0, ZMQ_POLLIN, 0 };
}
Listener::~Listener()
{
    delete m_ilsocket;
    delete m_olsocket;
    delete [] m_items;
}
void Listener::LoopHandler(const Interval &msg, const Theron::Address from)
{
    //std::cout<<"loop......."<<msg.value<<std::endl;;
    if(!isStop)
    {
        listen(msg.value);
        Send(msg,this->GetAddress());
    }else
    {
        while(!operList.empty())
        {
            OperSig sig={10};
            Send(sig,operList.front());
            operList.pop();
        }
    }
}
void Listener::OperHandler(const OperSig &msg, const Theron::Address from)
{
    //std::cout<<"oper.......\n";
    if(msg.value==0)
    {
        isStop=true;
        operList.push(from);
    }else if(msg.value==1)
    {
        isStop=false;
        OperSig sig={11};
        Send(sig,from);
    }
}
void Listener::listen(const int timeout)
{
    zmq::poll (m_items, 2, timeout*1000);
    if (m_items [0].revents & ZMQ_POLLIN)
    {
        BaseMqMessage mq_msg=MqUtil::RecvMqMessage(m_ilsocket);
        std::cout<<"send out"<<std::endl;
        mq_msg.print();
        std::string type=mq_msg.getHeadAtt("type");
        if(type.length()>0)
        {
            MqUtil::SendMqMessage(m_olsocket,mq_msg);
        }
    }

    if (m_items [1].revents & ZMQ_POLLIN)
    {
        BaseMqMessage mq_msg=MqUtil::RecvMqMessage(m_olsocket);
        std::cout<<"recv"<<std::endl;
        mq_msg.print();
        Send(mq_msg,m_listenInter.GetAddress());
    }
}
