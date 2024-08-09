#ifndef RAND_LIST
#define RAND_LIST

#include <cstddef>
#include <cstring>
template<class DATA>
class rand_list{
private:
  DATA *list;int length,N;
  bool expend(){
    if(list==NULL)return 1;
    DATA* temp;temp=new DATA[(N+1)*2];
    memcpy(temp,list,sizeof(DATA)*length);
    delete[] list;N=(N+1)*2-1;list=temp;
    return 0;
  }
  bool expend(int nAdd){
    if(list==NULL)return 1;
    DATA *temp;temp=new DATA[N+1+nAdd];
    memcpy(temp,list,sizeof(DATA)*length);
    delete[] list;N+=nAdd;list=temp;
    return 0;
  }
  void pureAdd(DATA value){
    list[length++]=value;return;
  }
public:
  rand_list(int n){
    length=0;list=new DATA[n];N=n-1;
  }
  rand_list(){
    length=0;list=NULL;N=0;
  }
  ~rand_list(){
    delete[] list;
  }
  rand_list& operator=(const rand_list &_in){
    if(&_in==this)return *this;
    if(_in.list==NULL){length=0;list=NULL;N=0;return *this;}
    length=_in.length;N=_in.N;list=new DATA[N+1];
    memcpy(list,_in.list,sizeof(DATA)*(N+1));
    return *this;
  }
  bool add(DATA value){
    if(length>N&&expend()==1)
      return 1;
    pureAdd(value);return 0;
  }
  bool add(DATA value,int delta){
    if(length>N&&expend(delta)==1)
      return 1;
    pureAdd(value);return 0;
  }
  bool del(unsigned long long int seed){
    if(length<=0)return 1;
    int temp=length;
    list[seed%temp]=list[--length];
    return 0;
  }
  DATA select(unsigned long long int seed){
    return list[seed%length];
  }
  operator int(){
    return length;
  }
  void clear(){
    length=0;
  }
};

#endif
