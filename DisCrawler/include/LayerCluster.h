
#include <string>
#include <map>
#include <list>
#include "distance.h"
#ifndef __LAYERCLUSTER_H__
#define __LAYERCLUSTER_H__
class LayerCluster
{
private:
     Distance ld;
     std::map<int,std::list<std::string> > vatts;
     std::list<std::pair<int, std::list<int> > > classes;
     std::map<int,double> distMap;
public:
     LayerCluster()
	  :vatts(),classes(),distMap()
     {
     }
     bool AddString(std::string str,int i);
     bool AddString(std::list<std::string> &list,int index);
     bool AddString(const std::map<int,std::list<std::string> > &strs);
     std::list<int> GetClassID();
     std::list<int> GetClassByID(int id);
     std::list<std::string> GetAtt(int index);
     int CacuCenter(std::list<int> &indexs);
     bool ChangeCenter(std::string dest);
     double CacuTDist(std::list<int> &indexs,int index);
     double GetClassDist(int index);
     double AttDist(int i,int j);
     bool Cluster(int dy_high,int dy_low);
     std::pair<int, std::list<int> > MergeClass(const std::pair<int, std::list<int> > &class1,const std::pair<int, std::list<int> > &class2);
     void printClass();
     void printAtts();
     
};

#endif
