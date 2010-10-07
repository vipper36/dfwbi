/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsISoapTask.idl
 */

#ifndef __gen_nsISoapTask_h__
#define __gen_nsISoapTask_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsISoapTask */
#define NS_ISOAPTASK_IID_STR "557d2727-fb30-47c5-bba5-db56e593936d"

#define NS_ISOAPTASK_IID \
  {0x557d2727, 0xfb30, 0x47c5, \
    { 0xbb, 0xa5, 0xdb, 0x56, 0xe5, 0x93, 0x93, 0x6d }}

class NS_NO_VTABLE NS_SCRIPTABLE nsISoapTask : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ISOAPTASK_IID)

  /* attribute long jobId; */
  NS_SCRIPTABLE NS_IMETHOD GetJobId(PRInt32 *aJobId) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetJobId(PRInt32 aJobId) = 0;

  /* attribute AUTF8String type; */
  NS_SCRIPTABLE NS_IMETHOD GetType(nsACString & aType) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetType(const nsACString & aType) = 0;

  /* attribute long wrapid; */
  NS_SCRIPTABLE NS_IMETHOD GetWrapid(PRInt32 *aWrapid) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetWrapid(PRInt32 aWrapid) = 0;

  /* attribute long wrapver; */
  NS_SCRIPTABLE NS_IMETHOD GetWrapver(PRInt32 *aWrapver) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetWrapver(PRInt32 aWrapver) = 0;

  /* attribute long taskId; */
  NS_SCRIPTABLE NS_IMETHOD GetTaskId(PRInt32 *aTaskId) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetTaskId(PRInt32 aTaskId) = 0;

  /* void AddUrl (in AUTF8String url, in long uid); */
  NS_SCRIPTABLE NS_IMETHOD AddUrl(const nsACString & url, PRInt32 uid) = 0;

  /* long GetUrlCount (); */
  NS_SCRIPTABLE NS_IMETHOD GetUrlCount(PRInt32 *_retval NS_OUTPARAM) = 0;

  /* void GetUrlByIndex (in long index, out long uid, out AUTF8String url); */
  NS_SCRIPTABLE NS_IMETHOD GetUrlByIndex(PRInt32 index, PRInt32 *uid NS_OUTPARAM, nsACString & url NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsISoapTask, NS_ISOAPTASK_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISOAPTASK \
  NS_SCRIPTABLE NS_IMETHOD GetJobId(PRInt32 *aJobId); \
  NS_SCRIPTABLE NS_IMETHOD SetJobId(PRInt32 aJobId); \
  NS_SCRIPTABLE NS_IMETHOD GetType(nsACString & aType); \
  NS_SCRIPTABLE NS_IMETHOD SetType(const nsACString & aType); \
  NS_SCRIPTABLE NS_IMETHOD GetWrapid(PRInt32 *aWrapid); \
  NS_SCRIPTABLE NS_IMETHOD SetWrapid(PRInt32 aWrapid); \
  NS_SCRIPTABLE NS_IMETHOD GetWrapver(PRInt32 *aWrapver); \
  NS_SCRIPTABLE NS_IMETHOD SetWrapver(PRInt32 aWrapver); \
  NS_SCRIPTABLE NS_IMETHOD GetTaskId(PRInt32 *aTaskId); \
  NS_SCRIPTABLE NS_IMETHOD SetTaskId(PRInt32 aTaskId); \
  NS_SCRIPTABLE NS_IMETHOD AddUrl(const nsACString & url, PRInt32 uid); \
  NS_SCRIPTABLE NS_IMETHOD GetUrlCount(PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetUrlByIndex(PRInt32 index, PRInt32 *uid NS_OUTPARAM, nsACString & url NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISOAPTASK(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetJobId(PRInt32 *aJobId) { return _to GetJobId(aJobId); } \
  NS_SCRIPTABLE NS_IMETHOD SetJobId(PRInt32 aJobId) { return _to SetJobId(aJobId); } \
  NS_SCRIPTABLE NS_IMETHOD GetType(nsACString & aType) { return _to GetType(aType); } \
  NS_SCRIPTABLE NS_IMETHOD SetType(const nsACString & aType) { return _to SetType(aType); } \
  NS_SCRIPTABLE NS_IMETHOD GetWrapid(PRInt32 *aWrapid) { return _to GetWrapid(aWrapid); } \
  NS_SCRIPTABLE NS_IMETHOD SetWrapid(PRInt32 aWrapid) { return _to SetWrapid(aWrapid); } \
  NS_SCRIPTABLE NS_IMETHOD GetWrapver(PRInt32 *aWrapver) { return _to GetWrapver(aWrapver); } \
  NS_SCRIPTABLE NS_IMETHOD SetWrapver(PRInt32 aWrapver) { return _to SetWrapver(aWrapver); } \
  NS_SCRIPTABLE NS_IMETHOD GetTaskId(PRInt32 *aTaskId) { return _to GetTaskId(aTaskId); } \
  NS_SCRIPTABLE NS_IMETHOD SetTaskId(PRInt32 aTaskId) { return _to SetTaskId(aTaskId); } \
  NS_SCRIPTABLE NS_IMETHOD AddUrl(const nsACString & url, PRInt32 uid) { return _to AddUrl(url, uid); } \
  NS_SCRIPTABLE NS_IMETHOD GetUrlCount(PRInt32 *_retval NS_OUTPARAM) { return _to GetUrlCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetUrlByIndex(PRInt32 index, PRInt32 *uid NS_OUTPARAM, nsACString & url NS_OUTPARAM) { return _to GetUrlByIndex(index, uid, url); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISOAPTASK(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetJobId(PRInt32 *aJobId) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetJobId(aJobId); } \
  NS_SCRIPTABLE NS_IMETHOD SetJobId(PRInt32 aJobId) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetJobId(aJobId); } \
  NS_SCRIPTABLE NS_IMETHOD GetType(nsACString & aType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetType(aType); } \
  NS_SCRIPTABLE NS_IMETHOD SetType(const nsACString & aType) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetType(aType); } \
  NS_SCRIPTABLE NS_IMETHOD GetWrapid(PRInt32 *aWrapid) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWrapid(aWrapid); } \
  NS_SCRIPTABLE NS_IMETHOD SetWrapid(PRInt32 aWrapid) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetWrapid(aWrapid); } \
  NS_SCRIPTABLE NS_IMETHOD GetWrapver(PRInt32 *aWrapver) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWrapver(aWrapver); } \
  NS_SCRIPTABLE NS_IMETHOD SetWrapver(PRInt32 aWrapver) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetWrapver(aWrapver); } \
  NS_SCRIPTABLE NS_IMETHOD GetTaskId(PRInt32 *aTaskId) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTaskId(aTaskId); } \
  NS_SCRIPTABLE NS_IMETHOD SetTaskId(PRInt32 aTaskId) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetTaskId(aTaskId); } \
  NS_SCRIPTABLE NS_IMETHOD AddUrl(const nsACString & url, PRInt32 uid) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddUrl(url, uid); } \
  NS_SCRIPTABLE NS_IMETHOD GetUrlCount(PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUrlCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetUrlByIndex(PRInt32 index, PRInt32 *uid NS_OUTPARAM, nsACString & url NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUrlByIndex(index, uid, url); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsSoapTask : public nsISoapTask
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISOAPTASK

  nsSoapTask();

private:
  ~nsSoapTask();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsSoapTask, nsISoapTask)

nsSoapTask::nsSoapTask()
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
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSoapTask::SetJobId(PRInt32 aJobId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String type; */
NS_IMETHODIMP nsSoapTask::GetType(nsACString & aType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSoapTask::SetType(const nsACString & aType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long wrapid; */
NS_IMETHODIMP nsSoapTask::GetWrapid(PRInt32 *aWrapid)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSoapTask::SetWrapid(PRInt32 aWrapid)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long wrapver; */
NS_IMETHODIMP nsSoapTask::GetWrapver(PRInt32 *aWrapver)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSoapTask::SetWrapver(PRInt32 aWrapver)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long taskId; */
NS_IMETHODIMP nsSoapTask::GetTaskId(PRInt32 *aTaskId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSoapTask::SetTaskId(PRInt32 aTaskId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void AddUrl (in AUTF8String url, in long uid); */
NS_IMETHODIMP nsSoapTask::AddUrl(const nsACString & url, PRInt32 uid)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long GetUrlCount (); */
NS_IMETHODIMP nsSoapTask::GetUrlCount(PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetUrlByIndex (in long index, out long uid, out AUTF8String url); */
NS_IMETHODIMP nsSoapTask::GetUrlByIndex(PRInt32 index, PRInt32 *uid NS_OUTPARAM, nsACString & url NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsISoapTask_h__ */
