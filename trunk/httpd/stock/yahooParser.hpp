#ifndef __YAHOO_PARSER_H__
#define __YAHOO_PARSER_H__
#include <boost/config/warning_disable.hpp>
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

     ///////////////////////////////////////////////////////////////////////////
     //  Our employee struct
     ///////////////////////////////////////////////////////////////////////////
     //[tutorial_employee_struct
     struct DayPrice
     {
	  std::string date;
	  double open;
	  double high;
	  double low;
	  double close;
	  double volum;
	  double money;
     };
     //]

// We need to tell fusion about our employee struct
// to make it a first-class fusion citizen. This has to
// be in global scope.

//[tutorial_employee_adapt_struct
     BOOST_FUSION_ADAPT_STRUCT(
	  client::DayPrice,
	  (std::string, date)
	  (double, open)
	  (double, high)
	  (double, low)
	  (double, close)
	  (double, volum)
	  (double, money)
	  )
     //]


     ///////////////////////////////////////////////////////////////////////////////
     //  Our employee parser
     ///////////////////////////////////////////////////////////////////////////////
     //[tutorial_employee_parser
     template <typename Iterator>
     struct employee_parser : qi::grammar<Iterator, employee(), ascii::space_type>
     {
	  employee_parser() : employee_parser::base_type(start)
	       {
		    using qi::int_;
		    using qi::lit;
		    using qi::double_;
		    using qi::lexeme;
		    using ascii::char_;

		    quoted_string %= lexeme['"' >> +(char_ - '"') >> '"'];

		    start %=
			 lit("employee")
			 >> '{'
			 >>  int_ >> ','
			 >>  quoted_string >> ','
			 >>  quoted_string >> ','
			 >>  double_
			 >>  '}'
			 ;
	       }

	  qi::rule<Iterator, std::string(), ascii::space_type> quoted_string;
	  qi::rule<Iterator, employee(), ascii::space_type> start;
     };
     //]
}
