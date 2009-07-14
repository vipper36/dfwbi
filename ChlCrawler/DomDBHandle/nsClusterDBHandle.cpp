#include "nsClusterDBHandle.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "property.h"

#include "nsIUrlIO.h"
#include "nsVoidArray.h"

#include <sstream>
#include <iostream>
#include <list>

using namespace std;

NS_IMPL_ISUPPORTS1(nsClusterDBHandle, nsIClusterDBHandle)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsClusterDBHandle)

static nsModuleComponentInfo components[] ={
    {
        NS_NSCLUSTERDBHANDLE_CLASSNAME,
        NS_NSCLUSTERDBHANDLE_CID,
        NS_NSCLUSTERDBHANDLE_CONTRACTID,
        nsClusterDBHandleConstructor,
    }
};

NS_IMPL_NSGETMODULE("nsClusterDBHandleModule", components)

nsClusterDBHandle::nsClusterDBHandle() {
    /* member initializers and constructor code */
    nsresult rv;
    url_handle = do_CreateInstance("@nyapc.com/XPCOM/nsUrlDBIO;1", &rv);
    if (NS_FAILED(rv)) {
        ERROR << "Get nsUrlDBIO  Error:" << rv << "\n";
        url_handle = NULL;
    }
}

nsClusterDBHandle::~nsClusterDBHandle() {
    /* destructor code */
}

/* void SetLocation (in AUTF8String location); */
NS_IMETHODIMP nsClusterDBHandle::SetLocation(const nsACString & location) {
    this->mLocation = location;
    LOG<<"[nsIClusterDBHandle] SetLocation:"<<mLocation.get()<<endl;
    if (url_handle != NULL)
        url_handle->SetLocation(location);
    return NS_OK;
}

/* void SaveWrapRules (in PRInt32 con_type, in PRInt32 con_attr, in AUTF8String rules); */
NS_IMETHODIMP nsClusterDBHandle::SaveWrapRules(PRInt32 con_type, PRInt32 con_attr, const nsACString & rules) {
    string c_type;
    string c_attr;
    stringstream ss;
    ss << con_type << "\n";
    ss << con_attr << "\n";
    ss >> c_type;
    ss >> c_attr;

    nsresult rv;

    init_db();
    nsCOMPtr<mozIStorageConnection> conn;
    rv = mozSs->OpenDatabase(file, getter_AddRefs(conn));
    if (NS_FAILED(rv))
        return NS_OK;
    PRBool connReady = false;
    conn->GetConnectionReady(&connReady);
    //LOG<<"save wrapper : conn ready?"<<connReady<<"\n";
    if (connReady) {
        PRBool tExist = false;
        conn->TableExists(nsCString("WRAPPER"), &tExist);
        //LOG<<"save wrapper : table exist?"<<tExist<<"\n";
        if (tExist) {
            nsCOMPtr<mozIStorageStatement> state;
            nsCString sql_co("select con_type from WRAPPER where con_type=");
            sql_co.Append(c_type.c_str());
            //LOG<<"sql:"<<sql_co.get()<<"\n";

            conn->CreateStatement(sql_co, getter_AddRefs(state));
            PRBool exec = true;
            state->ExecuteStep(&exec);
            if (exec) {
                nsCOMPtr<mozIStorageStatement> state_update;
                nsCString sql("update wrapper set wrapper='");
                sql.Append(rules);
                sql.Append("', con_att=");
                sql.Append(c_attr.c_str());
                sql.Append(" where con_type=");
                sql.Append(c_type.c_str());
                LOG << "sql: " << sql.get() << "\n";
                conn->CreateStatement(sql, getter_AddRefs(state_update));
                state_update->Execute();
            } else {
                nsCOMPtr<mozIStorageStatement> state_insert;
                nsCString sql("insert into wrapper (con_type,wrapper,con_att) values (");
                sql.Append(c_type.c_str());
                sql.Append(", '");
                sql.Append(rules);
                sql.Append("', '");
                sql.Append(c_attr.c_str());
                sql.Append("');");
                LOG << "sql: " << sql.get() << "\n";
                conn->CreateStatement(sql, getter_AddRefs(state_insert));
                state_insert->Execute();
            }
        }
    }

    return NS_OK;
}

