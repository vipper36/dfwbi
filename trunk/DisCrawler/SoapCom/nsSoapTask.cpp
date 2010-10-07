#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsSoapTask.h"
#include <iostream>
#include <sstream>
#include "property.h"
NS_IMPL_ISUPPORTS1(nsSoapTask, nsISoapTask)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsSoapTask)

static nsModuleComponentInfo components[] =
{
     {
	  NS_SOAPTASK_CLASSNAME,
	  NS_SOAPTASK_CID,
	  NS_SOAPTASK_CONTRACTID,
	  nsSoapTaskConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsSoapTaskModule", components)




nsSoapTask::nsSoapTask()
:JobId(0),
     WrapId(0)
{
     /* member initializers and constructor code */
}

nsSoapTask::~nsSoapTask()
{
     /* destructor code */
}

/* attribute long jobId; */
NS_IMETHODIMP nsSoapTask::GetJobId(PRInt32 *aJobId)
{
     *aJobId=JobId;
     return NS_OK;
}
NS_IMETHODIMP nsSoapTask::SetJobId(PRInt32 aJobId)
{
     JobId=aJobId;
    return NS_OK;
}

/* attribute AUTF8String type; */
NS_IMETHODIMP nsSoapTask::GetType(nsACString & aType)
{
     aType=Type;
     return NS_OK;
}
NS_IMETHODIMP nsSoapTask::SetType(const nsACString & aType)
{
     Type=aType;
    return NS_OK;
}

/* attribute long wrapid; */
NS_IMETHODIMP nsSoapTask::GetWrapid(PRInt32 *aWrapid)
{
     *aWrapid=WrapId;
     return NS_OK;
}
NS_IMETHODIMP nsSoapTask::SetWrapid(PRInt32 aWrapid)
{
     WrapId=aWrapid;
    return NS_OK;
}
/* attribute long wrapver; */
NS_IMETHODIMP nsSoapTask::GetWrapver(PRInt32 *aWrapver)
{
    *aWrapver=WrapVer;
    return NS_OK;
}
NS_IMETHODIMP nsSoapTask::SetWrapver(PRInt32 aWrapver)
{
     WrapVer=aWrapver;
     return NS_OK;
}
/* attribute long taskId; */
NS_IMETHODIMP nsSoapTask::GetTaskId(PRInt32 *aTaskId)
{
     *aTaskId=TaskId;
     LOG<<"task:"<<*aTaskId<<"\n";
     return NS_OK;
}
NS_IMETHODIMP nsSoapTask::SetTaskId(PRInt32 aTaskId)
{
     TaskId=aTaskId;
     LOG<<"set task:"<<TaskId<<"\n";
     return NS_OK;
}
/* void AddUrl (in AUTF8String url, in long uid); */
NS_IMETHODIMP nsSoapTask::AddUrl(const nsACString & url, PRInt32 uid)
{
     nsCString tmpurl(url);
     std::string tmpStr(tmpurl.get());
     urls.push_back(make_pair(uid,tmpStr));
     return NS_OK;
}

/* long GetUrlCount (); */
NS_IMETHODIMP nsSoapTask::GetUrlCount(PRInt32 *_retval)
{
     PRInt32 len=urls.size();
     *_retval=len;
     return NS_OK;
}
/* void GetUrlByIndex (in long index, out long uid, out AUTF8String url); */
NS_IMETHODIMP nsSoapTask::GetUrlByIndex(PRInt32 index, PRInt32 *uid, nsACString & url)
{
     std::pair<int,std::string> tmpUrl=urls[index];
     nsCString tmStr(tmpUrl.second.c_str());
     url=tmStr;
     *uid=tmpUrl.first;
     return NS_OK;
}

