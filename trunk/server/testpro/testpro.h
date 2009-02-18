#ifndef _TESTPRO_
#define _TESTPRO_

#ifdef __cplusplus 
extern "C"
{
#endif
     void *testpro_create();
#ifdef __cplusplus      
}
#endif
class testProduct
{
public:
     testProduct()
	  :a(10),b(20)
	  {
	  }
     ~testProduct()
	  {}
     virtual void print();
private:
     int a;
     int b;
};
#endif