/* void LoadWrapRules (in PRInt32 con_type, out AUTF8String rules); */
NS_IMETHODIMP nsClusterDBHandle::LoadWrapRules(PRInt32 con_type, nsACString & rules) {
    string c_type;
    stringstream ss;
    ss << con_type << "\n";
    ss >> c_type;

    nsresult rv;

    init_db();
    nsCOMPtr<mozIStorageConnection> conn;
    rv = mozSs->OpenDatabase(file, getter_AddRefs(conn));
    if (NS_FAILED(rv))
        return NS_OK;
    PRBool connReady = false;
    conn->GetConnectionReady(&connReady);
    if (connReady) {
        PRBool tExist = false;
        conn->TableExists(nsCString("WRAPPER"), &tExist);
        if (tExist) {
            nsCOMPtr<mozIStorageStatement> state;
            nsCString sql_co("select wrapper from WRAPPER where con_type=");
            sql_co.Append(c_type.c_str());
            LOG << "sql:" << sql_co.get() << "\n";

            conn->CreateStatement(sql_co, getter_AddRefs(state));
            PRBool exec = true;
            state->ExecuteStep(&exec);
            if (exec) {
                state->GetUTF8String(0, rules);
            }
        }
    }

    return NS_OK;
}

/* void SetPageType (in nsIUrlAtt url, in PRInt32 type); */
NS_IMETHODIMP nsClusterDBHandle::SetPageType(nsIUrlAtt *url, PRInt32 type) {
    if (url != NULL && url_handle != nsnull) {
        stringstream ss;
        ss << type;
        nsCString c_type(ss.str().c_str());
        url->SetConAtt(c_type);
        url_handle->UpdateALL(url, (PRUint16) LINK_STAT_ANALYZED_DOM);
    }
    return NS_OK;
}

/* void InsertNewPage (in nsIUrlAtt url); */
NS_IMETHODIMP nsClusterDBHandle::InsertNewPage(nsIUrlAtt *url) {
    if (url != NULL && url_handle != nsnull)
        url_handle->PutURL(url);
    return NS_OK;
}

/* void GetURLID (in AUTF8String url, out PRUint32 id); */
NS_IMETHODIMP nsClusterDBHandle::GetURLID(const nsACString & url, PRUint32 *id) {
    if (url_handle == nsnull) return NS_OK;
    if (url.Length() > 0)
        url_handle->GetURLID(url, id);
    //LOG<<nsCString(url).get()<<" id "<<*id<<"\n";
    return NS_OK;
}

/* void UpdateClusterType (in PRInt32 con_type, in PRInt32 con_attr); */
NS_IMETHODIMP nsClusterDBHandle::UpdateClusterType(PRInt32 con_type, PRInt32 con_attr) {
    string c_type;
    string c_attr;
    stringstream ss;
    ss << con_type << "\n";
    ss << con_attr << "\n";
    ss >> c_type;
    ss >> c_attr;

    nsresult rv;

    init_db();
    nsCOMPtr<mozIStorageConnection> conn;
    rv = mozSs->OpenDatabase(file, getter_AddRefs(conn));
    if (NS_FAILED(rv))
        return NS_OK;
    PRBool connReady = false;
    conn->GetConnectionReady(&connReady);
    //LOG<<"save wrapper : conn ready?"<<connReady<<"\n";
    if (connReady) {
        PRBool tExist = false;
        conn->TableExists(nsCString("WRAPPER"), &tExist);
        //LOG<<"save wrapper : table exist?"<<tExist<<"\n";
        if (tExist) {
            nsCOMPtr<mozIStorageStatement> state;
            nsCString sql_co("select con_type from WRAPPER where con_type=");
            sql_co.Append(c_type.c_str());
            //LOG<<"sql:"<<sql_co.get()<<"\n";

            conn->CreateStatement(sql_co, getter_AddRefs(state));
            PRBool exec = true;
            state->ExecuteStep(&exec);
            if (exec) {
                nsCOMPtr<mozIStorageStatement> state_update;
                nsCString sql("update wrapper set ");
                sql.Append("con_att=");
                sql.Append(c_attr.c_str());
                sql.Append(" where con_type=");
                sql.Append(c_type.c_str());
                LOG << "sql: " << sql.get() << "\n";
                conn->CreateStatement(sql, getter_AddRefs(state_update));
                state_update->Execute();
            } else {
                nsCOMPtr<mozIStorageStatement> state_insert;
                nsCString sql("insert into wrapper (con_type,con_att,wrapper) values (");
                sql.Append(c_type.c_str());
                sql.Append(", ");
                sql.Append(c_attr.c_str());
                sql.Append(",'');");
                LOG << "sql: " << sql.get() << "\n";
                conn->CreateStatement(sql, getter_AddRefs(state_insert));
                state_insert->Execute();
            }
        }
    }

    return NS_OK;
}

