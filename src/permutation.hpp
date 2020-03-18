#ifndef PERMUTATION_HPP
#define PERMUTATION_HPP

#include <iostream>
#include <cassert>
#include "config.hpp"

using namespace std;

class Permutation{
protected:
  int data[STRANDS+1];
public:
  int read_int(string s,size_t& offset);
  Permutation();
  Permutation(string s);
  Permutation(const Permutation& P);
  int operator()(int i) const;
  Permutation operator*(int i) const;
};

string to_string(const Permutation& P);
ostream& operator<<(ostream& os,const Permutation& P);

inline
Permutation::Permutation(){
}

inline
Permutation::Permutation(const Permutation& P){
  for(int i=1;i<=STRANDS;++i){
    data[i]=P.data[i];
  }
}

inline int
Permutation::operator()(int i) const{
  assert(1<=i and i<=STRANDS);
  return data[i];
}
#endif
