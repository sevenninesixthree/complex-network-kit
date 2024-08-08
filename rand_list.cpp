#include <cstddef>
#include "rand_list.h"
#define GRAPH_ERROR 1
#define GRAPH_SUCCESS 0
#define pre template <class DATA>
#define rl rand_list<DATA>

pre bool rl::expend(){
  if(list==NULL)return GRAPH_ERROR;
  DATA* temp;temp=new DATA[(N+1)*2];
  memcpy(temp,list,sizeof(DATA)*length);
  delete[] list;N=(N+1)*2-1;list=temp;
  return GRAPH_SUCCESS;
}
pre bool rl::expend(int nAdd){
  if(list==NULL)return GRAPH_ERROR;
  DATA *temp;temp=new DATA[N+1+nAdd];
  memcpy(temp,list,sizeof(DATA)*length);
  delete[] list;N+=nAdd;list=temp;
  return GRAPH_SUCCESS;
}
pre void rl::pureAdd(DATA value){
  list[length++]=value;return;
}
pre rl::rand_list(int n){
  length=0;list=new DATA[n];N=n-1;
}
pre rl::rand_list(){
  length=0;list=NULL;N=0;
}
pre rl::~rand_list(){
  delete[] list;
}
pre rl& rl::operator=(const rand_list &_in){
  if(&_in==this)return *this;
  if(_in.list==NULL){length=0;list=NULL;N=0;return *this;}
  length=_in.length;N=_in.N;list=new DATA[N+1];
  memcpy(list,_in.list,sizeof(DATA)*(N+1));
  return *this;
}
pre bool rl::add(DATA value){
  if(length>N&&expend()==GRAPH_ERROR)
    return GRAPH_ERROR;
  pureAdd(value);return GRAPH_SUCCESS;
}
pre bool rl::add(DATA value,int delta){
  if(length>N&&expend(delta)==GRAPH_ERROR)
    return GRAPH_ERROR;
  pureAdd(value);return GRAPH_SUCCESS;
}
pre bool rl::del(unsigned long long int seed){
  if(length<=0)return GRAPH_ERROR;
  int temp=length;
  list[seed%temp]=list[--length];
  return GRAPH_SUCCESS;
}
pre DATA rl::select(unsigned long long int seed){
  return list[seed%length];
}
pre rl::operator int(){
  return length;
}
pre void rl::clear(){
  length=0;
}
