/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIIDXCreator.idl
 */

#ifndef __gen_nsIIDXCreator_h__
#define __gen_nsIIDXCreator_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIIDXCreator */
#define NS_IIDXCREATOR_IID_STR "5d9f8bd2-1dc8-4f09-b9d0-786cb1ad2473"

#define NS_IIDXCREATOR_IID \
  {0x5d9f8bd2, 0x1dc8, 0x4f09, \
    { 0xb9, 0xd0, 0x78, 0x6c, 0xb1, 0xad, 0x24, 0x73 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIIDXCreator : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IIDXCREATOR_IID)

  /* void SetReference (in AUTF8String refer); */
  NS_SCRIPTABLE NS_IMETHOD SetReference(const nsACString & refer) = 0;

  /* void SetTitle (in AUTF8String title); */
  NS_SCRIPTABLE NS_IMETHOD SetTitle(const nsACString & title) = 0;

  /* void SetDate (in AUTF8String date); */
  NS_SCRIPTABLE NS_IMETHOD SetDate(const nsACString & date) = 0;

  /* void SetField (in AUTF8String name, in AUTF8String value); */
  NS_SCRIPTABLE NS_IMETHOD SetField(const nsACString & name, const nsACString & value) = 0;

  /* void SetDB (in AUTF8String db); */
  NS_SCRIPTABLE NS_IMETHOD SetDB(const nsACString & db) = 0;

  /* void SetContent (in AUTF8String htmlContent); */
  NS_SCRIPTABLE NS_IMETHOD SetContent(const nsACString & htmlContent) = 0;

  /* void GetIDX (out AUTF8String idx); */
  NS_SCRIPTABLE NS_IMETHOD GetIDX(nsACString & idx) = 0;

  /* void SendIDX (in AUTF8String url); */
  NS_SCRIPTABLE NS_IMETHOD SendIDX(const nsACString & url) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIIDXCreator, NS_IIDXCREATOR_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIIDXCREATOR \
  NS_SCRIPTABLE NS_IMETHOD SetReference(const nsACString & refer); \
  NS_SCRIPTABLE NS_IMETHOD SetTitle(const nsACString & title); \
  NS_SCRIPTABLE NS_IMETHOD SetDate(const nsACString & date); \
  NS_SCRIPTABLE NS_IMETHOD SetField(const nsACString & name, const nsACString & value); \
  NS_SCRIPTABLE NS_IMETHOD SetDB(const nsACString & db); \
  NS_SCRIPTABLE NS_IMETHOD SetContent(const nsACString & htmlContent); \
  NS_SCRIPTABLE NS_IMETHOD GetIDX(nsACString & idx); \
  NS_SCRIPTABLE NS_IMETHOD SendIDX(const nsACString & url); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIIDXCREATOR(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetReference(const nsACString & refer) { return _to SetReference(refer); } \
  NS_SCRIPTABLE NS_IMETHOD SetTitle(const nsACString & title) { return _to SetTitle(title); } \
  NS_SCRIPTABLE NS_IMETHOD SetDate(const nsACString & date) { return _to SetDate(date); } \
  NS_SCRIPTABLE NS_IMETHOD SetField(const nsACString & name, const nsACString & value) { return _to SetField(name, value); } \
  NS_SCRIPTABLE NS_IMETHOD SetDB(const nsACString & db) { return _to SetDB(db); } \
  NS_SCRIPTABLE NS_IMETHOD SetContent(const nsACString & htmlContent) { return _to SetContent(htmlContent); } \
  NS_SCRIPTABLE NS_IMETHOD GetIDX(nsACString & idx) { return _to GetIDX(idx); } \
  NS_SCRIPTABLE NS_IMETHOD SendIDX(const nsACString & url) { return _to SendIDX(url); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIIDXCREATOR(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetReference(const nsACString & refer) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetReference(refer); } \
  NS_SCRIPTABLE NS_IMETHOD SetTitle(const nsACString & title) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetTitle(title); } \
  NS_SCRIPTABLE NS_IMETHOD SetDate(const nsACString & date) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetDate(date); } \
  NS_SCRIPTABLE NS_IMETHOD SetField(const nsACString & name, const nsACString & value) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetField(name, value); } \
  NS_SCRIPTABLE NS_IMETHOD SetDB(const nsACString & db) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetDB(db); } \
  NS_SCRIPTABLE NS_IMETHOD SetContent(const nsACString & htmlContent) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetContent(htmlContent); } \
  NS_SCRIPTABLE NS_IMETHOD GetIDX(nsACString & idx) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetIDX(idx); } \
  NS_SCRIPTABLE NS_IMETHOD SendIDX(const nsACString & url) { return !_to ? NS_ERROR_NULL_POINTER : _to->SendIDX(url); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsIDXCreator : public nsIIDXCreator
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIIDXCREATOR

  nsIDXCreator();

private:
  ~nsIDXCreator();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsIDXCreator, nsIIDXCreator)

nsIDXCreator::nsIDXCreator()
{
  /* member initializers and constructor code */
}

nsIDXCreator::~nsIDXCreator()
{
  /* destructor code */
}

/* void SetReference (in AUTF8String refer); */
NS_IMETHODIMP nsIDXCreator::SetReference(const nsACString & refer)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetTitle (in AUTF8String title); */
NS_IMETHODIMP nsIDXCreator::SetTitle(const nsACString & title)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetDate (in AUTF8String date); */
NS_IMETHODIMP nsIDXCreator::SetDate(const nsACString & date)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetField (in AUTF8String name, in AUTF8String value); */
NS_IMETHODIMP nsIDXCreator::SetField(const nsACString & name, const nsACString & value)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetDB (in AUTF8String db); */
NS_IMETHODIMP nsIDXCreator::SetDB(const nsACString & db)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetContent (in AUTF8String htmlContent); */
NS_IMETHODIMP nsIDXCreator::SetContent(const nsACString & htmlContent)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetIDX (out AUTF8String idx); */
NS_IMETHODIMP nsIDXCreator::GetIDX(nsACString & idx)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SendIDX (in AUTF8String url); */
NS_IMETHODIMP nsIDXCreator::SendIDX(const nsACString & url)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIIDXCreator_h__ */
