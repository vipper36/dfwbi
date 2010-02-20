#include "HttpReqest.h"
const char *
http_req_type_char[] = {
  "GET",
  "OPTIONS",
  "HEAD",
  "POST",
  "PUT",
  "DELETE",
  "TRACE",
  "CONNECT",
  "PROPFIND",
  "PROPPATCH",
  "MKCOL",
  "COPY",
  "MOVE",
  "LOCK",
  "UNLOCK",
  NULL
};
void HttpReqest::setHost(std::string &host)
{
     _host=host;
}
void HttpReqest::setVersion(std::string ver)
{
     _http_ver=ver;
}
void HttpReqest::setType(http_req_type type)
{
     _type=type;
}
void HttpReqest::setResource(std::string &res)
{
     _resource=res;
}
void HttpReqest::setBody(std::string &body)
{
     _body=body;
}
void HttpReqest::addHead(std::string &headTag,std::string &value)
{
     _heads.insert(std::make_pair(headTag,value));
}
std::ostream &operator<<(std::ostream &os,HttpReqest &req)
{
     os<<http_req_type_char[req._type]<<" "<<req._resource<<" HTTP/"<<req._http_ver<<std::endl;
     os<<"Host: "<<req._host<<std::endl;
     std::map<std::string,std::string>::iterator Itr=req._heads.begin();
     for(;Itr!=req._heads.end();++Itr)
     {
	  os<<Itr->first<<": "<<Itr->second<<std::endl;
     }
     os<<std::endl<<std::endl;
     os<<req._body<<std::endl;
     return os;
}
