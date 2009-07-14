/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIIndexDoc.idl
 */

#ifndef __gen_nsIIndexDoc_h__
#define __gen_nsIIndexDoc_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIUrlAtt; /* forward declaration */


/* starting interface:    nsIIndexDoc */
#define NS_IINDEXDOC_IID_STR "03416f9b-5460-4799-8e7f-6673e12246ce"

#define NS_IINDEXDOC_IID \
  {0x03416f9b, 0x5460, 0x4799, \
    { 0x8e, 0x7f, 0x66, 0x73, 0xe1, 0x22, 0x46, 0xce }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIIndexDoc : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IINDEXDOC_IID)

  /* attribute AUTF8String Title; */
  NS_SCRIPTABLE NS_IMETHOD GetTitle(nsACString & aTitle) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetTitle(const nsACString & aTitle) = 0;

  /* attribute AUTF8String PublishDate; */
  NS_SCRIPTABLE NS_IMETHOD GetPublishDate(nsACString & aPublishDate) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetPublishDate(const nsACString & aPublishDate) = 0;

  /* attribute AUTF8String Source; */
  NS_SCRIPTABLE NS_IMETHOD GetSource(nsACString & aSource) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetSource(const nsACString & aSource) = 0;

  /* attribute AUTF8String Author; */
  NS_SCRIPTABLE NS_IMETHOD GetAuthor(nsACString & aAuthor) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetAuthor(const nsACString & aAuthor) = 0;

  /* attribute AUTF8String Content; */
  NS_SCRIPTABLE NS_IMETHOD GetContent(nsACString & aContent) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetContent(const nsACString & aContent) = 0;

  /* attribute AUTF8String Fields; */
  NS_SCRIPTABLE NS_IMETHOD GetFields(nsACString & aFields) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetFields(const nsACString & aFields) = 0;

  /* void SetUrl (in nsIUrlAtt url_attr); */
  NS_SCRIPTABLE NS_IMETHOD SetUrl(nsIUrlAtt *url_attr) = 0;

  /* void GetUrl (out nsIUrlAtt url_attr); */
  NS_SCRIPTABLE NS_IMETHOD GetUrl(nsIUrlAtt **url_attr) = 0;

  /* void AddField (in AUTF8String fieldname, in AUTF8String fieldvalue); */
  NS_SCRIPTABLE NS_IMETHOD AddField(const nsACString & fieldname, const nsACString & fieldvalue) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIIndexDoc, NS_IINDEXDOC_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIINDEXDOC \
  NS_SCRIPTABLE NS_IMETHOD GetTitle(nsACString & aTitle); \
  NS_SCRIPTABLE NS_IMETHOD SetTitle(const nsACString & aTitle); \
  NS_SCRIPTABLE NS_IMETHOD GetPublishDate(nsACString & aPublishDate); \
  NS_SCRIPTABLE NS_IMETHOD SetPublishDate(const nsACString & aPublishDate); \
  NS_SCRIPTABLE NS_IMETHOD GetSource(nsACString & aSource); \
  NS_SCRIPTABLE NS_IMETHOD SetSource(const nsACString & aSource); \
  NS_SCRIPTABLE NS_IMETHOD GetAuthor(nsACString & aAuthor); \
  NS_SCRIPTABLE NS_IMETHOD SetAuthor(const nsACString & aAuthor); \
  NS_SCRIPTABLE NS_IMETHOD GetContent(nsACString & aContent); \
  NS_SCRIPTABLE NS_IMETHOD SetContent(const nsACString & aContent); \
  NS_SCRIPTABLE NS_IMETHOD GetFields(nsACString & aFields); \
  NS_SCRIPTABLE NS_IMETHOD SetFields(const nsACString & aFields); \
  NS_SCRIPTABLE NS_IMETHOD SetUrl(nsIUrlAtt *url_attr); \
  NS_SCRIPTABLE NS_IMETHOD GetUrl(nsIUrlAtt **url_attr); \
  NS_SCRIPTABLE NS_IMETHOD AddField(const nsACString & fieldname, const nsACString & fieldvalue); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIINDEXDOC(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetTitle(nsACString & aTitle) { return _to GetTitle(aTitle); } \
  NS_SCRIPTABLE NS_IMETHOD SetTitle(const nsACString & aTitle) { return _to SetTitle(aTitle); } \
  NS_SCRIPTABLE NS_IMETHOD GetPublishDate(nsACString & aPublishDate) { return _to GetPublishDate(aPublishDate); } \
  NS_SCRIPTABLE NS_IMETHOD SetPublishDate(const nsACString & aPublishDate) { return _to SetPublishDate(aPublishDate); } \
  NS_SCRIPTABLE NS_IMETHOD GetSource(nsACString & aSource) { return _to GetSource(aSource); } \
  NS_SCRIPTABLE NS_IMETHOD SetSource(const nsACString & aSource) { return _to SetSource(aSource); } \
  NS_SCRIPTABLE NS_IMETHOD GetAuthor(nsACString & aAuthor) { return _to GetAuthor(aAuthor); } \
  NS_SCRIPTABLE NS_IMETHOD SetAuthor(const nsACString & aAuthor) { return _to SetAuthor(aAuthor); } \
  NS_SCRIPTABLE NS_IMETHOD GetContent(nsACString & aContent) { return _to GetContent(aContent); } \
  NS_SCRIPTABLE NS_IMETHOD SetContent(const nsACString & aContent) { return _to SetContent(aContent); } \
  NS_SCRIPTABLE NS_IMETHOD GetFields(nsACString & aFields) { return _to GetFields(aFields); } \
  NS_SCRIPTABLE NS_IMETHOD SetFields(const nsACString & aFields) { return _to SetFields(aFields); } \
  NS_SCRIPTABLE NS_IMETHOD SetUrl(nsIUrlAtt *url_attr) { return _to SetUrl(url_attr); } \
  NS_SCRIPTABLE NS_IMETHOD GetUrl(nsIUrlAtt **url_attr) { return _to GetUrl(url_attr); } \
  NS_SCRIPTABLE NS_IMETHOD AddField(const nsACString & fieldname, const nsACString & fieldvalue) { return _to AddField(fieldname, fieldvalue); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIINDEXDOC(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetTitle(nsACString & aTitle) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTitle(aTitle); } \
  NS_SCRIPTABLE NS_IMETHOD SetTitle(const nsACString & aTitle) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetTitle(aTitle); } \
  NS_SCRIPTABLE NS_IMETHOD GetPublishDate(nsACString & aPublishDate) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPublishDate(aPublishDate); } \
  NS_SCRIPTABLE NS_IMETHOD SetPublishDate(const nsACString & aPublishDate) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetPublishDate(aPublishDate); } \
  NS_SCRIPTABLE NS_IMETHOD GetSource(nsACString & aSource) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSource(aSource); } \
  NS_SCRIPTABLE NS_IMETHOD SetSource(const nsACString & aSource) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetSource(aSource); } \
  NS_SCRIPTABLE NS_IMETHOD GetAuthor(nsACString & aAuthor) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAuthor(aAuthor); } \
  NS_SCRIPTABLE NS_IMETHOD SetAuthor(const nsACString & aAuthor) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAuthor(aAuthor); } \
  NS_SCRIPTABLE NS_IMETHOD GetContent(nsACString & aContent) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetContent(aContent); } \
  NS_SCRIPTABLE NS_IMETHOD SetContent(const nsACString & aContent) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetContent(aContent); } \
  NS_SCRIPTABLE NS_IMETHOD GetFields(nsACString & aFields) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFields(aFields); } \
  NS_SCRIPTABLE NS_IMETHOD SetFields(const nsACString & aFields) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFields(aFields); } \
  NS_SCRIPTABLE NS_IMETHOD SetUrl(nsIUrlAtt *url_attr) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetUrl(url_attr); } \
  NS_SCRIPTABLE NS_IMETHOD GetUrl(nsIUrlAtt **url_attr) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUrl(url_attr); } \
  NS_SCRIPTABLE NS_IMETHOD AddField(const nsACString & fieldname, const nsACString & fieldvalue) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddField(fieldname, fieldvalue); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsIndexDoc : public nsIIndexDoc
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIINDEXDOC

  nsIndexDoc();

