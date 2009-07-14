#include "nsDocHandle.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsIIndexDoc.h"
#include "nsIUrlAtt.h"

#include <iostream>
#include <sstream>
#include "property.h"

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDocHandle, nsIDocHandle)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsDocHandle)

static nsModuleComponentInfo components[] =
{
     {
          NS_DOCHANDLE_CLASSNAME,
          NS_DOCHANDLE_CID,
          NS_DOCHANDLE_CONTRACTID,
          nsDocHandleConstructor,
     }
};

NS_IMPL_NSGETMODULE("nsDocHandleModule", components)

nsDocHandle::nsDocHandle()
{
  /* member initializers and constructor code */
}

nsDocHandle::~nsDocHandle()
{
  /* destructor code */
}

/* void SaveIDX (in nsIIndexDoc idx); */
NS_IMETHODIMP nsDocHandle::SaveIDX(nsIIndexDoc *idx)
{
	nsCString url, title, date, source, author, content, fields;
	PRInt32 id = -1;
	
	idx->GetTitle(title);
	idx->GetPublishDate(date);
	idx->GetSource(source);
	idx->GetAuthor(author);
	idx->GetContent(content);
	idx->GetFields(fields);

	title.StripChars("\'");
	date.StripChars("\'");
	content.StripChars("\'");
	source.StripChars("\'");
	author.StripChars("\'");
	fields.StripChars("\'");

	nsIUrlAtt * url_att = NULL;
	idx->GetUrl(&url_att);
	if(url_att == NULL) return NS_OK;
	url_att->GetLink(url);
	url_att->GetId(&id);
	if(id <= 0) return NS_OK;
	string url_id;
	stringstream ss;
	ss << id;
	ss >> url_id;

	nsresult rv;

	nsCOMPtr<mozIStorageConnection> conn;
	rv=mozSs->OpenDatabase(file,getter_AddRefs(conn));
	if (NS_FAILED(rv))
		return NS_OK;
	PRBool connReady=false;
	conn->GetConnectionReady(&connReady);
	if(connReady)
	{
		PRBool tExist = false;
		//conn->TableExists(nsCString("IDX_CON"),&tExist);
		//if(tExist)
		{
			nsCOMPtr<mozIStorageStatement> state;
			nsCString sql_co("select url_id from IDX_CON where url_id=");
			sql_co.Append(url_id.c_str());
			//LOG<<"sql:"<<sql_co.get()<<"\n";

			conn->CreateStatement(sql_co,getter_AddRefs(state));
			PRBool exec=true;
			state->ExecuteStep(&exec);
			if(exec)
			{
				nsCOMPtr<mozIStorageStatement> state_update;
				nsCString sql("update idx_con set ");
				sql.Append("title='");
				sql.Append(title);
				sql.Append("',pub_time='");
				sql.Append(date);
				sql.Append("',author='");
				sql.Append(author);
				sql.Append("',source='");
				sql.Append(source);
				sql.Append("',content='");
				sql.Append(content);
				sql.Append("',other='");
				sql.Append(fields);
				sql.Append("' where url_id=");
				sql.Append(url_id.c_str());
				LOG<<"sql: "<<sql.get()<<"\n";
				conn->CreateStatement(sql,getter_AddRefs(state_update));
				state_update->Execute();
			}
			else
			{
				nsCOMPtr<mozIStorageStatement> state_insert;
				nsCString sql("insert into idx_con (url_id,title,pub_time,author,source,content,other) values ('");
				sql.Append(url_id.c_str());
				sql.Append("', '");
				sql.Append(title);
				sql.Append("', '");
				sql.Append(date);
				sql.Append("', '");
				sql.Append(author);
				sql.Append("', '");
				sql.Append(source);
				sql.Append("', '");
				sql.Append(content);
				sql.Append("', '");
				sql.Append(fields);
				sql.Append("');");
				LOG<<"sql: "<<sql.get()<<"\n";
				conn->CreateStatement(sql,getter_AddRefs(state_insert));
				state_insert->Execute();
			}
		}
	}

	return NS_OK;
}

/* void SetLocation (in AUTF8String location); */
NS_IMETHODIMP nsDocHandle::SetLocation(const nsACString & location)
{
	mLocation = location;
	init_db();
	return NS_OK;
}

int nsDocHandle::init_db()
{
	if(mozSs == NULL)
	{
		nsresult rv;
		mozSs=do_CreateInstance("@mozilla.org/storage/service;1", &rv);
		if (NS_FAILED(rv))
		{
			ERROR<<"Get  mozIStorageService  Error:"<<rv<<"\n";
			return 0;
		}
		
		if(file == NULL)
		{
			open_db_file();			
		}
	}
}

int nsDocHandle::open_db_file()
{
	nsresult rv;
	rv = NS_NewLocalFile(NS_ConvertUTF8toUTF16(mLocation), 
				PR_FALSE, getter_AddRefs(file));
	if (NS_FAILED(rv))
	{
		LOG<<"Init File  Error:"<<hex<<rv<<"\n";
		return -1;
	}
	return 0;
}
