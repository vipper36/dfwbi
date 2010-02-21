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
  namespace ascii = boost::spirit::ascii;

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
namespace yahoo
{
  template <typename Iterator>
  struct yhday_parser : qi::grammar<Iterator, DayPrice(), ascii::space_type>
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
    qi::rule<Iterator, DayPrice(), ascii::space_type> start;
  };

  template <typename Iterator>
  struct yhy_parser : qi::grammar<Iterator, YearData(), ascii::space_type>
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
    qi::rule<Iterator, YearData(), ascii::space_type> start;
  };
  
  template <typename Iterator>
  struct yhmin_parser : qi::grammar<Iterator, MinPrice(), ascii::space_type>
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
    qi::rule<Iterator, MinPrice(), ascii::space_type> start;
  };
  template <typename Iterator>
  struct yhd_parser : qi::grammar<Iterator, DayData(), ascii::space_type>
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
    qi::rule<Iterator, DayData(), ascii::space_type> start;
  };
}
#endif
