#include "config.hpp"
#include "init.hpp"
#include "work.hpp"
#include "signature.hpp"
#include <omp.h>
#include <unordered_set>
using namespace std;

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
						
  next_signatures(prec,cur);
  for(char l=2;l<=10;++l){
    cur.clear();
    cout<<"------------------------"<<endl;
    cout<<"Length : "<<(int)l<<endl;
    next_signatures(prec,cur);
    fstream file;
    file.open(DATA_DIR+to_string((int)l)+".csv",ios::out);
    size_t n=0;
    for(auto it=cur.begin();it!=cur.end();++it){
      size_t ns=work(*it);
      int rank=it->rank();
      if(ns!=0) file<<it->csv()<<","<<rank<<","<<ns<<endl;
      n+=(rank*ns);
    }
    cout<<"-> "<<n<<" braids."<<endl;
    swap(cur,prec);
  }
}

int main(int argc,char** argv){
  run<GEN>();
}
