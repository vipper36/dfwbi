#include <string>
#include <iostream>
#include "HttpResponse.h"
#include "HttpClient.h"
#include "Yahoo.h"
int main(int argc,char **argv)
{
  if(argc<2)
    {
      std::cout<<"usage:httptest url"<<std::endl;
      return 0;
    }
  std::string url(argv[1]);
  std::cout<<url<<std::endl;
  Yahoo yh;
  std::string cStock("000585.SZ");
  std::string ctime("2003-01-01");
  std::list<std::string> sl=yh.GetHisData(cStock,ctime);
  std::list<std::string>::iterator Itr=sl.begin();
  for(;Itr!=sl.end();++Itr)
    {
        std::cout<<*Itr<<std::endl;
    }
  std::list<std::string> snl;
  snl.push_back("000585.SZ");
  snl.push_back("000001.SS");
  snl.push_back("IBM");
  std::map<std::string,std::string> sm=yh.GetDayData(snl);
  std::map<std::string,std::string>::iterator Itr1=sm.begin();
  for(;Itr1!=sm.end();++Itr1)
    {
      std::cout<<Itr1->first<<":--"<<Itr1->second<<std::endl;
    }
  std::string pr=yh.GetDayData(cStock);
  std::cout<<pr<<std::endl;
}
