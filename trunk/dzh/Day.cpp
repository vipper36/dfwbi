#include <boost/program_options.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
#pragma pack(1)

namespace po = boost::program_options;
struct GLOBAL_DATA { 
    int dayflag; 
    int reserve1; 
    int reserve2; 
    int stocksum; 
    int startblock; 
    int lastblock;
};
struct INDEX_DATA{ 
    char code[10]; 
    int dayrecordnum; 
    unsigned short int record[25];
};
struct DAY_DATA
{
    int date; 
    float open; 
    float high; 
    float low; 
    float close; 
    float amount; 
    float money; 
    unsigned short int rise; 
    unsigned short int fall; 
};
int main(int argc,char**argv)
{
    int length;
    GLOBAL_DATA head;
    INDEX_DATA index;
    std::ifstream is;
    std::string dataFile("DAY.DAT");
    std::string stock;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "usage message")
        ("config,f", po::value(&dataFile), "data file")
        ("stock,s", po::value(&stock), "data file")
        ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    if (vm.count("help")) {
        std::cout << desc << "\n";
        std::cout << "usage:httpd -f [config file]" << "\n";
        return 0;
    }
    is.open (dataFile.c_str(), std::ios::binary );
    
    // get length of file:
//  is.seekg (0, std::ios::end);
//  length = is.tellg();
//  is.seekg (0, std::ios::beg);
//  std::cout<<length<<std::endl;
    // allocate memory:

    // read data as a block:
    is.read ((char*)&head,sizeof(GLOBAL_DATA));
    std::map<std::string,INDEX_DATA> stockMap;
    for(int i=0;i<head.stocksum;i++)
    {
        is.read ((char*)&index,sizeof(INDEX_DATA));
        stockMap.insert(std::make_pair<std::string,INDEX_DATA>(std::string(index.code),index));
    }
    std::map<std::string,INDEX_DATA>::iterator beg;
    std::map<std::string,INDEX_DATA>::iterator end;
    if(stock.length()>0)
    {
        beg= stockMap.find(stock);
        if(beg!=stockMap.end())
        {
            end=beg;
            ++end;
        }
    }else
    {
        beg= stockMap.begin();
        end= stockMap.end();
    }
    std::cout<<"'Date','Open','High','Low','Close','Volume','Money','Rise','Fall','Ticker'"<<std::endl;
    for(std::map<std::string,INDEX_DATA>::iterator it=beg;it!=end;++it)
    {
        char data[8192*25];
	memset(data,0,sizeof(data));
        for(int i=0;i<25;i++)
        {
            char tmp[8192];
            if(it->second.record[i]<head.startblock)
            {
                is.seekg (0x41000+8192*it->second.record[i], std::ios::beg);
                is.read (tmp,8192);
                memcpy(data+8192*i,tmp,8192);
            }
        }
        int ind=0;
        while(ind<256*25)
        {
            DAY_DATA day;
            memcpy(&day,data+ind*32,32);
            ind++;
            if(day.date==0)
                break;
            boost::posix_time::ptime pdate=boost::posix_time::from_time_t(day.date);
            std::cout<<"'"<<boost::gregorian::to_iso_extended_string(pdate.date())<<"','"<<day.open<<"','"
                     <<day.high<<"','"<<day.low<<"','"<<day.close<<"','"<<day.amount
                     <<"','"<<day.money<<"','"<<day.rise<<"','"<<day.fall<<"','"<<it->first<<"'"<<std::endl;
        }
    }
    is.close();
    return 0;
}
