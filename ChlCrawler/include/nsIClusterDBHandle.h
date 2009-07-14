/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIClusterDBHandle.idl
 */

#ifndef __gen_nsIClusterDBHandle_h__
#define __gen_nsIClusterDBHandle_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIUrlAtt; /* forward declaration */

class nsCStringArray; /* forward declaration */


/* starting interface:    nsIClusterDBHandle */
#define NS_ICLUSTERDBHANDLE_IID_STR "65c713d8-8967-45ef-afcd-493ea13bea37"

#define NS_ICLUSTERDBHANDLE_IID \
  {0x65c713d8, 0x8967, 0x45ef, \
    { 0xaf, 0xcd, 0x49, 0x3e, 0xa1, 0x3b, 0xea, 0x37 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIClusterDBHandle : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ICLUSTERDBHANDLE_IID)

  /* void SetLocation (in AUTF8String location); */
  NS_SCRIPTABLE NS_IMETHOD SetLocation(const nsACString & location) = 0;

  /* void SaveWrapRules (in PRInt32 con_type, in PRInt32 con_attr, in AUTF8String rules); */
  NS_SCRIPTABLE NS_IMETHOD SaveWrapRules(PRInt32 con_type, PRInt32 con_attr, const nsACString & rules) = 0;

  /* void LoadWrapRules (in PRInt32 con_type, out AUTF8String rules); */
  NS_SCRIPTABLE NS_IMETHOD LoadWrapRules(PRInt32 con_type, nsACString & rules) = 0;

  /* void SetPageType (in nsIUrlAtt url, in PRInt32 type); */
  NS_SCRIPTABLE NS_IMETHOD SetPageType(nsIUrlAtt *url, PRInt32 type) = 0;

  /* void InsertNewPage (in nsIUrlAtt url); */
  NS_SCRIPTABLE NS_IMETHOD InsertNewPage(nsIUrlAtt *url) = 0;

  /* void GetURLID (in AUTF8String url, out PRUint32 id); */
  NS_SCRIPTABLE NS_IMETHOD GetURLID(const nsACString & url, PRUint32 *id) = 0;

  /* void UpdateClusterType (in PRInt32 con_type, in PRInt32 con_attr); */
  NS_SCRIPTABLE NS_IMETHOD UpdateClusterType(PRInt32 con_type, PRInt32 con_attr) = 0;

  /* void SavePage (in PRInt32 url_id, in AUTF8String type); */
  NS_SCRIPTABLE NS_IMETHOD SavePage(PRInt32 url_id, const nsACString & type) = 0;

  /* void GetPage (out PRInt32 uid, out AUTF8String page); */
  NS_SCRIPTABLE NS_IMETHOD GetPage(PRInt32 *uid, nsACString & page) = 0;

  /* void SetConType (in PRInt32 url_id, in PRInt32 con_type); */
  NS_SCRIPTABLE NS_IMETHOD SetConType(PRInt32 url_id, PRInt32 con_type) = 0;

  /* void GetNumberOfCluster (out PRInt32 num); */
  NS_SCRIPTABLE NS_IMETHOD GetNumberOfCluster(PRInt32 *num) = 0;

  /* void GetClusterID ([array, size_is (count)] out PRUint32 ids, out PRUint32 count); */
  NS_SCRIPTABLE NS_IMETHOD GetClusterID(PRUint32 **ids, PRUint32 *count) = 0;

  /* void GetPageByConType (in PRUint32 con_type, in PRUint32 num, in nsCStringArray docs, out PRUint32 count); */
  NS_SCRIPTABLE NS_IMETHOD GetPageByConType(PRUint32 con_type, PRUint32 num, nsCStringArray *docs, PRUint32 *count) = 0;

  /* void GetClusterType (in PRUint32 name, out PRUint32 type); */
  NS_SCRIPTABLE NS_IMETHOD GetClusterType(PRUint32 name, PRUint32 *type) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIClusterDBHandle, NS_ICLUSTERDBHANDLE_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSICLUSTERDBHANDLE \
  NS_SCRIPTABLE NS_IMETHOD SetLocation(const nsACString & location); \
  NS_SCRIPTABLE NS_IMETHOD SaveWrapRules(PRInt32 con_type, PRInt32 con_attr, const nsACString & rules); \
  NS_SCRIPTABLE NS_IMETHOD LoadWrapRules(PRInt32 con_type, nsACString & rules); \
  NS_SCRIPTABLE NS_IMETHOD SetPageType(nsIUrlAtt *url, PRInt32 type); \
  NS_SCRIPTABLE NS_IMETHOD InsertNewPage(nsIUrlAtt *url); \
  NS_SCRIPTABLE NS_IMETHOD GetURLID(const nsACString & url, PRUint32 *id); \
  NS_SCRIPTABLE NS_IMETHOD UpdateClusterType(PRInt32 con_type, PRInt32 con_attr); \
  NS_SCRIPTABLE NS_IMETHOD SavePage(PRInt32 url_id, const nsACString & type); \
  NS_SCRIPTABLE NS_IMETHOD GetPage(PRInt32 *uid, nsACString & page); \
  NS_SCRIPTABLE NS_IMETHOD SetConType(PRInt32 url_id, PRInt32 con_type); \
  NS_SCRIPTABLE NS_IMETHOD GetNumberOfCluster(PRInt32 *num); \
  NS_SCRIPTABLE NS_IMETHOD GetClusterID(PRUint32 **ids, PRUint32 *count); \
  NS_SCRIPTABLE NS_IMETHOD GetPageByConType(PRUint32 con_type, PRUint32 num, nsCStringArray *docs, PRUint32 *count); \
  NS_SCRIPTABLE NS_IMETHOD GetClusterType(PRUint32 name, PRUint32 *type); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSICLUSTERDBHANDLE(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetLocation(const nsACString & location) { return _to SetLocation(location); } \
  NS_SCRIPTABLE NS_IMETHOD SaveWrapRules(PRInt32 con_type, PRInt32 con_attr, const nsACString & rules) { return _to SaveWrapRules(con_type, con_attr, rules); } \
  NS_SCRIPTABLE NS_IMETHOD LoadWrapRules(PRInt32 con_type, nsACString & rules) { return _to LoadWrapRules(con_type, rules); } \
  NS_SCRIPTABLE NS_IMETHOD SetPageType(nsIUrlAtt *url, PRInt32 type) { return _to SetPageType(url, type); } \
  NS_SCRIPTABLE NS_IMETHOD InsertNewPage(nsIUrlAtt *url) { return _to InsertNewPage(url); } \
  NS_SCRIPTABLE NS_IMETHOD GetURLID(const nsACString & url, PRUint32 *id) { return _to GetURLID(url, id); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateClusterType(PRInt32 con_type, PRInt32 con_attr) { return _to UpdateClusterType(con_type, con_attr); } \
  NS_SCRIPTABLE NS_IMETHOD SavePage(PRInt32 url_id, const nsACString & type) { return _to SavePage(url_id, type); } \
  NS_SCRIPTABLE NS_IMETHOD GetPage(PRInt32 *uid, nsACString & page) { return _to GetPage(uid, page); } \
  NS_SCRIPTABLE NS_IMETHOD SetConType(PRInt32 url_id, PRInt32 con_type) { return _to SetConType(url_id, con_type); } \
  NS_SCRIPTABLE NS_IMETHOD GetNumberOfCluster(PRInt32 *num) { return _to GetNumberOfCluster(num); } \
  NS_SCRIPTABLE NS_IMETHOD GetClusterID(PRUint32 **ids, PRUint32 *count) { return _to GetClusterID(ids, count); } \
  NS_SCRIPTABLE NS_IMETHOD GetPageByConType(PRUint32 con_type, PRUint32 num, nsCStringArray *docs, PRUint32 *count) { return _to GetPageByConType(con_type, num, docs, count); } \
  NS_SCRIPTABLE NS_IMETHOD GetClusterType(PRUint32 name, PRUint32 *type) { return _to GetClusterType(name, type); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSICLUSTERDBHANDLE(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetLocation(const nsACString & location) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetLocation(location); } \
  NS_SCRIPTABLE NS_IMETHOD SaveWrapRules(PRInt32 con_type, PRInt32 con_attr, const nsACString & rules) { return !_to ? NS_ERROR_NULL_POINTER : _to->SaveWrapRules(con_type, con_attr, rules); } \
  NS_SCRIPTABLE NS_IMETHOD LoadWrapRules(PRInt32 con_type, nsACString & rules) { return !_to ? NS_ERROR_NULL_POINTER : _to->LoadWrapRules(con_type, rules); } \
  NS_SCRIPTABLE NS_IMETHOD SetPageType(nsIUrlAtt *url, PRInt32 type) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetPageType(url, type); } \
  NS_SCRIPTABLE NS_IMETHOD InsertNewPage(nsIUrlAtt *url) { return !_to ? NS_ERROR_NULL_POINTER : _to->InsertNewPage(url); } \
  NS_SCRIPTABLE NS_IMETHOD GetURLID(const nsACString & url, PRUint32 *id) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetURLID(url, id); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateClusterType(PRInt32 con_type, PRInt32 con_attr) { return !_to ? NS_ERROR_NULL_POINTER : _to->UpdateClusterType(con_type, con_attr); } \
  NS_SCRIPTABLE NS_IMETHOD SavePage(PRInt32 url_id, const nsACString & type) { return !_to ? NS_ERROR_NULL_POINTER : _to->SavePage(url_id, type); } \
  NS_SCRIPTABLE NS_IMETHOD GetPage(PRInt32 *uid, nsACString & page) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPage(uid, page); } \
  NS_SCRIPTABLE NS_IMETHOD SetConType(PRInt32 url_id, PRInt32 con_type) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetConType(url_id, con_type); } \
  NS_SCRIPTABLE NS_IMETHOD GetNumberOfCluster(PRInt32 *num) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNumberOfCluster(num); } \
  NS_SCRIPTABLE NS_IMETHOD GetClusterID(PRUint32 **ids, PRUint32 *count) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetClusterID(ids, count); } \
  NS_SCRIPTABLE NS_IMETHOD GetPageByConType(PRUint32 con_type, PRUint32 num, nsCStringArray *docs, PRUint32 *count) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPageByConType(con_type, num, docs, count); } \
  NS_SCRIPTABLE NS_IMETHOD GetClusterType(PRUint32 name, PRUint32 *type) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetClusterType(name, type); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsClusterDBHandle : public nsIClusterDBHandle
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICLUSTERDBHANDLE

  nsClusterDBHandle();

