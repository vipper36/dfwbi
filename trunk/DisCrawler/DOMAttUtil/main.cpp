#include <iostream>
#include <fstream>
#include "LayerCluster.h"
#include <functional>
#include <algorithm>
int main(int argc,char* argv[])
{
     LayerCluster lc;
     std::ifstream ifs(argv[1]);
     int i=0;
     while(!ifs.eof())
     {
	  std::string line;
	  getline(ifs,line);
	  if(line.length()>0)
	  {
	       
	       lc.AddString(line,i);
	       i++;
	  }
	  
     }
     lc.printAtts();
     
     lc.Cluster(10,4);
     lc.printClass();
     
}
