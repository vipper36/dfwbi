#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsUrlFileIO.h"
#include "nsIInputStream.h"
#include "nsIOutputStream.h"
#include "nsILineInputStream.h"
#include <iostream>
#include <sstream>
#include "sha1.h"
#include <stdlib.h>
#include "property.h"
NS_IMPL_ISUPPORTS1(nsUrlFileIO, nsIUrlIO)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsUrlFileIO)

static nsModuleComponentInfo components[] =
{
  {
    NS_URLFILEIO_CLASSNAME,
    NS_URLFILEIO_CID,
    NS_URLFILEIO_CONTRACTID,
    nsUrlFileIOConstructor,
  }
};
NS_IMPL_NSGETMODULE("nsUrlFileIOModule", components)



nsUrlFileIO::nsUrlFileIO()
:curr(0)
{
     /* member initializers and constructor code */
}

nsUrlFileIO::~nsUrlFileIO()
{
  /* destructor code */
}

/* void GetURL (out nsIUrlAtt url, in unsigned short stat); */
NS_IMETHODIMP nsUrlFileIO::GetURL(nsIUrlAtt **url, PRUint16 stat)
{
     PRInt32 count=urls.Count();
     LOG<<"count:"<<count<<":"<<curr<<"\n";
     if(curr<count)
     {
	  *url = urls[curr];
	  NS_ADDREF(*url);
	  curr++;
     }else
     {
	  urls.Clear();
	  curr=0;
	  *url=nsnull;
	  return NS_ERROR_FAILURE;
     }
     
     return NS_OK;
}
/* void GetURLByLayer (out nsIUrlAtt url, in unsigned short stat, in unsigned short stlay, in unsigned short endlay); */
NS_IMETHODIMP nsUrlFileIO::GetURLByLayer(nsIUrlAtt **url, PRUint16 stat, PRUint16 stlay, PRUint16 endlay)
{
    return NS_OK;
}
/* void GetURLByChl (out nsIUrlAtt url, in unsigned short stat, in unsigned long chlId); */
NS_IMETHODIMP nsUrlFileIO::GetURLByCol(nsIUrlAtt **url, PRUint16 stat, PRUint32 chlId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
/* void SetLocation (in AUTF8String location); */
NS_IMETHODIMP nsUrlFileIO::SetLocation(const nsACString & location)
{
     nsCString mLocation(location);
     LOG<<mLocation.get()<<"\n";
     nsresult rv = NS_NewLocalFile(NS_ConvertUTF8toUTF16(mLocation), PR_FALSE,
				   getter_AddRefs(file));
     if (NS_FAILED(rv))
	  return rv;
     ReadUrls(0);
     return NS_OK;
}

/* void GetType (out unsigned short type); */
NS_IMETHODIMP nsUrlFileIO::GetType(PRUint16 *type)
{
     *type=LOCAL_FILE;
    return NS_OK;
}

/* void UpdateStat (in nsIUrlAtt url, in unsigned short stat); */
NS_IMETHODIMP nsUrlFileIO::UpdateStat(nsIUrlAtt *url, PRUint16 stat)
{
     return NS_OK;
}


/* void UpdateALL (in nsIUrlAtt url, in unsigned short stat); */
NS_IMETHODIMP nsUrlFileIO::UpdateALL(nsIUrlAtt *url, PRUint16 stat)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void UpdateCol (in nsIUrlAtt url, in AUTF8String colName, in AUTF8String value, in unsigned short stat); */
NS_IMETHODIMP nsUrlFileIO::UpdateCol(nsIUrlAtt *url, const nsACString & colName, const nsACString & value, PRUint16 stat)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}


/* void PutURL (in nsIUrlAtt url); */
NS_IMETHODIMP nsUrlFileIO::PutURL(nsIUrlAtt *url)
{
     nsCOMPtr<nsIOutputStream> outStream;
     nsresult rv=NS_NewLocalFileOutputStream(getter_AddRefs(outStream), file);
     if (NS_FAILED(rv))
     {
	  return NS_ERROR_ILLEGAL_VALUE;
     }
     if(outStream!=nsnull)
     {
	  nsCString tmpUrl;
	  url->GetLink(tmpUrl);
	  tmpUrl.Append("\n");
	  PRUint32 wlen;
	  outStream->Write( tmpUrl.get() , tmpUrl.Length() ,&wlen) ;
	  if(wlen>0)
	       return NS_OK;
	  else
	       return NS_ERROR_ILLEGAL_VALUE;
     }
     return NS_ERROR_ILLEGAL_VALUE;
}
int nsUrlFileIO::ReadUrls(PRInt32 stat)
{
     int lc=0;
     nsCOMPtr<nsIInputStream> mInput;
     nsresult rv=NS_NewLocalFileInputStream(getter_AddRefs(mInput), file);
     if (NS_FAILED(rv))
     {
	  LOG<<"Get stream error:"<<rv<<"\n";
	  return 0;
     }
     
     nsCOMPtr<nsILineInputStream> lstream=do_QueryInterface(mInput);
     nsCString line;
     PRBool ret=PR_FALSE;
     do
     {
	  lstream->ReadLine(line,&ret);
	  nsCOMPtr<nsIUrlAtt> tmp =do_CreateInstance("@nyapc.com/XPCOM/nsUrlAtt;1");
	  tmp->SetLink(line);
	  urls.AppendObject(tmp);
	  lc++;
     }while(ret);
     mInput->Close();
     return lc;
}
/* void GetURLID (in AUTF8String url, out unsigned long id); */
NS_IMETHODIMP nsUrlFileIO::GetURLID(const nsACString & url, PRUint32 *id)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetURLbyID (out nsIUrlAtt url, in long id); */
NS_IMETHODIMP nsUrlFileIO::GetURLbyID(nsIUrlAtt **url, PRInt32 id)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
/* void UpdatebyID (in long id, in AUTF8String colName, in AUTF8String value, in unsigned short stat); */
NS_IMETHODIMP nsUrlFileIO::UpdatebyID(PRInt32 id, const nsACString & colName, const nsACString & value, PRUint16 stat)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
/* void UpdateStatByHash (in AUTF8String hash, in unsigned short stat); */
NS_IMETHODIMP nsUrlFileIO::UpdateStatByHash(const nsACString & hash, PRUint16 stat)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
