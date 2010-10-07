#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsSoapInter.h"
#include "nsISupportsArray.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "property.h"

NS_IMPL_ISUPPORTS1(nsSoapInter, nsISoapInter)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsSoapInter)

static nsModuleComponentInfo components[] =
{
     {
	  NS_SOAPINTER_CLASSNAME,
	  NS_SOAPINTER_CID,
	  NS_SOAPINTER_CONTRACTID,
	  nsSoapInterConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsSoapInterModule", components)



nsSoapInter::nsSoapInter()
:service()
{
     /* member initializers and constructor code */
     nsresult rv;
     soap_set_mode(&service, SOAP_C_UTFSTRING);
}

nsSoapInter::~nsSoapInter()
{
     /* destructor code */
}
/* void SetAddress (in AUTF8String address); */
NS_IMETHODIMP nsSoapInter::SetAddress(const nsACString & address)
{
     mAddress=address;
     return NS_OK;

}
/* long getVersion (in long id); */
NS_IMETHODIMP nsSoapInter::GetVersion(PRInt32 id, PRInt32 *_retval)
{
     if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();
     _nyapc1__getVersion req;
     req.id=id;
     _nyapc1__getVersionResponse res;
     if (service.getVersion(&req,&res) == SOAP_OK)
     {
	  PRInt32 version=res.getVersionReturn;
	  *_retval=version;
	  return NS_OK;
     }else
     {
	  *_retval=-1;
	  return NS_ERROR_FAILURE;
     }
}
/* nsISoapJob getJob (in long id); */
NS_IMETHODIMP nsSoapInter::GetJob(PRInt32 id, nsISoapJob **_retval )
{
     if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();
     _nyapc1__getJob req;
     req.id=id;
     _nyapc1__getJobResponse res;
     if (service.getJob(&req,&res) == SOAP_OK)
     {
	  PRInt32 jobid=res.getJobReturn->id;
	  nsCString comment(res.getJobReturn->comment->c_str());
	  nsCString name(res.getJobReturn->name->c_str());
	  nsCString seed(res.getJobReturn->seed->c_str());
	  nsCString seedType(res.getJobReturn->seedType->c_str());
	  nsCOMPtr<nsISoapJob> job=do_CreateInstance("@nyapc.com/XPCOM/nsSoapJob;1");
	  job->SetId(jobid);
	  job->SetComment(comment);
	  job->SetSeed(seed);
	  job->SetName(name);
	  job->SetSeedType(seedType);
	  *_retval=job;
	  NS_ADDREF(*_retval);
	  return NS_OK;
     }else
     {
	  *_retval=nsnull;
	  return NS_ERROR_FAILURE;
     }
}
/* long addJob (in AUTF8String name, in AUTF8String url, in AUTF8String type, in AUTF8String comment); */
NS_IMETHODIMP nsSoapInter::AddJob(const nsACString & name, const nsACString & url, const nsACString & type, const nsACString & comment, PRInt32 *_retval)
{
     if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();
     _nyapc1__addJob req;
     nsCString nameStr(name);
     nsCString urlStr(url);
     nsCString typeStr(type);
     nsCString commentStr(comment);
     req.name=std::string(nameStr.get());
     req.url=std::string(urlStr.get());
     req.type=std::string(typeStr.get());
     req.comment=std::string(commentStr.get());
     _nyapc1__addJobResponse res;
     if (service.addJob(&req,&res) == SOAP_OK)
     {
	  PRBool ret=res.addJobReturn;
	  *_retval=ret;
	  return NS_OK;
     }else
     {
	  *_retval=-1;
	  return NS_ERROR_FAILURE;
     }
     return NS_OK;
}

/* boolean updateJob (in long id); */
NS_IMETHODIMP nsSoapInter::UpdateJob(PRInt32 id, PRBool *_retval )
{
     if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();
     _nyapc1__updateJob req;
     req.id=id;
     _nyapc1__updateJobResponse res;
     if (service.updateJob(&req,&res) == SOAP_OK)
     {
	  PRBool ret=res.updateJobReturn;
	  *_retval=ret;
	  return NS_OK;
     }else
     {
	  *_retval=PR_FALSE;
	  return NS_ERROR_FAILURE;
     }
}

/* AUTF8String getWrapper (in long id); */
NS_IMETHODIMP nsSoapInter::GetWrapper(PRInt32 id, nsACString & _retval )
{
     if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();
     _nyapc1__getWrapper req;
     req.id=id;
     _nyapc1__getWrapperResponse res;
     if (service.getWrapper(&req,&res) == SOAP_OK)
     {
	  nsCString ret(res.getWrapperReturn.c_str());
	  _retval=ret;
	  return NS_OK;
     }else
     {
	  return NS_ERROR_FAILURE;
     }

}
/* nsISoapTask getTask (in long cid, in long num); */
NS_IMETHODIMP nsSoapInter::GetTask(PRInt32 cid, PRInt32 num, nsISoapTask **_retval)
{
     if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();
     _nyapc1__getTask req;
     req.cid=cid;
     req.num=num;
     _nyapc1__getTaskResponse res;
     if (service.getTask(&req,&res) == SOAP_OK)
     {
	  if(res.getTaskReturn!=NULL)
	  {
	       PRInt32 jobid=res.getTaskReturn->job_USCOREid;
	       nsCString type(res.getTaskReturn->type->c_str());
	       PRInt32 wrapid=res.getTaskReturn->wrap_USCOREid;
	       PRInt32 wrapver=res.getTaskReturn->wrap_USCOREversion;
	       PRInt32 taskid=res.getTaskReturn->taskId;
	       LOG<<"jid:"<<jobid<<"\n";
	       nsCOMPtr<nsISoapTask> task=do_CreateInstance("@nyapc.com/XPCOM/nsSoapTask;1");

	       task->SetJobId(jobid);
	       task->SetType(type);
	       task->SetWrapid(wrapid);
	       task->SetWrapver(wrapver);
	       task->SetTaskId(taskid);
	       std::vector<std::string> urlVec;
	       split(*(res.getTaskReturn->urls), "[##]",urlVec);
	       for(std::vector<std::string>::iterator it=urlVec.begin();it!=urlVec.end();++it)
	       {
		    if(it->length()>0)
		    {
			 std::vector<std::string> urlele;
			 split(*it, "[#]",urlele);
			 nsCString tmpUrl(urlele[0].c_str());
			 task->AddUrl(tmpUrl,atoi(urlele[1].c_str()));
		    }
	       }
	       *_retval=task;
	       NS_ADDREF(*_retval);
	       return NS_OK;
	  }else
	  {
	       *_retval=nsnull;
	       return NS_OK;
	  }
     }else
     {
	  *_retval=nsnull;
	  return NS_ERROR_FAILURE;
     }
     return NS_OK;
}
/* nsISoapTask getTaskByJobId (in long cid, in long jobid, in AUTF8String type, in long num); */
NS_IMETHODIMP nsSoapInter::GetTaskByJobId(PRInt32 cid, PRInt32 jobid, const nsACString & type, PRInt32 num, nsISoapTask **_retval)
{
     nsCString nsType(type);

    if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();
     _nyapc1__getTaskByJobId req;
     req.cid=cid;
     req.type=std::string(nsType.get());
     req.num=num;
     req.jid=jobid;
     _nyapc1__getTaskByJobIdResponse res;
     if (service.getTaskByJobId(&req,&res) == SOAP_OK)
     {
	  if(res.getTaskByJobIdReturn!=NULL)
	  {
	       PRInt32 jobid=res.getTaskByJobIdReturn->job_USCOREid;
	       nsCString type(res.getTaskByJobIdReturn->type->c_str());
	       PRInt32 wrapid=res.getTaskByJobIdReturn->wrap_USCOREid;
	       PRInt32 wrapver=res.getTaskByJobIdReturn->wrap_USCOREversion;
	       PRInt32 taskid=res.getTaskByJobIdReturn->taskId;
	       LOG<<"jid:"<<jobid<<"\n";
	       nsCOMPtr<nsISoapTask> task=do_CreateInstance("@nyapc.com/XPCOM/nsSoapTask;1");

	       task->SetJobId(jobid);
	       task->SetType(type);
	       task->SetWrapid(wrapid);
	       task->SetWrapver(wrapver);
	       task->SetTaskId(taskid);
	       std::vector<std::string> urlVec;
	       split(*(res.getTaskByJobIdReturn->urls), "[##]",urlVec);
	       for(std::vector<std::string>::iterator it=urlVec.begin();it!=urlVec.end();++it)
	       {
		    if(it->length()>0)
		    {
			 std::vector<std::string> urlele;
			 split(*it, "[#]",urlele);
			 nsCString tmpUrl(urlele[0].c_str());
			 task->AddUrl(tmpUrl,atoi(urlele[1].c_str()));
		    }
	       }
	       *_retval=task;
	       NS_ADDREF(*_retval);
	       return NS_OK;
	  }else
	  {
	       *_retval=nsnull;
	       return NS_OK;
	  }
     }else
     {
	  *_retval=nsnull;
	  return NS_ERROR_FAILURE;
     }
     return NS_OK;
}
/* nsISoapTask getWrapTask (in long cid, in long num); */
NS_IMETHODIMP nsSoapInter::GetWrapTask(PRInt32 cid, PRInt32 num, nsISoapTask **_retval)
{
     if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();
     _nyapc1__getWrapTask req;
     req.cid=cid;
     req.num=num;
     _nyapc1__getWrapTaskResponse res;
     if (service.getWrapTask(&req,&res) == SOAP_OK)
     {
	  if(res.getWrapTaskReturn!=NULL)
	  {

	       PRInt32 jobid=res.getWrapTaskReturn->job_USCOREid;
	       nsCString type(res.getWrapTaskReturn->type->c_str());
	       PRInt32 wrapid=res.getWrapTaskReturn->wrap_USCOREid;
	       PRInt32 wrapver=res.getWrapTaskReturn->wrap_USCOREversion;
	       PRInt32 taskid=res.getWrapTaskReturn->taskId;
	       nsCOMPtr<nsISoapTask> task=do_CreateInstance("@nyapc.com/XPCOM/nsSoapTask;1");

	       task->SetJobId(jobid);
	       task->SetType(type);
	       task->SetWrapid(wrapid);
	       task->SetWrapver(wrapver);
	       task->SetTaskId(taskid);
	       std::vector<std::string> urlVec;
	       split(*(res.getWrapTaskReturn->urls), "[##]",urlVec);
	       for(std::vector<std::string>::iterator it=urlVec.begin();it!=urlVec.end();++it)
	       {
		    if(it->length()>0)
		    {
			 std::vector<std::string> urlele;
			 split(*it, "[#]",urlele);
			 nsCString tmpUrl(urlele[0].c_str());
			 task->AddUrl(tmpUrl,atoi(urlele[1].c_str()));
		    }
	       }
	       *_retval=task;
	       NS_ADDREF(*_retval);
	  }
	  return NS_OK;
     }else
     {
	  *_retval=nsnull;
	  return NS_ERROR_FAILURE;
     }
}
/* boolean updateWrapper (in AUTF8String wrap, in long id, in long taskid); */
NS_IMETHODIMP nsSoapInter::UpdateWrapper(const nsACString & wrap, PRInt32 id, PRInt32 taskid, PRBool *_retval)
{
     if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();
     nsCString tmpWrap(wrap);
     _nyapc1__updateWrapper req;
     req.id=id;
     req.taskid=taskid;
     req.wrap=std::string(tmpWrap.get());
     _nyapc1__updateWrapperResponse res;
     if (service.updateWrapper(&req,&res) == SOAP_OK)
     {
	  PRBool ret=res.updateWrapperReturn;
	  *_retval=ret;
	  return NS_OK;
     }else
     {
	  *_retval=PR_FALSE;
	  return NS_ERROR_FAILURE;
     }
}
/* boolean updateWrapGen (in AUTF8String wrapgen, in long id); */
NS_IMETHODIMP nsSoapInter::UpdateWrapGen(const nsACString & wrapgen, PRInt32 id, PRBool *_retval)
{
     if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();
     nsCString tmpWrap(wrapgen);
     _nyapc1__updateWrapGen req;
     req.id=id;
     req.wrapgen=std::string(tmpWrap.get());
     _nyapc1__updateWrapGenResponse res;
     if (service.updateWrapGen(&req,&res) == SOAP_OK)
     {
	  PRBool ret=res.updateWrapGenReturn;
	  *_retval=ret;
	  return NS_OK;
     }else
     {
	  *_retval=PR_FALSE;
	  return NS_ERROR_FAILURE;
     }
}


/* long getStat (in long cid); */
NS_IMETHODIMP nsSoapInter::GetStat(PRInt32 cid, PRInt32 *_retval)
{
     if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();
     _nyapc1__getStat req;
     req.cid=cid;
     _nyapc1__getStatResponse res;
     if (service.getStat(&req,&res) == SOAP_OK)
     {
	  PRInt32 stat=res.getStatReturn;
	  *_retval=stat;
	  return NS_OK;
     }else
     {
	  *_retval=-1;
	  return NS_ERROR_FAILURE;
     }
}
/* boolean putResult (in AUTF8String result, in long id); */
NS_IMETHODIMP nsSoapInter::PutResult(const nsACString & result, PRInt32 id, PRBool *_retval )
{
     if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();
     nsCString tmpRe(result);
     _nyapc1__putResult req;
     req.cid=id;
     req.res=std::string(tmpRe.get());
     _nyapc1__putResultResponse res;
     if (service.putResult(&req,&res) == SOAP_OK)
     {
	  PRBool ret=res.putResultReturn;
	  *_retval=ret;
	  return NS_OK;
     }else
     {
	  *_retval=PR_FALSE;
	  return NS_ERROR_FAILURE;
     }
}

/* nsISupportsArray getJobs (); */
NS_IMETHODIMP nsSoapInter::GetJobs(nsISupportsArray **_retval )
{
     nsresult rv;
     nsCOMPtr<nsISupportsArray> result = do_CreateInstance(NS_SUPPORTSARRAY_CONTRACTID,&rv);
     if (NS_FAILED(rv))
	  return rv;

     if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();
     _nyapc1__getJobs req;
     _nyapc1__getJobsResponse res;
     if (service.getJobs(&req,&res) == SOAP_OK)
     {
	  for(std::vector<nyapc1__JobAtt*>::iterator it=res.getJobsReturn.begin();it!=res.getJobsReturn.end();++it)
	  {
	       PRInt32 jobid=(*it)->id;
	       nsCString comment((*it)->comment->c_str());
	       nsCString name((*it)->name->c_str());
	       nsCString seed((*it)->seed->c_str());
	       nsCString seedType((*it)->seedType->c_str());
	       nsCOMPtr<nsISoapJob> job=do_CreateInstance("@nyapc.com/XPCOM/nsSoapJob;1");
	       job->SetId(jobid);
	       job->SetComment(comment);
	       job->SetSeed(seed);
	       job->SetName(name);
	       job->SetSeedType(seedType);
	       nsISupports *tmp;
	       CallQueryInterface(job,&tmp);
	       result->AppendElement(tmp);
	  }
     }

     *_retval=result;
     NS_ADDREF(*_retval);
     return NS_OK;
}

/* void getJobID ([array, size_is (id_size)] out long id, out unsigned long id_size); */
NS_IMETHODIMP nsSoapInter::GetJobID(PRInt32 **id , PRUint32 *id_size )
{
     if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();
     _nyapc1__getJobID req;
     _nyapc1__getJobIDResponse res;
     if (service.getJobID(&req,&res) == SOAP_OK)
     {
	  *id_size=res.getJobIDReturn.size();
	  *id=new int[*id_size];
	  int i=0;
	  for(std::vector<int>::iterator it=res.getJobIDReturn.begin();it!=res.getJobIDReturn.end();++it)
	  {
	       (*id)[i]=*it;
	       i++;
	  }
	  return NS_OK;
     }else
     {
	  return NS_ERROR_FAILURE;
     }
}
/* AUTF8String getWrapGen (in long id); */
NS_IMETHODIMP nsSoapInter::GetWrapGen(PRInt32 id, nsACString & _retval)
{
     if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();
     _nyapc1__getWrapGen req;
     req.id=id;
     _nyapc1__getWrapGenResponse res;
     if (service.getWrapGen(&req,&res) == SOAP_OK)
     {
	  nsCString ret(res.getWrapGenReturn.c_str());
	  _retval=ret;
	  return NS_OK;
     }else
     {
	  return NS_ERROR_FAILURE;
     }
}
/* boolean addWrapper (in long jobid, in AUTF8String type, in AUTF8String wrapper, in AUTF8String wrapgen, in AUTF8String comment); */
NS_IMETHODIMP nsSoapInter::AddWrapper(PRInt32 jobid, const nsACString & type, const nsACString & wrapper, const nsACString & wrapgen, const nsACString & comment, PRBool *_retval)
{
     if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();
     _nyapc1__addWrapper req;
     nsCString typeStr(type);
     nsCString wrapperStr(wrapper);
     nsCString Vargen(wrapgen);
     nsCString commentStr(comment);

     req.jobId=jobid;
     req.Wrapper=std::string(wrapperStr.get());
     req.vargen=std::string(Vargen.get());
     req.type=std::string(typeStr.get());
     req.comment=std::string(commentStr.get());
     _nyapc1__addWrapperResponse res;
     if (service.addWrapper(&req,&res) == SOAP_OK)
     {
	  PRBool ret=res.addWrapperReturn;
	  *_retval=ret;
	  return NS_OK;
     }else
     {
	  *_retval=PR_FALSE;
	  return NS_ERROR_FAILURE;
     }
     return NS_OK;
}
/* boolean hasTask (in long cid); */
NS_IMETHODIMP nsSoapInter::HasTask(PRInt32 cid, PRBool *_retval)
{
     if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();

     _nyapc1__hasTask req;
     req.cid=cid;
     _nyapc1__hasTaskResponse res;
     if (service.hasTask(&req,&res) == SOAP_OK)
     {
	  *_retval=res.hasTaskReturn;
     }
     return NS_OK;
}

bool nsSoapInter::split(const std::string& s, std::string c,std::vector<std::string>& v)
{
     std::string::size_type i = 0;
     std::string::size_type j = s.find(c);
     while (j != std::string::npos) {
          v.push_back(s.substr(i, j-i));
          i = j+c.length();
          j = s.find(c, i);
     }
     if(j == std::string::npos)
     {
	  std::string tmp=s.substr(i, s.length( ));
	  if(tmp.length()>0)
	       v.push_back(tmp);
     }
     return true;
}

/* nsISupportsArray getJobsWrapStat0 (); */
NS_IMETHODIMP nsSoapInter::GetJobsWrapStatInvalid(nsISupportsArray **_retval)
{
	 nsresult rv;
     nsCOMPtr<nsISupportsArray> result = do_CreateInstance(NS_SUPPORTSARRAY_CONTRACTID,&rv);
     if (NS_FAILED(rv))
	  return rv;

     if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();
     _nyapc1__getJobsWrapStatInvalid req;
     _nyapc1__getJobsWrapStatInvalidResponse res;
     if (service.getJobsWrapStatInvalid(&req,&res) == SOAP_OK)
     {
	  for(std::vector<nyapc1__JobAtt*>::iterator it=res.getJobsWrapStatInvalidReturn.begin();it!=res.getJobsWrapStatInvalidReturn.end();++it)
	  {
	       PRInt32 jobid=(*it)->id;
	       nsCString comment((*it)->comment->c_str());
	       nsCString name((*it)->name->c_str());
	       nsCString seed;
	       nsCString seedType;
	       if((*it)->seed!=NULL)
		    seed=nsCString((*it)->seed->c_str());
	       if((*it)->seedType!=NULL)
		    seedType=nsCString((*it)->seedType->c_str());
	       nsCOMPtr<nsISoapJob> job=do_CreateInstance("@nyapc.com/XPCOM/nsSoapJob;1");
	       job->SetId(jobid);
	       job->SetComment(comment);
	       job->SetSeed(seed);
	       job->SetName(name);
	       job->SetSeedType(seedType);
	       nsISupports *tmp;
	       CallQueryInterface(job,&tmp);
	       result->AppendElement(tmp);
	  }
     }

     *_retval=result;
     NS_ADDREF(*_retval);
     return NS_OK;
}
/* nsISoapTask getWrap0Task (in long cid, in long jobid, in AUTF8String type, in long num); */
NS_IMETHODIMP nsSoapInter::GetWrapInvalidTaskByJobId(PRInt32 cid, PRInt32 jobid, const nsACString & type, PRInt32 num, nsISoapTask **_retval)
{
     nsCString nsType(type);

    if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();
     _nyapc1__getWrapInvalidTaskByJobId req;
     req.cid=cid;
     req.type=std::string(nsType.get());
     req.num=num;
     req.jid=jobid;
     _nyapc1__getWrapInvalidTaskByJobIdResponse res;
     if (service.getWrapInvalidTaskByJobId(&req,&res) == SOAP_OK)
     {
	  if(res.getWrapInvalidTaskByJobIdReturn!=NULL)
	  {
	       PRInt32 jobid=res.getWrapInvalidTaskByJobIdReturn->job_USCOREid;
	       nsCString type(res.getWrapInvalidTaskByJobIdReturn->type->c_str());
	       PRInt32 wrapid=res.getWrapInvalidTaskByJobIdReturn->wrap_USCOREid;
	       PRInt32 wrapver=res.getWrapInvalidTaskByJobIdReturn->wrap_USCOREversion;
	       PRInt32 taskid=res.getWrapInvalidTaskByJobIdReturn->taskId;
	       LOG<<"jid:"<<jobid<<"\n";
	       nsCOMPtr<nsISoapTask> task=do_CreateInstance("@nyapc.com/XPCOM/nsSoapTask;1");

	       task->SetJobId(jobid);
	       task->SetType(type);
	       task->SetWrapid(wrapid);
	       task->SetWrapver(wrapver);
	       task->SetTaskId(taskid);
	       std::vector<std::string> urlVec;
	       split(*(res.getWrapInvalidTaskByJobIdReturn->urls), "[##]",urlVec);
	       for(std::vector<std::string>::iterator it=urlVec.begin();it!=urlVec.end();++it)
	       {
		    LOG<<"urlatt:"<<*it<<"\n";
		    if(it->length()>0)
		    {
			 std::vector<std::string> urlele;
			 split(*it, "[#]",urlele);
			 nsCString tmpUrl(urlele[0].c_str());
			 LOG<<"url:"<<urlele[0]<<"id"<<urlele[1]<<"\n";
			 task->AddUrl(tmpUrl,atoi(urlele[1].c_str()));
		    }
	       }
	       *_retval=task;
	       NS_ADDREF(*_retval);
	       return NS_OK;
	  }else
	  {
	       *_retval=nsnull;
	       return NS_OK;
	  }
     }else
     {
	  *_retval=nsnull;
	  return NS_ERROR_FAILURE;
     }
     return NS_OK;
}
/* boolean delJob (in long jobid); */
NS_IMETHODIMP nsSoapInter::DelJob(PRInt32 jobid, PRBool *_retval)
{
	if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();

	_nyapc1__delJob req;
	req.id = jobid;
	_nyapc1__delJobResponse res;
	if (service.delJob(&req,&res) == SOAP_OK)
	{
	  PRBool ret=res.delJobReturn;
	  *_retval=ret;
	  return NS_OK;
	}else
	{
	  *_retval=PR_FALSE;
	  return NS_ERROR_FAILURE;
	}

    return NS_OK;
}

/* boolean updateJobUrl (in long jobid, in AUTF8String url); */
NS_IMETHODIMP nsSoapInter::UpdateJobUrl(PRInt32 jobid, const nsACString & url, PRBool *_retval)
{
	nsCString nsurl(url);
	if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();
	_nyapc1__updateJobUrl req;
	req.id = jobid;
	req.url = std::string(nsurl.get());;

	_nyapc1__updateJobUrlResponse res;
	if (service.updateJobUrl(&req,&res) == SOAP_OK)
	{
	  PRBool ret=res.updateJobUrlReturn;
	  *_retval=ret;
	  return NS_OK;
	}else
	{
	  *_retval=PR_FALSE;
	  return NS_ERROR_FAILURE;
	}

    return NS_OK;
}
/* boolean updateWrapperCheckOk (in AUTF8String wrap, in long wrapid); */
NS_IMETHODIMP nsSoapInter::UpdateWrapperCheckOk(const nsACString & wrap, PRInt32 wrapid, PRBool *_retval)
{

    nsCString nswrap(wrap);
	if(mAddress.Length()>0)
	  service.soap_endpoint=mAddress.get();

	_nyapc1__updateWrapperCheckOk req;
	req.wrap = std::string(nswrap.get());
	req.wrapId = wrapid;

	_nyapc1__updateWrapperCheckOkResponse res;
	if (service.updateWrapperCheckOk(&req,&res) == SOAP_OK)
	{
	  PRBool ret=res.updateWrapperCheckOkReturn;
	  *_retval=ret;
	  return NS_OK;
	}else
	{
	  *_retval=PR_FALSE;
	  return NS_ERROR_FAILURE;
	}

    return NS_OK;
}
