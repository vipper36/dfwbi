/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsICluster.idl
 */

#ifndef __gen_nsICluster_h__
#define __gen_nsICluster_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIAttSet; /* forward declaration */

class nsIClustModel; /* forward declaration */


/* starting interface:    nsICluster */
#define NS_ICLUSTER_IID_STR "ad6857e0-2ed3-49ae-9ef7-223fb668daf4"

#define NS_ICLUSTER_IID \
  {0xad6857e0, 0x2ed3, 0x49ae, \
    { 0x9e, 0xf7, 0x22, 0x3f, 0xb6, 0x68, 0xda, 0xf4 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsICluster : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ICLUSTER_IID)

  /* void SetAtt (in nsIAttSet set); */
  NS_SCRIPTABLE NS_IMETHOD SetAtt(nsIAttSet *set) = 0;

  /* void SetDoubleParam (in AUTF8String name, in double value); */
  NS_SCRIPTABLE NS_IMETHOD SetDoubleParam(const nsACString & name, double value) = 0;

  /* void SetStringParam (in AUTF8String name, in AUTF8String value); */
  NS_SCRIPTABLE NS_IMETHOD SetStringParam(const nsACString & name, const nsACString & value) = 0;

  /* void CaculModel (); */
  NS_SCRIPTABLE NS_IMETHOD CaculModel(void) = 0;

  /* nsIClustModel GetResultModel (); */
  NS_SCRIPTABLE NS_IMETHOD GetResultModel(nsIClustModel **_retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsICluster, NS_ICLUSTER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSICLUSTER \
  NS_SCRIPTABLE NS_IMETHOD SetAtt(nsIAttSet *set); \
  NS_SCRIPTABLE NS_IMETHOD SetDoubleParam(const nsACString & name, double value); \
  NS_SCRIPTABLE NS_IMETHOD SetStringParam(const nsACString & name, const nsACString & value); \
  NS_SCRIPTABLE NS_IMETHOD CaculModel(void); \
  NS_SCRIPTABLE NS_IMETHOD GetResultModel(nsIClustModel **_retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSICLUSTER(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetAtt(nsIAttSet *set) { return _to SetAtt(set); } \
  NS_SCRIPTABLE NS_IMETHOD SetDoubleParam(const nsACString & name, double value) { return _to SetDoubleParam(name, value); } \
  NS_SCRIPTABLE NS_IMETHOD SetStringParam(const nsACString & name, const nsACString & value) { return _to SetStringParam(name, value); } \
  NS_SCRIPTABLE NS_IMETHOD CaculModel(void) { return _to CaculModel(); } \
  NS_SCRIPTABLE NS_IMETHOD GetResultModel(nsIClustModel **_retval NS_OUTPARAM) { return _to GetResultModel(_retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSICLUSTER(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetAtt(nsIAttSet *set) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAtt(set); } \
  NS_SCRIPTABLE NS_IMETHOD SetDoubleParam(const nsACString & name, double value) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetDoubleParam(name, value); } \
  NS_SCRIPTABLE NS_IMETHOD SetStringParam(const nsACString & name, const nsACString & value) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetStringParam(name, value); } \
  NS_SCRIPTABLE NS_IMETHOD CaculModel(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->CaculModel(); } \
  NS_SCRIPTABLE NS_IMETHOD GetResultModel(nsIClustModel **_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetResultModel(_retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsCluster : public nsICluster
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICLUSTER

  nsCluster();

private:
  ~nsCluster();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsCluster, nsICluster)

nsCluster::nsCluster()
{
  /* member initializers and constructor code */
}

nsCluster::~nsCluster()
{
  /* destructor code */
}

/* void SetAtt (in nsIAttSet set); */
NS_IMETHODIMP nsCluster::SetAtt(nsIAttSet *set)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetDoubleParam (in AUTF8String name, in double value); */
NS_IMETHODIMP nsCluster::SetDoubleParam(const nsACString & name, double value)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetStringParam (in AUTF8String name, in AUTF8String value); */
NS_IMETHODIMP nsCluster::SetStringParam(const nsACString & name, const nsACString & value)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void CaculModel (); */
NS_IMETHODIMP nsCluster::CaculModel()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIClustModel GetResultModel (); */
NS_IMETHODIMP nsCluster::GetResultModel(nsIClustModel **_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsICluster_h__ */
