#include <string>
#include <iostream>
#include "HttpResponse.h"
#include "HttpClient.h"
#include "Yahoo.h"
#include "Stock.h"
#include "StockDataAdaptor.h"
int main(int argc,char **argv)
{
  if(argc<2)
    {
      std::cout<<"usage:httptest url"<<std::endl;
      return 0;
    }
//   std::string url(argv[1]);
//   std::cout<<url<<std::endl;
//   Yahoo yh;
//   std::string cStock("000585.SZ");
//   std::string ctime("2003-01-01");
//   std::list<std::string> sl=yh.GetHisData(cStock,ctime);
//   std::list<std::string>::iterator Itr=sl.begin();
//   for(;Itr!=sl.end();++Itr)
//     {
//         std::cout<<*Itr<<std::endl;
//     }
//   std::list<std::string> snl;
//   snl.push_back("000585.SZ");
//   snl.push_back("000001.SS");
//   snl.push_back("IBM");
//   std::map<std::string,std::string> sm=yh.GetDayData(snl);
//   std::map<std::string,std::string>::iterator Itr1=sm.begin();
//   for(;Itr1!=sm.end();++Itr1)
//     {
//       std::cout<<Itr1->first<<":--"<<Itr1->second<<std::endl;
//     }
//   std::string pr=yh.GetDayData(cStock);
//   std::cout<<pr<<std::endl;
  Stock st("000585.SZ");
  //  Stock st("IBM");
  StockDataAdaptor sda;
  std::string ctime("2003-01-01");
  sda.FillHisdata(&st,ctime);
  sda.FillCurentData(&st);
  std::map<std::string,double> hisCloseM=st.getHisValuePair("Close");
  std::map<std::string,double>::iterator Itr1=hisCloseM.begin();
  for(;Itr1!=hisCloseM.end();++Itr1)
    {
      std::cout<<Itr1->first<<":--"<<Itr1->second<<std::endl;
    }
  std::cout<<"111111111111111111"<<std::endl;
  std::map<std::string,double> dayCloseM=st.getDayValuePair("Close");
  std::map<std::string,double>::iterator Itr2=dayCloseM.begin();
  for(;Itr2!=dayCloseM.end();++Itr2)
    {
      std::cout<<Itr2->first<<":--"<<Itr2->second<<std::endl;
    }
  std::cout<<"2222222222222222222"<<std::endl;
  std::list<double> hisCloseL=st.getHisValueList("Close");
  std::list<double>::iterator Itr3=hisCloseL.begin();
  for(;Itr3!=hisCloseL.end();++Itr3)
    {
      std::cout<<*Itr3<<std::endl;
    }
  std::cout<<"333333333333333333"<<std::endl;
  std::list<double> dayCloseL=st.getDayValueList("Close");
  std::list<double>::iterator Itr4=dayCloseL.begin();
  for(;Itr4!=dayCloseL.end();++Itr4)
    {
      std::cout<<*Itr4<<std::endl;
    }
  
}
