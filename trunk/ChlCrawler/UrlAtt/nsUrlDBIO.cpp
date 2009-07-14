#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsUrlDBIO.h"
#include "mozIStorageConnection.h"
#include "mozIStorageStatement.h"
#include <iostream>
#include <sstream>
#include "sha1.h"
#include <stdlib.h>
#include "property.h"
NS_IMPL_ISUPPORTS1(nsUrlDBIO, nsIUrlIO)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsUrlDBIO)

static nsModuleComponentInfo components[] =
{
     {
	  NS_URLDBIO_CLASSNAME,
	  NS_URLDBIO_CID,
	  NS_URLDBIO_CONTRACTID,
	  nsUrlDBIOConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsUrlDBIOModule", components)



nsUrlDBIO::nsUrlDBIO()
:curr(0),
     currStat(0)
{
     /* member initializers and constructor code */
     nsresult rv;
     mozSs=do_CreateInstance("@mozilla.org/storage/service;1", &rv);
     if (NS_FAILED(rv))
     {
 	  LOG<<"Get  mozIStorageService  Error:"<<rv<<"\n";
     }
}

nsUrlDBIO::~nsUrlDBIO()
{
     /* destructor code */
}

/* void GetURL (out nsIUrlAtt url, in unsigned short stat); */
NS_IMETHODIMP nsUrlDBIO::GetURL(nsIUrlAtt **url, PRUint16 stat)
{
     PRInt32 count=urls.Count();
     if(stat==currStat&&curr<count)
     {
	  *url = urls[curr];
	  NS_ADDREF(*url);
	  curr++;
     }
         else
         {
     	  urls.Clear();
     	  curr=0;
	  currStat=stat;
	  int len=ReadbyStat(stat);
	  count=urls.Count();
	  if(curr<count)
	  {
	       *url = urls[curr];
	       NS_ADDREF(*url);
	       curr++;
	  }else
	  {
	       *url=nsnull;
	       return NS_ERROR_FAILURE;
	  }
       }
     
     return NS_OK;
}
/* void GetURLByLayer (out nsIUrlAtt url, in unsigned short stat, in unsigned short stlay, in unsigned short endlay); */
NS_IMETHODIMP nsUrlDBIO::GetURLByLayer(nsIUrlAtt **url, PRUint16 stat, PRUint16 stlay, PRUint16 endlay)
{
     PRInt32 count=urls.Count();
     if(stat==currStat&&curr<count)
     {
	  *url = urls[curr];
	  NS_ADDREF(*url);
	  curr++;
     }else
     {
	  urls.Clear();
	  curr=0;
	  currStat=stat;
	  int len=ReadbyLayer(stat,stlay,endlay);
	  count=urls.Count();
	  if(curr<count)
	  {
	       *url = urls[curr];
	       NS_ADDREF(*url);
	       curr++;
	  }else
	  {
	       *url=nsnull;
	       return NS_ERROR_FAILURE;
	  }
     }
     return NS_OK;
}
/* void GetURLByChl (out nsIUrlAtt url, in unsigned short stat, in unsigned long chlId); */
NS_IMETHODIMP nsUrlDBIO::GetURLByCol(nsIUrlAtt **url, PRUint16 stat, PRUint32 colId)
{
     PRInt32 count=urls.Count();
     if(stat==currStat&&curr<count)
     {
	  *url = urls[curr];
	  NS_ADDREF(*url);
	  curr++;
     }else
     {
	  urls.Clear();
	  curr=0;
	  currStat=stat;
	  int len=ReadbyCol(stat,colId);
	  count=urls.Count();
	  if(curr<count)
	  {
	       *url = urls[curr];
	       NS_ADDREF(*url);
	       curr++;
	  }else
	  {
	       *url=nsnull;
	       return NS_ERROR_FAILURE;
	  }
     }
     return NS_OK;
}
/* void SetLocation (in AUTF8String location); */
NS_IMETHODIMP nsUrlDBIO::SetLocation(const nsACString & location)
{
     nsCString mLocation(location);
     nsresult rv = NS_NewLocalFile(NS_ConvertUTF8toUTF16(mLocation), PR_FALSE,
				   getter_AddRefs(file));
     if (NS_FAILED(rv))
	  return rv;
     return NS_OK;
}

/* void GetType (out unsigned short type); */
NS_IMETHODIMP nsUrlDBIO::GetType(PRUint16 *type)
{
     *type=DATABASE;
     return NS_OK;
}

/* void UpdateStat (in nsIUrlAtt url, in unsigned short stat); */
NS_IMETHODIMP nsUrlDBIO::UpdateStat(nsIUrlAtt *url, PRUint16 stat)
{
     nsCOMPtr<mozIStorageConnection> conn;
     nsresult rv=mozSs->OpenDatabase(file,getter_AddRefs(conn));
     if (NS_FAILED(rv))
	  return rv;
     PRBool connReady=false;
     conn->GetConnectionReady(&connReady);
     if(connReady)
     {
	  PRBool tExist;
	  conn->TableExists(nsCString("URL_LIST"),&tExist);
	  if(tExist)
	  {
	       std::stringstream ss;
	       ss<<stat;
	       PRInt32 id;
	       url->GetId(&id);
	       nsCOMPtr<mozIStorageStatement> statSql;
	       nsCString sSql("update URL_LIST set stat='");
	       sSql.Append(ss.str().c_str());
	       ss.str("");
	       sSql.Append("' where id='");
	       ss.clear();
	       ss<<id;
	       sSql.Append(ss.str().c_str());
	       sSql.Append("'");
	       LOG<<sSql.get()<<"\n";
	       conn->CreateStatement(sSql,getter_AddRefs(statSql));
	       statSql->Execute();
	  }
     }
     conn->Close();
     return NS_OK;
}
/* void UpdateALL (in nsIUrlAtt url, in unsigned short stat); */
NS_IMETHODIMP nsUrlDBIO::UpdateALL(nsIUrlAtt *url, PRUint16 stat)
{
     nsCOMPtr<mozIStorageConnection> conn;
     nsresult rv=mozSs->OpenDatabase(file,getter_AddRefs(conn));
     if (NS_FAILED(rv))
	  return rv;
     PRBool connReady=false;
     conn->GetConnectionReady(&connReady);
     if(connReady)
     {
	  PRBool tExist;
	  conn->TableExists(nsCString("URL_LIST"),&tExist);
	  if(tExist)
	  {
	       PRInt32 colId,nextId,parId;
	       PRUint16 layer;
	       nsCString urlType,conType,conAtt;
	       std::stringstream ss;

	       url->GetLayer(&layer);
	       url->GetUrlType(urlType);
	       url->GetConType(conType);
	       url->GetConAtt(conAtt);
	       url->GetColId(&colId);
	       url->GetNextId(&nextId);
	       url->GetParId(&parId);

	       
	       PRInt32 id;
	       url->GetId(&id);
	       nsCOMPtr<mozIStorageStatement> statSql;
	       nsCString sSql("update URL_LIST set stat='");
	       ss<<stat;
	       sSql.Append(ss.str().c_str());
	       ss.str("");

	       sSql.Append("',layer='");
	       ss<<layer;
	       sSql.Append(ss.str().c_str());
	       ss.str("");
	       
	       sSql.Append("',url_type='");
	       sSql.Append(urlType);

	       sSql.Append("',con_type='");
	       sSql.Append(conType);

	       sSql.Append("',con_att='");
	       sSql.Append(conAtt);

	       sSql.Append("',col_id='");
	       ss<<colId;
	       sSql.Append(ss.str().c_str());
	       ss.str("");

	       sSql.Append("',next_id='");
	       ss<<nextId;
	       sSql.Append(ss.str().c_str());
	       ss.str("");

	       sSql.Append("',par_id='");
	       ss<<parId;
	       sSql.Append(ss.str().c_str());
	       ss.str("");

	       sSql.Append("' where id='");
	       ss.clear();
	       ss<<id;
	       sSql.Append(ss.str().c_str());
	       sSql.Append("'");
	       LOG<<sSql.get()<<"\n";
	       conn->CreateStatement(sSql,getter_AddRefs(statSql));
	       statSql->Execute();
	  }
     }
     conn->Close();
     return NS_OK;
}
/* void UpdateCol (in nsIUrlAtt url, in AUTF8String colName, in AUTF8String value, in unsigned short stat); */
NS_IMETHODIMP nsUrlDBIO::UpdateCol(nsIUrlAtt *url, const nsACString & colName, const nsACString & value, PRUint16 stat)
{
     nsCOMPtr<mozIStorageConnection> conn;
     nsresult rv=mozSs->OpenDatabase(file,getter_AddRefs(conn));
     if (NS_FAILED(rv))
	  return rv;
     PRBool connReady=false;
     conn->GetConnectionReady(&connReady);
     if(connReady)
     {
	  PRBool tExist;
	  conn->TableExists(nsCString("URL_LIST"),&tExist);
	  if(tExist)
	  {
	       std::stringstream ss;
	       ss<<stat;
	       PRInt32 id;
	       url->GetId(&id);
	       nsCOMPtr<mozIStorageStatement> statSql;
	       nsCString sSql("update URL_LIST set stat='");
	       sSql.Append(ss.str().c_str());
	       ss.str("");
	       sSql.Append("',");
	       sSql.Append(colName);
	       sSql.Append("='");
	       sSql.Append(value);
	       sSql.Append("' where id='");
	       ss<<id;
	       sSql.Append(ss.str().c_str());
	       sSql.Append("'");
	       LOG<<sSql.get()<<"\n";
	       conn->CreateStatement(sSql,getter_AddRefs(statSql));
	       statSql->Execute();
	  }
     }
     conn->Close();
     return NS_OK;
}
/* void PutURL (in nsIUrlAtt url); */
NS_IMETHODIMP nsUrlDBIO::PutURL(nsIUrlAtt *url)
{
     nsCOMPtr<mozIStorageConnection> conn;
     nsresult rv=mozSs->OpenDatabase(file,getter_AddRefs(conn));
     if (NS_FAILED(rv))
	  return rv;
     PRBool connReady=false;
     conn->GetConnectionReady(&connReady);
     if(connReady)
     {
	  
	  PRBool tExist;
	  conn->TableExists(nsCString("URL_LIST"),&tExist);
	  if(tExist)
	  {
	       PRInt32 colId,nextId,parId;
	       PRUint16 layer;
	       nsCString hash,link,title,urlType,conType,conAtt;
	       std::stringstream ss;

	       url->GetHash(hash);
	       url->GetLink(link);
	       url->GetTitle(title);
	       url->GetLayer(&layer);
	       url->GetUrlType(urlType);
	       url->GetConType(conType);
	       url->GetConAtt(conAtt);
	       url->GetColId(&colId);
	       url->GetNextId(&nextId);
	       url->GetParId(&parId);

		       
	       nsCOMPtr<mozIStorageStatement> statSql;
	       nsCString sSql("insert into  URL_LIST(hash,link,title,url_type,con_type,con_att,col_id,layer,next_id,par_id,stat,link_count) values('");
	       sSql.Append(hash);
	       sSql.Append("','");
	       sSql.Append(link);
	       sSql.Append("','");
	       sSql.Append(title);
	       sSql.Append("','");
	       sSql.Append(urlType);
	       sSql.Append("','");
	       sSql.Append(conType);
	       sSql.Append("','");
	       sSql.Append(conAtt);
	       sSql.Append("','");
	       ss<<colId;
	       sSql.Append(ss.str().c_str());
	       ss.str("");
	       sSql.Append("','");
	       ss<<layer;
	       sSql.Append(ss.str().c_str());
	       ss.str("");
	       sSql.Append("','");
	       ss<<nextId;
	       sSql.Append(ss.str().c_str());
	       ss.str("");
	       sSql.Append("','");
	       ss<<parId;
	       sSql.Append(ss.str().c_str());
	       ss.str("");
	       sSql.Append("','0',1)");
	       LOG<<sSql.get()<<"\n";
	       conn->CreateStatement(sSql,getter_AddRefs(statSql));
	       statSql->Execute();
	       PRInt32 errCode=0;
	       conn->GetLastError(&errCode);
	       std::cout<<"error:"<<errCode<<std::endl;
	       if(errCode!=0)
	       {
		    nsCOMPtr<mozIStorageStatement> ustatSql;
		    nsCString usSql("update URL_LIST set link_count=link_count+1 where hash='");
		    usSql.Append(hash);
		    usSql.Append("'");
		    LOG<<usSql.get()<<"\n";
		    conn->CreateStatement(usSql,getter_AddRefs(ustatSql));
		    ustatSql->Execute();
	       }
	       
	  }
     }
     conn->Close();
     return NS_OK;
}
int nsUrlDBIO::ReadbyStat(PRInt16 stat)
{
     int lc=0;
     nsCOMPtr<mozIStorageConnection> conn;
     nsresult rv=mozSs->OpenDatabase(file,getter_AddRefs(conn));
     if (NS_FAILED(rv))
	  return rv;
     PRBool connReady=false;
     conn->GetConnectionReady(&connReady);
     if(connReady)
     {
	  PRBool tExist;
	  conn->TableExists(nsCString("URL_LIST"),&tExist);
	  if(tExist)
	  {
	       std::stringstream ss;
	       ss<<stat;
	       nsCOMPtr<mozIStorageStatement> state;
	       nsCString sSql("select id,hash,link,title,url_type,con_type,con_att,col_id,layer,next_id,par_id from URL_LIST where stat='");
	       sSql.Append(ss.str().c_str());
	       ss.str("");
	       sSql.Append("' limit 0,5");
	       LOG<<sSql.get()<<"\n";
	       conn->CreateStatement(sSql,getter_AddRefs(state));
	       lc=ReadUrls(state);
	  }
     }
     conn->Close();
     return lc;
}
int nsUrlDBIO::ReadbyLayer(PRInt16 stat,PRUint16 stlay, PRUint16 endlay)
{
     int lc=0;
     nsCOMPtr<mozIStorageConnection> conn;
     nsresult rv=mozSs->OpenDatabase(file,getter_AddRefs(conn));
     if (NS_FAILED(rv))
	  return rv;
     PRBool connReady=false;
     conn->GetConnectionReady(&connReady);
     if(connReady)
     {
	  PRBool tExist;
	  conn->TableExists(nsCString("URL_LIST"),&tExist);
	  if(tExist)
	  {
	       std::stringstream ss;
	       nsCOMPtr<mozIStorageStatement> state;
	       nsCString sSql("select id,hash,link,title,url_type,con_type,con_att,col_id,layer,next_id,par_id from URL_LIST where stat='");
	       ss<<stat;
	       sSql.Append(ss.str().c_str());
	       ss.str("");
	       sSql.Append("' and layer>='");
	       ss<<stlay;
	       sSql.Append(ss.str().c_str());
	       ss.str("");
	       sSql.Append("' and layer<'");
	       ss<<endlay;
	       sSql.Append(ss.str().c_str());
	       ss.str("");
	       sSql.Append("' limit 0,20");
	       LOG<<sSql.get()<<"\n";
	       conn->CreateStatement(sSql,getter_AddRefs(state));
	       lc=ReadUrls(state);
	  }
     }
     conn->Close();
     return lc;
}
int nsUrlDBIO::ReadbyCol(PRInt16 stat,PRUint16 colId)
{
     int lc=0;
     nsCOMPtr<mozIStorageConnection> conn;
     nsresult rv=mozSs->OpenDatabase(file,getter_AddRefs(conn));
     if (NS_FAILED(rv))
	  return rv;
     PRBool connReady=false;
     conn->GetConnectionReady(&connReady);
     if(connReady)
     {
	  PRBool tExist;
	  conn->TableExists(nsCString("URL_LIST"),&tExist);
	  if(tExist)
	  {
	       std::stringstream ss;
	       nsCOMPtr<mozIStorageStatement> state;
	       nsCString sSql("select id,hash,link,title,url_type,con_type,con_att,col_id,layer,next_id,par_id from URL_LIST where stat='");
	       ss<<stat;
	       sSql.Append(ss.str().c_str());
	       ss.str("");
	       sSql.Append("' and col_id='");
	       ss<<colId;
	       sSql.Append(ss.str().c_str());
	       ss.str("");
	       sSql.Append("' limit 0,20");
	       LOG<<sSql.get()<<"\n";
	       conn->CreateStatement(sSql,getter_AddRefs(state));
	       lc=ReadUrls(state);
	  }
     }
     conn->Close();
     return lc;
}
int nsUrlDBIO::ReadUrls(mozIStorageStatement *state)
{
     int lc=0;
     PRBool exec=true;
     do
     {
	  PRInt32 id,colId,nextId,parId,layer;
	  nsCString hash,link,title,urlType,conType,conAtt;
	  state->ExecuteStep(&exec);
	  if(exec)
	  {
	       state->GetInt32(0,&id);
	       state->GetUTF8String(1,hash);
	       state->GetUTF8String(2,link);
	       state->GetUTF8String(3,title);
	       state->GetUTF8String(4,urlType);
	       state->GetUTF8String(5,conType);
	       state->GetUTF8String(6,conAtt);
	       state->GetInt32(7,&colId);
	       state->GetInt32(8,&layer);
	       state->GetInt32(9,&nextId);
	       state->GetInt32(10,&parId);
	       nsCOMPtr<nsIUrlAtt> tmp =do_CreateInstance("@nyapc.com/XPCOM/nsUrlAtt;1");
	       tmp->SetId(id);
	       tmp->SetHash(hash);
	       tmp->SetLink(link);
	       tmp->SetTitle(title);
	       tmp->SetLayer(PRInt16(layer));
	       tmp->SetUrlType(urlType);
	       tmp->SetConType(conType);
	       tmp->SetConType(conAtt);
	       tmp->SetColId(colId);
	       tmp->SetNextId(nextId);
	       tmp->SetParId(parId);
	       urls.AppendObject(tmp);
	       lc++;
	  }
     }while(exec);
     return lc;
}
/* void GetURLID (in AUTF8String url, out unsigned long id); */
NS_IMETHODIMP nsUrlDBIO::GetURLID(const nsACString & url, PRUint32 *id)
{
     *id=0;
     nsCOMPtr<mozIStorageConnection> conn;
     nsresult rv=mozSs->OpenDatabase(file,getter_AddRefs(conn));
     if (NS_FAILED(rv))
	  return rv;
     PRBool connReady=false;
     conn->GetConnectionReady(&connReady);
     if(connReady)
     {
	  PRBool tExist;
	  conn->TableExists(nsCString("URL_LIST"),&tExist);
	  if(tExist)
	  {
	       nsCString Link(url);
	       SHA1 sha;
	       sha.Reset();
	       
	       sha << Link.get();
	       unsigned message_digest[5];
	       sha.Result(message_digest);
	       std::stringstream ss;
	       for(int i=0;i<5;i++)
	       {
		    ss<<std::hex<<message_digest[i];
	       }
	       nsCOMPtr<mozIStorageStatement> state;
	       nsCString sSql("select id from URL_LIST where hash='");
	       sSql.Append(ss.str().c_str());
	       sSql.Append("'");
	       LOG<<sSql.get()<<"\n";
	       conn->CreateStatement(sSql,getter_AddRefs(state));
	       PRBool exec=false;
	       PRInt32 tmpId;
	       state->ExecuteStep(&exec);
	       if(exec)
	       {
		    state->GetInt32(0,&tmpId);
		    *id=tmpId;
	       }
	  }
     }
     conn->Close();
     return NS_OK;
}

/* void GetURLbyID (out nsIUrlAtt url, in long id); */
NS_IMETHODIMP nsUrlDBIO::GetURLbyID(nsIUrlAtt **url, PRInt32 id)
{
     *url=nsnull;
     nsCOMPtr<mozIStorageConnection> conn;
     nsresult rv=mozSs->OpenDatabase(file,getter_AddRefs(conn));
     if (NS_FAILED(rv))
	  return rv;
     PRBool connReady=false;
     conn->GetConnectionReady(&connReady);
     if(connReady)
     {
	  PRBool tExist;
	  conn->TableExists(nsCString("URL_LIST"),&tExist);
	  if(tExist)
	  {
	       std::stringstream ss;
	       nsCOMPtr<mozIStorageStatement> state;
	       nsCString sSql("select id,hash,link,title,url_type,con_type,con_att,col_id,layer,next_id,par_id from URL_LIST where id='");
	       ss<<id;
	       sSql.Append(ss.str().c_str());
	       ss.str("");
	       sSql.Append("'");
	       LOG<<sSql.get()<<"\n";
	       conn->CreateStatement(sSql,getter_AddRefs(state));
	       PRBool exec=true;
	       PRInt32 id,colId,nextId,parId,layer;
	       nsCString hash,link,title,urlType,conType,conAtt;
	       state->ExecuteStep(&exec);
	       if(exec)
	       {
		    state->GetInt32(0,&id);
		    state->GetUTF8String(1,hash);
		    state->GetUTF8String(2,link);
		    state->GetUTF8String(3,title);
		    state->GetUTF8String(4,urlType);
		    state->GetUTF8String(5,conType);
		    state->GetUTF8String(6,conAtt);
		    state->GetInt32(7,&colId);
		    state->GetInt32(8,&layer);
		    state->GetInt32(9,&nextId);
		    state->GetInt32(10,&parId);
		    nsCOMPtr<nsIUrlAtt> tmp =do_CreateInstance("@nyapc.com/XPCOM/nsUrlAtt;1");
		    tmp->SetId(id);
		    tmp->SetHash(hash);
		    tmp->SetLink(link);
		    tmp->SetTitle(title);
		    tmp->SetLayer(PRInt16(layer));
		    tmp->SetUrlType(urlType);
		    tmp->SetConType(conType);
		    tmp->SetConType(conAtt);
		    tmp->SetColId(colId);
		    tmp->SetNextId(nextId);
		    tmp->SetParId(parId);
		    *url=tmp;
		    NS_ADDREF(*url);
	       }
	  }
     }
     conn->Close();
     return NS_OK;
}
/* void UpdatebyID (in long id, in AUTF8String colName, in AUTF8String value, in unsigned short stat); */
NS_IMETHODIMP nsUrlDBIO::UpdatebyID(PRInt32 id, const nsACString & colName, const nsACString & value, PRUint16 stat)
{
     nsCOMPtr<mozIStorageConnection> conn;
     nsresult rv=mozSs->OpenDatabase(file,getter_AddRefs(conn));
     if (NS_FAILED(rv))
	  return rv;
     PRBool connReady=false;
     conn->GetConnectionReady(&connReady);
     if(connReady)
     {
	  PRBool tExist;
	  conn->TableExists(nsCString("URL_LIST"),&tExist);
	  if(tExist)
	  {
	       std::stringstream ss;
	       nsCOMPtr<mozIStorageStatement> statSql;
	       nsCString sSql("update URL_LIST set stat='");
	       ss<<stat;
	       sSql.Append(ss.str().c_str());
	       ss.str("");
	       sSql.Append("',");
	       sSql.Append(colName);
	       sSql.Append("='");
	       sSql.Append(value);
	       sSql.Append("' where id='");
	       ss<<id;
	       sSql.Append(ss.str().c_str());
	       sSql.Append("'");
	       LOG<<sSql.get()<<"\n";
	       conn->CreateStatement(sSql,getter_AddRefs(statSql));
	       statSql->Execute();
	  }
     }
     conn->Close();
     return NS_OK;
}
/* void UpdateStatByHash (in AUTF8String hash, in unsigned short stat); */
NS_IMETHODIMP nsUrlDBIO::UpdateStatByHash(const nsACString & hash, PRUint16 stat)
{
     nsCOMPtr<mozIStorageConnection> conn;
     nsresult rv=mozSs->OpenDatabase(file,getter_AddRefs(conn));
     if (NS_FAILED(rv))
	  return rv;
     PRBool connReady=false;
     conn->GetConnectionReady(&connReady);
     if(connReady)
     {
	  PRBool tExist;
	  conn->TableExists(nsCString("URL_LIST"),&tExist);
	  if(tExist)
	  {
	       std::stringstream ss;
	       ss<<stat;
	       nsCOMPtr<mozIStorageStatement> statSql;
	       nsCString sSql("update URL_LIST set stat='");
	       sSql.Append(ss.str().c_str());
	       ss.str("");
	       sSql.Append("' where hash='");
	       sSql.Append(hash);
	       sSql.Append("'");
	       LOG<<sSql.get()<<"\n";
	       conn->CreateStatement(sSql,getter_AddRefs(statSql));
	       statSql->Execute();
	  }
     }
     conn->Close();
     return NS_OK;
}
