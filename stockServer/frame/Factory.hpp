#ifndef __LOKI_ACTORFACTORY_INC_
#define __LOKI_ACTORFACTORY_INC_
#include <string>
#include <map>
#include "BaseException.hpp"
#include "ActorCreator.hpp"
#include <Theron/Framework.h>
namespace Factory
{
    class Factory
    {
    public:
        static Factory* Instance()
            {
                if(m_instance==0)
                {
                    m_instance=new Factory();
                }
                return m_instance;
            }
        static void Destroy()
            {
                delete m_instance;
            }
        template<typename TActor>
        bool Register(const std::string& id)
            {
                ActorCreator<TActor> *creator=new ActorCreator<TActor>(&m_framework);
                return associations_.insert(
                    typename IdToActorMap::value_type(id, creator)).second != 0;
            }

        bool Unregister(const std::string& id)
            {
                return associations_.erase(id) != 0;
            }

        Theron::ActorRef CreateActor(const std::string& id)
            {
                typename IdToActorMap::iterator i = associations_.find(id);
                if (i != associations_.end())
                {
                    return (*(i->second))();
                }
                throw BaseException(UnKnownPro, "Unknown product" );
            }
    protected:
        ~Factory()
            {
                associations_.clear();
            }
    
        Factory():m_framework(20)
            {
            }
    private:
        Theron::Framework m_framework;
        static Factory* m_instance;
        typedef std::map<std::string, Creator* > IdToActorMap;
        IdToActorMap associations_;
    };
    Factory* Factory::m_instance=NULL;
}
#endif
