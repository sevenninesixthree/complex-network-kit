#ifndef TOOLS
#define TOOLS

double getCpu();

class state_arry{
private:
  unsigned int* storage;
  struct bit_tool{
    unsigned int mask;unsigned int shift;
  }cell,self,data;
  unsigned int length,pointer;
public:
  state_arry(int stateNum,int n);
  ~state_arry();
  void write(int agent,int state);
  int read(int agent);
};

#endif
