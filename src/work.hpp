#ifndef WORK_HPP
#define WORK_HPP

#include <fstream>
#include <vector>
#include "stl.hpp"
#include "braid.hpp"
#include "permutation.hpp"
#include "signature.hpp"


size_t work(const Signature<Artin>& s);
template<class T> void load(const Signature<Artin>& s,T& dst);
template<class T> void load(const Signature<Artin>& s,T& dst,Signature<Artin>::Action& action);
void output(const Signature<Artin>& s,const set<Braid>& braids);

template<class T> void
load(const Signature<Artin>& s,T& dst){
  //cout<<"Load "<<s<<endl;
  if(not s.has_length_zero()){
    pair<Signature<Artin>,Signature<Artin>::Action> res=s.minimize();
    load(res.first,dst,res.second);
  }
  else{
    Braid b;
    insert(dst,b);
  }
}

template<class T> void
load(const Signature<Artin>& s,T& dst,Signature<Artin>::Action& action){
  //cout<<" SubLoad "<<s<<endl;
  string filename=s.filename();
  fstream file;
  file.open(DATA_DIR+filename.c_str(),ios::in);
  if(file.is_open()){
    size_t bsize=s.compressed_braid_size();
    char l=s.braid_length();
    char buffer[bsize];
    while(true){
      file.read(buffer,bsize);
      if(file.gcount()==0) break;
      Braid b(buffer,l);
      if(action.apply_negation) b.negate();
      if(action.apply_phi) b.phi();
      insert(dst,b);
    }
  }
}
#endif
