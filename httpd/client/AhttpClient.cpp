//
// sync_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>
#include "AhttpClient.h"
using boost::asio::ip::tcp;
bool AhttpClient::connect()
{
     tcp::resolver::query query(_url.getHost(), _url.getPort());
     resolver_.async_resolve(query,
			    boost::bind(&AhttpClient::handle_resolve, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::iterator));
     return true;
}
void AhttpClient::handle_resolve(const boost::system::error_code& err,
		    tcp::resolver::iterator endpoint_iterator)
{
     if (!err)
     {
	  // Attempt a connection to the first endpoint in the list. Each endpoint
	  // will be tried until we successfully establish a connection.
	  tcp::endpoint endpoint = *endpoint_iterator;
	  _socket.async_connect(endpoint,
				boost::bind(&AhttpClient::handle_connect, this,
					    boost::asio::placeholders::error, ++endpoint_iterator));
     }
     else
     {
	  std::cout << "Error: " << err.message() << "\n";
     }
}
void AhttpClient::handle_connect(const boost::system::error_code& err,
		    tcp::resolver::iterator endpoint_iterator)
{
     if (!err)
     {
	  // The connection was successful. Send the request.
	   boost::asio::streambuf resbuf;
	   std::ostream request_stream(&resbuf);
	   request_stream<<_request;
	  boost::asio::async_write(_socket, resbuf,
				   boost::bind(&AhttpClient::handle_write_request, this,
					       boost::asio::placeholders::error));
     }
     else if (endpoint_iterator != tcp::resolver::iterator())
     {
	  // The connection failed. Try the next endpoint in the list.
	  _socket.close();
	  tcp::endpoint endpoint = *endpoint_iterator;
	  _socket.async_connect(endpoint,
				boost::bind(&AhttpClient::handle_connect, this,
					    boost::asio::placeholders::error, ++endpoint_iterator));
     }
     else
     {
	  std::cout << "Error: " << err.message() << "\n";
     }
}
void AhttpClient::handle_write_request(const boost::system::error_code& err)
{
     if (!err)
     {
	  boost::asio::async_read(_socket, resbuf_,boost::asio::transfer_at_least(1),
					boost::bind(&AhttpClient::handle_write_request, this,
						    boost::asio::placeholders::error));
     }
     else if(err == boost::asio::error::eof)
     {
	  std::istream resp_stream(&resbuf_);
	  resp_stream>>_response;
	  res_fin=true;
     }
     else
     {
	  std::cout << "Error: " << err.message() << "\n";
     }
}
bool AhttpClient::connect(std::string &url)
{
     _url.setUrl(url);
     _request.setHost(_url.getHost());
     _request.setType(http_req_type_get);
     _request.setResource(_url.getResource());
     return connect();

}
HttpResponse &AhttpClient::getResponse()
{
     int count=0;
     io_s.run();
     while(!res_fin&&count<100)
     {
	  boost::this_thread::sleep(boost::posix_time::milliseconds(100));
	  count++;
     }
     io_s.stop();
     res_fin=false;
     return _response;
}
void AhttpClient::addHead(std::string &tag,std::string &val)
{
     _request.addHead(tag,val);
}
void AhttpClient::setRequest(HttpReqest &req)
{
     _request=req;
}
