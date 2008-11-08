#ifndef LOKI_FACTORYPARM_INC_
#define LOKI_FACTORYPARM_INC_
#include "BaseException.h"

template
<
    class AbstractProduct,
    typename IdentifierType,
    typename ProductCreator = AbstractProduct* (*)()
    >
class Factory
{
public:
    static Factory* Instance()
        {
            if(m_instance==0)
            {
                m_instance=new Factory<AbstractProduct,IdentifierType,ProductCreator>();
            }
            return m_instance;
        }    
    bool Register(const IdentifierType& id, ProductCreator creator)
        {
            return associations_.insert(
                typename IdToProductMap::value_type(id, creator)).second != 0;
        }

    bool Unregister(const IdentifierType& id)
        {
            return associations_.erase(id) != 0;
        }

    AbstractProduct* CreateObject(const IdentifierType& id)
        {
            typename IdToProductMap::iterator i = associations_.find(id);
            if (i != associations_.end())
            {
                return (i->second)();
            }
            throw BaseException(UnKnownPro, "Unknown product ID" );
        }
protected:
    ~Factory()
        {
            associations_.clear();
        }
    
    Factory()
        {
        }
private:
    
    static Factory<AbstractProduct,IdentifierType,ProductCreator>* m_instance;
    typedef std::map<IdentifierType, ProductCreator> IdToProductMap;
    IdToProductMap associations_;
};
template
<
    class AbstractProduct,
    typename IdentifierType,
    typename ProductCreator
    >
Factory<AbstractProduct,IdentifierType,ProductCreator> *
Factory<AbstractProduct,IdentifierType,ProductCreator>::m_instance=NULL;

#endif
