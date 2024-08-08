#include "genGraph.h"
#include "rand_list.h"
#include <cstring>
#include <random>
using namespace std;
graph gen_ER(int N,double p,int seed){
  if(N<=1)return graph();
  graph ans(N,(double)N*p);
  mt19937 eng(seed);
  uniform_real_distribution<> gen(0,1);
  for(int i=0;i<N;i++)
    for(int j=0;j<N;j++)
      if(gen(eng)<=p){
        ans.link(i,j);
        ans.link(j,i);
      }
  return ans;
}
graph gen_ER(int N,int M,int seed){
  if(N<=1)return graph();
  graph ans;
  ans=graph(N,M/N+1);
  mt19937 eng(seed);
  for(int i=1;i<=M;i++){
    int p=eng()%N,q=eng()%N;
    while(p==q||ans.check_linked(p,q))
      p=eng()%N,q=eng()%N;
    ans.link(p,q);ans.link(q,p);
  }
  return ans;
}
graph gen_BA(int N,int n0,int q,int seed){
  graph ans(N,q);
  mt19937 eng(seed);
  int* line;line=new int[N*q*2+N];
  int* refresh;refresh=new int[q];
  bool* flag;flag=new bool[N];
  memset(flag,0,sizeof(bool)*N);
  line[0]=0;
  for(int i=1;i<n0;i++){
    ans.link(i,i-1);ans.link(i-1,i);
    line[++line[0]]=i;line[++line[0]]=i-1;
  }
  for(int i=n0;i<N;i++){
    for(int j=0;j<q;j++){
      int check;
      do{
        check=eng()%line[0]+1;
      }while(flag[line[check]]);
      flag[line[check]]=1;line[line[0]+j]=line[check];
      line[line[0]+q+j]=i;refresh[j]=line[check];
      ans.link(i,line[check]);ans.link(line[check],i);
    }
    for(int j=0;j<q;j++)flag[refresh[j]]=0;
    line[0]+=q*2;
  }
  return ans;
}
graph gen_ALL(int N){
  graph ans(N,N);
  for(int i=0;i<N;i++)
    for(int j=i+1;j<N;j++)
    {ans.link(i,j);ans.link(j,i);}
  return ans;
}
graph gen_latic(int w,int l){
  graph ans(w*l,4);
  int x[]={0,1,0,-1};
  int y[]={1,0,-1,0};
  for(int i=0;i<w;i++)
    for(int j=0;j<l;j++)
      for(int k=0;k<4;k++)
        if(0<=i+x[k]&&i+x[k]<w)
          if(0<=j+y[k]&&j+y[k]<l)
            ans.link(i+j*w,i+x[k]+(j+y[k])*w);
  return ans;
}
graph gen_UCM(int N,int m0,double gamma,int seed){
  if(gamma>0)gamma=-gamma;
  if(m0<2)m0=2;
  double *pk;pk=new double[(int)sqrt(N)+2];
  for(int i=m0;i*i<=N;i++){
    pk[i]=pow(i,gamma);pk[0]+=pk[i];
  }
  int* d;d=new int[N];
  double check;
  uniform_real_distribution<> gen(0,pk[0]);
  mt19937_64 eng(seed);
  int at,all=0,m=0;
  for(int i=0;i<N;i++){
    check=gen(eng);
    at=m0-1;while(check>0)check-=pk[++at];
    d[i]=at;all+=at;m=at>m?at:m;
  }
  if(all&1){d[0]+=1;all+=1;m=d[0]>m?d[0]:m;}
  graph ans(N,d);
  int* line;line=new int[all+1];line[0]=0;
  for(int i=0;i<N;i++)
    for(int j=1;j<=d[i];j++)
      line[++line[0]]=i;
  bool* flag;flag=new bool[N];
  memset(flag,0,sizeof(bool)*N);
  gen=uniform_real_distribution<>(0,1);
  while(all){
    int i=eng()%all+1;int p=line[i],q;
    flag[p]=1;int* ni=ans.get_neighbour(p);
    for(int i=1;i<=ni[0];i++)flag[ni[i]]=1;
    int j,k=0;ni=NULL;
    do{
      j=eng()%all+1;k+=1;
    }while(flag[line[j]]&&k<=1000);
    if(k>=1000){
      p=gen(eng)*N;int q=ans.del(p);
      ans.del(q,p);
      line[++all]=p;line[++all]=q;
    }
    q=line[j];
    ans.link(p,q);ans.link(q,p);
    line[i]=line[all--];line[j]=line[all--];
    flag[p]=0;ni=ans.get_neighbour(p);
    for(int i=1;i<=ni[0];i++)flag[ni[i]]=0;
  }
  return ans;
}
graph gen_RR(int N,int k,int seed){
  if(N<=1)return graph();
  if(N*k&1)return graph();
  graph ans(N,k);mt19937 eng(seed);
  rand_list<int> list(N*k);
  for(int i=0;i<N;i++)for(int j=1;j<=k;j++)list.add(i);
  int p,q,i=0;unsigned tp,tq;
  while(list){
    i=0;
    do{
      i++;if(i>=1000)break;
      tp=eng();p=list.select(tp);
      tq=eng();q=list.select(tq);
    }while(p==q||ans.check_linked(p,q));
    if(i>=1000)return graph();
    list.del(tp);list.del(tq);
    ans.link(p,q);ans.link(q,p);
  }
  return ans;
}
