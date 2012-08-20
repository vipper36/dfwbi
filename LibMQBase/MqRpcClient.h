#ifndef MQRPCCLIENT_H
#define MQRPCCLIENT_H
#include <sstream>
#include <zmq.hpp>
#include <string>
#include <queue>
#include <Theron/Framework.h>

#include "IXMessage.h"
#include "RpcActor.h"
template<typename T>
class MessageCollector
{
public:

    inline void Handler(const BaseMqMessage &message, const Theron::Address /*from*/)
    {
        IXMqMessage<T> irmsg(message);
        m_body = irmsg.getIXMsg().Getbody();
    }

    inline T GetBody() const
    {
        return m_body;
    }

private:

    T m_body;
};
class MqRpcClient
{
    public:
        MqRpcClient(std::string address,int size=5,int timeout):m_framework(size),m_context(size)
        {
            m_address=address;
            std::cout<<m_address<<std::endl;
            for(int i=0;i<size;i++)
            {
                RpcActor::Parameters params;
                params.mValue=m_address;
                params.mContext=&m_context;
                params.timeout=timeout;
                Theron::ActorRef worker(m_framework.CreateActor<RpcActor>(params));
                actQue.push(worker);
            }
        }
        ~MqRpcClient(){}
        std::string GetAddress() { return m_address; }
        void SetAddress(std::string val) { m_address = val; }
        template<typename T>
        T RpcCall(IXReqMessage msg,MessageCollector<T> messageCollector)
        {
            Theron::Receiver receiver;
            receiver.RegisterHandler(&messageCollector, &MessageCollector<T>::Handler);
            Theron::ActorRef aref=actQue.front();
            actQue.pop();
            aref.Push(msg, receiver.GetAddress());
            actQue.push(aref);
            receiver.Wait();
            //need to do exception with timeout!!!
            return messageCollector.GetBody();
        }
    private:
        Theron::Framework m_framework;
        std::string m_address;
        zmq::context_t m_context;
    protected:
        std::queue<Theron::ActorRef> actQue;
};

#endif // MQRPCCLIENT_H
