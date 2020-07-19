#include <unordered_set>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "config.hpp"
#include "init.hpp"
#include "work.hpp"
#include "signature.hpp"
#include "results.hpp"

using namespace std;

ResultsReducer cilk_result;

template<Gen G> void treat(int l,const Signature<G>& s){
  size_t n=work(s);
  int rank=s.rank();
  //  if(ns!=0) file<<s.csv()<<","<<rank<<","<<ns<<","<<ng<<endl;
  cilk_result.n(l)+=(rank*n);
}

template<Gen G> void run(){
  if(G==Artin){
    cout<<"*******************"<<endl;
    cout<<"* Gbraids - Artin *"<<endl;
    cout<<"*******************"<<endl;
  }
  else{
    cout<<"******************"<<endl;
    cout<<"* Gbraids - dual *"<<endl;
    cout<<"******************"<<endl;
  }
  cout<<"Number of strands : "<<STRANDS<<endl;
  cout<<"Combinatorics type : ";
#ifdef SPHERICAL
  cout<<"spherical";
#else
  cout<<"geodesic";
#endif
  cout<<"."<<endl;
  cout<<"-> Init ";
  init<G,STRANDS>();
  cout<<"... done."<<endl;
  set<Signature<G>> prec,cur;
  load(1,prec);
  cout<<" Workers number is "<<__cilkrts_get_nworkers()<<endl;					
  next_signatures(prec,cur);
  //cout<<"prec = "<<prec<<endl;
  //cout<<" cur = "<<cur<<endl;
  for(char l=2;l<=20;++l){
    cur.clear();
    cout<<"------------------------"<<endl;
    cout<<"Length : "<<(int)l<<endl;
    next_signatures(prec,cur);
    fstream file;
    file.open(DATA_DIR+to_string((int)l)+".csv",ios::out);
    size_t n_sph=0;
    size_t n_geo=0;
    for(auto it=cur.begin();it!=cur.end();++it){
      cilk_spawn treat(l,*it);
      //treat(l,*it);
    }
    cilk_sync;
    cout<<"-> "<<cilk_result.n(l)<<endl;
    swap(cur,prec);
  }
}

int main(int argc,char** argv){
  run<GEN>();
}
