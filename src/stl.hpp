#ifndef STL_HPP
#define STL_HPP

#include <set>
#include <vector>
#include "braid.hpp"

using namespace std;

using SetBraid=set<Braid>;
using VectorBraid=vector<Braid>;

template<class T> ostream& operator<<(ostream& os,const set<T>& s);

template<class T> ostream&
operator<<(ostream& os,const set<T>& s){
  if(s.empty()) return os<<"{}";
  auto it=s.begin();
  os<<'{'<<*it;
  for(++it;it!=s.end();++it){
    os<<','<<*it;
  }
  return os<<'}';
}



#endif
