#include "LayerCluster.h"
#include <functional>
#include <algorithm>
#include <iostream>
#include <limits.h>
struct addValue:public std::binary_function< std::list<int>&,std::pair<int, std::list<int> >,bool>
{
     bool operator()(std::list<int> &indexs, std::pair<int, std::list<int> > i) const
	  {
	       indexs.push_back(i.first);
	       return true;
	  }
};
struct addIndex:public std::binary_function< std::list<std::pair<int, std::list<int> > >&,std::pair<int,std::list<std::string> >,bool>
{
     bool operator()(std::list<std::pair<int, std::list<int> > > &cls,std::pair<int,std::list<std::string> > i) const
	  {
	       std::list<int> tmpList;
	       tmpList.push_back(i.first);
	       cls.push_back(make_pair(i.first,tmpList));
	       return true;
	       
	  }
};
struct IntPrt:public std::binary_function< std::map<int,std::list<std::string> > &,int,void>
{
     void operator()(std::map<int,std::list<std::string> > &cls,int i) const
	  {
	       
	       std::cout<<i<<"---"<<std::endl;
	       for(std::list<std::string>::iterator it=cls[i].begin();it!=cls[i].end();++it)
		    std::cout<<"  :--"<<*it<<std::endl;
	  }
};

struct AttPrt
{
     bool operator()(std::pair<int, std::list<std::string> > att) const
	  {
	       std::cout<<att.first<<"---"<<std::endl;
	       for(std::list<std::string>::iterator it=att.second.begin();it!=att.second.end();++it)
		    std::cout<<"  :--"<<*it<<std::endl;
	  }
};
struct ClassPrt:public std::binary_function< std::map<int,std::list<std::string> > &,std::pair<int, std::list<int> > ,bool>
{
     bool operator()(std::map<int,std::list<std::string> > &cls, std::pair<int, std::list<int> > cl) const
	  {
	       
	       std::cout<<"class:"<<cl.first<<std::endl;
	       std::for_each(cl.second.begin(),cl.second.end(),bind1st(IntPrt(),cls));
	  }
};
std::list<std::string> LayerCluster::GetAtt(int index)
{
     return vatts[index];
}

bool LayerCluster::AddString(std::string str,int index)
{
     std::map<int,std::list<std::string> >::iterator fit=vatts.find(index);
     if(fit!=vatts.end())
	  fit->second.push_back(str);
     else
     {
	  std::list<std::string> tmp;
	  tmp.push_back(str);
	  vatts.insert(std::make_pair(index,tmp));
     }
	  
}
bool LayerCluster::AddString(std::list<std::string> &list,int index)
{
     std::map<int,std::list<std::string> >::iterator fit=vatts.find(index);
     if(fit!=vatts.end())
	  for(std::list<std::string>::iterator it=list.begin();it!=list.end();++it)
	       fit->second.push_back(*it);
     else
     {
	  vatts.insert(std::make_pair(index,list));
     }
     
}

bool LayerCluster::AddString(const std::map<int,std::list<std::string> >&strs)
{
     vatts.insert(strs.begin(),strs.end());
}

std::list<int> LayerCluster::GetClassID()
{
     std::list<int> ret;
     addValue av;
     std::for_each(classes.begin(),classes.end(),std::bind1st(av,ret));
     return ret;
}

std::list<int> LayerCluster::GetClassByID(int id)
{
     for(std::list<std::pair<int, std::list<int> > >::iterator it=classes.begin();it!=classes.end();++it)
     {
	  if(it->first==id)
	       return it->second;
     }
     return std::list<int>();
}
double LayerCluster::GetClassDist(int id)
{
     for(std::list<std::pair<int, std::list<int> > >::iterator it=classes.begin();it!=classes.end();++it)
     {
	  if(it->first==id)
	  {
	       double dist=CacuTDist(it->second,it->first);
	
	       return dist/double(it->second.size());
	  }
     }
     return -1;
}

