#ifndef _ACTOR_CREATOR_
#define _ACTOR_CREATOR_
#include <Theron/Theron.h>
namespace Factory
{
    class Creator
    {
    public:
        virtual Theron::ActorRef operator()()=0;
    };
    template<typename TActor>
    class ActorCreator:public Creator
    {
    private:
        Theron::Framework *m_framework;
    public:
        ActorCreator(Theron::Framework *framework)
            {
                m_framework=framework;
            }
        
        Theron::ActorRef operator()()
            {
                return m_framework->CreateActor<TActor>();
            }
        ~ActorCreator()
            {
            }
    };
}
#endif