private:
  ~nsClusterDBHandle();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsClusterDBHandle, nsIClusterDBHandle)

nsClusterDBHandle::nsClusterDBHandle()
{
  /* member initializers and constructor code */
}

nsClusterDBHandle::~nsClusterDBHandle()
{
  /* destructor code */
}

/* void SetLocation (in AUTF8String location); */
NS_IMETHODIMP nsClusterDBHandle::SetLocation(const nsACString & location)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SaveWrapRules (in PRInt32 con_type, in PRInt32 con_attr, in AUTF8String rules); */
NS_IMETHODIMP nsClusterDBHandle::SaveWrapRules(PRInt32 con_type, PRInt32 con_attr, const nsACString & rules)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void LoadWrapRules (in PRInt32 con_type, out AUTF8String rules); */
NS_IMETHODIMP nsClusterDBHandle::LoadWrapRules(PRInt32 con_type, nsACString & rules)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetPageType (in nsIUrlAtt url, in PRInt32 type); */
NS_IMETHODIMP nsClusterDBHandle::SetPageType(nsIUrlAtt *url, PRInt32 type)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void InsertNewPage (in nsIUrlAtt url); */
NS_IMETHODIMP nsClusterDBHandle::InsertNewPage(nsIUrlAtt *url)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetURLID (in AUTF8String url, out PRUint32 id); */
NS_IMETHODIMP nsClusterDBHandle::GetURLID(const nsACString & url, PRUint32 *id)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void UpdateClusterType (in PRInt32 con_type, in PRInt32 con_attr); */
NS_IMETHODIMP nsClusterDBHandle::UpdateClusterType(PRInt32 con_type, PRInt32 con_attr)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SavePage (in PRInt32 url_id, in AUTF8String type); */
NS_IMETHODIMP nsClusterDBHandle::SavePage(PRInt32 url_id, const nsACString & type)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetPage (out PRInt32 uid, out AUTF8String page); */
NS_IMETHODIMP nsClusterDBHandle::GetPage(PRInt32 *uid, nsACString & page)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetConType (in PRInt32 url_id, in PRInt32 con_type); */
NS_IMETHODIMP nsClusterDBHandle::SetConType(PRInt32 url_id, PRInt32 con_type)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetNumberOfCluster (out PRInt32 num); */
NS_IMETHODIMP nsClusterDBHandle::GetNumberOfCluster(PRInt32 *num)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetClusterID ([array, size_is (count)] out PRUint32 ids, out PRUint32 count); */
NS_IMETHODIMP nsClusterDBHandle::GetClusterID(PRUint32 **ids, PRUint32 *count)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetPageByConType (in PRUint32 con_type, in PRUint32 num, in nsCStringArray docs, out PRUint32 count); */
NS_IMETHODIMP nsClusterDBHandle::GetPageByConType(PRUint32 con_type, PRUint32 num, nsCStringArray *docs, PRUint32 *count)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetClusterType (in PRUint32 name, out PRUint32 type); */
NS_IMETHODIMP nsClusterDBHandle::GetClusterType(PRUint32 name, PRUint32 *type)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIClusterDBHandle_h__ */
