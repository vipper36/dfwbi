/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsILoginCookieFetch.idl
 */

#ifndef __gen_nsILoginCookieFetch_h__
#define __gen_nsILoginCookieFetch_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMDocument; /* forward declaration */


/* starting interface:    nsILoginCookieFetch */
#define NS_ILOGINCOOKIEFETCH_IID_STR "761f8765-dc9f-428c-b9e0-01a09e5c6b4d"

#define NS_ILOGINCOOKIEFETCH_IID \
  {0x761f8765, 0xdc9f, 0x428c, \
    { 0xb9, 0xe0, 0x01, 0xa0, 0x9e, 0x5c, 0x6b, 0x4d }}

class NS_NO_VTABLE NS_SCRIPTABLE nsILoginCookieFetch : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ILOGINCOOKIEFETCH_IID)

  /* void SetDocument (in nsIDOMDocument doc, in AUTF8String url, in AUTF8String userName, in AUTF8String password); */
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc, const nsACString & url, const nsACString & userName, const nsACString & password) = 0;

  /* AUTF8String GetLoginCookie (); */
  NS_SCRIPTABLE NS_IMETHOD GetLoginCookie(nsACString & _retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsILoginCookieFetch, NS_ILOGINCOOKIEFETCH_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSILOGINCOOKIEFETCH \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc, const nsACString & url, const nsACString & userName, const nsACString & password); \
  NS_SCRIPTABLE NS_IMETHOD GetLoginCookie(nsACString & _retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSILOGINCOOKIEFETCH(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc, const nsACString & url, const nsACString & userName, const nsACString & password) { return _to SetDocument(doc, url, userName, password); } \
  NS_SCRIPTABLE NS_IMETHOD GetLoginCookie(nsACString & _retval NS_OUTPARAM) { return _to GetLoginCookie(_retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSILOGINCOOKIEFETCH(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc, const nsACString & url, const nsACString & userName, const nsACString & password) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetDocument(doc, url, userName, password); } \
  NS_SCRIPTABLE NS_IMETHOD GetLoginCookie(nsACString & _retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLoginCookie(_retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsLoginCookieFetch : public nsILoginCookieFetch
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSILOGINCOOKIEFETCH

  nsLoginCookieFetch();

private:
  ~nsLoginCookieFetch();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsLoginCookieFetch, nsILoginCookieFetch)

nsLoginCookieFetch::nsLoginCookieFetch()
{
  /* member initializers and constructor code */
}

nsLoginCookieFetch::~nsLoginCookieFetch()
{
  /* destructor code */
}

/* void SetDocument (in nsIDOMDocument doc, in AUTF8String url, in AUTF8String userName, in AUTF8String password); */
NS_IMETHODIMP nsLoginCookieFetch::SetDocument(nsIDOMDocument *doc, const nsACString & url, const nsACString & userName, const nsACString & password)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AUTF8String GetLoginCookie (); */
NS_IMETHODIMP nsLoginCookieFetch::GetLoginCookie(nsACString & _retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsILoginCookieFetch_h__ */
