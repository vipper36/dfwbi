#ifndef __YAHOO_PARSER_H__
#define __YAHOO_PARSER_H__
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <string>
#include <complex>

namespace yahoo
{
  namespace qi = boost::spirit::qi;
  namespace standard  = boost::spirit::standard ;
  struct DayPrice
  {
    int date;
    double open;
    double high;
    double low;
    double close;
    double volum;
    double money;
  };
  struct YearData
  {
    int year;
    std::list<DayPrice> price_list;
  };

  struct YearsData
  {
    std::list<YearData> year_list;
  };
  
  struct MinPrice
  {
    double open;
    double high;
    double low;
    double close;
    double volum;
    double money;
  };
  struct DayData
  {
    int date;
    std::list<MinPrice> price_list;
  };
  struct DaysData
  {
    int date;
    std::list<DayData> price_list;
  };
}
  BOOST_FUSION_ADAPT_STRUCT(
			    yahoo::DayPrice,
			    (int, date)
			    (double, open)
			    (double, high)
			    (double, low)
			    (double, close)
			    (double, volum)
			    (double, money)
			    )
  BOOST_FUSION_ADAPT_STRUCT(
			    yahoo::YearData,
			    (int, year)
			    (std::list<yahoo::DayPrice>, price_list)
			    )
  BOOST_FUSION_ADAPT_STRUCT(
        		    yahoo::YearsData,
        		    (std::list<yahoo::YearData>, year_list)
        		    )
  BOOST_FUSION_ADAPT_STRUCT(
			    yahoo::MinPrice,
			    (double, open)
			    (double, high)
			    (double, low)
			    (double, close)
			    (double, volum)
			    (double, money)
			    )
  BOOST_FUSION_ADAPT_STRUCT(
			    yahoo::DayData,
			    (int, date)
			    (std::list<yahoo::MinPrice>, price_list)
			    )
  BOOST_FUSION_ADAPT_STRUCT(
        		    yahoo::DaysData,
        		    (std::list<yahoo::DayData>, day_list)
        		    )
namespace yahoo
{
  template <typename Iterator>
  struct yhday_parser : qi::grammar<Iterator, DayPrice(), standard::space_type>
  {
    yhday_parser() : yhday_parser::base_type(start)
    {
      using qi::int_;
      using qi::lit;
      using qi::double_;

      start =
	'['>>int_ >> ','
	>>  double_ >> ','
	>>  double_ >> ','
	>>  double_ >> ','
	>>  double_ >> ','
	>>  double_ >> ','
	>>  double_ >> ']'
	;
    }
    qi::rule<Iterator, DayPrice(), standard::space_type> start;
  };

  template <typename Iterator>
  struct yhy_parser : qi::grammar<Iterator, YearData(), standard::space_type>
  {
    yhy_parser() : yhy_parser::base_type(start)
    {
      using qi::int_;
      using qi::lit;

      start =
	"[\"">>  int_ >> "\",\"["
	>>  yhday_%',' >>  "]\"]"
	;
    }
    yhday_parser<Iterator> yhday_;
    qi::rule<Iterator, YearData(), standard::space_type> start;
  };

  template <typename Iterator>
  struct yhyl_parser : qi::grammar<Iterator, YearsData(), standard::space_type>
  {
    yhyl_parser() : yhyl_parser::base_type(start)
    {
      start =
          '['>>yhy_%','>>"]0"
        ;
    }
    yhy_parser<Iterator> yhy_;
    qi::rule<Iterator, YearsData(), standard::space_type> start;
  };
  
  template <typename Iterator>
  struct yhmin_parser : qi::grammar<Iterator, MinPrice(), standard::space_type>
  {
    yhmin_parser() : yhmin_parser::base_type(start)
    {
      using qi::lit;
      using qi::double_;

      start =
	'['>> double_ >> ','
	>>  double_ >> ','
	>>  double_ >> ','
	>>  double_ >> ','
	>>  double_ >> ','
	>>  double_ >> ']'
	;
    }
    qi::rule<Iterator, MinPrice(), standard::space_type> start;
  };
  template <typename Iterator>
  struct yhd_parser : qi::grammar<Iterator, DayData(), standard::space_type>
  {
    yhd_parser() : yhd_parser::base_type(start)
    {
      using qi::int_;
      using qi::lit;

      start =
	"[" >>  int_ >> ",\"["
	>>  yhmin_%',' >>  "]\"]"
	;
    }
    yhmin_parser<Iterator> yhmin_;
    qi::rule<Iterator, DayData(), standard::space_type> start;
  };
  template <typename Iterator>
  struct yhdl_parser : qi::grammar<Iterator, DaysData(), standard::space_type>
  {
    yhdl_parser() : yhdl_parser::base_type(start)
    {
      start =
          '['>>yhd_%','>>"]0"
        ;
    }
    yhd_parser<Iterator> yhd_;
    qi::rule<Iterator, DaysData(), standard::space_type> start;
  };
}
#endif
