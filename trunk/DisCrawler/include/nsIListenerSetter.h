/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIListenerSetter.idl
 */

#ifndef __gen_nsIListenerSetter_h__
#define __gen_nsIListenerSetter_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIStatManager; /* forward declaration */


/* starting interface:    nsIListenerSetter */
#define NS_ILISTENERSETTER_IID_STR "7a02b886-e622-4b25-8f87-543c5024c4b0"

#define NS_ILISTENERSETTER_IID \
  {0x7a02b886, 0xe622, 0x4b25, \
    { 0x8f, 0x87, 0x54, 0x3c, 0x50, 0x24, 0xc4, 0xb0 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIListenerSetter : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ILISTENERSETTER_IID)

  /* void SetStatManager (in nsIStatManager man); */
  NS_SCRIPTABLE NS_IMETHOD SetStatManager(nsIStatManager *man) = 0;

  /* void SetId (in long id); */
  NS_SCRIPTABLE NS_IMETHOD SetId(PRInt32 id) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIListenerSetter, NS_ILISTENERSETTER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSILISTENERSETTER \
  NS_SCRIPTABLE NS_IMETHOD SetStatManager(nsIStatManager *man); \
  NS_SCRIPTABLE NS_IMETHOD SetId(PRInt32 id); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSILISTENERSETTER(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetStatManager(nsIStatManager *man) { return _to SetStatManager(man); } \
  NS_SCRIPTABLE NS_IMETHOD SetId(PRInt32 id) { return _to SetId(id); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSILISTENERSETTER(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetStatManager(nsIStatManager *man) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetStatManager(man); } \
  NS_SCRIPTABLE NS_IMETHOD SetId(PRInt32 id) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetId(id); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsListenerSetter : public nsIListenerSetter
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSILISTENERSETTER

  nsListenerSetter();

private:
  ~nsListenerSetter();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsListenerSetter, nsIListenerSetter)

nsListenerSetter::nsListenerSetter()
{
  /* member initializers and constructor code */
}

nsListenerSetter::~nsListenerSetter()
{
  /* destructor code */
}

/* void SetStatManager (in nsIStatManager man); */
NS_IMETHODIMP nsListenerSetter::SetStatManager(nsIStatManager *man)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetId (in long id); */
NS_IMETHODIMP nsListenerSetter::SetId(PRInt32 id)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIListenerSetter_h__ */
