/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIDocSet.idl
 */

#ifndef __gen_nsIDocSet_h__
#define __gen_nsIDocSet_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMDocument; /* forward declaration */


/* starting interface:    nsIDocSet */
#define NS_IDOCSET_IID_STR "b60c7690-9e56-4f32-a9b9-4826fec2521d"

#define NS_IDOCSET_IID \
  {0xb60c7690, 0x9e56, 0x4f32, \
    { 0xa9, 0xb9, 0x48, 0x26, 0xfe, 0xc2, 0x52, 0x1d }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIDocSet : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOCSET_IID)

  /* long GetDocCount (); */
  NS_SCRIPTABLE NS_IMETHOD GetDocCount(PRInt32 *_retval NS_OUTPARAM) = 0;

  /* nsIDOMDocument GetDocByIndex (in long index); */
  NS_SCRIPTABLE NS_IMETHOD GetDocByIndex(PRInt32 index, nsIDOMDocument **_retval NS_OUTPARAM) = 0;

  /* void AddDocument (in nsIDOMDocument doc); */
  NS_SCRIPTABLE NS_IMETHOD AddDocument(nsIDOMDocument *doc) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDocSet, NS_IDOCSET_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOCSET \
  NS_SCRIPTABLE NS_IMETHOD GetDocCount(PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetDocByIndex(PRInt32 index, nsIDOMDocument **_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD AddDocument(nsIDOMDocument *doc); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOCSET(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetDocCount(PRInt32 *_retval NS_OUTPARAM) { return _to GetDocCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDocByIndex(PRInt32 index, nsIDOMDocument **_retval NS_OUTPARAM) { return _to GetDocByIndex(index, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD AddDocument(nsIDOMDocument *doc) { return _to AddDocument(doc); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOCSET(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetDocCount(PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDocCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDocByIndex(PRInt32 index, nsIDOMDocument **_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDocByIndex(index, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD AddDocument(nsIDOMDocument *doc) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddDocument(doc); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDocSet : public nsIDocSet
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOCSET

  nsDocSet();

private:
  ~nsDocSet();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDocSet, nsIDocSet)

nsDocSet::nsDocSet()
{
  /* member initializers and constructor code */
}

nsDocSet::~nsDocSet()
{
  /* destructor code */
}

/* long GetDocCount (); */
NS_IMETHODIMP nsDocSet::GetDocCount(PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIDOMDocument GetDocByIndex (in long index); */
NS_IMETHODIMP nsDocSet::GetDocByIndex(PRInt32 index, nsIDOMDocument **_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void AddDocument (in nsIDOMDocument doc); */
NS_IMETHODIMP nsDocSet::AddDocument(nsIDOMDocument *doc)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDocSet_h__ */
