#ifndef WORK_HPP
#define WORK_HPP

#include <fstream>
#include <vector>
#include "stl.hpp"
#include "braid.hpp"
#include "permutation.hpp"
#include "signature.hpp"

void insert(SetBraid& s,const Braid& b);
void insert(VectorBraid& s,const Braid& b);

size_t work(const Signature& s);
template<class T> void load(const Signature& s,T& dst,Invariant* inv=nullptr);
template<class T> void load(const Signature& s,T& dst,bool phi,bool negate,Invariant* inv);
void output(const Signature& s,const SetBraid& braids);
size_t approx_number(const  Signature& s);
void invariants(const Signature& s_out,set<Invariant>& invs);
size_t work_split(const Signature& s);


inline void insert(SetBraid& s,const Braid& b){
  s.insert(b);
}

inline void insert(VectorBraid& v,const Braid& b){
  v.push_back(b);
}

template<class T> inline void
load(const Signature& s,T& dst,Invariant* inv){
  if(s.get_l()>0){
    bool phi;
    Signature rs=(phi=s.is_phi_reducible())?s.phi():s;
    if(rs.is_negative()) load(rs.negate(),dst,phi,true,inv);
    else load(rs,dst,phi,false,inv);
  }
  else{
    Braid b;
    insert(dst,b);
  }
}

template<class T> inline void
load(const Signature& s,T& dst,bool phi,bool negate,Invariant* inv){
  string filename=s.filename();
  fstream file;
  file.open(DATA_DIR+filename.c_str(),ios::in);
  char l=s.get_l();
  if(file.is_open()){
    size_t bsize=(l-1)/3+1;
    char buffer[bsize];
    while(true){
      file.read(buffer,bsize);
      if(file.gcount()==0) break;
      Braid b(buffer,l);
      if(negate) b.negate();
      if(phi) b.phi();
      if(inv==nullptr) insert(dst,b);
      else{
	if(b.invariant()==*inv){
	  insert(dst,b);
	}
      }
    }
  }
}
#endif
