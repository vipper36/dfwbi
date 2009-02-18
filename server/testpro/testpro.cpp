#include <iostream>
#include "testpro.h"
void *testpro_create()
{
     testProduct *ret=new testProduct();
     return (void*)ret;
}
void testProduct::print()
{
     std::cout<<"a:"<<a<<std::endl;
     std::cout<<"b:"<<b<<std::endl;
}
