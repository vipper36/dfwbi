#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "file_list.h"

void *list_create()
{
  file_list *ret=new file_list();
  return (void*)ret;
}
void file_list::open(std::string source,std::string mark)
{
  _list.clear();
  if(source.length()>0)
    {
      std::ifstream sif(source.c_str());
      std::string line;
      while(!sif.eof())
	{
	  std::getline(sif,line);
	  std::vector<std::string> resv;
	  boost::algorithm::split( resv, line, boost::algorithm::is_any_of(",") );
	  if(resv.size()>1)
	    {
	      _list.insert(std::make_pair(resv[0]+"."+mark,resv[0]));
	    }
	}
    }
}
std::map<std::string,std::string> &file_list::GetList()
{
  return _list;
}
