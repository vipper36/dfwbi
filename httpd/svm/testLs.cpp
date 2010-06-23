#include <iostream>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>
#include <boost/numeric/ublas/io.hpp>

#include "LSFitting.h"
using namespace boost::numeric::ublas;
int main()
{
  matrix<double>  x(5,2);
  x(0,0)=2000;
  x(1,0)=2001;
  x(2,0)=2002;
  x(3,0)=2003;
  x(4,0)=2004;
  x(0,1)=1;
  x(1,1)=1;
  x(2,1)=1;
  x(3,1)=1;
  x(4,1)=1;
  std::cout<<x<<std::endl;
  vector<double>  y(5);
  y(0)=9.34;
  y(1)=8.50;
  y(2)=7.62;
  y(3)=6.93;
  y(4)=6.60;
  std::cout<<y<<std::endl;
  lsf::LSFitting<double> ls(x,y);
  ls.calcParams();
  std::cout<<ls.getParams()<<std::endl;
  std::cout<<"ls end!"<<std::endl;
}
