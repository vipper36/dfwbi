#ifndef __HTTP_REQEST__
#define __HTTP_REQEST__
#include <map>
#include <string>
#include <ostream>
typedef enum http_req_type {
  http_req_type_get = 0,
  http_req_type_options,
  http_req_type_head,
  http_req_type_post,
  http_req_type_put,
  http_req_type_delete,
  http_req_type_trace,
  http_req_type_connect,
  http_req_type_propfind,
  http_req_type_proppatch,
  http_req_type_mkcol,
  http_req_type_copy,
  http_req_type_move,
  http_req_type_lock,
  http_req_type_unlock
} http_req_type;
class HttpReqest
{
private:
     http_req_type _type;
     std::string _http_ver;
     std::string _host;
     std::string _resource;
     std::string _body;
     std::map<std::string,std::string> _heads;
public:
     HttpReqest()
	  :_type(http_req_type_get),
	   _http_ver("1.0"),
	   _host(),
	   _resource(),
	   _body()
	  {};
     ~HttpReqest(){};
     void setHost(std::string &host);
     void setVersion(std::string ver);
     void setType(http_req_type type);
     void setResource(std::string &res);
     void setBody(std::string &body);
     void addHead(std::string &headTag,std::string &value);
     friend std::ostream &operator<<(std::ostream &os,HttpReqest &req);
  
};
#endif
