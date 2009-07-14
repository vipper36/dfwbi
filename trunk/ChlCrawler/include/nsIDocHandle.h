/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIDocHandle.idl
 */

#ifndef __gen_nsIDocHandle_h__
#define __gen_nsIDocHandle_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIIndexDoc; /* forward declaration */


/* starting interface:    nsIDocHandle */
#define NS_IDOCHANDLE_IID_STR "952610dc-5157-4dcb-bc13-7f8ec0429e00"

#define NS_IDOCHANDLE_IID \
  {0x952610dc, 0x5157, 0x4dcb, \
    { 0xbc, 0x13, 0x7f, 0x8e, 0xc0, 0x42, 0x9e, 0x00 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIDocHandle : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOCHANDLE_IID)

  /* void SaveIDX (in nsIIndexDoc idx); */
  NS_SCRIPTABLE NS_IMETHOD SaveIDX(nsIIndexDoc *idx) = 0;

  /* void SetLocation (in AUTF8String location); */
  NS_SCRIPTABLE NS_IMETHOD SetLocation(const nsACString & location) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDocHandle, NS_IDOCHANDLE_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOCHANDLE \
  NS_SCRIPTABLE NS_IMETHOD SaveIDX(nsIIndexDoc *idx); \
  NS_SCRIPTABLE NS_IMETHOD SetLocation(const nsACString & location); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOCHANDLE(_to) \
  NS_SCRIPTABLE NS_IMETHOD SaveIDX(nsIIndexDoc *idx) { return _to SaveIDX(idx); } \
  NS_SCRIPTABLE NS_IMETHOD SetLocation(const nsACString & location) { return _to SetLocation(location); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOCHANDLE(_to) \
  NS_SCRIPTABLE NS_IMETHOD SaveIDX(nsIIndexDoc *idx) { return !_to ? NS_ERROR_NULL_POINTER : _to->SaveIDX(idx); } \
  NS_SCRIPTABLE NS_IMETHOD SetLocation(const nsACString & location) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetLocation(location); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDocHandle : public nsIDocHandle
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOCHANDLE

  nsDocHandle();

private:
  ~nsDocHandle();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDocHandle, nsIDocHandle)

nsDocHandle::nsDocHandle()
{
  /* member initializers and constructor code */
}

nsDocHandle::~nsDocHandle()
{
  /* destructor code */
}

/* void SaveIDX (in nsIIndexDoc idx); */
NS_IMETHODIMP nsDocHandle::SaveIDX(nsIIndexDoc *idx)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetLocation (in AUTF8String location); */
NS_IMETHODIMP nsDocHandle::SetLocation(const nsACString & location)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDocHandle_h__ */
