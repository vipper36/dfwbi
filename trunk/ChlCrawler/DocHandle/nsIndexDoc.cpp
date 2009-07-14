#include "nsIndexDoc.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"

#include <iostream>

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsIndexDoc, nsIIndexDoc)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsIndexDoc)

static nsModuleComponentInfo components[] =
{
     {
          NS_INDEXDOC_CLASSNAME,
          NS_INDEXDOC_CID,
          NS_INDEXDOC_CONTRACTID,
          nsIndexDocConstructor,
     }
};

NS_IMPL_NSGETMODULE("nsIndexDocModule", components)

nsIndexDoc::nsIndexDoc()
{
	/* member initializers and constructor code */
	url = NULL;
}

nsIndexDoc::~nsIndexDoc()
{
  /* destructor code */
}

/* attribute AUTF8String Title; */
NS_IMETHODIMP nsIndexDoc::GetTitle(nsACString & aTitle)
{
	aTitle = title;
	return NS_OK;
}
NS_IMETHODIMP nsIndexDoc::SetTitle(const nsACString & aTitle)
{
	title = aTitle;
	return NS_OK;
}

/* attribute AUTF8String PublishDate; */
NS_IMETHODIMP nsIndexDoc::GetPublishDate(nsACString & aPublishDate)
{
	aPublishDate = date;
	return NS_OK;
}
NS_IMETHODIMP nsIndexDoc::SetPublishDate(const nsACString & aPublishDate)
{
	date = aPublishDate;
	return NS_OK;
}

/* attribute AUTF8String Source; */
NS_IMETHODIMP nsIndexDoc::GetSource(nsACString & aSource)
{
	aSource = source;
	return NS_OK;
}
NS_IMETHODIMP nsIndexDoc::SetSource(const nsACString & aSource)
{
	source = aSource;
	return NS_OK;
}

/* attribute AUTF8String Author; */
NS_IMETHODIMP nsIndexDoc::GetAuthor(nsACString & aAuthor)
{
	aAuthor = author;
	return NS_OK;
}
NS_IMETHODIMP nsIndexDoc::SetAuthor(const nsACString & aAuthor)
{
	author = aAuthor;
	return NS_OK;
}

/* attribute AUTF8String Content; */
NS_IMETHODIMP nsIndexDoc::GetContent(nsACString & aContent)
{
	aContent = content;
	return NS_OK;
}
NS_IMETHODIMP nsIndexDoc::SetContent(const nsACString & aContent)
{
	content = aContent;
	return NS_OK;
}

/* attribute AUTF8String Fields; */
NS_IMETHODIMP nsIndexDoc::GetFields(nsACString & aFields)
{
	aFields = fields;
	return NS_OK;
}
NS_IMETHODIMP nsIndexDoc::SetFields(const nsACString & aFields)
{
	fields = aFields;
	return NS_OK;
}

/* void SetCurUrl (in nsIUrlAtt url_attr); */
NS_IMETHODIMP nsIndexDoc::SetUrl(nsIUrlAtt *url_attr)
{
	url = url_attr;	
	return NS_OK;
}

/* void GetUrl (out nsIUrlAtt url_attr); */
NS_IMETHODIMP nsIndexDoc::GetUrl(nsIUrlAtt **url_attr)
{
	*url_attr = url;
	return NS_OK;
}

/* void AddField (in AUTF8String fieldname, in AUTF8String fieldvalue); */
NS_IMETHODIMP nsIndexDoc::AddField(const nsACString & fieldname, const nsACString & fieldvalue)
{
	if(fieldname.Length()==0) return NS_OK;
	nsCString f("DREFIELD ");
	f.Append(fieldname);
	f.Append("=\"");
	f.Append(fieldvalue);
	f.Append("\"\n");
	fields.Append(f);
	return NS_OK;
}
