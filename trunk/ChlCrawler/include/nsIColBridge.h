/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIColBridge.idl
 */

#ifndef __gen_nsIColBridge_h__
#define __gen_nsIColBridge_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIColBridge */
#define NS_ICOLBRIDGE_IID_STR "f709726c-9599-44a2-a9aa-8595e6f6e204"

#define NS_ICOLBRIDGE_IID \
  {0xf709726c, 0x9599, 0x44a2, \
    { 0xa9, 0xaa, 0x85, 0x95, 0xe6, 0xf6, 0xe2, 0x04 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIColBridge : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ICOLBRIDGE_IID)

  /* void SetColSource (in AUTF8String src, in AUTF8String comName); */
  NS_SCRIPTABLE NS_IMETHOD SetColSource(const nsACString & src, const nsACString & comName) = 0;

  /* void SetUrlSource (in AUTF8String src, in AUTF8String comName); */
  NS_SCRIPTABLE NS_IMETHOD SetUrlSource(const nsACString & src, const nsACString & comName) = 0;

  /* void GetColName (in AUTF8String url, out AUTF8String name); */
  NS_SCRIPTABLE NS_IMETHOD GetColName(const nsACString & url, nsACString & name) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIColBridge, NS_ICOLBRIDGE_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSICOLBRIDGE \
  NS_SCRIPTABLE NS_IMETHOD SetColSource(const nsACString & src, const nsACString & comName); \
  NS_SCRIPTABLE NS_IMETHOD SetUrlSource(const nsACString & src, const nsACString & comName); \
  NS_SCRIPTABLE NS_IMETHOD GetColName(const nsACString & url, nsACString & name); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSICOLBRIDGE(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetColSource(const nsACString & src, const nsACString & comName) { return _to SetColSource(src, comName); } \
  NS_SCRIPTABLE NS_IMETHOD SetUrlSource(const nsACString & src, const nsACString & comName) { return _to SetUrlSource(src, comName); } \
  NS_SCRIPTABLE NS_IMETHOD GetColName(const nsACString & url, nsACString & name) { return _to GetColName(url, name); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSICOLBRIDGE(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetColSource(const nsACString & src, const nsACString & comName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetColSource(src, comName); } \
  NS_SCRIPTABLE NS_IMETHOD SetUrlSource(const nsACString & src, const nsACString & comName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetUrlSource(src, comName); } \
  NS_SCRIPTABLE NS_IMETHOD GetColName(const nsACString & url, nsACString & name) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetColName(url, name); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsColBridge : public nsIColBridge
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICOLBRIDGE

  nsColBridge();

private:
  ~nsColBridge();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsColBridge, nsIColBridge)

nsColBridge::nsColBridge()
{
  /* member initializers and constructor code */
}

nsColBridge::~nsColBridge()
{
  /* destructor code */
}

/* void SetColSource (in AUTF8String src, in AUTF8String comName); */
NS_IMETHODIMP nsColBridge::SetColSource(const nsACString & src, const nsACString & comName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetUrlSource (in AUTF8String src, in AUTF8String comName); */
NS_IMETHODIMP nsColBridge::SetUrlSource(const nsACString & src, const nsACString & comName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetColName (in AUTF8String url, out AUTF8String name); */
NS_IMETHODIMP nsColBridge::GetColName(const nsACString & url, nsACString & name)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIColBridge_h__ */
