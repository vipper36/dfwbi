#ifndef LOKI_FACTORYPARM_INC_
#define LOKI_FACTORYPARM_INC_
#include <string>
#include <map>
#include "BaseException.h"
#include "ProductCreator.h"
template
<
     typename AbstractProduct,
     template <typename> class PCreator=ProductCreator
    >
class Factory
{
public:
     static Factory* Instance()
        {
            if(m_instance==0)
            {
	      m_instance=new Factory<AbstractProduct,PCreator>();
            }
            return m_instance;
        }    
     bool Register(const std::string& id)
	  {
	    PCreator<AbstractProduct> creator;
	       return associations_.insert(
		    typename IdToProductMap::value_type(id, creator)).second != 0;
	  }

     bool Unregister(const std::string& id)
        {
            return associations_.erase(id) != 0;
        }

     AbstractProduct* CreateObject(const std::string& id)
        {
            typename IdToProductMap::iterator i = associations_.find(id);
            if (i != associations_.end())
            {
	      return (i->second)(id);
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
    
  static Factory<AbstractProduct,PCreator >* m_instance;
  typedef std::map<std::string, PCreator<AbstractProduct> > IdToProductMap;
     IdToProductMap associations_;
};
template
<
  typename AbstractProduct,
  template <typename> class PCreator
  >
Factory<AbstractProduct,PCreator> *
Factory<AbstractProduct,PCreator>::m_instance=NULL;

#endif
