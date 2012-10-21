#ifndef DISPATCHACTOR_H
#define DISPATCHACTOR_H
#include "ContextManager.h"
template<typename Actor>
class DispatchActor: public Theron::Actor
{
public:
    struct Parameters
    {
        int count;
        Theron::Address sAdd;
    };
public:
    DispatchActor(Parameters param)
    {
        m_source=param.sAdd;
        ContextManager *cm=ContextManager::Instance();
        for(int i=0; i<param.count; i++)
        {
            Theron::ActorRef worker(cm->getTheronContext()->CreateActor<Actor>());
            m_actorList.push_back(worker);
        }
        m_cit=m_actorList.begin();
        RegisterHandler(this, &DispatchActor<Actor>::MQMessageHandler);
        RegisterHandler(this, &DispatchActor<Actor>::WMessageHandler);
    }
    virtual ~DispatchActor() {}

    void MQMessageHandler(const BaseMqMessage &msg, const Theron::Address from)
    {
        ActorMqMessage aMsg(msg);
        MsgWrapper wMsg(aMsg.getActorMsg());
        if(m_cit==m_actorList.end())
            m_cit=m_actorList.begin();
        m_cit->Push(wMsg,this->GetAddress());
        m_cit++;
    }
    void WMessageHandler(const MsgWrapper &msg, const Theron::Address from)
    {
        ActorMqMessage aMsg(msg.getMsg());
        Send(aMsg,m_source);
    }
private:
    Theron::Address m_source;
    std::list<Theron::ActorRef>::iterator m_cit;
    std::list<Theron::ActorRef> m_actorList;
};

#endif // DISPATCHACTOR_H
