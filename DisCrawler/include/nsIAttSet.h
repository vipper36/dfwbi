/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIAttSet.idl
 */

#ifndef __gen_nsIAttSet_h__
#define __gen_nsIAttSet_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIAttVec; /* forward declaration */


/* starting interface:    nsIAttSet */
#define NS_IATTSET_IID_STR "2e4b3c70-d3a8-40be-988d-bee2ac90b9fb"

#define NS_IATTSET_IID \
  {0x2e4b3c70, 0xd3a8, 0x40be, \
    { 0x98, 0x8d, 0xbe, 0xe2, 0xac, 0x90, 0xb9, 0xfb }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIAttSet : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IATTSET_IID)

  /* long GetLength (); */
  NS_SCRIPTABLE NS_IMETHOD GetLength(PRInt32 *_retval NS_OUTPARAM) = 0;

  /* void SetVetor (in long index, in nsIAttVec value); */
  NS_SCRIPTABLE NS_IMETHOD SetVetor(PRInt32 index, nsIAttVec *value) = 0;

  /* void AppendVector (in nsIAttVec value); */
  NS_SCRIPTABLE NS_IMETHOD AppendVector(nsIAttVec *value) = 0;

  /* void AppendSet (in nsIAttSet set); */
  NS_SCRIPTABLE NS_IMETHOD AppendSet(nsIAttSet *set) = 0;

  /* nsIAttVec GetVectorByIndex (in long index); */
  NS_SCRIPTABLE NS_IMETHOD GetVectorByIndex(PRInt32 index, nsIAttVec **_retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIAttSet, NS_IATTSET_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIATTSET \
  NS_SCRIPTABLE NS_IMETHOD GetLength(PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD SetVetor(PRInt32 index, nsIAttVec *value); \
  NS_SCRIPTABLE NS_IMETHOD AppendVector(nsIAttVec *value); \
  NS_SCRIPTABLE NS_IMETHOD AppendSet(nsIAttSet *set); \
  NS_SCRIPTABLE NS_IMETHOD GetVectorByIndex(PRInt32 index, nsIAttVec **_retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIATTSET(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetLength(PRInt32 *_retval NS_OUTPARAM) { return _to GetLength(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetVetor(PRInt32 index, nsIAttVec *value) { return _to SetVetor(index, value); } \
  NS_SCRIPTABLE NS_IMETHOD AppendVector(nsIAttVec *value) { return _to AppendVector(value); } \
  NS_SCRIPTABLE NS_IMETHOD AppendSet(nsIAttSet *set) { return _to AppendSet(set); } \
  NS_SCRIPTABLE NS_IMETHOD GetVectorByIndex(PRInt32 index, nsIAttVec **_retval NS_OUTPARAM) { return _to GetVectorByIndex(index, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIATTSET(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetLength(PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLength(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetVetor(PRInt32 index, nsIAttVec *value) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetVetor(index, value); } \
  NS_SCRIPTABLE NS_IMETHOD AppendVector(nsIAttVec *value) { return !_to ? NS_ERROR_NULL_POINTER : _to->AppendVector(value); } \
  NS_SCRIPTABLE NS_IMETHOD AppendSet(nsIAttSet *set) { return !_to ? NS_ERROR_NULL_POINTER : _to->AppendSet(set); } \
  NS_SCRIPTABLE NS_IMETHOD GetVectorByIndex(PRInt32 index, nsIAttVec **_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetVectorByIndex(index, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAttSet : public nsIAttSet
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIATTSET

  nsAttSet();

private:
  ~nsAttSet();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAttSet, nsIAttSet)

nsAttSet::nsAttSet()
{
  /* member initializers and constructor code */
}

nsAttSet::~nsAttSet()
{
  /* destructor code */
}

/* long GetLength (); */
NS_IMETHODIMP nsAttSet::GetLength(PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetVetor (in long index, in nsIAttVec value); */
NS_IMETHODIMP nsAttSet::SetVetor(PRInt32 index, nsIAttVec *value)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void AppendVector (in nsIAttVec value); */
NS_IMETHODIMP nsAttSet::AppendVector(nsIAttVec *value)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void AppendSet (in nsIAttSet set); */
NS_IMETHODIMP nsAttSet::AppendSet(nsIAttSet *set)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAttVec GetVectorByIndex (in long index); */
NS_IMETHODIMP nsAttSet::GetVectorByIndex(PRInt32 index, nsIAttVec **_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIAttSet_h__ */
