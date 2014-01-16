#ifndef RESHANDLER_H
#define RESHANDLER_H
#include <iostream>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include "mongo/client/dbclient.h"
#include <boost/uuid/sha1.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/device/file.hpp>
#include <sstream>
#include <fstream>
#include "response.h"
namespace StockMarket
{
class ResHandler
{
public:
    ResHandler()
    {
        c.connect("localhost");
    }
    ~ResHandler() {}
    void operator ()(Response &res)
    {
        std::cout << "head...\n";
        std::cout << res.getHead().finger<<"..\n";
        std::cout << (int)res.getHead().zip<<"..\n";
        std::cout << res.getHead().cmd<<"..\n";
        std::cout << res.getHead().len1<<"..\n";
        std::cout << res.getHead().len2<<"..\n";
        std::cout << res.getHead().seq_id<<"..\n";

        if(res.getHead().cmd==StockMarket::CMD_STOCK_LIST)
        {
            boost::iostreams::stream_buffer<boost::iostreams::array_source>  buf(res.getData().get(), res.getHead().len1);
            if(res.getHead().zip==0x0c)
            {
                std::istream in(&buf);
                HandleList(in);
            }else
            {
                boost::iostreams::filtering_istream in;
                in.push(boost::iostreams::zlib_decompressor());
                in.push(buf);
                HandleList(in);
            }

        }
        else if(res.getHead().cmd==StockMarket::CMD_STOCK_KLINE&&res.getHead().len1>100)
        {

            boost::iostreams::stream_buffer<boost::iostreams::array_source>  buf(res.getData().get(), res.getHead().len1);
            if(res.getHead().zip==0x0c)
            {
                std::istream in(&buf);
                if(seqCode.find(res.getHead().seq_id)!=seqCode.end())
                {
                    std::cout << "seq:"<<res.getHead().seq_id<<" code:"<<seqCode[res.getHead().seq_id]<<"..\n";
                    HandleKLine(in,seqCode[res.getHead().seq_id]);
                }
            }else
            {
//                stringstream ss;
//                ss<<res.getHead().seq_id;
//                boost::iostreams::filtering_ostream fos;
//                fos.push(boost::iostreams::zlib_decompressor());
//                fos.push(boost::iostreams::file_sink(ss.str().c_str()));
//                boost::iostreams::write(fos, res.getData().get(), res.getHead().len1);

                boost::iostreams::filtering_istream in;
                in.push(boost::iostreams::zlib_decompressor());
                in.push(buf);
                if(seqCode.find(res.getHead().seq_id)!=seqCode.end())
                {
                    std::cout << "seq:"<<res.getHead().seq_id<<" code:"<<seqCode[res.getHead().seq_id]<<"..\n";
                    HandleKLine(in,seqCode[res.getHead().seq_id]);
                }

            }

        }

    }
    void addSeq(uint seq,std::string code)
    {
        seqCode.insert(std::make_pair(seq,code));
    }
    std::string getStock()
    {
        std::string ret="";
        if(!codeQue.empty())
        {
            ret=codeQue.front();
            codeQue.pop();
        }
        return ret;
    }
    MarketInfo::MarketType getMarcket()
    {
        MarketInfo::MarketType ret=MarketInfo::MarketType(-1);
        if(!marckQue.empty())
        {
            ret=marckQue.front();
            marckQue.pop();
        }
        return ret;
    }
    ushort getOffset(MarketInfo::MarketType m)
    {
        return offsetMap[m];
    }
private:
    std::map<std::string,long> codeCurr;
    std::map<uint,std::string> seqCode;
    std::map<MarketInfo::MarketType,ushort> offsetMap;
    std::queue<std::string> codeQue;
    std::queue<MarketInfo::MarketType> marckQue;
    mongo::DBClientConnection c;
    void HandleKLine(std::istream &in,std::string code)
    {
        std::cout << "count1:"<<readShort(in)<<"..\n";
        KLine last;
        memset(&last,0,sizeof(last));
        if(codeCurr.find(code)==codeCurr.end())
        {
            mongo::Query condition = QUERY("code"<<code).sort("datetime",-1);
            mongo::BSONObj columns = BSON("datetime"<<1<<"code"<<1);
            auto_ptr<mongo::DBClientCursor> cursor=c.query("kline.day",condition,1,0,&columns,0,0);
            while (cursor->more()) {
                mongo::BSONObj p = cursor->next();
                codeCurr.insert(std::make_pair(code,p.getField("datetime").timestampInc()));
            }
        }
        while(!in.eof())
        {
            last.date=readInt(in);
            if(validDate(last.date))
            {
                int dltaopen=readLong(in);
                int dltaclose=readLong(in);
                int dltahigh=readLong(in);
                int dltalow=readLong(in);
                int mount=readLong(in);
                readInt(in);
                if(last.open==0)
                {
                    last.open=dltaopen;
                }
                else
                    last.open=last.close+dltaopen;

                last.close=last.open+dltaclose;
                last.high=last.open+dltahigh;
                last.low=last.open+dltalow;
                last.mount=mount;
                std::cout << "date:"<<last.date;
                std::cout << "open:"<<last.open<<"----"<<dltaopen<<"\n";
                std::cout << "close:"<<last.close<<"----"<<dltaclose<<"\n";
                std::cout << "high:"<<last.high<<"----"<<dltahigh<<"\n";
                std::cout << "low:"<<last.low<<"----"<<dltalow<<"\n";
                insertKline(code,last);
            }

        }
    }
    bool validDate(int date)
    {
        int year=date/10000;
        int month=(date-year*10000)/100;
        int day=date-year*10000-month*100;
        if(year<1950||year>2100)
            return false;
        if(month>12||month<1)
            return false;
        if(day>31||day<1)
            return false;

    }
    std::string sha1(std::string src)
    {
        boost::uuids::detail::sha1 s;
        char hash[20];
        memset(hash,0,sizeof(hash));
        s.process_bytes(src.c_str(), src.size());
        unsigned int digest[5];
        s.get_digest(digest);
        for(int i = 0; i < 5; ++i)
        {
            const char* tmp = reinterpret_cast<char*>(digest);
            hash[i*4] = tmp[i*4+3];
            hash[i*4+1] = tmp[i*4+2];
            hash[i*4+2] = tmp[i*4+1];
            hash[i*4+3] = tmp[i*4];
        }
        std::stringstream hashstr;
        for(int i = 0; i < 20; ++i)
        {
            hashstr<<std::hex << ((hash[i] & 0x000000F0) >> 4)
            << (hash[i] & 0x0000000F);
        }
        return hashstr.str();
    }
    void insertKline(std::string code,KLine data)
    {
        long last=0;
        std::map<std::string,long>::iterator fit=codeCurr.find(code);
        if(fit!=codeCurr.end())
            last=fit->second;
        int year=data.date/10000;
        int month=(data.date-year*10000)/100;
        int day=data.date-year*10000-month*100;
        std::cout << "year:"<<year<<"month:"<<month<<"day:"<<day<<code<<"\n";
        boost::posix_time::ptime datetime(boost::gregorian::date(year,month,day));
        boost::posix_time::ptime time_t_epoch(boost::gregorian::date(1970,1,1));
        boost::posix_time::time_duration diff = datetime - time_t_epoch;

        if(diff.total_seconds()>last)
        {
            mongo::BSONObjBuilder b;
            b  << "code"<<code;
            b  << "date"<<data.date;
            b.appendTimestamp("datetime",diff.total_seconds());
            b  << "date_iso"<<boost::posix_time::to_iso_extended_string(datetime);
            b << "open"<<data.open/1000.0;
            b << "close"<<data.close/1000.0;
            b<< "high"<<data.high/1000.0;
            b << "low"<<data.low/1000.0;
            b << "mount"<< data.mount;

            std::string uid = sha1(code+boost::posix_time::to_iso_extended_string(datetime));

            b<<"id"<<uid;
            mongo::BSONObj p = b.obj();
            std::cout<<"insert:"<<p<<std::endl;
            c.insert("kline.day",p);
        }

    }
    void HandleList(std::istream &in)
    {
        std::cout << "count1:"<<readShort(in)<<"..\n";

        uint next_flag=0;
        uint current=0;
        int data_count=0;
        boost::asio::streambuf databuf;
        std::ostream os(&databuf);
        std::istream datais(&databuf);
        std::list<std::string> codeList;
        while(!in.eof())
        {
            if(next_flag==0)
            {
                readShort(in);
                unsigned char third=readChar(in);
                unsigned char forth=readChar(in);
                std::string code=readCode(forth,in);
                codeList.push_back(code);
                unsigned char first=readChar(in);
                unsigned char second=readChar(in);
                next_flag=(uint(first)<<24)|(uint(second)<<16)|(uint(third)<<8)|uint(forth);
                data_count=0;
            }
            else
            {
                unsigned char data=readChar(in);
                current=current<<8|(uint)data;
                if(current==next_flag)
                {
                    std::vector<int> numList=readLong(datais,data_count-3);
                    std::cout << "number count:"<<numList.size()<<"..\n";
//                    Bid bid(numList);
//                    bid.print();
                    char tmp[3];
                    datais.read(tmp,3);
                    std::string code=readCode(data,in);
                    codeList.push_back(code);
                    unsigned char first=readChar(in);
                    unsigned char second=readChar(in);
                    next_flag=uint(first)<<24|uint(second)<<16|(next_flag&0xffff);
                    //std::cout <<std::hex<< "next_flag:"<<next_flag<<"..\n";
                    data_count=0;
                }
                else
                {
                    data_count++;
                    os.put(data);
                }
            }

        }
        std::cout <<"code count:"<<codeList.size()<<"..\n";
        if(codeList.size()==50)
        {
            std::string frontCode=codeList.front();
            MarketInfo::MarketType m=MarketInfo::get_market_type_from_code(frontCode.c_str());
            if(offsetMap.find(m)!=offsetMap.end())
            {
                offsetMap[m]+=50;
                std::cout << "add marcket: " << m<<" offset"<< offsetMap[m]<< "\n";
            }
            else
            {
                std::cout << "add marcket: " << m<<" offset"<< 50<< "\n";
                offsetMap.insert(std::make_pair(m,50));
            }
            marckQue.push(m);
        }
        for(std::list<std::string>::iterator it=codeList.begin(); it!=codeList.end(); ++it)
        {
            std::cout <<"code:"<<*it<<"..\n";
            codeQue.push(*it);
        }
    }
    boost::posix_time::ptime stringToDateTime(const std::string &text)
    {
        const std::locale fct(std::locale::classic(),new boost::gregorian::date_input_facet("%Y%m%d"));
        std::istringstream is(text);
        is.imbue(fct);
        boost::posix_time::ptime date;
        is >> date;
        return date;
    }
    int readLong(std::istream &in)
    {
        int number=0;
        int aByte=(int)readChar(in);
        bool negative=(aByte >= 0x40 && aByte < 0x80)  || aByte >= 0xc0;
        int i=0;
        while(aByte>=0x80)
        {
            if(i>0)
            {
                int temp=(aByte-0x80);
                for(int j=0;j<i-1;j++)
                {
                    temp=temp*0x80;
                }
                number+=temp*0x40;
            }
            else
                number+=aByte-0x80;
            aByte=(int)readChar(in);
            i++;
        }
        if(i>0)
            {
                int temp=aByte;
                for(int j=0;j<i-1;j++)
                {
                    temp=temp*0x80;
                }
                number+=temp*0x40;
            }
        else
            number=number+aByte;
        if(negative)
            number=0x40-number;
        return number;

    }
    std::vector<int> readLong(std::istream &in,int count)
    {
        std::cout << "data count:"<<count<<"..\n";
        std::vector<int> ret;
        int c=0;
        int num_count=0;
        while(c<count)
        {
            if(num_count==9)
            {
                readInt(in);
                c+=4;
            }

            if(num_count==12)
            {
                readChar(in);
                c++;
            }
            int i=0;
            int number=0;
            int aByte=(int)readChar(in);
            c++;
            bool negative=(aByte >= 0x40 && aByte < 0x80)  || aByte >= 0xc0;

            while(aByte>=0x80&&c<count)
            {
                if(i>0)
                {
                    int temp=(aByte-0x80);
                    for(int j=0;j<i-1;j++)
                    {
                        temp=temp*0x80;
                    }
                    number+=temp*0x40;
                }
                else
                    number+=aByte-0x80;
                aByte=(int)readChar(in);
                i++;
                c++;
            }
            if(i>0)
            {
                int temp=aByte;
                for(int j=0;j<i-1;j++)
                {
                    temp=temp*0x80;
                }
                number+=temp*0x40;
            }

            else
                number=number+aByte;
            if(negative)
                number=0x40-number;
            num_count++;
            ret.push_back(number);
        }
        return ret;

    }
    uint readInt(std::istream &in)
    {
        uint ret;
        in.read((char*)&ret,sizeof(ret));
        return ret;

    }
    ushort readShort(std::istream &in)
    {
        ushort ret;
        in.read((char*)&ret,sizeof(ret));
        return ret;
    }
    unsigned char readChar(std::istream &in)
    {
        unsigned char ret;
        in.read((char*)&ret,sizeof(ret));
        return ret;
    }
    std::string readCode(unsigned char first,std::istream &in)
    {
        char code[MarketInfo::StocksCodeLen+1];
        memset(code,0,MarketInfo::StocksCodeLen+1);
        in.read(code+1,MarketInfo::StocksCodeLen-1);
        code[0]=(char)first;
        return std::string(code);
    }
};
}

#endif // RESHANDLER_H
