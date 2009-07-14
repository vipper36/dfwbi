/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIDOMAnalysis.idl
 */

#ifndef __gen_nsIDOMAnalysis_h__
#define __gen_nsIDOMAnalysis_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIPersistentProperties; /* forward declaration */

class nsIDOMDocument; /* forward declaration */

class nsIIDXCreator; /* forward declaration */

class nsIUrlAtt; /* forward declaration */


/* starting interface:    nsIDOMAnalysis */
#define NS_IDOMANALYSIS_IID_STR "1a0cbfc4-f991-4bfd-90ec-f97b882c716c"

#define NS_IDOMANALYSIS_IID \
  {0x1a0cbfc4, 0xf991, 0x4bfd, \
    { 0x90, 0xec, 0xf9, 0x7b, 0x88, 0x2c, 0x71, 0x6c }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIDOMAnalysis : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMANALYSIS_IID)

  /* PRUint32 Analysis (in nsIDOMDocument doc); */
  NS_SCRIPTABLE NS_IMETHOD Analysis(nsIDOMDocument *doc, PRUint32 *_retval) = 0;

  /* void SetCurUrl (in nsIUrlAtt url_attr); */
  NS_SCRIPTABLE NS_IMETHOD SetCurUrl(nsIUrlAtt *url_attr) = 0;

  /* void SetProperty (in nsIPersistentProperties p); */
  NS_SCRIPTABLE NS_IMETHOD SetProperty(nsIPersistentProperties *p) = 0;

  /* void SaveWrapper (); */
  NS_SCRIPTABLE NS_IMETHOD SaveWrapper(void) = 0;

  /* void LoadConfig (); */
  NS_SCRIPTABLE NS_IMETHOD LoadConfig(void) = 0;

  /* void SetIdxCreator (in nsIIDXCreator creator); */
  NS_SCRIPTABLE NS_IMETHOD SetIdxCreator(nsIIDXCreator *creator) = 0;

  /* void GetClusterAttr (in PRUint32 cid, out PRUint32 attr); */
  NS_SCRIPTABLE NS_IMETHOD GetClusterAttr(PRUint32 cid, PRUint32 *attr) = 0;

  /* void SetClusterType (in PRUint32 cid, in PRUint32 type); */
  NS_SCRIPTABLE NS_IMETHOD SetClusterType(PRUint32 cid, PRUint32 type) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMAnalysis, NS_IDOMANALYSIS_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMANALYSIS \
  NS_SCRIPTABLE NS_IMETHOD Analysis(nsIDOMDocument *doc, PRUint32 *_retval); \
  NS_SCRIPTABLE NS_IMETHOD SetCurUrl(nsIUrlAtt *url_attr); \
  NS_SCRIPTABLE NS_IMETHOD SetProperty(nsIPersistentProperties *p); \
  NS_SCRIPTABLE NS_IMETHOD SaveWrapper(void); \
  NS_SCRIPTABLE NS_IMETHOD LoadConfig(void); \
  NS_SCRIPTABLE NS_IMETHOD SetIdxCreator(nsIIDXCreator *creator); \
  NS_SCRIPTABLE NS_IMETHOD GetClusterAttr(PRUint32 cid, PRUint32 *attr); \
  NS_SCRIPTABLE NS_IMETHOD SetClusterType(PRUint32 cid, PRUint32 type); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMANALYSIS(_to) \
  NS_SCRIPTABLE NS_IMETHOD Analysis(nsIDOMDocument *doc, PRUint32 *_retval) { return _to Analysis(doc, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetCurUrl(nsIUrlAtt *url_attr) { return _to SetCurUrl(url_attr); } \
  NS_SCRIPTABLE NS_IMETHOD SetProperty(nsIPersistentProperties *p) { return _to SetProperty(p); } \
  NS_SCRIPTABLE NS_IMETHOD SaveWrapper(void) { return _to SaveWrapper(); } \
  NS_SCRIPTABLE NS_IMETHOD LoadConfig(void) { return _to LoadConfig(); } \
  NS_SCRIPTABLE NS_IMETHOD SetIdxCreator(nsIIDXCreator *creator) { return _to SetIdxCreator(creator); } \
  NS_SCRIPTABLE NS_IMETHOD GetClusterAttr(PRUint32 cid, PRUint32 *attr) { return _to GetClusterAttr(cid, attr); } \
  NS_SCRIPTABLE NS_IMETHOD SetClusterType(PRUint32 cid, PRUint32 type) { return _to SetClusterType(cid, type); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMANALYSIS(_to) \
  NS_SCRIPTABLE NS_IMETHOD Analysis(nsIDOMDocument *doc, PRUint32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Analysis(doc, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetCurUrl(nsIUrlAtt *url_attr) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCurUrl(url_attr); } \
  NS_SCRIPTABLE NS_IMETHOD SetProperty(nsIPersistentProperties *p) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetProperty(p); } \
  NS_SCRIPTABLE NS_IMETHOD SaveWrapper(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->SaveWrapper(); } \
  NS_SCRIPTABLE NS_IMETHOD LoadConfig(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->LoadConfig(); } \
  NS_SCRIPTABLE NS_IMETHOD SetIdxCreator(nsIIDXCreator *creator) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetIdxCreator(creator); } \
  NS_SCRIPTABLE NS_IMETHOD GetClusterAttr(PRUint32 cid, PRUint32 *attr) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetClusterAttr(cid, attr); } \
  NS_SCRIPTABLE NS_IMETHOD SetClusterType(PRUint32 cid, PRUint32 type) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetClusterType(cid, type); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMAnalysis : public nsIDOMAnalysis
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMANALYSIS

  nsDOMAnalysis();

private:
  ~nsDOMAnalysis();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMAnalysis, nsIDOMAnalysis)

nsDOMAnalysis::nsDOMAnalysis()
{
  /* member initializers and constructor code */
}

nsDOMAnalysis::~nsDOMAnalysis()
{
  /* destructor code */
}

/* PRUint32 Analysis (in nsIDOMDocument doc); */
NS_IMETHODIMP nsDOMAnalysis::Analysis(nsIDOMDocument *doc, PRUint32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetCurUrl (in nsIUrlAtt url_attr); */
NS_IMETHODIMP nsDOMAnalysis::SetCurUrl(nsIUrlAtt *url_attr)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetProperty (in nsIPersistentProperties p); */
NS_IMETHODIMP nsDOMAnalysis::SetProperty(nsIPersistentProperties *p)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SaveWrapper (); */
NS_IMETHODIMP nsDOMAnalysis::SaveWrapper()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void LoadConfig (); */
NS_IMETHODIMP nsDOMAnalysis::LoadConfig()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetIdxCreator (in nsIIDXCreator creator); */
NS_IMETHODIMP nsDOMAnalysis::SetIdxCreator(nsIIDXCreator *creator)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetClusterAttr (in PRUint32 cid, out PRUint32 attr); */
NS_IMETHODIMP nsDOMAnalysis::GetClusterAttr(PRUint32 cid, PRUint32 *attr)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetClusterType (in PRUint32 cid, in PRUint32 type); */
NS_IMETHODIMP nsDOMAnalysis::SetClusterType(PRUint32 cid, PRUint32 type)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMAnalysis_h__ */
