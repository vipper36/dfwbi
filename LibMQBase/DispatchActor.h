#ifndef DISPATCHACTOR_H
#define DISPATCHACTOR_H

template<typename Actor>
class DispatchActor: public Theron::Actor
{
    struct Parameters
    {
        int count;
        Theron::Address sAdd;
        Theron::Framework *frame;
    };
    public:
        DispatchActor(Parameters param) {
            m_source=param.sAdd;
            for(int i=0;i<param.count;i++)
            {
                Theron::ActorRef worker(frame->CreateActor<Actor>());
                m_actorList.push_back(worker);
            }
            m_cit=m_actorList.begin();
        }
        virtual ~DispatchActor() {}

        void MQMessageHandler(BaseMqMessage &msg, const Theron::Address from)
        {
            if(m_source==from)
            {
                if(cit==m_actorList.end())
                    m_cit=m_actorList.begin();
                m_cit->Push(msg,this->GetAddress());
                m_cit++;
            }else{
                Send(msg, from);
            }

        }
    private:
    Theron::Address m_source;
    std::list<Theron::ActorRef>::iterator m_cit;
    std::list<Theron::ActorRef> m_actorList;
};

#endif // DISPATCHACTOR_H
