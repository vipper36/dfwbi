//
// async_client.cpp
// ~~~~~~~~~~~~~~~~
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
#include <sstream>
using boost::asio::ip::tcp;

class client
{
public:
     client(const std::string& server, const std::string& stock)
	  : io_s(),
	    resolver_(io_s),
	    socket_(io_s),
	    query_(server, "http")
	  {
	       // Form the request. We specify the "Connection: close" header so that the
	       // server will close the socket after transmitting the response. This will
	       // allow us to treat all data up until the EOF as the content.
	       std::ostream request_stream(&request_);
	       request_stream << "GET " << "/list="<<stock << " HTTP/1.0\r\n";
	       request_stream << "Host: " << server << "\r\n";
	       request_stream << "Accept: */*\r\n";
	       request_stream << "Connection: close\r\n\r\n";

	       // Start an asynchronous resolve to translate the server and service names
	       // into a list of endpoints.
	       
	  }
     void run()
	  {
	       
	       resolver_.async_resolve(query_,
				       boost::bind(&client::handle_resolve, this,
						   boost::asio::placeholders::error,
						   boost::asio::placeholders::iterator));
	       io_s.run();
	  }

private:
     void handle_resolve(const boost::system::error_code& err,
			 tcp::resolver::iterator endpoint_iterator)
	  {
	       if (!err)
	       {
		    // Attempt a connection to the first endpoint in the list. Each endpoint
		    // will be tried until we successfully establish a connection.
		    tcp::endpoint endpoint = *endpoint_iterator;
		    socket_.async_connect(endpoint,
					  boost::bind(&client::handle_connect, this,
						      boost::asio::placeholders::error, ++endpoint_iterator));
	       }
	       else
	       {
		    std::cout << "Error: " << err.message() << "\n";
	       }
	  }

     void handle_connect(const boost::system::error_code& err,
			 tcp::resolver::iterator endpoint_iterator)
	  {
	       if (!err)
	       {
		    // The connection was successful. Send the request.
		    boost::asio::async_write(socket_, request_,
					     boost::bind(&client::handle_write_request, this,
							 boost::asio::placeholders::error));
	       }
	       else if (endpoint_iterator != tcp::resolver::iterator())
	       {
		    // The connection failed. Try the next endpoint in the list.
		    socket_.close();
		    tcp::endpoint endpoint = *endpoint_iterator;
		    socket_.async_connect(endpoint,
					  boost::bind(&client::handle_connect, this,
						      boost::asio::placeholders::error, ++endpoint_iterator));
	       }
	       else
	       {
		    std::cout << "Error: " << err.message() << "\n";
	       }
	  }

     void handle_write_request(const boost::system::error_code& err)
	  {
	       if (!err)
	       {
		    // Read the response status line.
		    boost::asio::async_read_until(socket_, response_, "\";",
						  boost::bind(&client::handle_read, this,
							      boost::asio::placeholders::error));
	       }
	       else
	       {
		    std::cout << "Error: " << err.message() << "\n";
	       }
	  }

     void handle_read(const boost::system::error_code& err)
	  {
	       if (!err)
	       {
		    // Check that response is OK.
		    std::stringstream string_stream;
		    string_stream<<&response_;
		    std::string strRes=string_stream.str();
		    std::string::size_type idx1=strRes.find("hq_str_");
		    if(idx1==std::string::npos)
		    {
			 std::cout<<"response error"<<std::endl;
			 return;
		    }
		    std::string::size_type idx2=strRes.find("=\"");
		    if(idx2==std::string::npos)
		    {
			 std::cout<<"response error"<<std::endl;
			 return;
		    }
		    std::string stockCode=strRes.substr(idx1+7,idx2-idx1-7);
		    std::string::size_type idx3=strRes.find("\";");
		    if(idx3==std::string::npos)
		    {
			 std::cout<<"response error"<<std::endl;
			 return;
		    }
		    std::string infoString= strRes.substr(idx2+2,idx3-idx2);
		    std::list<std::string> results;
		    boost::split(results, infoString, boost::is_any_of(","));
		    std::list<std::string>::const_iterator p = results.begin();
		    std::cout<<"股票代码："<<stockCode<<std::endl;
		    std::cout<<"股票名："<<*p++<<std::endl;
		    std::cout<<"今日开盘价："<<*p++<<std::endl;
		    std::cout<<"昨日收盘价："<<*p++<<std::endl;
		    std::cout<<"当前价格："<<*p++<<std::endl;
		    std::cout<<"今日最高价："<<*p++<<std::endl;
		    std::cout<<"今日最低价："<<*p++<<std::endl;
		    std::cout<<"买一："<<*p++<<std::endl;
		    std::cout<<"卖一："<<*p++<<std::endl;
		    std::cout<<"成交量："<<*p++<<std::endl;
		    std::cout<<"成交额："<<*p++<<std::endl;
		    std::cout<<"买一："<<*p++<<"::"<<*p++<<std::endl;
		    std::cout<<"买二："<<*p++<<"::"<<*p++<<std::endl;
		    std::cout<<"买三："<<*p++<<"::"<<*p++<<std::endl;
		    std::cout<<"买四："<<*p++<<"::"<<*p++<<std::endl;
		    std::cout<<"买五："<<*p++<<"::"<<*p++<<std::endl;
		    std::cout<<"卖一："<<*p++<<"::"<<*p++<<std::endl;
		    std::cout<<"卖二："<<*p++<<"::"<<*p++<<std::endl;
		    std::cout<<"卖三："<<*p++<<"::"<<*p++<<std::endl;
		    std::cout<<"卖四："<<*p++<<"::"<<*p++<<std::endl;
		    std::cout<<"卖五："<<*p++<<"::"<<*p++<<std::endl;
		    std::cout<<"卖间："<<*p++<<"  "<<*p++<<std::endl;
		    std::cout<<"==================================="<<std::endl;
		    socket_.close();
	       }
	       else
	       {
		    std::cout << "Error: " << err << "\n";
	       }
	  }     
     tcp::resolver::query query_;
     boost::asio::io_service io_s;
     tcp::resolver resolver_;
     tcp::socket socket_;
     boost::asio::streambuf request_;
     boost::asio::streambuf response_;
};
void query_stock(boost::asio::deadline_timer *t, std::string &server,std::string &stock)
{
     client c(server, stock);
     boost::thread thr(boost::bind(&client::run, &c));
     t->expires_at(t->expires_at() + boost::posix_time::seconds(2));
     t->async_wait(boost::bind(query_stock,t,server,stock));
     thr.join();
}
int main(int argc, char* argv[])
{
     try
     {
	  if (argc != 3)
	  {
	       std::cout << "Usage: async_client <server> <path>\n";
	       std::cout << "Example:\n";
	       std::cout << "  async_client www.boost.org /LICENSE_1_0.txt\n";
	       return 1;
	  }
	  boost::asio::io_service io_ser;
	  boost::asio::deadline_timer t(io_ser, boost::posix_time::seconds(2));
	  std::string server(argv[1]);
	  std::string stock(argv[2]);
	  t.async_wait(boost::bind(query_stock,&t,server,stock));
	  io_ser.run();
     }
     catch (std::exception& e)
     {
	  std::cout << "Exception: " << e.what() << "\n";
     }

     return 0;
}
