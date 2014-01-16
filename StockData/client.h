#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <queue>
#include <boost/smart_ptr.hpp>
#include <climits>
#include "response.h"
#include "request.h"
#include "ResHandler.h"
using boost::asio::deadline_timer;
using boost::asio::ip::tcp;
struct smart_buffer
{
    smart_buffer():len(0),data() {}
    uint len;
    boost::shared_ptr<char> data;
};
class client
{
public:
    client(boost::asio::io_service& io_service)
        : stopped_(false),
          socket_(io_service),
          deadline_(io_service),
          heartbeat_timer_(io_service),
          writewait_(io_service),
          requestQue(),
          history(true)
    {
    }
    template <typename REQ>
    void send(REQ request)
    {
        smart_buffer buffer;
        buffer.len=sizeof(request);
        buffer.data.reset(new char[buffer.len]);
        memcpy(buffer.data.get(),&request,buffer.len);
        requestQue.push(buffer);
    }
    void send(StockMarket::StockKLineStruct request)
    {
        char code[StockMarket::MarketInfo::StocksCodeLen+1];
        memset(code,0,sizeof(code));
        memcpy(code,request.stock_code,StockMarket::MarketInfo::StocksCodeLen);
        handler.addSeq(request.header.seq_id,std::string(code));
        smart_buffer buffer;
        buffer.len=sizeof(request);
        buffer.data.reset(new char[buffer.len]);
        memcpy(buffer.data.get(),&request,buffer.len);
        requestQue.push(buffer);
    }
    void send(char* data,std::size_t len)
    {
        smart_buffer buffer;
        buffer.len=len;
        buffer.data.reset(new char[buffer.len]);
        memcpy(buffer.data.get(),data,buffer.len);
        requestQue.push(buffer);
    }
    void start(tcp::resolver::iterator endpoint_iter)
    {
        start_connect(endpoint_iter);

        deadline_.async_wait(boost::bind(&client::check_deadline, this));
    }

    void stop()
    {
        stopped_ = true;
        boost::system::error_code ignored_ec;
        socket_.close(ignored_ec);
        deadline_.cancel();
        heartbeat_timer_.cancel();
    }
    uint getSeq(ushort cmd)
    {
        uint ret=0;
        if(sequence.find(cmd)!=sequence.end())
        {
            ret=sequence[cmd];
            if(sequence[cmd]==UINT_MAX)
                sequence[cmd];
            else
                sequence[cmd]++;

        }else{
            sequence.insert(std::make_pair(cmd,1));
        }
        return ret;
    }
    void setType(bool his)
    {
        history=his;
    }
private:
    void start_connect(tcp::resolver::iterator endpoint_iter)
    {
        if (endpoint_iter != tcp::resolver::iterator())
        {
            std::cout << "Trying " << endpoint_iter->endpoint() << "...\n";

            deadline_.expires_from_now(boost::posix_time::seconds(60));

            socket_.async_connect(endpoint_iter->endpoint(),
                                  boost::bind(&client::handle_connect,
                                              this, _1, endpoint_iter));
        }
        else
        {
            stop();
        }
    }

