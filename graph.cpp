#include "graph.h"
#include <cstddef>
#include<cstring>
#include<ctime>
#include<cmath>
#define GRAPH_ERROR 1
#define GRAPH_SUCCESS 0
using namespace std;

graph::graph(){
  v=NULL;n=0;en=0;dm=NULL;nm=0;
  blank=new int;*blank=0;
}

graph::graph(int n0,int m0){
  v=new int*[n0];n=0;en=0;nm=n0;
  dm=new int[n0];blank=new int;*blank=0;
  for(int i=0;i<n0;i++){
    v[i]=new int[m0+1];
    v[i][0]=0;
    dm[i]=m0;
  }
}

graph::graph(int n0,int* k){
  v=new int*[n0];n=0;en=0;nm=n0;
  dm=new int[n0];blank=new int;*blank=0;
  memcpy(dm,k,sizeof(int)*n0);
  for(int i=0;i<n0;i++){
    v[i]=new int[dm[i]+1];
    v[i][0]=0;
  }
}

graph::graph(const graph&_in){
  int d;n=_in.n;en=_in.en;nm=_in.nm;
  blank=new int;*blank=0;
  dm=new int[nm];memcpy(dm,_in.dm,sizeof(int)*nm);
  v=new int*[nm];for(int i=0;i<nm;i++){
    v[i]=new int[dm[i]+1];
    memcpy(v[i],_in.v[i],sizeof(int)*(dm[i]+1));
  }
}

graph& graph::operator=(const graph &_in){
  if(&_in==this)return *this;
  for(int i=0;i<n;i++)delete v[i];
  delete v;delete dm;
  if(_in.v==NULL){
    v=NULL;n=0;en=0;dm=NULL;nm=0;
    return *this;
  }
  int d;n=_in.n;en=_in.en;nm=_in.nm;
  blank=new int;*blank=0;
  dm=new int[nm];memcpy(dm,_in.dm,sizeof(int)*nm);
  v=new int*[nm];for(int i=0;i<nm;i++){
    v[i]=new int[dm[i]+1];
    memcpy(v[i],_in.v[i],sizeof(int)*(dm[i]+1));
  }return *this;
}

bool graph::link(int from,int to){
  if(from>nm||to>nm)return 0;
  n=n>from?n:from;n=n>to?n:to;
  if(v[from][0]>=dm[from]){
    int* temp;
    temp=new int[(dm[from]<<1)+1];
    memcpy(temp,v[from],sizeof(int)*(dm[from]+1));
    delete v[from];v[from]=temp;
    dm[from]<<=1;
  }v[from][++v[from][0]]=to;en+=1;
  return 1;
}

bool graph::link(int from,int to,int add){
  if(from>nm||to>nm)return 0;
  n=n>from?n:from;n=n>to?n:to;
  if(v[from][0]>=dm[from]){
    int* temp;
    temp=new int[(dm[from]+add)+1];
    memcpy(temp,v[from],sizeof(int)*(dm[from]+1));
    delete v[from];v[from]=temp;
    dm[from]+=add;
  }v[from][++v[from][0]]=to;en+=1;
  return 1;
}

int graph::del(int point){
  if(v[point][0]==1)return -1;
  int ans=v[point][v[point][0]];
  v[point][0]-=1;en-=1;return ans;
}

bool graph::del(int point,int link_to){
  if(v[point][0]==0)return 0;
  for(int i=1;i<=v[point][0];i++)
    if(v[point][i]==link_to){
      v[point][i]=v[point][v[point][0]--];
      return 1;
    }return 0;
}

bool graph::check_linked(int point,int link_to){
  bool ans=0;
  for(int i=1;i<=v[point][0];i++)
    if(v[point][i]==link_to)return 1;
  return 0;
}

int* graph::get_neighbour(int point){
  if(point<=n)return v[point];
  return blank;
}

double graph::get_k_mean(){
  return (double)en/(double)nm;
}

int graph::get_k_max(){
  int ans=0;
  for(int i=0;i<=n;i++)
    if(ans<v[i][0])ans=v[i][0];
  return ans;
}

int graph::get_k_total(){
  return en;
}

ostream &operator<<(ostream &_out,graph &picture){
  _out<<picture.n;
  int** v=picture.v;
  for(int i=0;i<=picture.n;i++){
    _out<<' '<<v[i][0];
    for(int j=1;j<=v[i][0];j++)_out<<' '<<v[i][j];
  }
  return _out;
}

istream &operator>>(istream &_in,graph &picture){
  picture=graph();
  int n,temp;_in>>n;
  picture.n=n;picture.nm=n+1;
  picture.v=new int*[n+1];
    picture.dm=new int[n+1];
  for(int i=0;i<=n;i++){
    _in>>temp;picture.v[i]=new int[temp+1];
    picture.dm[i]=temp;picture.v[i][0]=temp;
    for(int j=1;j<=temp;j++)_in>>picture.v[i][j];
    picture.en+=temp;
  }
  return _in;
}

graph::operator bool(){
  if(v==NULL)return 0;
  return 1;
}

graph::operator int(){
  return nm;
}

graph::~graph(){
  if(nm==0)return;
  delete dm;dm=NULL;
  delete blank;blank=NULL;
  for(int i=0;i<nm;i++){
    delete v[i];v[i]=NULL;
  }delete v;v=NULL;
}
