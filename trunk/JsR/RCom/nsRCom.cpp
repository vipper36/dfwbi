#include <stdint.h>
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIClassInfoImpl.h"
#include "nsStringAPI.h"
#include <string>
#include <memory>
#include "nsRCom.h"
#include <iostream>
#include "nsMemory.h"
#include <sstream>

NS_IMPL_CLASSINFO(nsRCom, NULL, 0, NS_RCOM_CID)

NS_IMPL_ISUPPORTS1_CI(nsRCom, nsIRCom)


nsRCom::nsRCom():rc(NULL)
{
}

nsRCom::~nsRCom()
{
    if(rc!=NULL)
        delete rc;
}

/* long connect (in AUTF8String host, in long port); */
NS_IMETHODIMP nsRCom::Connect(const nsACString & host, int32_t port, int32_t *_retval)
{
    NS_IMETHODIMP ret=NS_ERROR_FAILURE;
    try {
        nsCString hostStr(host);
        rc = new Rconnection(hostStr.get(),port);
        std::cout << hostStr.get()<<":"<<port<< std::endl;
        *_retval=rc->connect();
        ret=NS_OK;
    }
    catch (...) {
        std::cout << "connect ERROR" << std::endl;
    }
    return ret;
}

/* AUTF8String eval (in AUTF8String url); */
NS_IMETHODIMP nsRCom::Eval(const nsACString & expr, nsACString & _retval)
{
    NS_IMETHODIMP ret=NS_ERROR_FAILURE;
    try {
        nsCString exprStr(expr);
        Rexp *xp=rc->eval(exprStr.get());
        if (xp) {
            Json::Value value=RexpToJson(xp);
            std::string out = value.toStyledString();
            _retval=nsCString(out.c_str());
            ret=NS_OK;
        }        
    }catch (...) {
        std::cout << "Eval excetion" << std::endl;
    }
    return ret;
}

/* void close (); */
NS_IMETHODIMP nsRCom::Close()
{
    if(rc!=NULL)
        delete rc;
}
Json::Value nsRCom::RexpToJson(Rexp *xp)
{
    Json::Value root;
    root["type"]=xp->type;
    switch(xp->type)
    {
    case XT_NULL:
        root["result"]="";
        break;
    case XT_INT:
    {
        Rinteger *x = (Rinteger*)xp;
        root["result"]=x->intAt(0);
        break;
    }
    case XT_DOUBLE:
    {
        Rdouble *x = (Rdouble*)xp;
        root["result"]=x->doubleAt(0);
        break;
    }
    case XT_STR:
    {
        Rstring *x = (Rstring*)xp;
        root["result"]=x->string();
        break;
    }
    case XT_LANG:
        root["result"]="";
        break;
    case XT_SYM:
    {
        Rsymbol *x = (Rsymbol*)xp;
        root["result"]=x->symbolName();
        break;
    }
    case XT_BOOL:
        root["result"]="";
        break;
    case XT_S4:
        root["result"]="";
        break;
    case XT_VECTOR:
    {
        Rvector *x = (Rvector*)xp;
        Json::Value result;
        for(int i=0;i<x->length();i++)
        {
            Json::Value val=RexpToJson(x->elementAt(i));
            result.append(val);
        }
        root["result"]=result;
        break;
    }
    case XT_LIST:
    {
        Rlist *tail = (Rlist*)xp;
        Json::Value result;
        while(tail!=0)
        {
            Json::Value val=RexpToJson(tail->head);
            result.append(val);
            tail=tail->tail;
        }
        root["result"]=result;
        break;
    }
    case XT_CLOS:
        root["result"]="";
        break;
    case XT_SYMNAME:
        root["result"]="";
        break;
    case XT_LIST_NOTAG:
        root["result"]="";
        break;
    case XT_LIST_TAG:
        root["result"]="";
        break;
    case XT_LANG_NOTAG:
        root["result"]="";
        break;
    case XT_LANG_TAG:
        root["result"]="";
        break;
    case XT_VECTOR_EXP:
        root["result"]="";
        break;
    case XT_VECTOR_STR:
        root["result"]="";
        break;
    case XT_ARRAY_INT:
    {
        Rinteger *x = (Rinteger*)xp;
        Json::Value result;
        for(int i=0;i<x->length();i++)
        {
            result.append(x->intAt(i));
        }
        root["result"]=result;
        break;
    }
    case XT_ARRAY_DOUBLE:
    {
        Rdouble *x = (Rdouble*)xp;
        Json::Value result;
        for(int i=0;i<x->length();i++)
        {
            result.append(x->doubleAt(i));
        }
        root["result"]=result;
        break;
    }
    case XT_ARRAY_STR:
    {
        Rstrings *x = (Rstrings*)xp;
        Json::Value result;
        for(int i=0;i<x->length();i++)
        {
            result.append(x->stringAt(i));
        }
        root["result"]=result;
        break;
    }
    case XT_ARRAY_BOOL_UA:
        root["result"]="";
        break;
    case XT_ARRAY_BOOL:
        root["result"]="";
        break;
    case XT_RAW:
        root["result"]="";
        break;
    case XT_ARRAY_CPLX:
        root["result"]="";
        break;
    default:
        root["result"]="";
    }
    return root;
}
