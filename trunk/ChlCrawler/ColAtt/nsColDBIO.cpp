#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsColDBIO.h"
#include "mozIStorageConnection.h"
#include "mozIStorageStatement.h"
#include <iostream>
#include <sstream>
#include "sha1.h"
#include <stdlib.h>
#include "property.h"
NS_IMPL_ISUPPORTS1(nsColDBIO, nsIColIO)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsColDBIO)

static nsModuleComponentInfo components[] =
{
     {
	  NS_COLDBIO_CLASSNAME,
	  NS_COLDBIO_CID,
	  NS_COLDBIO_CONTRACTID,
	  nsColDBIOConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsColDBIOModule", components)



nsColDBIO::nsColDBIO()
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

nsColDBIO::~nsColDBIO()
{
     /* destructor code */
}
/* void GetCol (out nsIColAtt col); */
NS_IMETHODIMP nsColDBIO::GetCol(nsIColAtt **col)
{
     PRInt32 count=cols.Count();
     if(count==0)
     {
	  curr=0;
	  ReadAllCols();
	  count=cols.Count();
     }
     if(curr<count)
     {
	  *col = cols[curr];
	  NS_ADDREF(*col);
	  curr++;
     }else
     {
	  cols.Clear();
	  *col=nsnull;
     }
     return NS_OK;
}

/* void SetLocation (in AUTF8String location); */
NS_IMETHODIMP nsColDBIO::SetLocation(const nsACString & location)
{
     nsCString mLocation(location);
     nsresult rv = NS_NewLocalFile(NS_ConvertUTF8toUTF16(mLocation), PR_FALSE,
				   getter_AddRefs(file));
     if (NS_FAILED(rv))
	  return rv;
     return NS_OK;
}

/* void GetType (out unsigned short type); */
NS_IMETHODIMP nsColDBIO::GetType(PRUint16 *type)
{
     *type=DATABASE;
     return NS_OK;
}

/* void PutCol (in nsIColAtt col); */
NS_IMETHODIMP nsColDBIO::PutCol(nsIColAtt *col)
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
	  conn->TableExists(nsCString("COL_LIST"),&tExist);
	  if(tExist)
	  {
	       PRInt32 chlId;
	       nsCString hash,url,name,alias;
	       std::stringstream ss;
	       
	       col->GetChlId(&chlId);
	       col->GetHash(hash);
	       col->GetUrl(url);
	       col->GetName(name);
	       col->GetAlias(alias);
		       
	       nsCOMPtr<mozIStorageStatement> statSql;
	       nsCString sSql("insert into  COL_LIST(chl_id,hash,url,name,alias,stat) values('");
	       ss<<chlId;
	       sSql.Append(ss.str().c_str());
	       ss.str("");
	       sSql.Append("','");
	       sSql.Append(hash);
	       sSql.Append("','");
	       sSql.Append(url);
	       sSql.Append("','");
	       sSql.Append(name);
	       sSql.Append("','");
	       sSql.Append(alias);
	       sSql.Append("','0')");
	       LOG<<sSql.get()<<"\n";
	       conn->CreateStatement(sSql,getter_AddRefs(statSql));
	       statSql->Execute();
	       PRInt32 errCode=0;
	       conn->GetLastError(&errCode);
	       std::cout<<"error:"<<errCode<<std::endl;
	       if(errCode!=0)
	       {
		    nsCOMPtr<mozIStorageStatement> ustatSql;
		    nsCString usSql("update COL_LIST set stat='0' where hash='");
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

/* void GetColByID (out nsIColAtt col, in long id); */
NS_IMETHODIMP nsColDBIO::GetColByID(nsIColAtt **col, PRInt32 id)
{
      *col=nsnull;
     nsCOMPtr<mozIStorageConnection> conn;
     nsresult rv=mozSs->OpenDatabase(file,getter_AddRefs(conn));
     if (NS_FAILED(rv))
	  return rv;
     PRBool connReady=false;
     conn->GetConnectionReady(&connReady);
     if(connReady)
     {
	  PRBool tExist;
	  conn->TableExists(nsCString("COL_LIST"),&tExist);
	  if(tExist)
	  {
	       std::stringstream ss;
	       nsCOMPtr<mozIStorageStatement> state;
	       nsCString sSql("select id,chl_id,hash,url,name,alias from COL_LIST where id='");
	       ss<<id;
	       sSql.Append(ss.str().c_str());
	       ss.str("");
	       sSql.Append("'");
	       LOG<<sSql.get()<<"\n";
	       conn->CreateStatement(sSql,getter_AddRefs(state));
	       PRBool exec=true;
	       PRInt32 id,chlId;
	       nsCString hash,url,name,alias;
	       state->ExecuteStep(&exec);
	       if(exec)
	       {
		    state->GetInt32(0,&id);
		    state->GetInt32(1,&chlId);
		    state->GetUTF8String(2,hash);
		    state->GetUTF8String(3,url);
		    state->GetUTF8String(4,name);
		    state->GetUTF8String(5,alias);
		    nsCOMPtr<nsIColAtt> tmp =do_CreateInstance("@nyapc.com/XPCOM/nsColAtt;1");
		    tmp->SetId(id);
		    tmp->SetChlId(chlId);
		    tmp->SetHash(hash);
		    tmp->SetUrl(url);
		    tmp->SetName(name);
		    tmp->SetAlias(alias);
		    *col=tmp;
		    NS_ADDREF(*col);
	       }
	  }
     }
     conn->Close();
     return NS_OK;
}

/* void UpdateByID (in long id, in AUTF8String colName, in AUTF8String value); */
NS_IMETHODIMP nsColDBIO::UpdateByID(PRInt32 id, const nsACString & colName, const nsACString & value)
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
	  conn->TableExists(nsCString("COL_LIST"),&tExist);
	  if(tExist)
	  {
	       std::stringstream ss;
	       nsCOMPtr<mozIStorageStatement> statSql;
	       nsCString sSql("update COL_LIST set ");
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
/* void UpdateStat (in nsIColAtt col, in AUTF8String stat); */
NS_IMETHODIMP nsColDBIO::UpdateStat(nsIColAtt *col, PRUint16 stat)
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
	  conn->TableExists(nsCString("COL_LIST"),&tExist);
	  if(tExist)
	  {
	       std::stringstream ss;
	       ss<<stat;
	       PRInt32 id;
	       col->GetId(&id);
	       nsCOMPtr<mozIStorageStatement> statSql;
	       nsCString sSql("update COL_LIST set stat='");
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

/* void GetColByStat (in AUTF8String stat, out nsIColAtt col); */
NS_IMETHODIMP nsColDBIO::GetColByStat(PRUint16 stat, nsIColAtt **col)
{
     
     PRInt32 count=cols.Count();
     if(count==0)
     {
	  curr=0;
	  ReadColsByStat(stat);
	  count=cols.Count();
     }
     if(curr<count)
     {
	  *col = cols[curr];
	  NS_ADDREF(*col);
	  curr++;
     }else
     {
	  cols.Clear();
	  *col=nsnull;
     }
     return NS_OK;
}
/** 
 * @brief Read all colum info.
 * 
 * 
 * @return 
 */
int nsColDBIO::ReadAllCols()
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
	  conn->TableExists(nsCString("COL_LIST"),&tExist);
	  if(tExist)
	  {
	       nsCOMPtr<mozIStorageStatement> state;
	       nsCString sSql("select id,chl_id,hash,url,name,alias from COL_LIST");
	       LOG<<sSql.get()<<"\n";
	       conn->CreateStatement(sSql,getter_AddRefs(state));
	       lc=ReadCols(state);
	  }
     }
     conn->Close();
     return lc;
}
/** 
 * @brief Read the colum info by the stat.
 * 
 * @param stat 
 * 
 * @return 
 */
int nsColDBIO::ReadColsByStat(PRUint16 stat)
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
	  conn->TableExists(nsCString("COL_LIST"),&tExist);
	  if(tExist)
	  {
	       std::stringstream ss;
	       ss<<stat;
	       nsCOMPtr<mozIStorageStatement> state;
	       nsCString sSql("select id,chl_id,hash,url,name,alias from COL_LIST where stat='");
	       sSql.Append(ss.str().c_str());
	       sSql.Append("'");
	       LOG<<sSql.get()<<"\n";
	       conn->CreateStatement(sSql,getter_AddRefs(state));
	       lc=ReadCols(state);
	  }
     }
     conn->Close();
     return lc;
}
int nsColDBIO::ReadCols(mozIStorageStatement *state)
{
     int lc=0;
     PRBool exec=true;
     do
     {
	  PRInt32 id,chlId;
	  nsCString hash,url,name,alias;
	  state->ExecuteStep(&exec);
	  if(exec)
	  {
	       state->GetInt32(0,&id);
	       state->GetInt32(1,&chlId);
	       state->GetUTF8String(2,hash);
	       state->GetUTF8String(3,url);
	       state->GetUTF8String(4,name);
	       state->GetUTF8String(5,alias);
	       nsCOMPtr<nsIColAtt> tmp =do_CreateInstance("@nyapc.com/XPCOM/nsColAtt;1");
	       tmp->SetId(id);
	       tmp->SetChlId(chlId);
	       tmp->SetHash(hash);
	       tmp->SetUrl(url);
	       tmp->SetName(name);
	       tmp->SetAlias(alias);
	       cols.AppendObject(tmp);
	       lc++;
	  }
     }while(exec);
     return lc;
}
