#include "tools.h"
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

#define BUF 256
char buffer[BUF];
char name[8];

enum CpuColumn{ALL,IDLE};

int getCpuTime(double* reg){
  int fd=open("/proc/stat", O_RDONLY);
  if(fd==-1)return fd;read(fd, buffer, BUF);
  double indate[4];sscanf(buffer, "%s%lf%lf%lf%lf",name,indate,indate+1,indate+2,indate+3);
  double all=0,idle=indate[3];
  for(double i:indate)all+=i;
  reg[ALL]=all;reg[IDLE]=idle;
  close(fd);
  return 0;
}
double getCpu(){
  double o[2],n[2],all,idle;
  getCpuTime(o);sleep(1);getCpuTime(n);
  idle=n[IDLE]-o[IDLE];all=n[ALL]-o[ALL];
  return (all-idle)/all*100.0;
}
int getCpuNum(){
  return sysconf(_SC_NPROCESSORS_ONLN);
}

/*state_arry::state_arry(int stateNum,int n){
  stateNum--;if(stateNum<0)stateNum=-stateNum;cell={0,0};
  int p=0;while(stateNum){p++;stateNum>>=1;}
  int q=1;while(q<p){q<<=1;cell.shift++;}
  for(int i=1;i<=q;i++)cell.mask+=cell.mask+1;
  p=sizeof(unsigned int)*4/q;self={0,0};
  while(p){p>>=1;self.shift++;self.mask+=self.mask+1;}
  length=(n>>self.shift)+1;storage=new unsigned int[length];
}

state_arry::~state_arry(){delete storage;}

void state_arry::write(int agent,int state){
  pointer=agent>>self.shift;
  data.shift=(agent&self.mask)<<cell.shift;
  data.mask=cell.mask<<data.shift;
  state<<=data.shift;
  storage[pointer]&=~data.mask;
  storage[pointer]+=state;
}

int state_arry::read(int agent){
  pointer=agent>>self.shift;
  data.shift=(agent&self.mask)<<cell.shift;
  data.mask=cell.mask<<data.shift;
  return (storage[pointer]&data.mask)>>data.shift;
}*/
