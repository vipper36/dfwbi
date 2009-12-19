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
#include <boost/algorithm/string.hpp>
#include "HttpClient.h"
using boost::asio::ip::tcp;
bool HttpClient::connect()
{
  tcp::resolver resolver(io_s);
  tcp::resolver::query query(_url.getHost(), _url.getPort());
  tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
  tcp::resolver::iterator end;
			       
  // Try each endpoint until we successfully establish a connection.
  boost::system::error_code error = boost::asio::error::host_not_found;
  while (error && endpoint_iterator != end)
    {
      _socket.close();
      _socket.connect(*endpoint_iterator++, error);
    }
  if (error)
    return false;
  return true;
}
bool HttpClient::connect(std::string &url)
{
  _url.setUrl(url);
  _request.setHost(_url.getHost());
  _request.setType(http_req_type_get);
  _request.setResource(_url.getResource());
  return connect();

}
HttpResponse &HttpClient::getResponse()
{
  return _response;
}
void HttpClient::addHead(std::string &tag,std::string &val)
{
  _request.addHead(tag,val);
}
void HttpClient::setRequest(HttpReqest &req)
{
  _request=req;
}

bool HttpClient::SendRequest()
{
       boost::system::error_code error = boost::asio::error::host_not_found;
  boost::asio::streambuf resbuf;
  std::ostream request_stream(&resbuf);
  request_stream<<_request;
  boost::asio::write(_socket, resbuf);
  boost::asio::streambuf respbuf;
  std::istream resp_stream(&respbuf);
  while (boost::asio::read(_socket, respbuf,
			   boost::asio::transfer_at_least(1), error));
  if (error != boost::asio::error::eof)
    return false;
  resp_stream>>_response;
  return true;
}
