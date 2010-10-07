/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsISoapJob.idl
 */

#ifndef __gen_nsISoapJob_h__
#define __gen_nsISoapJob_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsISoapJob */
#define NS_ISOAPJOB_IID_STR "f1ef9bac-c020-43e9-adef-64153d4348fe"

#define NS_ISOAPJOB_IID \
  {0xf1ef9bac, 0xc020, 0x43e9, \
    { 0xad, 0xef, 0x64, 0x15, 0x3d, 0x43, 0x48, 0xfe }}

class NS_NO_VTABLE NS_SCRIPTABLE nsISoapJob : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ISOAPJOB_IID)

  /* attribute long id; */
  NS_SCRIPTABLE NS_IMETHOD GetId(PRInt32 *aId) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetId(PRInt32 aId) = 0;

  /* attribute AUTF8String comment; */
  NS_SCRIPTABLE NS_IMETHOD GetComment(nsACString & aComment) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetComment(const nsACString & aComment) = 0;

  /* attribute AUTF8String seed; */
  NS_SCRIPTABLE NS_IMETHOD GetSeed(nsACString & aSeed) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetSeed(const nsACString & aSeed) = 0;

  /* attribute AUTF8String name; */
  NS_SCRIPTABLE NS_IMETHOD GetName(nsACString & aName) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsACString & aName) = 0;

  /* attribute AUTF8String seedType; */
  NS_SCRIPTABLE NS_IMETHOD GetSeedType(nsACString & aSeedType) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetSeedType(const nsACString & aSeedType) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsISoapJob, NS_ISOAPJOB_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISOAPJOB \
  NS_SCRIPTABLE NS_IMETHOD GetId(PRInt32 *aId); \
  NS_SCRIPTABLE NS_IMETHOD SetId(PRInt32 aId); \
  NS_SCRIPTABLE NS_IMETHOD GetComment(nsACString & aComment); \
  NS_SCRIPTABLE NS_IMETHOD SetComment(const nsACString & aComment); \
  NS_SCRIPTABLE NS_IMETHOD GetSeed(nsACString & aSeed); \
  NS_SCRIPTABLE NS_IMETHOD SetSeed(const nsACString & aSeed); \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsACString & aName); \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsACString & aName); \
  NS_SCRIPTABLE NS_IMETHOD GetSeedType(nsACString & aSeedType); \
  NS_SCRIPTABLE NS_IMETHOD SetSeedType(const nsACString & aSeedType); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISOAPJOB(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetId(PRInt32 *aId) { return _to GetId(aId); } \
  NS_SCRIPTABLE NS_IMETHOD SetId(PRInt32 aId) { return _to SetId(aId); } \
  NS_SCRIPTABLE NS_IMETHOD GetComment(nsACString & aComment) { return _to GetComment(aComment); } \
  NS_SCRIPTABLE NS_IMETHOD SetComment(const nsACString & aComment) { return _to SetComment(aComment); } \
  NS_SCRIPTABLE NS_IMETHOD GetSeed(nsACString & aSeed) { return _to GetSeed(aSeed); } \
  NS_SCRIPTABLE NS_IMETHOD SetSeed(const nsACString & aSeed) { return _to SetSeed(aSeed); } \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsACString & aName) { return _to GetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsACString & aName) { return _to SetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD GetSeedType(nsACString & aSeedType) { return _to GetSeedType(aSeedType); } \
  NS_SCRIPTABLE NS_IMETHOD SetSeedType(const nsACString & aSeedType) { return _to SetSeedType(aSeedType); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISOAPJOB(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetId(PRInt32 *aId) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetId(aId); } \
  NS_SCRIPTABLE NS_IMETHOD SetId(PRInt32 aId) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetId(aId); } \
  NS_SCRIPTABLE NS_IMETHOD GetComment(nsACString & aComment) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetComment(aComment); } \
  NS_SCRIPTABLE NS_IMETHOD SetComment(const nsACString & aComment) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetComment(aComment); } \
  NS_SCRIPTABLE NS_IMETHOD GetSeed(nsACString & aSeed) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSeed(aSeed); } \
  NS_SCRIPTABLE NS_IMETHOD SetSeed(const nsACString & aSeed) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetSeed(aSeed); } \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsACString & aName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsACString & aName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD GetSeedType(nsACString & aSeedType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSeedType(aSeedType); } \
  NS_SCRIPTABLE NS_IMETHOD SetSeedType(const nsACString & aSeedType) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetSeedType(aSeedType); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsSoapJob : public nsISoapJob
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISOAPJOB

  nsSoapJob();

private:
  ~nsSoapJob();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsSoapJob, nsISoapJob)

nsSoapJob::nsSoapJob()
{
  /* member initializers and constructor code */
}

nsSoapJob::~nsSoapJob()
{
  /* destructor code */
}

/* attribute long id; */
NS_IMETHODIMP nsSoapJob::GetId(PRInt32 *aId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSoapJob::SetId(PRInt32 aId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String comment; */
NS_IMETHODIMP nsSoapJob::GetComment(nsACString & aComment)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSoapJob::SetComment(const nsACString & aComment)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String seed; */
NS_IMETHODIMP nsSoapJob::GetSeed(nsACString & aSeed)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSoapJob::SetSeed(const nsACString & aSeed)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String name; */
NS_IMETHODIMP nsSoapJob::GetName(nsACString & aName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSoapJob::SetName(const nsACString & aName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String seedType; */
NS_IMETHODIMP nsSoapJob::GetSeedType(nsACString & aSeedType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSoapJob::SetSeedType(const nsACString & aSeedType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsISoapJob_h__ */
