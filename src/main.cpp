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
  pair<size_t,size_t> res=work(s);
  size_t ns=res.first;
  size_t ng=res.second;
  int rank=s.rank();
  //  if(ns!=0) file<<s.csv()<<","<<rank<<","<<ns<<","<<ng<<endl;
  cilk_result.n_sph(l)+=(rank*ns);
  cilk_result.n_geo(l)+=(rank*ng);
}

template<Gen G> void run(){
  if(G==Artin){
    cout<<"***************************"<<endl;
    cout<<"* Gbraids - Artin - Alone *"<<endl;
    cout<<"***************************"<<endl;
  }
  else{
    cout<<"**************************"<<endl;
    cout<<"* Gbraids - Dual - Alone *"<<endl;
    cout<<"**************************"<<endl;
  }
  cout<<"-> Init ";
  init<G>();
  cout<<"... done."<<endl;
  set<Signature<G>> prec,cur;
  load(1,prec);
  cout<<" Workers number is "<<__cilkrts_get_nworkers()<<endl;					
  next_signatures(prec,cur);
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
    }
    cilk_sync;
    cout<<"-> "<<cilk_result.n_sph(l)<<" braids."<<endl;
    cout<<"-> "<<cilk_result.n_geo(l)<<" geodesic words."<<endl;
    swap(cur,prec);
  }
}

int main(int argc,char** argv){
  run<GEN>();
}
