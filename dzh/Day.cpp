#include <iostream>
#include <fstream>
#include <string.h>
#pragma pack(1)

using namespace std;
struct GLOBAL_DATA { 
    int dayflag; 
    int reserve1; 
    int reserve2; 
    int stocksum; 
    int startblock; 
    int lastblock;
};
struct INDEX_DATA{ 
    char code[10]; 
    int dayrecordnum; 
    unsigned short int record[25];
};
struct DAY_DATA
{
    int date; 
    float open; 
    float high; 
    float low; 
    float close; 
    float amount; 
    float money; 
    unsigned short int rise; 
    unsigned short int fall; 
};

int main () {
  int length;
  GLOBAL_DATA *h;
  INDEX_DATA *s;
  ifstream is;
  is.open ("DAY.DAT", ios::binary );

  // get length of file:
  is.seekg (0, ios::end);
  length = is.tellg();
  is.seekg (0, ios::beg);
  std::cout<<length<<std::endl;
  // allocate memory:
  h = new GLOBAL_DATA();
  s =new INDEX_DATA();
  // read data as a block:
  is.read ((char*)h,sizeof(GLOBAL_DATA));
  is.seekg (sizeof(INDEX_DATA)*400, ios::cur);
  is.read ((char*)s,sizeof(INDEX_DATA));

  std::cout<<"flag:"<<h->dayflag<<std::endl;
  std::cout<<"count:"<<h->stocksum<<std::endl;
  std::cout<<"startblock:"<<h->startblock<<std::endl;
  std::cout<<"lastblock:"<<h->lastblock<<std::endl;

  std::cout<<"code:"<<s->code<<std::endl;
  std::cout<<"uval:"<<s->dayrecordnum<<std::endl;
  char *data=new char[8192*25];
  for(int i=0;i<25;i++)
  {
      char tmp[8192];
      std::cout<<"record"<<i<<":"<<s->record[i]<<std::endl;
      if(s->record[i]<h->startblock)
      {
          is.seekg (0x41000+8192*s->record[i], ios::beg);
          is.read (tmp,8192);
          memcpy(data+8192*i,tmp,8192);
      }
  }
  
  is.close();
  int index=0;
  while(index<256*25)
  {
      DAY_DATA day;
      memcpy(&day,data+index*32,32);
      index++;
      if(day.date==0)
          break;
      std::cout<<"date:"<<day.date<<std::endl;
      std::cout<<"open:"<<day.open<<std::endl;
      std::cout<<"high:"<<day.high<<std::endl;
      std::cout<<"low:"<<day.low<<std::endl;
      std::cout<<"close:"<<day.close<<std::endl;
      std::cout<<"amount:"<<day.amount<<std::endl;
      std::cout<<"money:"<<day.money<<std::endl;
      std::cout<<"rise:"<<day.rise<<std::endl;
      std::cout<<"fall:"<<day.fall<<std::endl;
  }
  
  delete [] data;
  delete h;
  return 0;
}