    void handle_connect(const boost::system::error_code& ec,
                        tcp::resolver::iterator endpoint_iter)
    {
        if (stopped_)
            return;

        if (!socket_.is_open())
        {
            std::cout << "Connect timed out\n";

            start_connect(++endpoint_iter);
        }
        else if (ec)
        {
            std::cout << "Connect error: " << ec.message() << "\n";

            socket_.close();
            start_connect(++endpoint_iter);
        }
        else
        {
            std::cout << "Connected to " << endpoint_iter->endpoint() << "\n";

            start_read();

            start_write();

            start_heartbeat();
        }
    }
    void write_heartbeat(const boost::system::error_code& error,std::size_t bytes_transferred)
    {
        if (stopped_)
            return;

        if (!error)
        {
            // Wait 10 seconds before sending the next heartbeat.
            heartbeat_timer_.expires_from_now(boost::posix_time::seconds(2));
            heartbeat_timer_.async_wait(boost::bind(&client::start_heartbeat, this));
            StockMarket::MarketInfo::MarketType m=handler.getMarcket();
            while(true)
            {
                if(m<0)
                    break;
                std::cout << "query marcket: " << m<<" offset"<< handler.getOffset(m)<< "\n";
                StockMarket::StockListStruct req(m, handler.getOffset(m), 50);
                req.header.seq_id=getSeq(StockMarket::CMD_STOCK_LIST);
                send(req);
                m=handler.getMarcket();
            }
            if(history)
            {
                std::string code=handler.getStock();
                if(code.length()>0)
                {
                    for(int i=12; i>=0; i--)
                    {
                        std::cout << "query code: " << code << "\n";
                        StockMarket::StockKLineStruct req(code,1,4,getSeq(StockMarket::CMD_STOCK_KLINE),i);
                        send(req);
                    }
                }
            }else
            {
                for(int i=0; i<=12; i++)
                {
                    std::string code=handler.getStock();
                    if(code.length()>0)
                    {
                        std::cout << "query code: " << code << "\n";
                        StockMarket::StockKLineStruct req(code,1,4,getSeq(StockMarket::CMD_STOCK_KLINE));
                        send(req);
                    }

                }
            }


        }
        else
        {
            std::cout << "Error on heartbeat: " << error.message() << "\n";

            stop();
        }
    }
    void start_heartbeat()
    {
        if (stopped_)
            return;

        StockMarket::StockHeartBeatStruct heartBeat(getSeq(StockMarket::CMD_HEART_BEAT));

        std::cout << "send heartbeat seq " <<  heartBeat.header.seq_id<<":"<<sizeof(heartBeat)<<":"<<heartBeat.header.cmd<< "\n";
        boost::asio::async_write(socket_, boost::asio::buffer(&heartBeat,sizeof(heartBeat)),
                                 boost::bind(&client::write_heartbeat, this, _1,_2));
    }
    void start_read()
    {
        deadline_.expires_from_now(boost::posix_time::seconds(60));
        next_count=sizeof(StockMarket::ResHead);
        left_inbuf=0;
        boost::asio::async_read(socket_, input_buffer_, boost::bind(&client::data_completion_condition, this, _1,_2),
                                boost::bind(&client::handle_readhead, this, _1,_2));
    }
    bool data_completion_condition(const boost::system::error_code& error,std::size_t bytes_transferred)
    {
        if (!error)
        {
            if(bytes_transferred>=next_count)
                return true;
            else
                return false;
        }
        else
        {
            stop();
            return false;
        }
    }
    void readHead()
    {
        std::auto_ptr<char> tmp(new char [sizeof(StockMarket::ResHead)]);
        std::istream is(&input_buffer_);
        is.read(tmp.get(),sizeof(StockMarket::ResHead));
        response.setHead(tmp.get());
    }
    void readData()
    {
        if(response.getHead().len1>0)
        {
            std::auto_ptr<char> tmp(new char [response.getHead().len1]);
            std::istream is(&input_buffer_);
            is.read(tmp.get(),response.getHead().len1);
            response.setData(tmp.get());
        }
    }
    void handle_readhead(const boost::system::error_code& ec,std::size_t bytes_transferred)
    {
        if (stopped_)
            return;
        std::cout << "read: " << bytes_transferred << "...\n";
        if (!ec)
        {
            std::size_t read_size=0;
            while(true)
            {
                if(read_size+sizeof(StockMarket::ResHead)<=bytes_transferred+left_inbuf)
                {
                    readHead();
                    read_size+=sizeof(StockMarket::ResHead);
                    std::cout << "handle head size: " << read_size << "...\n";
                    if(read_size+response.getHead().len1<=bytes_transferred+left_inbuf)
                    {
                        readData();
                        handler(response);
                        read_size+=response.getHead().len1;
                        std::cout << "handle data size: " << read_size << "...\n";
                        memset(&response,0,sizeof(response));

                    }
                    else
                    {
                        next_count=read_size+response.getHead().len1-(bytes_transferred+left_inbuf);
                        left_inbuf=(bytes_transferred+left_inbuf)-read_size;
                        std::cout << "next_count: " << next_count << "...\n";
                        deadline_.expires_from_now(boost::posix_time::seconds(60));
                        boost::asio::async_read(socket_, input_buffer_, boost::bind(&client::data_completion_condition, this, _1,_2),
                                                boost::bind(&client::handle_readdata, this, _1,_2));
                        break;
                    }
                }
                else
                {
                    next_count=read_size+sizeof(StockMarket::ResHead)-(bytes_transferred+left_inbuf);
                    left_inbuf=(bytes_transferred+left_inbuf)-read_size;
                    std::cout << "next_count: " << next_count << "...\n";
                    deadline_.expires_from_now(boost::posix_time::seconds(60));
                    boost::asio::async_read(socket_, input_buffer_, boost::bind(&client::data_completion_condition, this, _1,_2),
                                            boost::bind(&client::handle_readhead, this, _1,_2));
                    break;
                }
            }
        }
        else
        {
            std::cout << "Error on receive: " << ec.message() << "\n";
            stop();
        }
    }
    void handle_readdata(const boost::system::error_code& ec,std::size_t bytes_transferred)
    {
        if (stopped_)
            return;
        std::cout << "read: " << bytes_transferred << "...\n";
        if (!ec)
        {
            std::size_t read_size=0;
            while(true)
            {
                if(read_size+response.getHead().len1<=(bytes_transferred+left_inbuf))
                {
                    readData();
                    handler(response);
                    read_size+=response.getHead().len1;
                    memset(&response,0,sizeof(response));
                    std::cout << "handle data size: " << read_size << "...\n";
                    if(read_size+sizeof(StockMarket::ResHead)<=(bytes_transferred+left_inbuf))
                    {
                        readHead();
                        read_size+=sizeof(StockMarket::ResHead);
                        std::cout << "handle head size: " << read_size << "...\n";
                    }
                    else
                    {
                        next_count=read_size+sizeof(StockMarket::ResHead)-(bytes_transferred+left_inbuf);
                        left_inbuf=(bytes_transferred+left_inbuf)-read_size;
                        std::cout << "next_count: " << next_count << "...\n";
                        deadline_.expires_from_now(boost::posix_time::seconds(60));
                        boost::asio::async_read(socket_, input_buffer_, boost::bind(&client::data_completion_condition, this, _1,_2),
                                                boost::bind(&client::handle_readhead, this, _1,_2));
                        break;
                    }
                }
                else
                {
                    next_count=read_size+response.getHead().len1-(bytes_transferred+left_inbuf);
                    left_inbuf=(bytes_transferred+left_inbuf)-read_size;
                    std::cout << "next_count: " << next_count << "...\n";
                    deadline_.expires_from_now(boost::posix_time::seconds(60));
                    boost::asio::async_read(socket_, input_buffer_, boost::bind(&client::data_completion_condition, this, _1,_2),
                                            boost::bind(&client::handle_readdata, this, _1,_2));
                    break;
                }
            }
        }
        else
        {
            std::cout << "Error on receive: " << ec.message() << "\n";
            stop();
        }
    }

