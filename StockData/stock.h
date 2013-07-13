#ifndef _TDX_STOCK_H_
#define _TDX_STOCK_H_

#include <fstream>
#include <set>
#include <vector>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
namespace StockMarket
{

using namespace std;
using namespace boost;

enum CmdId
{
    CMD_STOCKHOLD_CHANGE = 0x000f,
    CMD_STOCK_LIST = 0x0524,
    CMD_INSTANT_TRANS = 0x0fc5,	// 0x0fc5, 0x0faf
    CMD_HIS_TRANS = 0x0fb5,
    CMD_HEART_BEAT = 0x0523,
    CMD_STOCK_KLINE = 0x0538
};
const static unsigned char  KLINE_FLAG= 0x4d;
typedef set<string> StringSet;
struct MarketInfo
{
    enum MarketType
    {
        MARKET_FIRST,
        MARKET_SHANGHAI_A = MARKET_FIRST,
        MARKET_SHANGHAI_B,
        MARKET_SHENZHEN_A,
        MARKET_SHENZHEN_B,
        MARKET_MAX,
        MARKET_UNKNOWN = MARKET_MAX,
    };
    static char get_block_from_market_type(MarketType t)
    {
        switch(t)
        {
        case MARKET_SHANGHAI_A:
            return 0;
        case MARKET_SHANGHAI_B:
            return 1;
        case MARKET_SHENZHEN_A:
            return 2;
        case MARKET_SHENZHEN_B:
            return 3;
        default:
            throw 0;
        }
    }
    const static int StocksCodeLen = 6;
    const static int StocksPerHand = 100;	// 100  股一手.
    const static float tax=0.003;				// 0.3 %
    static const int max_stocks_a_request = 30;
    static MarketInfo::MarketType get_market_type_from_code(const char* pCode)
    {
        if(pCode[0] == '0')
        {
            if(pCode[1] == '0')
                return MARKET_SHENZHEN_A;
        }
        else if(pCode[0] == '2')
            return MARKET_SHENZHEN_B;
        else if(pCode[0] == '6')
            return MARKET_SHANGHAI_A;
        else if(pCode[0] == '9')
        {
            if(pCode[1] == '0')
                return MARKET_SHANGHAI_B;	// 90xxxx
        }
        else
            return MARKET_UNKNOWN;
    }
    static short get_market_from_code(const char* pCode)
    {
        if(pCode[0] == '0')
        {
            if(pCode[1] == '0')
                return 0;
        }
        else if(pCode[0] == '2')
            return 0;
        else if(pCode[0] == '6')
            return 1;
        else if(pCode[0] == '9')
        {
            if(pCode[1] == '0')
                return 1;	// 90xxxx
        }
        else
            return -1;
    }

    static short get_market_type(const char* pCode)
    {
        return get_market_type_from_code(pCode);
    }

    static short get_market_type(const string& stock_code)
    {
        const char* pCode = stock_code.c_str();
        return get_market_type_from_code(pCode);
    }

    static char get_market_location_from_code(const char* pCode)
    {
        if(pCode[0] <= '4')
            return 0;					// 深圳 00xxxx, 03xxxx, 02xxxx, 3xxxxx(深圳指数)
        else
            return 1;					//上海 60xxxxx, 58xxxx, 99xxxx (上海指数)
    }

    static char get_market_location(const char* pCode)
    {
        return get_market_location_from_code(pCode);
    }

