#ifndef _PRODUCT_CREATOR_
#define _PRODUCT_CREATOR_
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "dllapi.hpp"
#include "stdio.h"
namespace Base
{
  typedef void* (*DLLFUN)();
  template<typename AbstractProduct>
  class ProductCreator:public boost::enable_shared_from_this<ProductCreator<AbstractProduct> >
  {
  private:
    std::string dll_id;
    HINSTANCE funHandle;
  public:
    ProductCreator()
      :dll_id(),
       funHandle(NULL)
    {
    }
    void setId(const std::string &id)
    {
      if(dll_id.length()>0&&funHandle!=NULL)
	{
	  myFreeLibrary(funHandle);
	}
      dll_id=id;
      funHandle=myLoadLibrary(const_cast<char*>(dll_id.c_str()));
      if (funHandle==NULL)
	{
	  throw BaseException(UnKnownPro, "Unknown product" );
	}
    }
    ProductCreator(const std::string &id)
      :dll_id(id),
       funHandle(NULL)
    {
      funHandle=myLoadLibrary(const_cast<char*>(dll_id.c_str()));
      if (funHandle==NULL)
	{
	  throw BaseException(UnKnownPro, "Unknown product" );
	}
    }
    AbstractProduct *operator()(const std::string &funName)
    {
	       
      DLLFUN fun=(DLLFUN)myGetProcAddress(funHandle,const_cast<char *>(funName.c_str()));
      if (fun==NULL)
	{
	  throw BaseException(UnKnownPro, "Error product Type" );
	}
      AbstractProduct *ret=(AbstractProduct *)fun();
      if (ret==NULL)
	{
	  throw BaseException(UnKnownPro, "Error Create product" );
	}
      return ret;
    }
    ~ProductCreator()
    {
      myFreeLibrary(funHandle);
    }
    typedef boost::shared_ptr<ProductCreator<AbstractProduct> > Creator_ptr;
  };
}
#endif
