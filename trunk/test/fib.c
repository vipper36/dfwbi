#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
int main(int argc,char** argv)
{
     if(argc<2)
	  cout<<"input param!!"<<endl;
     int count=atoi(argv[1]);
     int fib1=1;
     int fib2=1;
     for(int i=0;i<count;i++)
     {
	  fib1=fib1+fib2;
	  fib2=fib1+fib2;
	  cout<<"fib1="<<fib1<<" fib2="<<fib2<<endl;
	  double gold=((double)fib2)/((double)fib1);
	  printf("gold=%.20f\n",gold);
     }
	  
}