/* void SavePage (in nsIUrlAtt url, in AUTF8String type); */
NS_IMETHODIMP nsClusterDBHandle::SavePage(PRInt32 url_id, const nsACString & doc) {
    string uid;
    stringstream ss;
    ss << url_id << "\n";
    ss >> uid;

    nsresult rv;

    init_db();
    nsCOMPtr<mozIStorageConnection> conn;
    rv = mozSs->OpenDatabase(file, getter_AddRefs(conn));
    if (NS_FAILED(rv))
        return NS_OK;
    PRBool connReady = false;
    conn->GetConnectionReady(&connReady);
    if (connReady) {
        PRBool tExist = false;
        conn->TableExists(nsCString("URL_DOC"), &tExist);
        if (tExist) {
            nsCOMPtr<mozIStorageStatement> state;
            nsCString sql_co("select url_id from url_doc where url_id=");
            sql_co.Append(uid.c_str());
            LOG<<"sql:"<<sql_co.get()<<"\n";

            conn->CreateStatement(sql_co, getter_AddRefs(state));
            PRBool exec = true;
            state->ExecuteStep(&exec);
            if (exec) {
                nsCOMPtr<mozIStorageStatement> state_update;
                nsCString sql("update url_doc set ");
                sql.Append("doc='");
                sql.Append(doc);
                sql.Append("' where url_id=");
                sql.Append(uid.c_str());
                conn->CreateStatement(sql, getter_AddRefs(state_update));
                state_update->Execute();
            } else {
                nsCOMPtr<mozIStorageStatement> state_insert;
                nsCString sql("insert into url_doc (url_id,doc) values ('");
                sql.Append(uid.c_str());
                sql.Append("', '");
                sql.Append(doc);
                sql.Append("');");
                conn->CreateStatement(sql, getter_AddRefs(state_insert));
                state_insert->Execute();
            }
        }
    }
    return NS_OK;
}

/* void GetPage (out AUTF8String page); */
NS_IMETHODIMP nsClusterDBHandle::GetPage(PRInt32 *uid, nsACString & page) {
    nsresult rv;

    init_db();
    nsCOMPtr<mozIStorageConnection> conn;
    rv = mozSs->OpenDatabase(file, getter_AddRefs(conn));
    if (NS_FAILED(rv))
        return NS_OK;
    PRBool connReady = false;
    conn->GetConnectionReady(&connReady);
    if (connReady) {
        PRBool tExist = false;
        conn->TableExists(nsCString("URL_DOC"), &tExist);
        if (tExist) {
            nsCOMPtr<mozIStorageStatement> state;
            nsCString sql("select url_id, doc from url_doc where stat=0;");
            //LOG<<"sql:"<<sql_co.get()<<"\n";

            conn->CreateStatement(sql, getter_AddRefs(state));
            PRBool exec = true;
            state->ExecuteStep(&exec);
            if (exec) {
                state->GetInt32(0, uid);
                state->GetUTF8String(1, page);

                {
                    //update: set stat=1
                    nsCOMPtr<mozIStorageStatement> state_update;
                    nsCString sql1("update url_doc set ");
                    sql1.Append("stat='1' where url_id=");
                    stringstream ss;
                    ss << *uid;
                    sql1.Append(ss.str().c_str());
                    conn->CreateStatement(sql1, getter_AddRefs(state_update));
                    state_update->Execute();
                }
            } else {
                *uid = 0;
                page = nsCString("");
            }
        }
    }
    return NS_OK;
}

