#ifndef GEN_GRAPH
#define GEN_GRAPH

#include "graph.h"

int gen_ER(int N,double p,int seed,graph *ans);
int gen_ER(int N,int M,int seed,graph *ans);
int gen_BA(int N,int n0,int q,int seed,graph *ans);
int gen_ALL(int N,graph *ans);
int gen_latic(int w,int l,graph *ans);
int gen_UCM(int N,int m0,double gamma,int seed,graph *ans);
int gen_RR(int N,int k,int seed,graph *ans);

#endif
