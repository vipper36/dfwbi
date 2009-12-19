#include <iostream>
#include <sstream>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include "status.h"

namespace io = boost::iostreams;

void *status_create()
{
     status_cmd *ret=new status_cmd();
     return (void*)ret;
}
std::string status_cmd::handle(const std::string& param,const std::string& content)
{
  std::stringstream retStream;
  FILE* pipe = popen(param.c_str(), "r");
    
  io::stream_buffer<io::file_descriptor_source> fpstream(fileno(pipe));
  std::istream in(&fpstream);
    
  std::string line;
  while (in)
    {
      std::getline(in, line);
      retStream << line << std::endl;
    }
  
  return retStream.str();
}