    void start_write()
    {
        if (stopped_)
            return;
        if(!requestQue.empty())
        {
            smart_buffer buffer=requestQue.front();
            boost::asio::async_write(socket_, boost::asio::buffer(buffer.data.get(),buffer.len),
                                     boost::bind(&client::handle_write, this, _1,_2));
            requestQue.pop();
        }
        else
        {
            writewait_.expires_from_now(boost::posix_time::seconds(1));
            writewait_.async_wait(boost::bind(&client::start_write, this));
        }
    }

    void handle_write(const boost::system::error_code& error,std::size_t bytes_transferred)
    {
        if (stopped_)
            return;

        if (!error)
        {

            if(!requestQue.empty())
            {
                smart_buffer buffer=requestQue.front();
                boost::asio::async_write(socket_, boost::asio::buffer(buffer.data.get(),buffer.len),
                                         boost::bind(&client::handle_write, this, _1,_2));
                requestQue.pop();
            }
            else
            {
                writewait_.expires_from_now(boost::posix_time::seconds(1));
                writewait_.async_wait(boost::bind(&client::start_write, this));
            }

        }
        else
        {
            std::cout << "Error on heartbeat: " << error.message() << "\n";

            stop();
        }
    }

    void check_deadline()
    {
        std::cout << "check_deadline....."<<"\n";
        if (stopped_)
            return;


        if (deadline_.expires_at() <= deadline_timer::traits_type::now())
        {
            std::cout << "close socket..."<<"\n";
            socket_.close();

            deadline_.expires_at(boost::posix_time::pos_infin);
        }
        deadline_.async_wait(boost::bind(&client::check_deadline, this));
    }
private:
    bool stopped_;
    tcp::socket socket_;
    deadline_timer deadline_;
    deadline_timer writewait_;
    boost::asio::streambuf input_buffer_;
    StockMarket::Response response;
    std::queue<smart_buffer> requestQue;
    StockMarket::ResHandler handler;
    deadline_timer heartbeat_timer_;
    std::size_t next_count;
    std::size_t left_inbuf;
    std::map<ushort,uint> sequence;
    bool history;
};


#endif // CLIENT_H_INCLUDED