bool LayerCluster::Cluster(int dy_high,int dy_low)
{

     std::for_each(vatts.begin(),vatts.end(),std::bind1st(addIndex(),classes));
     while(1)
     {  
	  double min=INT_MAX;
	  std::list<std::pair<int, std::list<int> > >::iterator tit1,tit2;
	  bool hasMerg;
	  hasMerg=false;
	  for(std::list<std::pair<int, std::list<int> > >::iterator it=classes.begin();it!=classes.end();++it)
	  {
	    //	       std::cout<<"1type:"<<hasMerg<<std::endl;
	       std::list<std::pair<int, std::list<int> > >::iterator beg;
	       if(hasMerg)
		    beg=classes.begin();
	       else
		    beg=it;
	       std::list<std::pair<int, std::list<int> > >::iterator last=beg;
	       
	       for(std::list<std::pair<int, std::list<int> > >::iterator sit=beg;sit!=classes.end();++sit)
	       {
		    if(it->first==sit->first)
			 continue;
		    else
		    {
			 double dist=AttDist(it->first,sit->first);
			 //	 std::cout<<it->first<<" dist "<<sit->first<<" "<<dist<<std::endl;
			 if(dist<dy_low)
			 {
			      std::pair<int, std::list<int> > newclass=MergeClass(*it,*sit);
			      *it=newclass;
			      hasMerg=true;
			      classes.erase(sit);
			      sit=last;
			      continue;
			 }else
			 {
			      if(min>dist)
			      {
				   min=dist;
				   tit1=it;
				   tit2=sit;
			      }
			 }
			      
		    }
		    last=sit;
	       }
	  }
	  //std::cout<<"size:"<<classes.size()<<" min"<<min<<std::endl;
	  if(classes.size()<=1)
	       break;
	  if(!hasMerg)
	  {
	    if(min>dy_high)
	      break;
	    
	    std::pair<int, std::list<int> > newclass=MergeClass(*tit1,*tit2);
	    *tit1=newclass;
	    classes.erase(tit2);
	  }
     }
}
std::pair<int, std::list<int> > LayerCluster::MergeClass(const std::pair<int, std::list<int> > &class1,const std::pair<int, std::list<int> > &class2)
{
     int ret=0;
     int min=INT_MAX;
     std::list<int> tmp;
     
     for(std::list<int>::const_iterator it=class1.second.begin();it!=class1.second.end();++it)
	  tmp.push_back(*it);
     for(std::list<int>::const_iterator it=class2.second.begin();it!=class2.second.end();++it)
	  tmp.push_back(*it);
     int cen=CacuCenter(tmp);
     
     return std::make_pair(cen,tmp);
}
int LayerCluster::CacuCenter(std::list<int> &indexs)
{
     int ret=0;
     double min=INT_MAX;
     for(std::list<int>::iterator it=indexs.begin();it!=indexs.end();++it)
     {
	  double cur=CacuTDist(indexs,*it);
	  if(min>cur)
	  {
	       min=cur;
	       ret=*it;
	  }
     }
     return ret;
}
bool LayerCluster::ChangeCenter(std::string dest)
{
  for(std::list<std::pair<int, std::list<int> > >::iterator it=classes.begin();it!=classes.end();++it)
    {
     double min=INT_MAX;
     int tarCen=-1;
     for(std::list<int>::iterator jit=it->second.begin();jit!=it->second.end();++jit)
     {
       double cur=double(ld.LD(dest,*(vatts[*jit].begin())));
       if(min>cur)
	 {
	   min=cur;
	   tarCen=*jit;
	 }
     }
     if(tarCen>0)
       it->first=tarCen;
    }
  return true;
}
double LayerCluster::CacuTDist(std::list<int> &indexs,int index)
{
     double ret=0;
     for(std::list<int>::iterator it=indexs.begin();it!=indexs.end();++it)
     {
	  ret+=AttDist(index,*it);
     }
     return ret;
}
double LayerCluster::AttDist(int i,int j)
{
     int combine=i*10000+j;
     std::map<int,double>::iterator it=distMap.find(combine);
     if(it!=distMap.end())
     {
	       return it->second;
     }
     else
     {
	  double ret=0;
	  for(std::list<std::string>::iterator it=vatts[i].begin(),jit=vatts[j].begin()
		   ;it!=vatts[i].end();++it,++jit)
	  {
	    //	    std::cout<<"1:"<<*it<<"\n";
	    //	    std::cout<<"2:"<<*jit<<"\n";
	       ret+=double(ld.LD(*it,*jit));
	  }
	  distMap.insert(std::make_pair(combine,ret));
	  return ret;
     }
}

void LayerCluster::printClass()
{
     std::for_each(classes.begin(),classes.end(),std::bind1st(ClassPrt(),vatts));
}
void LayerCluster::printAtts()
{
     std::for_each(vatts.begin(),vatts.end(),AttPrt());
     
}

