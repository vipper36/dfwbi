/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIXpathUtil.idl
 */

#ifndef __gen_nsIXpathUtil_h__
#define __gen_nsIXpathUtil_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMDocument; /* forward declaration */

class nsIDOMNode; /* forward declaration */

class nsISupportsArray; /* forward declaration */


/* starting interface:    nsIXpathUtil */
#define NS_IXPATHUTIL_IID_STR "bd245bf5-2b01-4c41-a76b-573719a72d5e"

#define NS_IXPATHUTIL_IID \
  {0xbd245bf5, 0x2b01, 0x4c41, \
    { 0xa7, 0x6b, 0x57, 0x37, 0x19, 0xa7, 0x2d, 0x5e }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIXpathUtil : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IXPATHUTIL_IID)

  /* void SetDocument (in nsIDOMDocument doc); */
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc) = 0;

  /* AUTF8String GetXpath (in nsIDOMNode node, in short type); */
  NS_SCRIPTABLE NS_IMETHOD GetXpath(nsIDOMNode *node, PRInt16 type, nsACString & _retval NS_OUTPARAM) = 0;

  /* void GetNodes (in AUTF8String xpath, out nsISupportsArray nodes); */
  NS_SCRIPTABLE NS_IMETHOD GetNodes(const nsACString & xpath, nsISupportsArray **nodes NS_OUTPARAM) = 0;

  /* void GetSubNodes (in nsIDOMNode node, in AUTF8String xpath, out nsISupportsArray nodes); */
  NS_SCRIPTABLE NS_IMETHOD GetSubNodes(nsIDOMNode *node, const nsACString & xpath, nsISupportsArray **nodes NS_OUTPARAM) = 0;

  /* AUTF8String GetSubpath (in nsIDOMNode par, in nsIDOMNode sub); */
  NS_SCRIPTABLE NS_IMETHOD GetSubpath(nsIDOMNode *par, nsIDOMNode *sub, nsACString & _retval NS_OUTPARAM) = 0;

  /* void AddAttName (in AUTF8String name); */
  NS_SCRIPTABLE NS_IMETHOD AddAttName(const nsACString & name) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIXpathUtil, NS_IXPATHUTIL_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIXPATHUTIL \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc); \
  NS_SCRIPTABLE NS_IMETHOD GetXpath(nsIDOMNode *node, PRInt16 type, nsACString & _retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetNodes(const nsACString & xpath, nsISupportsArray **nodes NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetSubNodes(nsIDOMNode *node, const nsACString & xpath, nsISupportsArray **nodes NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetSubpath(nsIDOMNode *par, nsIDOMNode *sub, nsACString & _retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD AddAttName(const nsACString & name); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIXPATHUTIL(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc) { return _to SetDocument(doc); } \
  NS_SCRIPTABLE NS_IMETHOD GetXpath(nsIDOMNode *node, PRInt16 type, nsACString & _retval NS_OUTPARAM) { return _to GetXpath(node, type, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetNodes(const nsACString & xpath, nsISupportsArray **nodes NS_OUTPARAM) { return _to GetNodes(xpath, nodes); } \
  NS_SCRIPTABLE NS_IMETHOD GetSubNodes(nsIDOMNode *node, const nsACString & xpath, nsISupportsArray **nodes NS_OUTPARAM) { return _to GetSubNodes(node, xpath, nodes); } \
  NS_SCRIPTABLE NS_IMETHOD GetSubpath(nsIDOMNode *par, nsIDOMNode *sub, nsACString & _retval NS_OUTPARAM) { return _to GetSubpath(par, sub, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD AddAttName(const nsACString & name) { return _to AddAttName(name); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIXPATHUTIL(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetDocument(doc); } \
  NS_SCRIPTABLE NS_IMETHOD GetXpath(nsIDOMNode *node, PRInt16 type, nsACString & _retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetXpath(node, type, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetNodes(const nsACString & xpath, nsISupportsArray **nodes NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNodes(xpath, nodes); } \
  NS_SCRIPTABLE NS_IMETHOD GetSubNodes(nsIDOMNode *node, const nsACString & xpath, nsISupportsArray **nodes NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSubNodes(node, xpath, nodes); } \
  NS_SCRIPTABLE NS_IMETHOD GetSubpath(nsIDOMNode *par, nsIDOMNode *sub, nsACString & _retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSubpath(par, sub, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD AddAttName(const nsACString & name) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddAttName(name); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsXpathUtil : public nsIXpathUtil
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIXPATHUTIL

  nsXpathUtil();

private:
  ~nsXpathUtil();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsXpathUtil, nsIXpathUtil)

nsXpathUtil::nsXpathUtil()
{
  /* member initializers and constructor code */
}

nsXpathUtil::~nsXpathUtil()
{
  /* destructor code */
}

/* void SetDocument (in nsIDOMDocument doc); */
NS_IMETHODIMP nsXpathUtil::SetDocument(nsIDOMDocument *doc)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AUTF8String GetXpath (in nsIDOMNode node, in short type); */
NS_IMETHODIMP nsXpathUtil::GetXpath(nsIDOMNode *node, PRInt16 type, nsACString & _retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetNodes (in AUTF8String xpath, out nsISupportsArray nodes); */
NS_IMETHODIMP nsXpathUtil::GetNodes(const nsACString & xpath, nsISupportsArray **nodes NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetSubNodes (in nsIDOMNode node, in AUTF8String xpath, out nsISupportsArray nodes); */
NS_IMETHODIMP nsXpathUtil::GetSubNodes(nsIDOMNode *node, const nsACString & xpath, nsISupportsArray **nodes NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AUTF8String GetSubpath (in nsIDOMNode par, in nsIDOMNode sub); */
NS_IMETHODIMP nsXpathUtil::GetSubpath(nsIDOMNode *par, nsIDOMNode *sub, nsACString & _retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void AddAttName (in AUTF8String name); */
NS_IMETHODIMP nsXpathUtil::AddAttName(const nsACString & name)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIXpathUtil_h__ */