    static char get_market_location(const string& stock_code)
    {
        const char* pCode = stock_code.c_str();
        return get_market_location_from_code(pCode);
    }

};
struct KLine
{
    int     date;
    int		open;
    int		close;
    int 	high;
    int 	low;
    int		mount;
};
struct Transact
{
    short		minute;
    int			price;
    int 			vol;
    int 			count;	// 此笔成交量的成交次数。 0: 表示未知
    char		bs;		// 表示买成交量还是卖成交量0:buy, 1:sell
    bool operator == (const Transact& t)
    {
        minute=t.minute;
        price=t.price;
        vol=t.vol;
        count=t.count;
        bs=t.bs;
    }
};
struct Bid			// 盘口
{
public:
    Bid()
    {
    }
    Bid(std::vector<long> number)
    {
        posix_time::ptime now(posix_time::second_clock::local_time());
        posix_time::time_duration td(now.time_of_day());
        minute = (uint)(td.hours() * 60 + td.minutes());
        if(minute > 15 * 60)
            minute = 15 * 60;
        else if(11 * 60 + 30 < minute && minute < 13 * 60)
            minute = 11 * 60 + 30;
        price=number[0];
        y_close=price+number[1];
        open=price+number[2];
        high=price+number[3];
        low=price+number[4];

        total_vol=number[7];
        avail_vol=number[8];
        inner_vol=number[9];
        outer_vol=number[10];

        updown=number[11];

        buy_price1=price+number[12];
        sell_price1=price+number[13];
        buy_vol1=number[14];
        sell_vol1=number[15];
        buy_price2=price+number[16];
        sell_price2=price+number[17];
        buy_vol2=number[18];
        sell_vol2=number[19];
        buy_price3=price+number[20];
        sell_price3=price+number[21];
        buy_vol3=number[22];
        sell_vol3=number[23];
        buy_price4=price+number[24];
        sell_price4=price+number[25];
        buy_vol4=number[26];
        sell_vol4=number[27];
        buy_price5=price+number[28];
        sell_price5=price+number[29];
        buy_vol5=number[30];
        sell_vol5=number[31];
    }
    void print()
    {
        std::cout<<"minute:"<<minute<<"\n";
        std::cout<<"price:"<<price<<"\n";
        std::cout<<"y_close:"<<y_close<<"\n";
        std::cout<<"open:"<<open<<"\n";
        std::cout<<"high:"<<high<<"\n";
        std::cout<<"low:"<<low<<"\n";

        std::cout<<"total_vol:"<<total_vol<<"\n";
        std::cout<<"avail_vol:"<<avail_vol<<"\n";
        std::cout<<"inner_vol:"<<inner_vol<<"\n";
        std::cout<<"outer_vol:"<<outer_vol<<"\n";

        std::cout<<"updown:"<<updown<<"\n";

        std::cout<<"buy_price1:"<<buy_price1<<"\n";
        std::cout<<"sell_price1:"<<sell_price1<<"\n";
        std::cout<<"buy_vol1:"<<buy_vol1<<"\n";
        std::cout<<"sell_vol1:"<<sell_vol1<<"\n";
        std::cout<<"buy_price2:"<<buy_price2<<"\n";
        std::cout<<"sell_price2:"<<sell_price2<<"\n";
        std::cout<<"buy_vol2:"<<buy_vol2<<"\n";
        std::cout<<"sell_vol2:"<<sell_vol2<<"\n";
        std::cout<<"buy_price3:"<<buy_price3<<"\n";
        std::cout<<"sell_price3:"<<sell_price3<<"\n";
        std::cout<<"buy_vol3:"<<buy_vol3<<"\n";
        std::cout<<"sell_vol3:"<<sell_vol3<<"\n";
        std::cout<<"buy_price4:"<<buy_price4<<"\n";
        std::cout<<"sell_price4:"<<sell_price4<<"\n";
        std::cout<<"buy_vol4:"<<buy_vol4<<"\n";
        std::cout<<"sell_vol4:"<<sell_vol4<<"\n";
        std::cout<<"buy_price5:"<<buy_price5<<"\n";
        std::cout<<"sell_price5:"<<sell_price5<<"\n";
        std::cout<<"buy_vol5:"<<buy_vol5<<"\n";
        std::cout<<"sell_vol5:"<<sell_vol5<<"\n";
    }
    int			minute;
    int			price;			// 现价
    int			y_close;			// 昨收
    int			open;			// 开盘
    int			high;			// 最高
    int			low;				// 最低
//    int			buy;			// 买入
//    int			sell;			// 卖出

    int			total_vol;		// 总手，以股数计算
    int			avail_vol;		// 现手，以股数计算
    int			inner_vol;		// 内盘
    int			outer_vol;		// 外盘

    int			updown;			// 单笔升跌

    int			buy_price1;	// 买价1
    int			sell_price1;
    int			buy_vol1;	// 买量1
    int			sell_vol1;
    int			buy_price2;
    int			sell_price2;
    int			buy_vol2;
    int			sell_vol2;
    int			buy_price3;
    int			sell_price3;
    int			buy_vol3;
    int			sell_vol3;
    int			buy_price4;
    int			sell_price4;
    int			buy_vol4;
    int			sell_vol4;
    int			buy_price5;
    int			sell_price5;
    int			buy_vol5;
    int			sell_vol5;

};

struct BaseInfo
{
    string			stock_code;
    uint				update_time;
    double			ttl_amount;			// 总股本
    double			state_own_amount;	// 国家股
    double			init_amount;			// 发起股本
    double			corp_amount;		// 法人股本
    double			b_amount;			// B 股本
    double			h_amount;			// H 股本
    double			cir_amount;			// 流通 股本
    double			empl_amount;		// 职工 股本
    double			unknown1;			//
    double			ttl_asset;			// 总资产
    double			varible_asset;		// 流动 资产
    double			firm_asset;			// 固定 资产
    double			invisible_asset;		// 无形 资产
    double			long_term_invest;	// 长期投资
    double			varible_debt;		// 流动负债
    double			long_term_debt;		// 长期负债
    double			accu_fund;			// 公积金
    double			net_asset;			// 净资产
    double			major_income;		// 主营收入
    double			major_profit;		// 主营利润
    double			unknown2;			//
    double			bussiness_income;	// 营业收入
    double			invest_income;		// 营业收入
    double			allowance;			// 补贴收入
    double			non_bussiness_income;	// 业外收入
    double			income_adjustment;	// 收入调整
    double			ttl_profit;			// 利润总额
    double			unknown3;			//
    double			net_profit;			// 税后利润
    double			undist_profit;		// 未分配利润
    double			per_net_assert2;	// 每股净资产2
    static const int		record_len;
};
struct GBBQ
{
    string			code;
    char			chg_type;
// 变更类型
// 1: 正常
// 2: 与1相关的除权除息日股本变化
// 3:股本性质变化(例如职工股上市)
// 6: 增发.
// 8: 增发上市
    union
    {
        struct
        {
            float				cash;	 			// 每10 分红
            float				sell_price;			// 每股配售价格
            float				give_count;			// 每10 股送股数
            float				sell_count;			// 每10 股配售数
        } bonus;
        struct
        {
            float				old_cir;	 			// 旧流通股
            float				old_ttl;				// 旧总股本
            float				new_cir;			// 新流通股
            float				new_ttl;				// 新总股本
        } gb;
    } data;
};
}

#endif

