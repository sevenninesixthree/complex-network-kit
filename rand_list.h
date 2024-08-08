#ifndef RAND_LIST
#define RAND_LIST

template<class DATA>
class rand_list{
private:
  DATA *list;int length,N;
  bool expend();
  bool expend(int nAdd);
  void pureAdd(DATA value);
public:
  rand_list(int n);
  rand_list();
  ~rand_list();
  rand_list& operator=(const rand_list &_in);
  bool add(DATA value);
  bool add(DATA value,int delta);
  bool del(unsigned long long int seed);
  DATA select(unsigned long long int seed);
  operator int();
  void clear();
};

#endif
