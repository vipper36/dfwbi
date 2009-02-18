#ifndef _PRODUCT_CREATOR_
#define _PRODUCT_CREATOR_
#include "dllapi.h"
#include "stdio.h"
typedef void* (*DLLFUN)();
template<typename AbstractProduct>
class ProductCreator
{
public:
     AbstractProduct *operator()(const std::string &id)
	  {
	    HINSTANCE funHandle=myLoadLibrary(const_cast<char*>(id.c_str()));
	       if (funHandle==NULL)
	       {
		    throw BaseException(UnKnownPro, "Unknown product" );
	       }
	       std::string funName;
	       printf("%s\n",id.c_str());
	       size_t idx=id.rfind("/");
	       funName=id.substr(idx+1)+"_create";
	       printf("%s\n",funName.c_str());
	       DLLFUN fun=(DLLFUN)myGetProcAddress(funHandle,const_cast<char *>(funName.c_str()));
	       printf("0X%x\n",(long int)(fun));
	       if (fun==NULL)
	       {
		    throw BaseException(UnKnownPro, "Error product Type" );
	       }
	       AbstractProduct *ret=(AbstractProduct *)fun();
	       printf("0X%x\n",(long int)(ret));
	       if (ret==NULL)
	       {
		    throw BaseException(UnKnownPro, "Error Create product" );
	       }
	       //	       myFreeLibrary(funHandle);
	       return ret;
	  }
     
};
#endif
