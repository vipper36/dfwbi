#include "nsWrapperSave.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "mozIStorageConnection.h"
#include "mozIStorageStatement.h"
#include "nsISupportsArray.h"
#include "nsNetUtil.h"
#include "nsIDOM3Node.h"
#include "property.h"
#include <string>
#include <stack>
#include <set>
#include <sstream>
NS_IMPL_ISUPPORTS1(nsWrapperSave, nsIWrapperSave)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsWrapperSave)

static nsModuleComponentInfo components[] =
{
     {
	  NS_WRAPPERSAVE_CLASSNAME,
	  NS_WRAPPERSAVE_CID,
	  NS_WRAPPERSAVE_CONTRACTID,
	  nsWrapperSaveConstructor,
     }
};

NS_IMPL_NSGETMODULE("nsWrapperSaveModule", components)

nsWrapperSave::nsWrapperSave()
:file(nsnull)
{
     nsresult rv;
     mozSs=do_CreateInstance("@mozilla.org/storage/service;1", &rv);
     if (NS_FAILED(rv))
     {
 	  LOG<<"Get  mozIStorageService  Error:"<<rv<<"\n";
     }
}

nsWrapperSave::~nsWrapperSave()
{
     /* destructor code */
}
/* AUTF8String GetWrapper (in long wrapId, in long ver); */
NS_IMETHODIMP nsWrapperSave::GetWrapper(PRInt32 wrapId, PRInt32 ver, nsACString & _retval )
{
     if(file==nsnull)
     {
	 nsCString mLocation("/tmp/wrap.sqlite");
	 nsresult rv = NS_NewLocalFile(NS_ConvertUTF8toUTF16(mLocation), PR_FALSE,
				       getter_AddRefs(file));
	 if (NS_FAILED(rv))
	      return rv; 
     }
     nsCOMPtr<mozIStorageConnection> conn;
     nsresult rv=mozSs->OpenDatabase(file,getter_AddRefs(conn));
     if (NS_FAILED(rv))
	  return rv;
     PRBool connReady=false;
     conn->GetConnectionReady(&connReady);
     if(connReady)
     {
	  PRBool tExist;
	  conn->TableExists(nsCString("WRAPPER"),&tExist);
	  if(tExist)
	  {
	       std::stringstream ss;
	       nsCOMPtr<mozIStorageStatement> state;
	       nsCString sSql("select wrapper from WRAPPER where wrap_id=");
	       ss<<wrapId;
	       sSql.Append(ss.str().c_str());
	       sSql.Append(" and wrap_ver=");
	       ss.str("");
	       ss<<ver;
	       sSql.Append(ss.str().c_str());
	       LOG<<sSql.get()<<"\n";
	       conn->CreateStatement(sSql,getter_AddRefs(state));
	       
	       nsCString wrapper;
	       PRBool exec=true;
	       state->ExecuteStep(&exec);
	       if(exec)
	       {
		    state->GetUTF8String(0,wrapper);
		    _retval=wrapper;
	       }
	       
	  }
     }
     conn->Close();
     return NS_OK;
}

/* void SaveWrapper (in long wrapId, in long ver, in AUTF8String wrapper); */
NS_IMETHODIMP nsWrapperSave::SaveWrapper(PRInt32 wrapId, PRInt32 ver, const nsACString & wrapper)
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
	  conn->TableExists(nsCString("WRAPPER"),&tExist);
	  if(tExist)
	  {
	       std::stringstream ss;
	       nsCString tmpWrap(wrapper);
	       
	       nsCOMPtr<mozIStorageStatement> contSql;
	       nsCString hSql("select count(*) from WRAPPER where wrap_id=");
	       ss<<wrapId;
	       hSql.Append(ss.str().c_str());
	       ss.str("");
	       LOG<<hSql.get()<<"\n";
	       conn->CreateStatement(hSql,getter_AddRefs(contSql));
	       PRBool exec=true;
	       contSql->ExecuteStep(&exec);
	       PRInt32 count=0;
	       if(exec)
	       {
		    contSql->GetInt32(0,&count);
	       }
	       if(count==0)
	       {
		    nsCOMPtr<mozIStorageStatement> insSql;
		    nsCString sSql("insert into  CHL_LIST(wrap_id,wrap_ver,wrapper) values(");
		    ss<<wrapId;
		    hSql.Append(ss.str().c_str());
		    sSql.Append(",");
		    ss.str("");

		    ss<<ver;
		    hSql.Append(ss.str().c_str());
		    sSql.Append(",'");
		    ss.str("");

		    sSql.Append(wrapper);
		    sSql.Append("'");
		    LOG<<sSql.get()<<"\n";
		    conn->CreateStatement(sSql,getter_AddRefs(insSql));
		    insSql->Execute();
	       }else
	       {
		    nsCOMPtr<mozIStorageStatement> upSql;
		    nsCString sSql("update CHL_LIST set wrap_ver=");
		    ss<<ver;
		    hSql.Append(ss.str().c_str());
		    ss.str("");
		    sSql.Append(",wrapper='");
		    sSql.Append(wrapper);
		    sSql.Append("' where wrap_id=");

		    ss<<wrapId;
		    hSql.Append(ss.str().c_str());
		    ss.str("");

		    LOG<<sSql.get()<<"\n";
		    conn->CreateStatement(sSql,getter_AddRefs(upSql));
		    upSql->Execute();
	       }
	  }
     }
     conn->Close();
     return NS_OK;
}
/* void SetLoaction (in AUTF8String loc); */
NS_IMETHODIMP nsWrapperSave::SetLoaction(const nsACString & loc)
{
     nsCString mLocation(loc);
     nsresult rv = NS_NewLocalFile(NS_ConvertUTF8toUTF16(mLocation), PR_FALSE,
				   getter_AddRefs(file));
     return rv;
}
