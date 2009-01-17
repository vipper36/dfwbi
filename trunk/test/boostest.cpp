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
using namespace boost;
using namespace boost::unit_test;
using namespace std;
class myclass
{
public:
  void test(){};
};
void testfun()
{
}
class funTest:public test_suite{
public:
  funTest():test_suite("function test")
  {
    boost::shared_ptr<myclass> instance(new myclass());
    test_case *classfun=BOOST_CLASS_TEST_CASE(&myclass::test,instance);
    test_case *funtest=BOOST_TEST_CASE(testfun);
    add(classfun);
    add(funtest);
  }
};
test_suite*
init_unit_test_suite(int argc,char* argv[])
{
  std::string tmp("unit test frame");
  test_suite &mts=framework::master_test_suite();
  mts.value=tmp;
  try{
    test_suite* tmpsuit=new funTest();
    framework::master_test_suite().add(tmpsuit);
  }
  catch(boost::bad_lexical_cast const&)
    {
      throw std::exception();
    }
  return 0;
}