private:
  ~nsIndexDoc();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsIndexDoc, nsIIndexDoc)

nsIndexDoc::nsIndexDoc()
{
  /* member initializers and constructor code */
}

nsIndexDoc::~nsIndexDoc()
{
  /* destructor code */
}

/* attribute AUTF8String Title; */
NS_IMETHODIMP nsIndexDoc::GetTitle(nsACString & aTitle)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsIndexDoc::SetTitle(const nsACString & aTitle)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String PublishDate; */
NS_IMETHODIMP nsIndexDoc::GetPublishDate(nsACString & aPublishDate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsIndexDoc::SetPublishDate(const nsACString & aPublishDate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String Source; */
NS_IMETHODIMP nsIndexDoc::GetSource(nsACString & aSource)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsIndexDoc::SetSource(const nsACString & aSource)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String Author; */
NS_IMETHODIMP nsIndexDoc::GetAuthor(nsACString & aAuthor)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsIndexDoc::SetAuthor(const nsACString & aAuthor)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String Content; */
NS_IMETHODIMP nsIndexDoc::GetContent(nsACString & aContent)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsIndexDoc::SetContent(const nsACString & aContent)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String Fields; */
NS_IMETHODIMP nsIndexDoc::GetFields(nsACString & aFields)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsIndexDoc::SetFields(const nsACString & aFields)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetUrl (in nsIUrlAtt url_attr); */
NS_IMETHODIMP nsIndexDoc::SetUrl(nsIUrlAtt *url_attr)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetUrl (out nsIUrlAtt url_attr); */
NS_IMETHODIMP nsIndexDoc::GetUrl(nsIUrlAtt **url_attr)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void AddField (in AUTF8String fieldname, in AUTF8String fieldvalue); */
NS_IMETHODIMP nsIndexDoc::AddField(const nsACString & fieldname, const nsACString & fieldvalue)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIIndexDoc_h__ */
