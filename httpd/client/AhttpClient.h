#ifndef __AHTTP_CLIENT__
#define __AHTTP_CLIENT__
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

class AhttpClient
{
private:
     HttpUrl _url;
     boost::asio::io_service io_s;
     tcp::socket _socket;
public:
     AhttpClient()
	  :_url(),
	   io_s(),
	   _socket(io_s),
	   resolver_(io_s),
	   _request(),
	   _response(),
	   res_fin(false)
	  {};
     AhttpClient(std::string &url)
	  :_url(url),
	   io_s(),
	   _socket(io_s),
	   resolver_(io_s),
	   _request(),
	   _response(),
	   res_fin(false)
	  {
	       _request.setHost(_url.getHost());
	       _request.setType(http_req_type_get);
	       _request.setResource(_url.getResource());
	  };
     bool connect();
     void addHead(std::string &tag,std::string &val);
     void setRequest(HttpReqest &req);
     void handle_resolve(const boost::system::error_code& err,tcp::resolver::iterator endpoint_iterator);
     void handle_connect(const boost::system::error_code& err,tcp::resolver::iterator endpoint_iterator);
     void handle_write_request(const boost::system::error_code& err);

     bool connect(std::string &url);
     HttpResponse &getResponse();
     
private:
     tcp::resolver resolver_;
     boost::asio::streambuf resbuf_;
     bool res_fin;
     HttpReqest _request;
     HttpResponse _response;
};
#endif
