#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsChlDBIO.h"
#include "mozIStorageConnection.h"
#include "mozIStorageStatement.h"
#include <iostream>
#include <sstream>
#include "sha1.h"
#include <stdlib.h>
#include "property.h"
NS_IMPL_ISUPPORTS1(nsChlDBIO, nsIChlIO)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsChlDBIO)

static nsModuleComponentInfo components[] =
{
     {
	  NS_CHLDBIO_CLASSNAME,
	  NS_CHLDBIO_CID,
	  NS_CHLDBIO_CONTRACTID,
	  nsChlDBIOConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsChlDBIOModule", components)



nsChlDBIO::nsChlDBIO()
:curr(0)
{
     /* member initializers and constructor code */
     nsresult rv;
     mozSs=do_CreateInstance("@mozilla.org/storage/service;1", &rv);
     if (NS_FAILED(rv))
     {
 	  LOG<<"Get  mozIStorageService  Error:"<<rv<<"\n";
     }
}

nsChlDBIO::~nsChlDBIO()
{
     /* destructor code */
}
/* void GetChl (out nsIChlAtt col); */
NS_IMETHODIMP nsChlDBIO::GetChl(nsIChlAtt **chl)
{
     PRInt32 count=chls.Count();
     if(curr<count)
     {
	  *chl = chls[curr];
	  NS_ADDREF(*chl);
	  curr++;
     }else
     {
	  chls.Clear();
	  *chl=nsnull;
     }
     return NS_OK;
}

/* void SetLocation (in AUTF8String location); */
NS_IMETHODIMP nsChlDBIO::SetLocation(const nsACString & location)
{
     nsCString mLocation(location);
     nsresult rv = NS_NewLocalFile(NS_ConvertUTF8toUTF16(mLocation), PR_FALSE,
				   getter_AddRefs(file));
     if (NS_FAILED(rv))
	  return rv;
     ReadAllChls();
     return NS_OK;
}

/* void GetType (out unsigned short type); */
NS_IMETHODIMP nsChlDBIO::GetType(PRUint16 *type)
{
     *type=DATABASE;
     return NS_OK;
}

/* void PutChl (in nsIChlAtt chl); */
NS_IMETHODIMP nsChlDBIO::PutChl(nsIChlAtt *chl)
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
	  conn->TableExists(nsCString("CHL_LIST"),&tExist);
	  if(tExist)
	  {
	       nsCString hash,url,name,xpath;
	       std::stringstream ss;

	       chl->GetHash(hash);
	       chl->GetUrl(url);
	       chl->GetName(name);
	       chl->GetXPath(xpath);

		       
	       nsCOMPtr<mozIStorageStatement> statSql;
	       nsCString sSql("insert into  CHL_LIST(hash,url,name,xpath) values('");
	       sSql.Append(hash);
	       sSql.Append("','");
	       sSql.Append(url);
	       sSql.Append("','");
	       sSql.Append(name);
	       sSql.Append("','");
	       sSql.Append(xpath);
	       sSql.Append("')");
	       LOG<<sSql.get()<<"\n";
	       conn->CreateStatement(sSql,getter_AddRefs(statSql));
	       statSql->Execute();
	  }
     }
     conn->Close();
     return NS_OK;
}

/* void GetChlByID (out nsIChlAtt chl, in long id); */
NS_IMETHODIMP nsChlDBIO::GetChlByID(nsIChlAtt **chl, PRInt32 id)
{
     *chl=nsnull;
     nsCOMPtr<mozIStorageConnection> conn;
     nsresult rv=mozSs->OpenDatabase(file,getter_AddRefs(conn));
     if (NS_FAILED(rv))
	  return rv;
     PRBool connReady=false;
     conn->GetConnectionReady(&connReady);
     if(connReady)
     {
	  PRBool tExist;
	  conn->TableExists(nsCString("CHL_LIST"),&tExist);
	  if(tExist)
	  {
	       std::stringstream ss;
	       nsCOMPtr<mozIStorageStatement> state;
	       nsCString sSql("select id,hash,url,name,xpath from CHL_LIST where id='");
	       ss<<id;
	       sSql.Append(ss.str().c_str());
	       ss.str("");
	       sSql.Append("'");
	       LOG<<sSql.get()<<"\n";
	       conn->CreateStatement(sSql,getter_AddRefs(state));
	       PRBool exec=true;
	       PRInt32 id;
	       nsCString hash,url,name,xpath;
	       state->ExecuteStep(&exec);
	       if(exec)
	       {
		    state->GetInt32(0,&id);
		    state->GetUTF8String(1,hash);
		    state->GetUTF8String(2,url);
		    state->GetUTF8String(3,name);
		    state->GetUTF8String(4,xpath);
		    nsCOMPtr<nsIChlAtt> tmp =do_CreateInstance("@nyapc.com/XPCOM/nsChlAtt;1");
		    tmp->SetId(id);
		    tmp->SetHash(hash);
		    tmp->SetUrl(url);
		    tmp->SetName(name);
		    tmp->SetXPath(xpath);
		    *chl=tmp;
		    NS_ADDREF(*chl);
	       }
	  }
     }
     conn->Close();
     return NS_OK;
}

/* void UpdateByID (in long id, in AUTF8String colName, in AUTF8String value); */
NS_IMETHODIMP nsChlDBIO::UpdateByID(PRInt32 id, const nsACString & colName, const nsACString & value)
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
	  conn->TableExists(nsCString("CHL_LIST"),&tExist);
	  if(tExist)
	  {
	       std::stringstream ss;
	       nsCOMPtr<mozIStorageStatement> statSql;
	       nsCString sSql("update CHL_LIST set ");
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
int nsChlDBIO::ReadAllChls()
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
	  conn->TableExists(nsCString("CHL_LIST"),&tExist);
	  if(tExist)
	  {
	       nsCOMPtr<mozIStorageStatement> state;
	       nsCString sSql("select id,hash,url,name,xpath from CHL_LIST");
	       LOG<<sSql.get()<<"\n";
	       conn->CreateStatement(sSql,getter_AddRefs(state));
	       lc=ReadChls(state);
	  }
     }
     conn->Close();
     return lc;
}
int nsChlDBIO::ReadChls(mozIStorageStatement *state)
{
     int lc=0;
     PRBool exec=true;
     do
     {
	  PRInt32 id;
	  nsCString hash,url,name,xpath;
	  state->ExecuteStep(&exec);
	  if(exec)
	  {
	       state->GetInt32(0,&id);
	       state->GetUTF8String(1,hash);
	       state->GetUTF8String(2,url);
	       state->GetUTF8String(3,name);
	       state->GetUTF8String(4,xpath);
	       nsCOMPtr<nsIChlAtt> tmp =do_CreateInstance("@nyapc.com/XPCOM/nsChlAtt;1");
	       tmp->SetId(id);
	       tmp->SetHash(hash);
	       tmp->SetUrl(url);
	       tmp->SetName(name);
	       tmp->SetXPath(xpath);
	       chls.AppendObject(tmp);
	       lc++;
	  }
     }while(exec);
     return lc;
}
