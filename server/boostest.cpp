#include <boost/test/unit_test.hpp>
#include <boost/test/framework.hpp>
#include <boost/test/parameterized_test.hpp>
#include <boost/functional.hpp>
#include <boost/static_assert.hpp>
#include <boost/mem_fn.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>
#include "Factory.h"
#include "testpro/testpro.h"
using namespace boost;
using namespace boost::unit_test;
using namespace std;
void testfun()
{
  try
    {
     Factory<testProduct> *fact=Factory<testProduct>::Instance();
     std::string proName="testpro/testpro";
     fact-> Register(proName);
     testProduct *tp=fact->CreateObject(proName);
     tp->print();
    }
  catch(BaseException e)
    {
      std::cout<<e.what()<<std::endl;
    }
}
test_suite*
init_unit_test_suite( int argc, char* argv[] )
{
  test_suite* ts1 = BOOST_TEST_SUITE( "test_suite1" );
  ts1->add( BOOST_TEST_CASE( &testfun ) );
  framework::master_test_suite().add( ts1 );
  return 0;
}
