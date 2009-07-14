/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIChlWrapper.idl
 */

#ifndef __gen_nsIChlWrapper_h__
#define __gen_nsIChlWrapper_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsITreeNode; /* forward declaration */

class nsIDOMDocument; /* forward declaration */


/* starting interface:    nsIChlWrapper */
#define NS_ICHLWRAPPER_IID_STR "2366dbed-ebdd-44e7-a08c-40cc1402e156"

#define NS_ICHLWRAPPER_IID \
  {0x2366dbed, 0xebdd, 0x44e7, \
    { 0xa0, 0x8c, 0x40, 0xcc, 0x14, 0x02, 0xe1, 0x56 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIChlWrapper : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ICHLWRAPPER_IID)

  enum { ABS = 1U };

  enum { REL = 2U };

  enum { DUL = 2U };

  /* void SetTree (in nsITreeNode tree); */
  NS_SCRIPTABLE NS_IMETHOD SetTree(nsITreeNode *tree) = 0;

  /* void GetWrapper (out AUTF8String xpath); */
  NS_SCRIPTABLE NS_IMETHOD GetWrapper(nsACString & xpath) = 0;

  /* void SetXType (in unsigned short type); */
  NS_SCRIPTABLE NS_IMETHOD SetXType(PRUint16 type) = 0;

  /* void SetDocument (in nsIDOMDocument tree); */
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *tree) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIChlWrapper, NS_ICHLWRAPPER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSICHLWRAPPER \
  NS_SCRIPTABLE NS_IMETHOD SetTree(nsITreeNode *tree); \
  NS_SCRIPTABLE NS_IMETHOD GetWrapper(nsACString & xpath); \
  NS_SCRIPTABLE NS_IMETHOD SetXType(PRUint16 type); \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *tree); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSICHLWRAPPER(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetTree(nsITreeNode *tree) { return _to SetTree(tree); } \
  NS_SCRIPTABLE NS_IMETHOD GetWrapper(nsACString & xpath) { return _to GetWrapper(xpath); } \
  NS_SCRIPTABLE NS_IMETHOD SetXType(PRUint16 type) { return _to SetXType(type); } \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *tree) { return _to SetDocument(tree); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSICHLWRAPPER(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetTree(nsITreeNode *tree) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetTree(tree); } \
  NS_SCRIPTABLE NS_IMETHOD GetWrapper(nsACString & xpath) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWrapper(xpath); } \
  NS_SCRIPTABLE NS_IMETHOD SetXType(PRUint16 type) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetXType(type); } \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *tree) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetDocument(tree); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsChlWrapper : public nsIChlWrapper
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICHLWRAPPER

  nsChlWrapper();

private:
  ~nsChlWrapper();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsChlWrapper, nsIChlWrapper)

nsChlWrapper::nsChlWrapper()
{
  /* member initializers and constructor code */
}

nsChlWrapper::~nsChlWrapper()
{
  /* destructor code */
}

/* void SetTree (in nsITreeNode tree); */
NS_IMETHODIMP nsChlWrapper::SetTree(nsITreeNode *tree)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetWrapper (out AUTF8String xpath); */
NS_IMETHODIMP nsChlWrapper::GetWrapper(nsACString & xpath)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetXType (in unsigned short type); */
NS_IMETHODIMP nsChlWrapper::SetXType(PRUint16 type)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetDocument (in nsIDOMDocument tree); */
NS_IMETHODIMP nsChlWrapper::SetDocument(nsIDOMDocument *tree)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIChlWrapper_h__ */
