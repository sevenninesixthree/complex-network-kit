#ifndef GEN_GRAPH
#define GEN_GRAPH
#include "graph.h"
graph gen_ER(int N,double p,int seed);
graph gen_ER(int N,int M,int seed);
graph gen_BA(int N,int n0,int q,int seed);
graph gen_ALL(int N);
graph gen_latic(int w,int l);
graph gen_UCM(int N,int m0,double gamma,int seed);
graph gen_RR(int N,int k,int seed);
#endif
