//
// request_handler.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "request_handler.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <boost/lexical_cast.hpp>
#include "mime_types.hpp"
#include "reply.hpp"
#include "request.hpp"
#include "Logger.hpp"
#include <boost/algorithm/string.hpp>

namespace http {
     namespace server3 {

	  request_handler::request_handler(const std::string& doc_root)
	       : doc_root_(doc_root),
		 handle_command_()
	  {
	  }

	  void request_handler::handle_request(const request& req, reply& rep)
	  {
	       // Decode url to path.
	       std::string request_path;
	       if (!url_decode(req.uri, request_path))
	       {
		    rep = reply::stock_reply(reply::bad_request);
		    return;
	       }

	       std::map<std::string,std::string> cmds;
	       url_GetCommand(request_path,cmds);
	       LOG_DBG<<cmds.size();
	       if(cmds.empty())
	       {
		 handle_doc(request_path,rep);
	       }
	       else
	       {
		    int impCmdCount=0;
		    std::stringstream ss;
		    for(std::map<std::string,std::string>::iterator it=cmds.begin();it!=cmds.end();++it)
		    {
			 std::string cont;
			 if(req.method=="POST")
			      cont=req.content;
			 else
			      cont="";
			 std::string ret;
			 if(handle_command_.SigCommand(it->first,it->second,cont,ret))
			 {
			      ss<<ret<<std::endl;
			      impCmdCount++;
			 }
			
		    }
		    if(impCmdCount>0)
		    {
			 rep.status = reply::ok;
			 char buf[512];
			 while (ss.read(buf, sizeof(buf)).gcount() > 0)
			      rep.content.append(buf, ss.gcount());
			 rep.headers.resize(2);
			 rep.headers[0].name = "Content-Length";
			 rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
		    }else
		    {
			 rep= reply::stock_reply(reply::service_unavailable);
		    }
	       }
	       
	  }
	  void request_handler::handle_doc(const std::string& requestpath,reply& rep){
	       // Request path must be absolute and not contain "..".
	       std::string request_path=requestpath;
	       if (request_path.empty() || request_path[0] != '/'
		   || request_path.find("..") != std::string::npos)
	       {
		    rep = reply::stock_reply(reply::bad_request);
		    return;
	       }

	       // If path ends in slash (i.e. is a directory) then add "index.html".
	       if (request_path[request_path.size() - 1] == '/')
	       {
		    request_path += "index.html";
	       }

	       // Determine the file extension.
	       std::size_t last_slash_pos = request_path.find_last_of("/");
	       std::size_t last_dot_pos = request_path.find_last_of(".");
	       std::string extension;
	       if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
	       {
		    extension = request_path.substr(last_dot_pos + 1);
	       }

	       // Open the file to send back.
	       std::string full_path = doc_root_ + request_path;
	       std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
	       if (!is)
	       {
		    rep = reply::stock_reply(reply::not_found);
		    return;
	       }

	       // Fill out the reply to be sent to the client.
	       rep.status = reply::ok;
	       char buf[512];
	       while (is.read(buf, sizeof(buf)).gcount() > 0)
		    rep.content.append(buf, is.gcount());
	       rep.headers.resize(2);
	       rep.headers[0].name = "Content-Length";
	       rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
	       rep.headers[1].name = "Content-Type";
	       rep.headers[1].value = mime_types::extension_to_type(extension);
	  }
	  bool request_handler::url_decode(const std::string& in, std::string& out)
	  {
	       out.clear();
	       out.reserve(in.size());
	       for (std::size_t i = 0; i < in.size(); ++i)
	       {
		    if (in[i] == '%')
		    {
			 if (i + 3 <= in.size())
			 {
			      int value;
			      std::istringstream is(in.substr(i + 1, 2));
			      if (is >> std::hex >> value)
			      {
				   out += static_cast<char>(value);
				   i += 2;
			      }
			      else
			      {
				   return false;
			      }
			 }
			 else
			 {
			      return false;
			 }
		    }
		    else if (in[i] == '+')
		    {
			 out += ' ';
		    }
		    else
		    {
			 out += in[i];
		    }
	       }
	       return true;
	  }
	  bool request_handler::url_GetCommand(const std::string& in, std::map<std::string,std::string>& cmd)
	  {
	       cmd.clear();

	       typedef std::vector< std::string > split_vector_type;
	       
	       split_vector_type SplitVec; 
	       boost::split( SplitVec, in, boost::is_any_of("/") );
	       
	       for(split_vector_type::iterator it=SplitVec.begin();it!=SplitVec.end();++it)
	       {
		    if(it->length()>0)
		    {
			 split_vector_type SplitVec2; 
			 boost::split( SplitVec2, *it, boost::is_any_of("?") );
			 if(SplitVec2.size()>1)
			      cmd.insert(make_pair(SplitVec2[0],SplitVec2[1]));
		    }
	       }
	       return true;
	  }
	  
     } // namespace server3
} // namespace http
