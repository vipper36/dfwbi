/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIAttDim.idl
 */

#ifndef __gen_nsIAttDim_h__
#define __gen_nsIAttDim_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIAttDim */
#define NS_IATTDIM_IID_STR "e2a8f8eb-eb4f-4f47-8799-f1d2fb706a9e"

#define NS_IATTDIM_IID \
  {0xe2a8f8eb, 0xeb4f, 0x4f47, \
    { 0x87, 0x99, 0xf1, 0xd2, 0xfb, 0x70, 0x6a, 0x9e }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIAttDim : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IATTDIM_IID)

  /* long GetCount (); */
  NS_SCRIPTABLE NS_IMETHOD GetCount(PRInt32 *_retval NS_OUTPARAM) = 0;

  /* long GetDimId (in AUTF8String desc); */
  NS_SCRIPTABLE NS_IMETHOD GetDimId(const nsACString & desc, PRInt32 *_retval NS_OUTPARAM) = 0;

  /* void AddDim (in long id, in AUTF8String desc); */
  NS_SCRIPTABLE NS_IMETHOD AddDim(PRInt32 id, const nsACString & desc) = 0;

  /* AUTF8String GetDesc (in long id); */
  NS_SCRIPTABLE NS_IMETHOD GetDesc(PRInt32 id, nsACString & _retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIAttDim, NS_IATTDIM_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIATTDIM \
  NS_SCRIPTABLE NS_IMETHOD GetCount(PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetDimId(const nsACString & desc, PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD AddDim(PRInt32 id, const nsACString & desc); \
  NS_SCRIPTABLE NS_IMETHOD GetDesc(PRInt32 id, nsACString & _retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIATTDIM(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetCount(PRInt32 *_retval NS_OUTPARAM) { return _to GetCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDimId(const nsACString & desc, PRInt32 *_retval NS_OUTPARAM) { return _to GetDimId(desc, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD AddDim(PRInt32 id, const nsACString & desc) { return _to AddDim(id, desc); } \
  NS_SCRIPTABLE NS_IMETHOD GetDesc(PRInt32 id, nsACString & _retval NS_OUTPARAM) { return _to GetDesc(id, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIATTDIM(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetCount(PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDimId(const nsACString & desc, PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDimId(desc, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD AddDim(PRInt32 id, const nsACString & desc) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddDim(id, desc); } \
  NS_SCRIPTABLE NS_IMETHOD GetDesc(PRInt32 id, nsACString & _retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDesc(id, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAttDim : public nsIAttDim
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIATTDIM

  nsAttDim();

private:
  ~nsAttDim();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAttDim, nsIAttDim)

nsAttDim::nsAttDim()
{
  /* member initializers and constructor code */
}

nsAttDim::~nsAttDim()
{
  /* destructor code */
}

/* long GetCount (); */
NS_IMETHODIMP nsAttDim::GetCount(PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long GetDimId (in AUTF8String desc); */
NS_IMETHODIMP nsAttDim::GetDimId(const nsACString & desc, PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void AddDim (in long id, in AUTF8String desc); */
NS_IMETHODIMP nsAttDim::AddDim(PRInt32 id, const nsACString & desc)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AUTF8String GetDesc (in long id); */
NS_IMETHODIMP nsAttDim::GetDesc(PRInt32 id, nsACString & _retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIAttDim_h__ */
