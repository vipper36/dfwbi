/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIXSLTFetcher.idl
 */

#ifndef __gen_nsIXSLTFetcher_h__
#define __gen_nsIXSLTFetcher_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMDocument; /* forward declaration */


/* starting interface:    nsIXSLTFetcher */
#define NS_IXSLTFETCHER_IID_STR "3ec69b5a-4af9-4d09-8972-ce722d45d82a"

#define NS_IXSLTFETCHER_IID \
  {0x3ec69b5a, 0x4af9, 0x4d09, \
    { 0x89, 0x72, 0xce, 0x72, 0x2d, 0x45, 0xd8, 0x2a }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIXSLTFetcher : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IXSLTFETCHER_IID)

  /* void OpenXsltFile (in AUTF8String name); */
  NS_SCRIPTABLE NS_IMETHOD OpenXsltFile(const nsACString & name) = 0;

  /* void SetXsltDocStr (in AUTF8String content); */
  NS_SCRIPTABLE NS_IMETHOD SetXsltDocStr(const nsACString & content) = 0;

  /* void SetDocument (in nsIDOMDocument doc); */
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc) = 0;

  /* AUTF8String GetResultXML (); */
  NS_SCRIPTABLE NS_IMETHOD GetResultXML(nsACString & _retval NS_OUTPARAM) = 0;

  /* AUTF8String GetXsltVar (in AUTF8String name); */
  NS_SCRIPTABLE NS_IMETHOD GetXsltVar(const nsACString & name, nsACString & _retval NS_OUTPARAM) = 0;

  /* void SetXsltVar (in AUTF8String name, in AUTF8String value); */
  NS_SCRIPTABLE NS_IMETHOD SetXsltVar(const nsACString & name, const nsACString & value) = 0;

  /* AUTF8String GetXsltDocStr (); */
  NS_SCRIPTABLE NS_IMETHOD GetXsltDocStr(nsACString & _retval NS_OUTPARAM) = 0;

  /* unsigned long GetVarCount (); */
  NS_SCRIPTABLE NS_IMETHOD GetVarCount(PRUint32 *_retval NS_OUTPARAM) = 0;

  /* void GetVarByIndex (in long index, out AUTF8String name, out AUTF8String value); */
  NS_SCRIPTABLE NS_IMETHOD GetVarByIndex(PRInt32 index, nsACString & name NS_OUTPARAM, nsACString & value NS_OUTPARAM) = 0;

  /* void SetXsltParam (in AUTF8String name, in AUTF8String value); */
  NS_SCRIPTABLE NS_IMETHOD SetXsltParam(const nsACString & name, const nsACString & value) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIXSLTFetcher, NS_IXSLTFETCHER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIXSLTFETCHER \
  NS_SCRIPTABLE NS_IMETHOD OpenXsltFile(const nsACString & name); \
  NS_SCRIPTABLE NS_IMETHOD SetXsltDocStr(const nsACString & content); \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc); \
  NS_SCRIPTABLE NS_IMETHOD GetResultXML(nsACString & _retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetXsltVar(const nsACString & name, nsACString & _retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD SetXsltVar(const nsACString & name, const nsACString & value); \
  NS_SCRIPTABLE NS_IMETHOD GetXsltDocStr(nsACString & _retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetVarCount(PRUint32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetVarByIndex(PRInt32 index, nsACString & name NS_OUTPARAM, nsACString & value NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD SetXsltParam(const nsACString & name, const nsACString & value); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIXSLTFETCHER(_to) \
  NS_SCRIPTABLE NS_IMETHOD OpenXsltFile(const nsACString & name) { return _to OpenXsltFile(name); } \
  NS_SCRIPTABLE NS_IMETHOD SetXsltDocStr(const nsACString & content) { return _to SetXsltDocStr(content); } \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc) { return _to SetDocument(doc); } \
  NS_SCRIPTABLE NS_IMETHOD GetResultXML(nsACString & _retval NS_OUTPARAM) { return _to GetResultXML(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetXsltVar(const nsACString & name, nsACString & _retval NS_OUTPARAM) { return _to GetXsltVar(name, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetXsltVar(const nsACString & name, const nsACString & value) { return _to SetXsltVar(name, value); } \
  NS_SCRIPTABLE NS_IMETHOD GetXsltDocStr(nsACString & _retval NS_OUTPARAM) { return _to GetXsltDocStr(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetVarCount(PRUint32 *_retval NS_OUTPARAM) { return _to GetVarCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetVarByIndex(PRInt32 index, nsACString & name NS_OUTPARAM, nsACString & value NS_OUTPARAM) { return _to GetVarByIndex(index, name, value); } \
  NS_SCRIPTABLE NS_IMETHOD SetXsltParam(const nsACString & name, const nsACString & value) { return _to SetXsltParam(name, value); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIXSLTFETCHER(_to) \
  NS_SCRIPTABLE NS_IMETHOD OpenXsltFile(const nsACString & name) { return !_to ? NS_ERROR_NULL_POINTER : _to->OpenXsltFile(name); } \
  NS_SCRIPTABLE NS_IMETHOD SetXsltDocStr(const nsACString & content) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetXsltDocStr(content); } \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetDocument(doc); } \
  NS_SCRIPTABLE NS_IMETHOD GetResultXML(nsACString & _retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetResultXML(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetXsltVar(const nsACString & name, nsACString & _retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetXsltVar(name, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetXsltVar(const nsACString & name, const nsACString & value) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetXsltVar(name, value); } \
  NS_SCRIPTABLE NS_IMETHOD GetXsltDocStr(nsACString & _retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetXsltDocStr(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetVarCount(PRUint32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetVarCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetVarByIndex(PRInt32 index, nsACString & name NS_OUTPARAM, nsACString & value NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetVarByIndex(index, name, value); } \
  NS_SCRIPTABLE NS_IMETHOD SetXsltParam(const nsACString & name, const nsACString & value) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetXsltParam(name, value); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsXSLTFetcher : public nsIXSLTFetcher
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIXSLTFETCHER

  nsXSLTFetcher();

private:
  ~nsXSLTFetcher();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsXSLTFetcher, nsIXSLTFetcher)

nsXSLTFetcher::nsXSLTFetcher()
{
  /* member initializers and constructor code */
}

nsXSLTFetcher::~nsXSLTFetcher()
{
  /* destructor code */
}

/* void OpenXsltFile (in AUTF8String name); */
NS_IMETHODIMP nsXSLTFetcher::OpenXsltFile(const nsACString & name)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetXsltDocStr (in AUTF8String content); */
NS_IMETHODIMP nsXSLTFetcher::SetXsltDocStr(const nsACString & content)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetDocument (in nsIDOMDocument doc); */
NS_IMETHODIMP nsXSLTFetcher::SetDocument(nsIDOMDocument *doc)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AUTF8String GetResultXML (); */
NS_IMETHODIMP nsXSLTFetcher::GetResultXML(nsACString & _retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AUTF8String GetXsltVar (in AUTF8String name); */
NS_IMETHODIMP nsXSLTFetcher::GetXsltVar(const nsACString & name, nsACString & _retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetXsltVar (in AUTF8String name, in AUTF8String value); */
NS_IMETHODIMP nsXSLTFetcher::SetXsltVar(const nsACString & name, const nsACString & value)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AUTF8String GetXsltDocStr (); */
NS_IMETHODIMP nsXSLTFetcher::GetXsltDocStr(nsACString & _retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* unsigned long GetVarCount (); */
NS_IMETHODIMP nsXSLTFetcher::GetVarCount(PRUint32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetVarByIndex (in long index, out AUTF8String name, out AUTF8String value); */
NS_IMETHODIMP nsXSLTFetcher::GetVarByIndex(PRInt32 index, nsACString & name NS_OUTPARAM, nsACString & value NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetXsltParam (in AUTF8String name, in AUTF8String value); */
NS_IMETHODIMP nsXSLTFetcher::SetXsltParam(const nsACString & name, const nsACString & value)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIXSLTFetcher_h__ */
