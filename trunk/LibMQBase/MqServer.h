#ifndef MQSERVER_H
#define MQSERVER_H

template<typename Actor>
class MqServer
{
    public:
        MqServer(int count,std::string mAdd,std::string name):
            m_context(count),
            m_framework(count),
            m_listener(mAdd,ZMQ_DEALER,&m_context);
        {
            m_name=name;
            DispatchActor::Parameters params;
            params.count=count;
            params.frame=&m_framework;
            params.sAdd=m_listener.getReceiveAddr();
            m_dActor=m_framework.CreateActor<DispatchActor<Actor> >(params);
            m_listener.setActor(m_dActor);
        }
        virtual ~MqServer() {}
        void Start()
        {
            m_listener.start();
        }
    protected:
        Listener m_listener;
        zmq::context_t m_context;
        Theron::Framework m_framework;
        Theron::ActorRef m_dActor;
        std::string m_name;
    private:
        void RegServer()
        {
            IXMessage<std::string> msg;
            msg.addHeadAtt("type","reg");
            msg.addHeadAtt("name","server");
            msg.Setbody(m_name);
            IXMqMessage mq_msg(msg);
            mq_msg.addHeadAtt("type","reg");
            Theron::Receiver receiver;
            BaseMqMessage b_msg(mq_msg);
            m_dActor.Push(b_msg,receiver.GetAddress());
        }
};

#endif // MQSERVER_H