/* void SetConType (in PRInt32 url_id, in PRInt32 con_type); */
NS_IMETHODIMP nsClusterDBHandle::SetConType(PRInt32 url_id, PRInt32 con_type) {
    LOG << "------------\n";
    stringstream ss;
    ss << url_id << endl;
    ss << con_type << endl;
    string uid, ctype;
    ss >> uid;
    ss >> ctype;

    nsresult rv;

    init_db();
    nsCOMPtr<mozIStorageConnection> conn;
    rv = mozSs->OpenDatabase(file, getter_AddRefs(conn));
    if (NS_FAILED(rv))
        return NS_OK;
    PRBool connReady = false;
    conn->GetConnectionReady(&connReady);
    if (connReady) {
        PRBool tExist = false;
        conn->TableExists(nsCString("URL_LIST"), &tExist);
        if (tExist) {
            nsCOMPtr<mozIStorageStatement> state;
            nsCString sql_co("select id from url_list where id=");
            sql_co.Append(uid.c_str());
            LOG << "sql:" << sql_co.get() << "\n";

            conn->CreateStatement(sql_co, getter_AddRefs(state));
            PRBool exec = true;
            state->ExecuteStep(&exec);
            if (exec) {
                nsCOMPtr<mozIStorageStatement> state_update;
                nsCString sql("update url_list set ");
                sql.Append("con_type='");
                sql.Append(ctype.c_str());
                sql.Append("' where id=");
                sql.Append(uid.c_str());
                conn->CreateStatement(sql, getter_AddRefs(state_update));
                state_update->Execute();
            }
        }
    }
    return NS_OK;
}

/* void GetNumberOfCluster (out PRInt32 num); */
NS_IMETHODIMP nsClusterDBHandle::GetNumberOfCluster(PRInt32 *num) {
    nsresult rv;

    init_db();
    nsCOMPtr<mozIStorageConnection> conn;
    rv = mozSs->OpenDatabase(file, getter_AddRefs(conn));
    if (NS_FAILED(rv))
        return NS_OK;
    PRBool connReady = false;
    conn->GetConnectionReady(&connReady);
    if (connReady) {
        PRBool tExist = false;
        conn->TableExists(nsCString("WRAPPER"), &tExist);
        if (tExist) {
            nsCOMPtr<mozIStorageStatement> state;
            nsCString sql_co("select count(*) c from WRAPPER;");
            LOG << "sql:" << sql_co.get() << "\n";

            conn->CreateStatement(sql_co, getter_AddRefs(state));
            PRBool exec = true;
            state->ExecuteStep(&exec);
            if (exec) {
                PRInt32 count;
                state->GetInt32(0, &count);
                *num = count;
            }
        }
    }
    return NS_OK;
}

/* void GetClusterID ([array, size_is (count)] out PRUint32 ids, out PRUint32 count); */
NS_IMETHODIMP nsClusterDBHandle::GetClusterID(PRUint32 **ids, PRUint32 *count) {
    nsresult rv;
    int lc = 0;
    PRBool exec = true;

    if (ids == NULL) return NS_OK;
    PRUint32 * array_id = *ids;
    if (array_id == NULL) return NS_OK;

    init_db();
    nsCOMPtr<mozIStorageConnection> conn;
    rv = mozSs->OpenDatabase(file, getter_AddRefs(conn));
    if (NS_FAILED(rv))
        return NS_OK;
    PRBool connReady = false;
    conn->GetConnectionReady(&connReady);
    if (connReady) {
        PRBool tExist = false;
        conn->TableExists(nsCString("WRAPPER"), &tExist);
        if (tExist) {
            nsCOMPtr<mozIStorageStatement> state;
            nsCString sql_co("select con_type from WRAPPER;");
            LOG << "sql:" << sql_co.get() << "\n";

            conn->CreateStatement(sql_co, getter_AddRefs(state));
            do {
                state->ExecuteStep(&exec);
                if (exec) {
                    *count = ++lc;
                    PRInt32 id;
                    state->GetInt32(0, &id);
                    *array_id++ = id;
                }
            } while (exec);
        }
    }
    return NS_OK;
}

