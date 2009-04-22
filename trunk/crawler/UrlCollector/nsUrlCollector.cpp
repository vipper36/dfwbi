#include "nsUrlCollector.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsStringAPI.h"
#include "nsILocalFile.h"
#include "nsIFileStreams.h"
#include "nsNetUtil.h"
#include "nsILineInputStream.h"
#include <iostream>
NS_IMPL_ISUPPORTS1(nsUrlCollector, nsIUrlCollector)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsUrlCollector)

static nsModuleComponentInfo components[] =
{
     {
	  NS_URLCOLLECTOR_CLASSNAME, 
	  NS_URLCOLLECTOR_CID,
	  NS_URLCOLLECTOR_CONTRACTID,
	  nsUrlCollectorConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsUrlCollectorModule", components)

nsUrlCollector::nsUrlCollector()
{
     nsCOMPtr<nsILocalFile> file;
     nsresult rv = NS_NewLocalFile(NS_ConvertUTF8toUTF16("/var/CrawlerUrl.txt"), PR_FALSE,getter_AddRefs(file));
     if (NS_FAILED(rv))
	  std::cout<<"Get file error:"<<std::hex<<rv<<std::endl;
     rv=NS_NewLocalFileInputStream(getter_AddRefs(mInput), file);
     if (NS_FAILED(rv))
     {
	  std::cout<<"Get stream error:"<<std::hex<<rv<<std::endl;
     }
  /* member initializers and constructor code */
}

nsUrlCollector::~nsUrlCollector()
{
  /* destructor code */
}
/* boolean IsEmpty (); */
NS_IMETHODIMP nsUrlCollector::IsEmpty(PRBool *_retval)
{
     //Available do note work where
     PRUint32 alen=0;
     mInput->Available(&alen);
     std::cout<<"Available:"<<alen<<std::endl;
     if(alen==0)
     {
	  *_retval=PR_TRUE;
     }else
     {
	  *_retval=PR_FALSE;
     }
     return NS_OK;
}

/* void GetURL (out AUTF8String url); */
NS_IMETHODIMP nsUrlCollector::GetURL(nsACString & url)
{
     nsCOMPtr<nsILineInputStream> lstream=do_QueryInterface(mInput);
     nsCString line;
     PRBool ret;
     lstream->ReadLine(line,&ret);
     url=line;
//     std::cout<<"url:"<<ToNewCString(line)<<std::endl;
     return NS_OK;
}

/* End of implementation class template. */
