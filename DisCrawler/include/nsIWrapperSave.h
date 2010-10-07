/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIWrapperSave.idl
 */

#ifndef __gen_nsIWrapperSave_h__
#define __gen_nsIWrapperSave_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIWrapperSave */
#define NS_IWRAPPERSAVE_IID_STR "e6c5fa0c-ffc2-49dd-a3b4-670288f0401d"

#define NS_IWRAPPERSAVE_IID \
  {0xe6c5fa0c, 0xffc2, 0x49dd, \
    { 0xa3, 0xb4, 0x67, 0x02, 0x88, 0xf0, 0x40, 0x1d }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIWrapperSave : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IWRAPPERSAVE_IID)

  /* void SetLoaction (in AUTF8String loc); */
  NS_SCRIPTABLE NS_IMETHOD SetLoaction(const nsACString & loc) = 0;

  /* AUTF8String GetWrapper (in long wrapId, in long ver); */
  NS_SCRIPTABLE NS_IMETHOD GetWrapper(PRInt32 wrapId, PRInt32 ver, nsACString & _retval NS_OUTPARAM) = 0;

  /* void SaveWrapper (in long wrapId, in long ver, in AUTF8String wrapper); */
  NS_SCRIPTABLE NS_IMETHOD SaveWrapper(PRInt32 wrapId, PRInt32 ver, const nsACString & wrapper) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIWrapperSave, NS_IWRAPPERSAVE_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIWRAPPERSAVE \
  NS_SCRIPTABLE NS_IMETHOD SetLoaction(const nsACString & loc); \
  NS_SCRIPTABLE NS_IMETHOD GetWrapper(PRInt32 wrapId, PRInt32 ver, nsACString & _retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD SaveWrapper(PRInt32 wrapId, PRInt32 ver, const nsACString & wrapper); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIWRAPPERSAVE(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetLoaction(const nsACString & loc) { return _to SetLoaction(loc); } \
  NS_SCRIPTABLE NS_IMETHOD GetWrapper(PRInt32 wrapId, PRInt32 ver, nsACString & _retval NS_OUTPARAM) { return _to GetWrapper(wrapId, ver, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SaveWrapper(PRInt32 wrapId, PRInt32 ver, const nsACString & wrapper) { return _to SaveWrapper(wrapId, ver, wrapper); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIWRAPPERSAVE(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetLoaction(const nsACString & loc) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetLoaction(loc); } \
  NS_SCRIPTABLE NS_IMETHOD GetWrapper(PRInt32 wrapId, PRInt32 ver, nsACString & _retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWrapper(wrapId, ver, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SaveWrapper(PRInt32 wrapId, PRInt32 ver, const nsACString & wrapper) { return !_to ? NS_ERROR_NULL_POINTER : _to->SaveWrapper(wrapId, ver, wrapper); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsWrapperSave : public nsIWrapperSave
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIWRAPPERSAVE

  nsWrapperSave();

private:
  ~nsWrapperSave();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsWrapperSave, nsIWrapperSave)

nsWrapperSave::nsWrapperSave()
{
  /* member initializers and constructor code */
}

nsWrapperSave::~nsWrapperSave()
{
  /* destructor code */
}

/* void SetLoaction (in AUTF8String loc); */
NS_IMETHODIMP nsWrapperSave::SetLoaction(const nsACString & loc)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AUTF8String GetWrapper (in long wrapId, in long ver); */
NS_IMETHODIMP nsWrapperSave::GetWrapper(PRInt32 wrapId, PRInt32 ver, nsACString & _retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SaveWrapper (in long wrapId, in long ver, in AUTF8String wrapper); */
NS_IMETHODIMP nsWrapperSave::SaveWrapper(PRInt32 wrapId, PRInt32 ver, const nsACString & wrapper)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIWrapperSave_h__ */
