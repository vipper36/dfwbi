#ifndef __HTTP_CLIENT__
#define __HTTP_CLIENT__
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include "HttpUrl.h"
#include "HttpReqest.h"
#include "HttpResponse.h"
using boost::asio::ip::tcp;

class HttpClient
{
private:
     HttpUrl _url;
     boost::asio::io_service io_s;
     tcp::socket _socket;
public:
     HttpClient()
       :_url(),
       io_s(),
       _socket(io_s),
       _request(),
       _response()
       {};
     HttpClient(std::string &url)
       :_url(url),
       io_s(),
       _socket(io_s),
       _request(),
       _response()
     {
       _request.setHost(_url.getHost());
       _request.setType(http_req_type_get);
       _request.setResource(_url.getResource());
     };
     bool connect();
     bool connect(std::string &url);
     bool SendRequest();
     HttpResponse &getResponse();
     void addHead(std::string &tag,std::string &val);
     void setRequest(HttpReqest &req);
private:
     HttpReqest _request;
     HttpResponse _response;
};
#endif
