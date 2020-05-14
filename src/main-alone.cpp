#include "config.hpp"
#include "init.hpp"
#include "work.hpp"
#include "signature.hpp"
#include <boost/align/aligned_allocator.hpp>
#include <omp.h>
using namespace std;

int main(int argc,char** argv){
  cout<<"*******************"<<endl;
  cout<<"* Gbraids - Alone *"<<endl;
  cout<<"*******************"<<endl;
  cout<<"-> Init ";
  init();
  cout<<"... done."<<endl;
  size_t total=7;
  set<Signature> prec,cur;
  load(1,prec);
  for(char l=2;l<=12;++l){
    cur.clear();
    cout<<"------------------------"<<endl;
    cout<<"Length : "<<(int)l<<endl;
     next_signatures(prec,cur);
    fstream file;
    file.open(DATA_DIR+to_string((int)l)+".csv",ios::out);
    size_t n=0;
    for(auto it=cur.begin();it!=cur.end();++it){
      size_t ns=work(*it);
      int rank=it->get_rank();
      if(ns!=0) file<<it->csv()<<","<<rank<<","<<ns<<endl;
      n+=(rank*ns);
    }
    cout<<"-> "<<n<<" braids."<<endl;
    swap(cur,prec);
    total+=n;
  }
  cout<<endl<<"==> Total number of braids: "<<total<<endl;
}
