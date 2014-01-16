/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIRCom.idl
 */

#ifndef __gen_nsIRCom_h__
#define __gen_nsIRCom_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsISupportsArray; /* forward declaration */


/* starting interface:    nsIRCom */
#define NS_IRCOM_IID_STR "cc70ea23-ac24-4622-8372-98dba77231e0"

#define NS_IRCOM_IID \
  {0xcc70ea23, 0xac24, 0x4622, \
    { 0x83, 0x72, 0x98, 0xdb, 0xa7, 0x72, 0x31, 0xe0 }}

class NS_NO_VTABLE nsIRCom : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IRCOM_IID)

  /* long connect (in AUTF8String host, in long port); */
  NS_IMETHOD Connect(const nsACString & host, int32_t port, int32_t *_retval) = 0;

  /* AUTF8String eval (in AUTF8String url); */
  NS_IMETHOD Eval(const nsACString & url, nsACString & _retval) = 0;

  /* void close (); */
  NS_IMETHOD Close(void) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIRCom, NS_IRCOM_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIRCOM \
  NS_IMETHOD Connect(const nsACString & host, int32_t port, int32_t *_retval); \
  NS_IMETHOD Eval(const nsACString & url, nsACString & _retval); \
  NS_IMETHOD Close(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIRCOM(_to) \
  NS_IMETHOD Connect(const nsACString & host, int32_t port, int32_t *_retval) { return _to Connect(host, port, _retval); } \
  NS_IMETHOD Eval(const nsACString & url, nsACString & _retval) { return _to Eval(url, _retval); } \
  NS_IMETHOD Close(void) { return _to Close(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIRCOM(_to) \
  NS_IMETHOD Connect(const nsACString & host, int32_t port, int32_t *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Connect(host, port, _retval); } \
  NS_IMETHOD Eval(const nsACString & url, nsACString & _retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Eval(url, _retval); } \
  NS_IMETHOD Close(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Close(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsRCom : public nsIRCom
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIRCOM

  nsRCom();

private:
  ~nsRCom();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsRCom, nsIRCom)

nsRCom::nsRCom()
{
  /* member initializers and constructor code */
}

nsRCom::~nsRCom()
{
  /* destructor code */
}

/* long connect (in AUTF8String host, in long port); */
NS_IMETHODIMP nsRCom::Connect(const nsACString & host, int32_t port, int32_t *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AUTF8String eval (in AUTF8String url); */
NS_IMETHODIMP nsRCom::Eval(const nsACString & url, nsACString & _retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void close (); */
NS_IMETHODIMP nsRCom::Close()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIRCom_h__ */
