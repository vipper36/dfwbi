#ifndef __LOKI_FACTORYPARM_INC_
#define __LOKI_FACTORYPARM_INC_
#include <string>
#include <map>
#include "BaseException.hpp"
#include "ProductCreator.hpp"
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
	       boost::shared_ptr<PCreator<AbstractProduct> > creator(new PCreator<AbstractProduct>(id));
	       return associations_.insert(
		    typename IdToProductMap::value_type(id, creator)).second != 0;
	  }

     bool Unregister(const std::string& id)
	  {
	       return associations_.erase(id) != 0;
	  }

     AbstractProduct* CreateObject(const std::string& id,const std::string& fun)
	  {
	       typename IdToProductMap::iterator i = associations_.find(id);
	       if (i != associations_.end())
	       {
		    return (*(i->second))(fun);
	       }
	       throw BaseException(UnKnownPro, "Unknown product" );
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
     typedef std::map<std::string, boost::shared_ptr<PCreator<AbstractProduct> > > IdToProductMap;
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
