#include "tools.h"
#include <cstdio>
#include <string>

#define BUF 8
char buffer[BUF];

double getCpu(){
  FILE* info;char cmd[]=
    "top -b -n2 -d0"
    "|grep %Cpu"
    "|tr -dc '0-9.\n '"
    "|awk '{print $1}'";
  info=popen(cmd, "r");
  fgets(buffer, BUF, info);
  fgets(buffer, BUF, info);
  return std::stod(buffer);
}
int getCpuNum(){
  FILE* info;char cmd[]=
    "lscpu|grep CPU"
    "|head -2|tail -1"
    "|awk '{print $2}'";
  info=popen(cmd, "r");
  fgets(buffer, BUF, info);
  return std::stoi(buffer);
}

state_arry::state_arry(int stateNum,int n){
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
}
