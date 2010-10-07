/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsISoapInter.idl
 */

#ifndef __gen_nsISoapInter_h__
#define __gen_nsISoapInter_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsISoapTask; /* forward declaration */

class nsISoapJob; /* forward declaration */

class nsISupportsArray; /* forward declaration */


/* starting interface:    nsISoapInter */
#define NS_ISOAPINTER_IID_STR "414ef0b7-873a-49be-af3f-ebbecc727b6a"

#define NS_ISOAPINTER_IID \
  {0x414ef0b7, 0x873a, 0x49be, \
    { 0xaf, 0x3f, 0xeb, 0xbe, 0xcc, 0x72, 0x7b, 0x6a }}

class NS_NO_VTABLE NS_SCRIPTABLE nsISoapInter : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ISOAPINTER_IID)

  /* void SetAddress (in AUTF8String address); */
  NS_SCRIPTABLE NS_IMETHOD SetAddress(const nsACString & address) = 0;

  /* long getVersion (in long id); */
  NS_SCRIPTABLE NS_IMETHOD GetVersion(PRInt32 id, PRInt32 *_retval NS_OUTPARAM) = 0;

  /* nsISoapJob getJob (in long id); */
  NS_SCRIPTABLE NS_IMETHOD GetJob(PRInt32 id, nsISoapJob **_retval NS_OUTPARAM) = 0;

  /* long addJob (in AUTF8String name, in AUTF8String url, in AUTF8String type, in AUTF8String comment); */
  NS_SCRIPTABLE NS_IMETHOD AddJob(const nsACString & name, const nsACString & url, const nsACString & type, const nsACString & comment, PRInt32 *_retval NS_OUTPARAM) = 0;

  /* boolean updateJob (in long id); */
  NS_SCRIPTABLE NS_IMETHOD UpdateJob(PRInt32 id, PRBool *_retval NS_OUTPARAM) = 0;

  /* AUTF8String getWrapper (in long id); */
  NS_SCRIPTABLE NS_IMETHOD GetWrapper(PRInt32 id, nsACString & _retval NS_OUTPARAM) = 0;

  /* AUTF8String getWrapGen (in long id); */
  NS_SCRIPTABLE NS_IMETHOD GetWrapGen(PRInt32 id, nsACString & _retval NS_OUTPARAM) = 0;

  /* boolean addWrapper (in long jobid, in AUTF8String type, in AUTF8String wrapper, in AUTF8String wrapgen, in AUTF8String comment); */
  NS_SCRIPTABLE NS_IMETHOD AddWrapper(PRInt32 jobid, const nsACString & type, const nsACString & wrapper, const nsACString & wrapgen, const nsACString & comment, PRBool *_retval NS_OUTPARAM) = 0;

  /* nsISoapTask getTask (in long cid, in long num); */
  NS_SCRIPTABLE NS_IMETHOD GetTask(PRInt32 cid, PRInt32 num, nsISoapTask **_retval NS_OUTPARAM) = 0;

  /* nsISoapTask getTaskByJobId (in long cid, in long jobid, in AUTF8String type, in long num); */
  NS_SCRIPTABLE NS_IMETHOD GetTaskByJobId(PRInt32 cid, PRInt32 jobid, const nsACString & type, PRInt32 num, nsISoapTask **_retval NS_OUTPARAM) = 0;

  /* nsISoapTask getWrapTask (in long cid, in long num); */
  NS_SCRIPTABLE NS_IMETHOD GetWrapTask(PRInt32 cid, PRInt32 num, nsISoapTask **_retval NS_OUTPARAM) = 0;

  /* boolean updateWrapper (in AUTF8String wrap, in long id, in long taskid); */
  NS_SCRIPTABLE NS_IMETHOD UpdateWrapper(const nsACString & wrap, PRInt32 id, PRInt32 taskid, PRBool *_retval NS_OUTPARAM) = 0;

  /* boolean updateWrapGen (in AUTF8String wrapgen, in long id); */
  NS_SCRIPTABLE NS_IMETHOD UpdateWrapGen(const nsACString & wrapgen, PRInt32 id, PRBool *_retval NS_OUTPARAM) = 0;

  /* long getStat (in long cid); */
  NS_SCRIPTABLE NS_IMETHOD GetStat(PRInt32 cid, PRInt32 *_retval NS_OUTPARAM) = 0;

  /* boolean putResult (in AUTF8String result, in long id); */
  NS_SCRIPTABLE NS_IMETHOD PutResult(const nsACString & result, PRInt32 id, PRBool *_retval NS_OUTPARAM) = 0;

  /* nsISupportsArray getJobs (); */
  NS_SCRIPTABLE NS_IMETHOD GetJobs(nsISupportsArray **_retval NS_OUTPARAM) = 0;

  /* void getJobID ([array, size_is (id_size)] out long id, out unsigned long id_size); */
  NS_SCRIPTABLE NS_IMETHOD GetJobID(PRInt32 **id NS_OUTPARAM, PRUint32 *id_size NS_OUTPARAM) = 0;

  /* boolean hasTask (in long cid); */
  NS_SCRIPTABLE NS_IMETHOD HasTask(PRInt32 cid, PRBool *_retval NS_OUTPARAM) = 0;

  /* nsISupportsArray getJobsWrapStatInvalid (); */
  NS_SCRIPTABLE NS_IMETHOD GetJobsWrapStatInvalid(nsISupportsArray **_retval NS_OUTPARAM) = 0;

  /* nsISoapTask getWrapInvalidTaskByJobId (in long cid, in long jobid, in AUTF8String type, in long num); */
  NS_SCRIPTABLE NS_IMETHOD GetWrapInvalidTaskByJobId(PRInt32 cid, PRInt32 jobid, const nsACString & type, PRInt32 num, nsISoapTask **_retval NS_OUTPARAM) = 0;

  /* boolean delJob (in long jobid); */
  NS_SCRIPTABLE NS_IMETHOD DelJob(PRInt32 jobid, PRBool *_retval NS_OUTPARAM) = 0;

  /* boolean updateJobUrl (in long jobid, in AUTF8String url); */
  NS_SCRIPTABLE NS_IMETHOD UpdateJobUrl(PRInt32 jobid, const nsACString & url, PRBool *_retval NS_OUTPARAM) = 0;

  /* boolean updateWrapperCheckOk (in AUTF8String wrap, in long wrapid); */
  NS_SCRIPTABLE NS_IMETHOD UpdateWrapperCheckOk(const nsACString & wrap, PRInt32 wrapid, PRBool *_retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsISoapInter, NS_ISOAPINTER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISOAPINTER \
  NS_SCRIPTABLE NS_IMETHOD SetAddress(const nsACString & address); \
  NS_SCRIPTABLE NS_IMETHOD GetVersion(PRInt32 id, PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetJob(PRInt32 id, nsISoapJob **_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD AddJob(const nsACString & name, const nsACString & url, const nsACString & type, const nsACString & comment, PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD UpdateJob(PRInt32 id, PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetWrapper(PRInt32 id, nsACString & _retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetWrapGen(PRInt32 id, nsACString & _retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD AddWrapper(PRInt32 jobid, const nsACString & type, const nsACString & wrapper, const nsACString & wrapgen, const nsACString & comment, PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetTask(PRInt32 cid, PRInt32 num, nsISoapTask **_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetTaskByJobId(PRInt32 cid, PRInt32 jobid, const nsACString & type, PRInt32 num, nsISoapTask **_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetWrapTask(PRInt32 cid, PRInt32 num, nsISoapTask **_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD UpdateWrapper(const nsACString & wrap, PRInt32 id, PRInt32 taskid, PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD UpdateWrapGen(const nsACString & wrapgen, PRInt32 id, PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetStat(PRInt32 cid, PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD PutResult(const nsACString & result, PRInt32 id, PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetJobs(nsISupportsArray **_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetJobID(PRInt32 **id NS_OUTPARAM, PRUint32 *id_size NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD HasTask(PRInt32 cid, PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetJobsWrapStatInvalid(nsISupportsArray **_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetWrapInvalidTaskByJobId(PRInt32 cid, PRInt32 jobid, const nsACString & type, PRInt32 num, nsISoapTask **_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD DelJob(PRInt32 jobid, PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD UpdateJobUrl(PRInt32 jobid, const nsACString & url, PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD UpdateWrapperCheckOk(const nsACString & wrap, PRInt32 wrapid, PRBool *_retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISOAPINTER(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetAddress(const nsACString & address) { return _to SetAddress(address); } \
  NS_SCRIPTABLE NS_IMETHOD GetVersion(PRInt32 id, PRInt32 *_retval NS_OUTPARAM) { return _to GetVersion(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetJob(PRInt32 id, nsISoapJob **_retval NS_OUTPARAM) { return _to GetJob(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD AddJob(const nsACString & name, const nsACString & url, const nsACString & type, const nsACString & comment, PRInt32 *_retval NS_OUTPARAM) { return _to AddJob(name, url, type, comment, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateJob(PRInt32 id, PRBool *_retval NS_OUTPARAM) { return _to UpdateJob(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetWrapper(PRInt32 id, nsACString & _retval NS_OUTPARAM) { return _to GetWrapper(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetWrapGen(PRInt32 id, nsACString & _retval NS_OUTPARAM) { return _to GetWrapGen(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD AddWrapper(PRInt32 jobid, const nsACString & type, const nsACString & wrapper, const nsACString & wrapgen, const nsACString & comment, PRBool *_retval NS_OUTPARAM) { return _to AddWrapper(jobid, type, wrapper, wrapgen, comment, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetTask(PRInt32 cid, PRInt32 num, nsISoapTask **_retval NS_OUTPARAM) { return _to GetTask(cid, num, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetTaskByJobId(PRInt32 cid, PRInt32 jobid, const nsACString & type, PRInt32 num, nsISoapTask **_retval NS_OUTPARAM) { return _to GetTaskByJobId(cid, jobid, type, num, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetWrapTask(PRInt32 cid, PRInt32 num, nsISoapTask **_retval NS_OUTPARAM) { return _to GetWrapTask(cid, num, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateWrapper(const nsACString & wrap, PRInt32 id, PRInt32 taskid, PRBool *_retval NS_OUTPARAM) { return _to UpdateWrapper(wrap, id, taskid, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateWrapGen(const nsACString & wrapgen, PRInt32 id, PRBool *_retval NS_OUTPARAM) { return _to UpdateWrapGen(wrapgen, id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetStat(PRInt32 cid, PRInt32 *_retval NS_OUTPARAM) { return _to GetStat(cid, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD PutResult(const nsACString & result, PRInt32 id, PRBool *_retval NS_OUTPARAM) { return _to PutResult(result, id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetJobs(nsISupportsArray **_retval NS_OUTPARAM) { return _to GetJobs(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetJobID(PRInt32 **id NS_OUTPARAM, PRUint32 *id_size NS_OUTPARAM) { return _to GetJobID(id, id_size); } \
  NS_SCRIPTABLE NS_IMETHOD HasTask(PRInt32 cid, PRBool *_retval NS_OUTPARAM) { return _to HasTask(cid, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetJobsWrapStatInvalid(nsISupportsArray **_retval NS_OUTPARAM) { return _to GetJobsWrapStatInvalid(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetWrapInvalidTaskByJobId(PRInt32 cid, PRInt32 jobid, const nsACString & type, PRInt32 num, nsISoapTask **_retval NS_OUTPARAM) { return _to GetWrapInvalidTaskByJobId(cid, jobid, type, num, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD DelJob(PRInt32 jobid, PRBool *_retval NS_OUTPARAM) { return _to DelJob(jobid, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateJobUrl(PRInt32 jobid, const nsACString & url, PRBool *_retval NS_OUTPARAM) { return _to UpdateJobUrl(jobid, url, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateWrapperCheckOk(const nsACString & wrap, PRInt32 wrapid, PRBool *_retval NS_OUTPARAM) { return _to UpdateWrapperCheckOk(wrap, wrapid, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISOAPINTER(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetAddress(const nsACString & address) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAddress(address); } \
  NS_SCRIPTABLE NS_IMETHOD GetVersion(PRInt32 id, PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetVersion(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetJob(PRInt32 id, nsISoapJob **_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetJob(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD AddJob(const nsACString & name, const nsACString & url, const nsACString & type, const nsACString & comment, PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddJob(name, url, type, comment, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateJob(PRInt32 id, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->UpdateJob(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetWrapper(PRInt32 id, nsACString & _retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWrapper(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetWrapGen(PRInt32 id, nsACString & _retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWrapGen(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD AddWrapper(PRInt32 jobid, const nsACString & type, const nsACString & wrapper, const nsACString & wrapgen, const nsACString & comment, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddWrapper(jobid, type, wrapper, wrapgen, comment, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetTask(PRInt32 cid, PRInt32 num, nsISoapTask **_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTask(cid, num, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetTaskByJobId(PRInt32 cid, PRInt32 jobid, const nsACString & type, PRInt32 num, nsISoapTask **_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTaskByJobId(cid, jobid, type, num, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetWrapTask(PRInt32 cid, PRInt32 num, nsISoapTask **_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWrapTask(cid, num, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateWrapper(const nsACString & wrap, PRInt32 id, PRInt32 taskid, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->UpdateWrapper(wrap, id, taskid, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateWrapGen(const nsACString & wrapgen, PRInt32 id, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->UpdateWrapGen(wrapgen, id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetStat(PRInt32 cid, PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetStat(cid, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD PutResult(const nsACString & result, PRInt32 id, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->PutResult(result, id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetJobs(nsISupportsArray **_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetJobs(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetJobID(PRInt32 **id NS_OUTPARAM, PRUint32 *id_size NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetJobID(id, id_size); } \
  NS_SCRIPTABLE NS_IMETHOD HasTask(PRInt32 cid, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->HasTask(cid, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetJobsWrapStatInvalid(nsISupportsArray **_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetJobsWrapStatInvalid(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetWrapInvalidTaskByJobId(PRInt32 cid, PRInt32 jobid, const nsACString & type, PRInt32 num, nsISoapTask **_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWrapInvalidTaskByJobId(cid, jobid, type, num, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD DelJob(PRInt32 jobid, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->DelJob(jobid, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateJobUrl(PRInt32 jobid, const nsACString & url, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->UpdateJobUrl(jobid, url, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateWrapperCheckOk(const nsACString & wrap, PRInt32 wrapid, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->UpdateWrapperCheckOk(wrap, wrapid, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsSoapInter : public nsISoapInter
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISOAPINTER

  nsSoapInter();

private:
  ~nsSoapInter();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsSoapInter, nsISoapInter)

nsSoapInter::nsSoapInter()
{
  /* member initializers and constructor code */
}

nsSoapInter::~nsSoapInter()
{
  /* destructor code */
}

/* void SetAddress (in AUTF8String address); */
NS_IMETHODIMP nsSoapInter::SetAddress(const nsACString & address)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long getVersion (in long id); */
NS_IMETHODIMP nsSoapInter::GetVersion(PRInt32 id, PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsISoapJob getJob (in long id); */
NS_IMETHODIMP nsSoapInter::GetJob(PRInt32 id, nsISoapJob **_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long addJob (in AUTF8String name, in AUTF8String url, in AUTF8String type, in AUTF8String comment); */
NS_IMETHODIMP nsSoapInter::AddJob(const nsACString & name, const nsACString & url, const nsACString & type, const nsACString & comment, PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean updateJob (in long id); */
NS_IMETHODIMP nsSoapInter::UpdateJob(PRInt32 id, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AUTF8String getWrapper (in long id); */
NS_IMETHODIMP nsSoapInter::GetWrapper(PRInt32 id, nsACString & _retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AUTF8String getWrapGen (in long id); */
NS_IMETHODIMP nsSoapInter::GetWrapGen(PRInt32 id, nsACString & _retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean addWrapper (in long jobid, in AUTF8String type, in AUTF8String wrapper, in AUTF8String wrapgen, in AUTF8String comment); */
NS_IMETHODIMP nsSoapInter::AddWrapper(PRInt32 jobid, const nsACString & type, const nsACString & wrapper, const nsACString & wrapgen, const nsACString & comment, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsISoapTask getTask (in long cid, in long num); */
NS_IMETHODIMP nsSoapInter::GetTask(PRInt32 cid, PRInt32 num, nsISoapTask **_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsISoapTask getTaskByJobId (in long cid, in long jobid, in AUTF8String type, in long num); */
NS_IMETHODIMP nsSoapInter::GetTaskByJobId(PRInt32 cid, PRInt32 jobid, const nsACString & type, PRInt32 num, nsISoapTask **_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsISoapTask getWrapTask (in long cid, in long num); */
NS_IMETHODIMP nsSoapInter::GetWrapTask(PRInt32 cid, PRInt32 num, nsISoapTask **_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean updateWrapper (in AUTF8String wrap, in long id, in long taskid); */
NS_IMETHODIMP nsSoapInter::UpdateWrapper(const nsACString & wrap, PRInt32 id, PRInt32 taskid, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean updateWrapGen (in AUTF8String wrapgen, in long id); */
NS_IMETHODIMP nsSoapInter::UpdateWrapGen(const nsACString & wrapgen, PRInt32 id, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long getStat (in long cid); */
NS_IMETHODIMP nsSoapInter::GetStat(PRInt32 cid, PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean putResult (in AUTF8String result, in long id); */
NS_IMETHODIMP nsSoapInter::PutResult(const nsACString & result, PRInt32 id, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsISupportsArray getJobs (); */
NS_IMETHODIMP nsSoapInter::GetJobs(nsISupportsArray **_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void getJobID ([array, size_is (id_size)] out long id, out unsigned long id_size); */
NS_IMETHODIMP nsSoapInter::GetJobID(PRInt32 **id NS_OUTPARAM, PRUint32 *id_size NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean hasTask (in long cid); */
NS_IMETHODIMP nsSoapInter::HasTask(PRInt32 cid, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsISupportsArray getJobsWrapStatInvalid (); */
NS_IMETHODIMP nsSoapInter::GetJobsWrapStatInvalid(nsISupportsArray **_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsISoapTask getWrapInvalidTaskByJobId (in long cid, in long jobid, in AUTF8String type, in long num); */
NS_IMETHODIMP nsSoapInter::GetWrapInvalidTaskByJobId(PRInt32 cid, PRInt32 jobid, const nsACString & type, PRInt32 num, nsISoapTask **_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean delJob (in long jobid); */
NS_IMETHODIMP nsSoapInter::DelJob(PRInt32 jobid, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean updateJobUrl (in long jobid, in AUTF8String url); */
NS_IMETHODIMP nsSoapInter::UpdateJobUrl(PRInt32 jobid, const nsACString & url, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean updateWrapperCheckOk (in AUTF8String wrap, in long wrapid); */
NS_IMETHODIMP nsSoapInter::UpdateWrapperCheckOk(const nsACString & wrap, PRInt32 wrapid, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsISoapInter_h__ */