/* void GetPageByConType (in PRUint32 con_type, in PRUint32 num, out nsCStringArray docs, out PRUint32 count); */
NS_IMETHODIMP nsClusterDBHandle::GetPageByConType(PRUint32 con_type, PRUint32 num, nsCStringArray *docs, PRUint32 *count) {
    stringstream ss;
    ss << num << endl;
    ss << con_type << endl;
    string number, ctype;
    ss >> number;
    ss >> ctype;

    nsCStringArray * array = docs;
    list<int> ids;
    nsCString url_id;
    //array->AppendCString(nsCString("a"));
    //array->AppendCString(nsCString("b"));

    nsresult rv;
    int lc = 0;
    PRBool exec = true;

    if (array == NULL) return NS_OK;

    init_db();
    nsCOMPtr<mozIStorageConnection> conn;
    rv = mozSs->OpenDatabase(file, getter_AddRefs(conn));
    if (NS_FAILED(rv))
        return NS_OK;
    PRBool connReady = false;
    conn->GetConnectionReady(&connReady);
    if (connReady) {
        PRBool tExist = false;
        conn->TableExists(nsCString("URL_LIST"), &tExist);
        if (tExist) {
            nsCOMPtr<mozIStorageStatement> state;
            nsCString sql_co("select id from URL_LIST where con_type=");
            sql_co.Append(ctype.c_str());
            sql_co.Append(" limit 0,");
            sql_co.Append(number.c_str());
            LOG << "sql:" << sql_co.get() << "\n";

            conn->CreateStatement(sql_co, getter_AddRefs(state));
            do {
                state->ExecuteStep(&exec);
                if (exec) {
                    PRInt32 id;
                    state->GetInt32(0, &id);
                    ids.push_back(id);
                }
            } while (exec);
        }
    }

    if (ids.size() > 0) {
        list<int>::iterator it;
        for (it = ids.begin(); it != ids.end(); it++) {
            ss.clear();
            ss << *it << endl;
            string uid;
            ss >> uid;
            url_id.Append(uid.c_str());

            list<int>::iterator it1 = it;
            it1++;

            if (it1 != ids.end()) {
                url_id.Append(",");
            }
        }
    } else {
        return NS_OK;
    }

    if (connReady) {
        PRBool tExist = false;
        conn->TableExists(nsCString("URL_DOC"), &tExist);
        if (tExist) {
            nsCOMPtr<mozIStorageStatement> state;
            nsCString sql_co("select doc from URL_DOC where url_id in(");
            sql_co.Append(url_id);
            sql_co.Append(")");
            LOG << "sql:" << sql_co.get() << "\n";

            conn->CreateStatement(sql_co, getter_AddRefs(state));
            do {
                state->ExecuteStep(&exec);
                if (exec) {
                    lc++;
                    nsCString document;
                    state->GetUTF8String(0, document);
                    array->AppendCString(document);
                }
            } while (exec);
        }
    }

    *count = lc;
    return NS_OK;
}

/* void GetClusterType (in PRUint32 name, out PRUint32 type); */
NS_IMETHODIMP nsClusterDBHandle::GetClusterType(PRUint32 name, PRUint32 *type) {
    stringstream ss;
    string c_type;
    ss << name << "\n";
    ss >> c_type;

    nsresult rv;
    
    init_db();
    nsCOMPtr<mozIStorageConnection> conn;
    rv = mozSs->OpenDatabase(file, getter_AddRefs(conn));
    if (NS_FAILED(rv))
        return NS_OK;
    PRBool connReady = false;
    conn->GetConnectionReady(&connReady);
    if (connReady) {
        PRBool tExist = false;
        conn->TableExists(nsCString("WRAPPER"), &tExist);
        if (tExist) {
            nsCOMPtr<mozIStorageStatement> state;
            nsCString sql_co("select con_type from WRAPPER where con_type=");
            sql_co.Append(c_type.c_str());
            //LOG<<"sql:"<<sql_co.get()<<"\n";

            conn->CreateStatement(sql_co, getter_AddRefs(state));
            PRBool exec = true;
            state->ExecuteStep(&exec);
            if (exec) {
                nsCOMPtr<mozIStorageStatement> state_read;
                nsCString sql("select con_att from WRAPPER where con_type=");
                sql.Append(c_type.c_str());
                LOG << "sql: " << sql.get() << "\n";
                conn->CreateStatement(sql, getter_AddRefs(state_read));
                state_read->ExecuteStep(&exec);
                if(exec)
                {
                    PRInt32 t;
                    state_read->GetInt32(0, &t);
                    *type = t;
                    return NS_OK;
                }
            }
        }
    }
    
    return NS_OK;
}

int nsClusterDBHandle::init_db() {
    if (mozSs == NULL) {
        nsresult rv;
        mozSs = do_CreateInstance("@mozilla.org/storage/service;1", &rv);
        if (NS_FAILED(rv)) {
            ERROR << "Get  mozIStorageService  Error:" << rv << "\n";
            return 0;
        }

        if (file == NULL) {
            open_db_file();
        }
    }
}

int nsClusterDBHandle::open_db_file() {
    nsresult rv;
    rv = NS_NewLocalFile(NS_ConvertUTF8toUTF16(mLocation),
            PR_FALSE, getter_AddRefs(file));
    if (NS_FAILED(rv)) {
        LOG << "Init File  Error:" << hex << rv << "\n";
        return -1;
    }
    return 0;
}
