#ifndef GRAPH
#define GRAPH

#include <iostream>

class graph
{
private:
  int **v,n,en,*dm,nm,*blank;
public:
  graph();
  graph(int n0,int m0);
  graph(int n0,int* k);
  graph(const graph&_in);
  graph& operator=(const graph &_in);
  bool link(int from,int to);
  bool link(int from,int to,int add);
  int del(int point);
  bool del(int point,int link_to);
  bool check_linked(int point,int link_to);
  //用完后不要释放空间，一定要置`NULL`
  int* get_neighbour(int point);
  double get_k_mean();
  int get_k_max();
  int get_k_total();
  friend std::ostream &operator<<(std::ostream &_out,graph &picture);
  friend std::istream &operator>>(std::istream &_in,graph &picture);
  operator bool();
  operator int();
  ~graph();
};

#endif
