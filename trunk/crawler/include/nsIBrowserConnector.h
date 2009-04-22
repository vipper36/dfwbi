/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIBrowserConnector.idl
 */

#ifndef __gen_nsIBrowserConnector_h__
#define __gen_nsIBrowserConnector_h__


#ifndef __gen_nsIWebBrowser_h__
#include "nsIWebBrowser.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIBrowserConnector */
#define NS_IBROWSERCONNECTOR_IID_STR "34a28308-eb61-4d9c-90c3-50cfa264d6ea"

#define NS_IBROWSERCONNECTOR_IID \
  {0x34a28308, 0xeb61, 0x4d9c, \
    { 0x90, 0xc3, 0x50, 0xcf, 0xa2, 0x64, 0xd6, 0xea }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIBrowserConnector : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IBROWSERCONNECTOR_IID)

  /* void SetBrowser (in nsIWebBrowser browser); */
  NS_SCRIPTABLE NS_IMETHOD SetBrowser(nsIWebBrowser *browser) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIBrowserConnector, NS_IBROWSERCONNECTOR_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIBROWSERCONNECTOR \
  NS_SCRIPTABLE NS_IMETHOD SetBrowser(nsIWebBrowser *browser); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIBROWSERCONNECTOR(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetBrowser(nsIWebBrowser *browser) { return _to SetBrowser(browser); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIBROWSERCONNECTOR(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetBrowser(nsIWebBrowser *browser) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetBrowser(browser); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsBrowserConnector : public nsIBrowserConnector
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIBROWSERCONNECTOR

  nsBrowserConnector();

private:
  ~nsBrowserConnector();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsBrowserConnector, nsIBrowserConnector)

nsBrowserConnector::nsBrowserConnector()
{
  /* member initializers and constructor code */
}

nsBrowserConnector::~nsBrowserConnector()
{
  /* destructor code */
}

/* void SetBrowser (in nsIWebBrowser browser); */
NS_IMETHODIMP nsBrowserConnector::SetBrowser(nsIWebBrowser *browser)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIBrowserConnector_h__ */
